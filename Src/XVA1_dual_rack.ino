#include <stdint.h>  // Add this at the top if it's not already there
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <ST7789_t3.h>  // Hardware-specific library
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "SynthParameter.h"
#include "Button.h"
#include "Hardware.h"
#include <MIDI.h>
#include <RoxMux.h>
#include "global.h"
#include "Performance.h"
#include "Synthesizer.h"
#include <EEPROM.h>
#include <Encoder.h>

unsigned long saveButtonPressTime = 0;
bool savePerformanceHeldHandled = false;
bool savingPerformanceMode = false;

enum MenuOption {
  MENU_MIDI_CHANNEL,
  MENU_SPLIT_TRANSPOSE,
  MENU_OPTION_COUNT
};

const char *menuLabels[MENU_OPTION_COUNT] = {
  "MIDI Channel",
  "Split Transpose"
};

int midiChannel = 1;        // 1–16
int secondmidiChannel = 2;  // 1–16


enum MenuState {
  INACTIVE,
  SELECTING,
  EDITING
};

MenuState menuState = INACTIVE;
int currentMenuIndex = 0;

/* function prototypes */

void handleMainEncoder(bool clockwise, int speed);

void initOLEDDisplays();

void pollAllMCPs();

void displayPatchInfo();

void displayPatchInfo(bool paintItBlack);

void initButtons();

void clearShortcut();

void clearMainScreen();

void initMainScreen();

void initRotaryEncoders();

void rtrim(std::string &s, char c);

void readMainRotaryButton();

void readMainRotaryEncoder();

int getEncoderSpeed(int id);

#define SRP_TOTAL 1
Rox74HC595<SRP_TOTAL> srpanel;

// pins for 74HC595
#define LED_DATA 28   // pin 14 on 74HC595 (DATA)
#define LED_CLK 29    // pin 11 on 74HC595 (CLK)
#define LED_LATCH 30  // pin 12 on 74HC595 (LATCH)
#define LED_PWM -1    // pin 13 on 74HC595

void setup() {
  Serial.begin(115200);
  // if (!SD.begin(BUILTIN_SDCARD)) {
  //   Serial.println("SD card initialization failed!");
  // } else {
  //   Serial.println("SD card ready.");
  // }

  srpanel.begin(LED_DATA, LED_LATCH, LED_CLK, LED_PWM);

  // pullup i2c pins
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);

  mainEncoder.write(0);  // Resets encoder count to 0 on startup

  //MIDI 5 Pin DIN
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleControlChange(myControlChange);
  MIDI.setHandleProgramChange(myProgramChange);
  MIDI.setHandleAfterTouchChannel(myAfterTouch);
  MIDI.setHandlePitchBend(DinHandlePitchBend);
  MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.turnThruOn(midi::Thru::Mode::Off);

  //USB Client MIDI
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleProgramChange(myProgramChange);
  usbMIDI.setHandleAfterTouchChannel(myAfterTouch);
  usbMIDI.setHandlePitchChange(DinHandlePitchBend);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleNoteOff(myNoteOff);

  MIDI6.begin();
  MIDI6.turnThruOn(midi::Thru::Mode::Off);

  MIDI8.begin();
  MIDI8.turnThruOn(midi::Thru::Mode::Off);

  loadSplitPointFromEEPROM();
  loadGlobalSettings();

  Wire.begin();
  Wire.setClock(100000);  // Slow down I2C to 100kHz

  mcp1.begin(0);
  delay(10);
  mcp2.begin(1);
  delay(10);
  mcp3.begin(2);
  delay(10);
  mcp4.begin(3);
  delay(10);
  mcp5.begin(4);
  delay(10);
  mcp6.begin(5);
  delay(10);

  synthesizer.begin();

  initMainScreen();
  clearMainScreen();

  initRotaryEncoders();
  delay(10);
  initOLEDDisplays();
  initButtons();

  srpanel.writePin(UPPER_LED, HIGH);
  srpanel.writePin(LOWER_LED, LOW);
  srpanel.writePin(PATCH_LED, HIGH);
  srpanel.writePin(PERF_LED, LOW);

  synthesizer.selectPatchU(1);
  synthesizer.selectPatchL(1);
  parameterController.setDefaultSection();
  delay(10);
  parameterController.setDefaultSection();
  displayPatchInfo();
}

void loop() {
  pollAllMCPs();

  readMainRotaryEncoder();
  readMainRotaryButton();
  srpanel.update();  // update all the LEDs in the buttons
  MIDI.read();
  usbMIDI.read();
}

void readMainRotaryEncoder() {
  static int lastDetentPos = 0;
  int rawPos = mainEncoder.read();
  int detentPos = rawPos / 4;

  if (detentPos != lastDetentPos) {
    bool clockwise = (detentPos > lastDetentPos);
    int speed = abs(detentPos - lastDetentPos);

    if (activeShortcut != 0) {
      bool consumed = parameterController.rotaryEncoderChanged(0, clockwise, 1);
      if (!consumed) {
        handleMainEncoder(clockwise, speed);
      }
    } else {
      handleMainEncoder(clockwise, speed);
    }

    lastDetentPos = detentPos;
  }
}

void myProgramChange(uint8_t channel, uint8_t value) {
  int patchNum = value + 1;  // MIDI programs 0–127 → patches 1–128

  // === PERFORMANCE MODE ===
  if (inPerformanceMode) {
    if (channel == midiChannel) {
      if (value >= 0 && value < 128) {
        performanceIndex = value;
        loadPerformance(performanceIndex);
        displayPerformanceInfo();
      }
      return;
    }
  }

  // === PATCH MODE ===
  if (keyboardMode == WHOLE) {
    if (channel == midiChannel) {
      // WHOLE: Load upper, mirror to lower
      currentPatchNumberU = patchNum;
      synthesizer.selectPatchU(currentPatchNumberU);
      suppressLowerDisplay = true;
      synthesizer.setAllParameterL(currentPatchNumberU);
      suppressLowerDisplay = false;
    }
  } else {
    // DUAL or SPLIT
    if (channel == midiChannel) {
      currentPatchNumberU = patchNum;
      synthesizer.selectPatchU(currentPatchNumberU);
    } else if (channel == (secondmidiChannel)) {
      currentPatchNumberL = patchNum;
      synthesizer.selectPatchL(currentPatchNumberL);
    }
  }

  parameterController.setDefaultSection();
  parameterController.clearScreen();
  clearShortcut();
  displayPatchInfo();
}

void myControlChange(uint8_t channel, uint8_t controller, uint8_t value) {
  if (channel == midiChannel) {
    MIDI6.sendControlChange(controller, value, channel);
    MIDI8.sendControlChange(controller, value, channel);
  }
}

void myAfterTouch(uint8_t channel, uint8_t value) {
  if (channel == midiChannel) {
    switch (keyboardMode) {
      case WHOLE:
      case DUAL:
        MIDI6.sendAfterTouch(value, channel);
        MIDI8.sendAfterTouch(value, channel);
        break;

      case SPLIT:
        MIDI6.sendAfterTouch(value, channel);
        MIDI8.sendAfterTouch(value, channel);
        break;
    }
  }
}

void DinHandlePitchBend(uint8_t channel, int pitch) {

  if (channel == midiChannel) {
    switch (keyboardMode) {
      case WHOLE:
      case DUAL:
        MIDI6.sendPitchBend(pitch, channel);
        MIDI8.sendPitchBend(pitch, channel);
        break;

      case SPLIT:
        MIDI6.sendPitchBend(pitch, channel);
        MIDI8.sendPitchBend(pitch, channel);
        break;
    }
  }
}

void myNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (channel != midiChannel) return;

  if (settingSplitPoint) {
    splitPoint = note;
    saveSplitPointToEEPROM(splitPoint);
    settingSplitPoint = false;

    if (inPerformanceMode) {
      currentPerformance.splitPoint = splitPoint;
    }

    // Flash confirmation
    tft.fillRect(0, 0, 320, 26, TFT_GREEN);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextDatum(1);
    tft.drawString("Split Set: " + String(noteName(note)), 153, 6);

    delay(1000);
    showModeLabel();
    return;
  }

  switch (keyboardMode) {
    case WHOLE:
      if (toggle) {
        MIDI6.sendNoteOn(note, velocity, channel);
        noteTarget[note] = 6;
      } else {
        MIDI8.sendNoteOn(note, velocity, channel);
        noteTarget[note] = 8;
      }
      toggle = !toggle;
      break;

    case DUAL:
      MIDI6.sendNoteOn(note, velocity, channel);
      MIDI8.sendNoteOn(note, velocity, channel);
      noteTarget[note] = 0;  // both
      break;

    case SPLIT:
      if (note < splitPoint) {
        int transposed = note + splitTranspose;
        if (transposed < 0) transposed = 0;
        if (transposed > 127) transposed = 127;
        MIDI6.sendNoteOn(transposed, velocity, channel);
        noteTarget[note] = 6;
      } else {
        MIDI8.sendNoteOn(note, velocity, channel);
        noteTarget[note] = 8;
      }
      break;
  }
}

void myNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (channel != midiChannel) return;

  uint8_t target = noteTarget[note];

  switch (keyboardMode) {
    case WHOLE:
      if (target == 6) {
        MIDI6.sendNoteOff(note, velocity, channel);
      } else if (target == 8) {
        MIDI8.sendNoteOff(note, velocity, channel);
      } else {
        MIDI6.sendNoteOff(note, velocity, channel);
        MIDI8.sendNoteOff(note, velocity, channel);
      }
      break;

    case DUAL:
      MIDI6.sendNoteOff(note, velocity, channel);
      MIDI8.sendNoteOff(note, velocity, channel);
      break;

    case SPLIT:
      if (target == 6) {
        int transposed = note + splitTranspose;
        if (transposed < 0) transposed = 0;
        if (transposed > 127) transposed = 127;
        MIDI6.sendNoteOff(transposed, velocity, channel);
      } else if (target == 8) {
        MIDI8.sendNoteOff(note, velocity, channel);
      }
      break;
  }

  noteTarget[note] = 0;  // Clear tracking
}


void rotaryEncoderChanged(bool clockwise, int id) {
  int speed = getEncoderSpeed(id);

  Serial.println("Encoder " + String(id) + ": "
                 + (clockwise ? String("clockwise") : String("counter-clock-wise")) + ", Speed: " + String(speed));

  parameterController.rotaryEncoderChanged(id, clockwise, speed);
}

int getEncoderSpeed(int id) {
  unsigned long now = millis();
  unsigned long revolutionTime = now - lastTransition[id];

  int speed = 1;
  if (revolutionTime < 50) {
    speed = 10;
  } else if (revolutionTime < 125) {
    speed = 5;
  } else if (revolutionTime < 250) {
    speed = 2;
  }

  lastTransition[id] = now;
  return speed;
}

void initRotaryEncoders() {
  for (auto &rotaryEncoder : rotaryEncoders) {
    rotaryEncoder.init();
  }

  //mainRotaryEncoder.begin(true);
}

void initMainScreen() {
  tft.init(240, 320);
  //tft.useFrameBuffer(true);
  tft.setRotation(3);  // 0 & 2 Portrait. 1 & 3 landscape;
}

void initOLEDDisplays() {
  for (int d = 0; d < 8; d++) {
    multiplexer.selectChannel(d);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextWrap(false);
    display.clearDisplay();
    display.display();
  }
}

void initButtons() {
  for (auto &button : allButtons) {
    button->begin();
  }
  Serial.println("Setting encoder button as input");
  pinMode(MAIN_ROTARY_BTN_PIN, INPUT_PULLUP);
}

void displayPerformanceInfo() {
  tft.fillScreen(TFT_BLACK);

  // Header
  tft.fillRect(0, 0, 320, 26, TFT_CYAN);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextDatum(1);
  //tft.drawString("PERF " + String(performanceIndex + 1) + ": " + String(currentPerformance.name), 153, 6);
  String perfName = String(currentPerformance.name);
  if (perfName.length() > 16) perfName = perfName.substring(0, 16);

  String header = "P" + String(performanceIndex + 1) + ": " + perfName;
  tft.drawString(header, 153, 6);  // centered
  tft.setTextDatum(1);             // Reset datum to left for rest of UI

  // Labels
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.drawString("Upper", 60, 40);
  tft.drawString("Patch", 60, 70);

  if (currentPerformance.mode != WHOLE) {
    tft.drawString("Lower", 60, 140);
    tft.drawString("Patch", 60, 170);
  }

  // Divider
  tft.fillRect(0, 128, 320, 2, MY_ORANGE);

  // Numbers
  tft.setTextSize(5);
  tft.setTextColor(TFT_BLACK);
  tft.drawNumber(-1, 180, 50);  // Clear
  tft.setTextColor(MY_ORANGE, TFT_BLACK);
  tft.drawNumber(currentPerformance.upperPatchNo, 180, 50);

  if (currentPerformance.mode != WHOLE) {
    tft.setTextSize(5);
    tft.setTextColor(TFT_BLACK);
    tft.drawNumber(-1, 180, 150);  // Clear
    tft.setTextColor(MY_ORANGE, TFT_BLACK);
    tft.drawNumber(currentPerformance.lowerPatchNo, 180, 150);
  }

  // Upper patch name
  String upperPatchName = String(synthesizer.getPatchNameU().c_str());
  rtrimArduino(upperPatchName, ' ');
  tft.setTextSize(2);
  tft.setTextDatum(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillRect(0, 94, 320, 26, TFT_BLACK);
  tft.drawString(upperPatchName, 119, 100);

  // Lower patch name
  tft.fillRect(0, 191, 320, 26, TFT_BLACK);
  if (currentPerformance.mode != WHOLE) {
    String lowerPatchName = String(synthesizer.getPatchNameL().c_str());
    rtrimArduino(lowerPatchName, ' ');
    tft.drawString(lowerPatchName, 119, 200);
  }

  // Draw "Dual" or "Split" label next to "Lower" in DUAL/SPLIT mode
  if (currentPerformance.mode == DUAL || currentPerformance.mode == SPLIT) {
    tft.setTextSize(2);
    tft.setTextColor(MY_ORANGE, TFT_BLACK);  // Match highlight style
    tft.setTextDatum(0);

    const char *modeLabel = (currentPerformance.mode == DUAL) ? "Dual" : "Split";
    tft.drawString(modeLabel, 240, 40);  // same line as "Lower"
  }
  if (currentPerformance.mode == SPLIT) {
    tft.setTextSize(2);
    tft.setTextColor(MY_ORANGE, TFT_BLACK);  // Match highlight style
    tft.setTextDatum(0);

    const char *xposeLabel = "Xpose";
    tft.drawString(xposeLabel, 240, 140);  // same line as "Lower"
    // Transpose amount
    String transposeStr = (currentPerformance.splitTranspose >= 0 ? "+" : "") + String(currentPerformance.splitTranspose);
    tft.drawString(transposeStr, 240, 170);
  }

  // In SPLIT mode, show split point under "Patch" line
  if (currentPerformance.mode == SPLIT) {
    // Split point
    String splitText = String(noteName(currentPerformance.splitPoint));
    tft.setTextSize(2);
    tft.setTextColor(MY_ORANGE, TFT_BLACK);
    tft.setTextDatum(0);
    tft.drawString(splitText, 240, 70);  // inline with "Patch"
  }
}

void handleMainEncoder(bool clockwise, int speed) {

  if (menuState == SELECTING) {
    currentMenuIndex += (clockwise ? 1 : -1);
    if (currentMenuIndex < 0) currentMenuIndex = MENU_OPTION_COUNT - 1;
    if (currentMenuIndex >= MENU_OPTION_COUNT) currentMenuIndex = 0;

    displayMenu();
    return;
  }

  if (menuState == EDITING) {
    switch (currentMenuIndex) {
      case MENU_MIDI_CHANNEL:
        midiChannel += (clockwise ? 1 : -1);
        if (midiChannel < 1) midiChannel = 16;
        if (midiChannel > 16) midiChannel = 1;
        break;

      case MENU_SPLIT_TRANSPOSE:
        {
          int oldValue = splitTranspose;
          splitTranspose += (clockwise ? 1 : -1);
          if (splitTranspose < -24) splitTranspose = -24;
          if (splitTranspose > 24) splitTranspose = 24;

          if (splitTranspose != oldValue) {
            splitTransposeChanged = true;
          }
          break;
        }
    }

    displayMenu();  // reuse UI to show current value
    return;
  }

  //  Performance Scroll Mode
  if (inPerformanceMode && !savingPerformanceMode) {
    int oldIndex = performanceIndex;

    if (clockwise) {
      performanceIndex += speed;
      if (performanceIndex > 127) performanceIndex = 127;
    } else {
      performanceIndex -= speed;
      if (performanceIndex < 0) performanceIndex = 0;
    }

    if (performanceIndex != oldIndex) {
      loadPerformance(performanceIndex);
      displayPerformanceInfo();  // replaces displayPatchInfo()
    }

    return;
  }

  // === Performance Save Mode (already implemented) ===
  if (savingPerformanceMode) {
    int oldIndex = performanceIndex;

    if (clockwise) {
      performanceIndex += speed;
      if (performanceIndex > 127) performanceIndex = 127;
    } else {
      performanceIndex -= speed;
      if (performanceIndex < 0) performanceIndex = 0;
    }

    if (performanceIndex != oldIndex) {
      showPerformanceIndexUI(performanceIndex);  // simple header
    }

    return;
  }

  // === Normal Patch Mode Encoder Logic ===
  if (!lowerMode) {
    currentPatchNumber = synthesizer.getPatchNumberU();
  } else {
    currentPatchNumber = synthesizer.getPatchNumberL();
  }

  int oldValue = currentPatchNumber;

  if (clockwise) {
    if (currentPatchNumber < 128) {
      currentPatchNumber += speed;
      if (currentPatchNumber > 128) currentPatchNumber = 128;
    }
  } else {
    if (currentPatchNumber > 1) {
      currentPatchNumber -= speed;
      if (currentPatchNumber < 1) currentPatchNumber = 1;
    }
  }

  if (!lowerMode) {
    currentPatchNumberU = currentPatchNumber;
  } else {
    currentPatchNumberL = currentPatchNumber;
  }

  if (!saveMode) {
    if (currentPatchNumber != oldValue) {
      if (!lowerMode) {
        synthesizer.selectPatchU(currentPatchNumberU);

        if (keyboardMode == WHOLE) {
          suppressLowerDisplay = true;
          synthesizer.setAllParameterL(currentPatchNumberU);
          suppressLowerDisplay = false;
        }
      } else {
        synthesizer.selectPatchL(currentPatchNumberL);
      }

      MIDI6.sendControlChange(123, 127, 1);
      MIDI8.sendControlChange(123, 127, 1);
      clearShortcut();
      parameterController.setDefaultSection();
      displayPatchInfo();
    }
  }

  if (saveMode) {
    if (currentPatchNumber != oldValue) {
      if (!lowerMode) {
        synthesizer.changePatchU(currentPatchNumberU);

        if (keyboardMode == WHOLE) {
          suppressLowerDisplay = true;
          synthesizer.setAllParameterL(currentPatchNumberU);
          suppressLowerDisplay = false;
        }
      } else {
        synthesizer.changePatchL(currentPatchNumberL);
      }

      displayPatchInfo();
    }
  }
}

void showPerformanceIndexUI(int index) {
  tft.fillRect(0, 0, 320, 26, TFT_BLUE);  // header area
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setTextDatum(1);
  tft.drawString("Save to Perf " + String(index + 1), 153, 6);
}

void displayPatchInfo() {
  displayPatchInfo(false);
}

void rtrim(std::string &s, char c) {

  if (s.empty())
    return;

  std::string::iterator p;
  for (p = s.end(); p != s.begin() && *--p == c;)
    ;

  if (*p != c)
    p++;

  s.erase(p, s.end());
}

void rtrimArduino(String &s, char c) {
  while (s.endsWith(String(c))) {
    s.remove(s.length() - 1);
  }
}

void sendPatchToLowerOnly(int currentPatchNumber) {
  synthesizer.setAllParameterL(currentPatchNumber);
}

void displayPatchInfo(bool paintItBlack) {
  tft.setTextColor(paintItBlack ? MY_ORANGE : TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextDatum(1);

  if (!saveMode) {
    showModeLabel();
  }

  // Section labels
  tft.setTextColor((paintItBlack) ? TFT_BLACK : TFT_WHITE);
  tft.drawString("Upper", 60, 40);
  tft.drawString("Patch", 60, 70);

  if (keyboardMode != WHOLE) {
    tft.drawString("Lower", 60, 140);
    tft.drawString("Patch", 60, 170);
  }

  tft.fillRect(0, 128, 320, 2, MY_ORANGE);  // Divider line

  if (!paintItBlack) {
    tft.setTextColor(MY_ORANGE, TFT_BLACK);
  }

  // Upper patch number
  tft.setTextSize(5);
  tft.setTextColor(TFT_BLACK);
  tft.drawNumber(prevPatchNumberU, 180, 50);
  tft.setTextColor(MY_ORANGE, TFT_BLACK);
  tft.drawNumber(currentPatchNumberU, 180, 50);
  prevPatchNumberU = currentPatchNumberU;

  // Lower patch number (only in non-Whole modes)
  if (keyboardMode != WHOLE) {
    tft.setTextSize(5);
    tft.setTextColor(TFT_BLACK);
    tft.drawNumber(prevPatchNumberL, 180, 150);
    tft.setTextColor(MY_ORANGE, TFT_BLACK);
    tft.drawNumber(currentPatchNumberL, 180, 150);
    prevPatchNumberL = currentPatchNumberL;
  }

  // Patch name: Upper
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(1);
  tft.fillRect(0, 94, 320, 26, TFT_BLACK);
  if (!paintItBlack) {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
  }

  string nameU = synthesizer.getPatchNameU();
  rtrim(nameU, ' ');
  tft.setTextSize(2);
  tft.setTextDatum(1);
  tft.drawString(nameU.c_str(), 119, 100);
  tft.setTextDatum(0);
  tft.setTextSize(1);

  // Patch name: Lower (only if not in Whole mode)
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(1);
  tft.fillRect(0, 191, 320, 26, TFT_BLACK);
  if (!paintItBlack) {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
  }

  if (keyboardMode != WHOLE) {
    string nameL = synthesizer.getPatchNameL();
    rtrim(nameL, ' ');
    tft.setTextSize(2);
    tft.setTextDatum(1);
    tft.drawString(nameL.c_str(), 119, 200);
    tft.setTextDatum(0);
    tft.setTextSize(1);
  } else {
    // optionally clear lower label area if needed
    tft.fillRect(0, 140, 320, 80, TFT_BLACK);  // Clear lower patch section
  }
}

void clearMainScreen() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.fillRect(0, 0, 320, 26, MY_ORANGE);
  //tft.updateScreen();
}

void pollAllMCPs() {
  // Read all MCPs and feed the input to each encoder and shortcut button.
  // This is more efficient than reading one pin state at a time
  for (auto &mcp : allMCPs) {
    uint16_t gpioAB = mcp->readGPIOAB();

    for (auto &rotaryEncoder : rotaryEncoders) {
      // Only feed this in the encoder if this is coming from the correct MCP
      if (rotaryEncoder.getMCP() == mcp) {
        rotaryEncoder.feedInput(gpioAB);
      }
    }

    for (auto &button : allButtons) {
      if (button->getMcp() == mcp) {
        button->feedInput(gpioAB);
      }
    }
  }
}

void shortcutButtonChanged(Button *btn, bool released) {
  if (!released) {
    if (activeShortcut > 0) {
      parameterController.clearScreen();
    }

    activeShortcut = btn->id;  // Same section in upper and lower mode

    for (auto &shortcutButton : shortcutButtons) {
      shortcutButton->setLED(shortcutButton->id == btn->id);
    }

    displayPatchInfo(true);

    parameterController.setSection(activeShortcut);
  }
}

void mainButtonChanged(Button *btn, bool released) {

  switch (btn->id) {

    case MENU_BUTTON:
      if (!released) {
        if (menuState == INACTIVE) {
          menuState = SELECTING;
          currentMenuIndex = 0;
          srpanel.writePin(MENU_LED, HIGH);
          displayMenu();
        }
      }
      break;

    case PERF_BUTTON:
      if (!released) {
        inPerformanceMode = !inPerformanceMode;

        if (inPerformanceMode) {
          // Save current mode before switching to performance mode
          previousKeyboardMode = keyboardMode;

          srpanel.writePin(PERF_LED, HIGH);
          srpanel.writePin(PATCH_LED, LOW);
          loadPerformance(performanceIndex);
          displayPerformanceInfo();  // new screen for performances
        } else {
          srpanel.writePin(PERF_LED, LOW);
          srpanel.writePin(PATCH_LED, HIGH);

          tft.fillScreen(TFT_BLACK);

          // Restore previous patches
          synthesizer.selectPatchU(currentPatchNumberU);
          synthesizer.selectPatchL(currentPatchNumberL);

          // Restore previous keyboard mode (Whole/Dual/Split)
          keyboardMode = previousKeyboardMode;
          if (keyboardMode == WHOLE) {
            suppressLowerDisplay = true;
            synthesizer.setAllParameterL(currentPatchNumberU);
            suppressLowerDisplay = false;
          }
          displayPatchInfo();
        }
      }
      break;

    case MODE_BUTTON:
      if (!released) {
        // Start tracking press time
        modeButtonPressTime = millis();
        modeButtonHeldHandled = false;
      } else {
        unsigned long heldTime = millis() - modeButtonPressTime;

        // === SPLIT MODE: SET SPLIT POINT ===
        if (keyboardMode == SPLIT && heldTime >= 500 && !modeButtonHeldHandled) {

          settingSplitPoint = true;
          modeButtonHeldHandled = true;

          // Flash message
          tft.fillRect(0, 0, 320, 26, TFT_RED);
          tft.setTextColor(TFT_WHITE);
          tft.setTextSize(2);
          tft.setTextDatum(1);
          tft.drawString("Press Note to Set Split", 153, 6);
          return;  // Skip normal mode cycle
        }

        // === NORMAL SHORT PRESS: CYCLE MODES ===
        if (!modeButtonHeldHandled) {
          switch (keyboardMode) {
            case WHOLE:
              keyboardMode = DUAL;

              if (currentPatchNumberL < 1 || currentPatchNumberL > 128) {
                currentPatchNumberL = 1;
              }
              synthesizer.selectPatchL(currentPatchNumberL);
              displayPatchInfo();
              break;

            case DUAL:
              keyboardMode = SPLIT;
              displayPatchInfo();
              break;

            case SPLIT:
              keyboardMode = WHOLE;

              // Force exit lower mode
              lowerMode = false;
              lowerButtonPushed = false;
              srpanel.writePin(LOWER_LED, LOW);
              srpanel.writePin(UPPER_LED, HIGH);

              // Load upper patch and send to lower synth
              synthesizer.selectPatchU(currentPatchNumberU);
              suppressLowerDisplay = true;
              synthesizer.setAllParameterL(currentPatchNumberU);
              suppressLowerDisplay = false;

              displayPatchInfo();
              break;
          }
        }
      }
      break;

    case LOWER_BUTTON:
      if (!released) {
        if (keyboardMode == WHOLE) {

          return;
        }
        lowerButtonPushed = !lowerButtonPushed;
      }

      if (lowerButtonPushed) {
        lowerMode = true;
        srpanel.writePin(LOWER_LED, HIGH);  // Activate lower LED
        srpanel.writePin(UPPER_LED, LOW);   // Deactivate upper LED

        if (!saveMode) {
          synthesizer.selectPatchL(currentPatchNumberL);
          parameterController.setDefaultSection();
        }
      } else {
        lowerMode = false;
        srpanel.writePin(LOWER_LED, LOW);   // Deactivate lower LED
        srpanel.writePin(UPPER_LED, HIGH);  // Activate upper LED

        if (!saveMode) {
          synthesizer.selectPatchU(currentPatchNumberU);
          parameterController.setDefaultSection();
        }
      }
      break;

    case SAVE_BUTTON:
      if (!released) {
        saveButtonPressTime = millis();
        savePerformanceHeldHandled = false;
      } else {
        unsigned long heldTime = millis() - saveButtonPressTime;

        // === Long press → enter save-to-slot mode (works in patch & performance mode) ===
        if (heldTime >= 500 && !savePerformanceHeldHandled && !savingPerformanceMode) {
          Serial.println(F(">>> Entering Performance Save Mode"));
          savePerformanceHeldHandled = true;
          savingPerformanceMode = true;

          srpanel.writePin(SAVE_LED, HIGH);
          parameterController.clearScreen();

          tft.fillRect(0, 0, 320, 26, TFT_BLUE);
          tft.setTextColor(TFT_WHITE);
          tft.setTextSize(2);
          tft.setTextDatum(1);
          tft.drawString(inPerformanceMode ? "Save Performance" : "Select Slot to Save", 153, 6);

          showPerformanceIndexUI(performanceIndex);
        }

        // === Short press → Save Patch (patch mode only) ===
        else if (!inPerformanceMode && !savingPerformanceMode && heldTime < 500) {
          Serial.println(F(">>> Short press: Save Patch"));

          saveMode = !saveMode;

          if (saveMode) {
            if (activeShortcut > 0) {
              parameterController.clearScreen();
              clearShortcut();
              displayPatchInfo();
            }
            srpanel.writePin(SAVE_LED, HIGH);
            tft.fillRect(0, 0, 320, 26, TFT_VIOLET);
            tft.setTextColor(TFT_WHITE);
            tft.setTextSize(2);
            tft.setTextDatum(1);
            tft.drawString("Select Location", 153, 6);
            parameterController.setDefaultSection();
          } else {
            tft.setTextSize(2);
            tft.setTextDatum(1);
            tft.fillRect(0, 0, 320, 26, TFT_RED);
            tft.setTextColor(TFT_WHITE);
            tft.drawString("Writing Patch", 153, 6);

            if (!lowerMode) {
              currentPatchNumber = synthesizer.getPatchNumberU();
              synthesizer.setAllParameterU(currentPatchNumberU);
              synthesizer.savePatchDataU(currentPatchNumberU);
            } else {
              currentPatchNumber = synthesizer.getPatchNumberL();
              synthesizer.setAllParameterL(currentPatchNumberL);
              synthesizer.savePatchDataL(currentPatchNumberL);
            }

            delay(1000);
            displayPatchInfo();
            showModeLabel();
            srpanel.writePin(SAVE_LED, LOW);
          }
        }

        // === Save to selected performance slot (both modes) ===
        else if (savingPerformanceMode) {
          Serial.println(F(">>> Confirming Save to Performance Slot"));

          if (inPerformanceMode) {
            Performance updated = {
              .upperPatchNo = (uint8_t)currentPatchNumberU,
              .lowerPatchNo = (uint8_t)currentPatchNumberL,
              .mode = keyboardMode,
              .splitPoint = splitPoint,
              .splitTranspose = (int8_t)splitTranspose,
            };
            memcpy(updated.name, currentPerformance.name, sizeof(updated.name) - 1);
            updated.name[sizeof(updated.name) - 1] = '\0';

            savePerformance(performanceIndex, updated);
            currentPerformance = updated;

            tft.fillRect(0, 0, 320, 26, TFT_GREEN);
            tft.setTextColor(TFT_BLACK);
            tft.setTextSize(2);
            tft.setTextDatum(1);
            tft.drawString("Saved Performance", 153, 6);
            delay(1000);
            displayPerformanceInfo();
          } else {
            saveCurrentStateToPerformance();

            tft.fillRect(0, 0, 320, 26, TFT_GREEN);
            tft.setTextColor(TFT_BLACK);
            tft.setTextSize(2);
            tft.setTextDatum(1);
            tft.drawString("Saved to Slot " + String(performanceIndex + 1), 153, 6);
            delay(1000);
            displayPatchInfo();
          }

          savingPerformanceMode = false;
          srpanel.writePin(SAVE_LED, LOW);
        }
      }
      break;

    case ESC_BUTTON:
      if (!released) {

        if (menuState == EDITING) {
          // Exit setting edit, return to menu list
          menuState = SELECTING;
          displayMenu();
          return;
        }

        if (menuState == SELECTING) {
          // Exit the whole menu
          menuState = INACTIVE;
          srpanel.writePin(MENU_LED, LOW);
          tft.fillScreen(TFT_BLACK);  // clear menu UI
          if (inPerformanceMode) {
            if (splitTransposeChanged) {
              currentPerformance.splitTranspose = splitTranspose;
            }
            splitTransposeChanged = false;
            displayPerformanceInfo();
          } else {
            displayPatchInfo();
          }
          return;
        }

        if (activeShortcut > 0) {
          parameterController.clearScreen();
          clearShortcut();
          displayPatchInfo();
        }

        if (saveMode) {
          saveMode = false;
          tft.fillRect(0, 160, 320, 26, TFT_BLACK);
          parameterController.clearScreen();
          clearShortcut();
          displayPatchInfo();
          srpanel.writePin(SAVE_LED, LOW);
        }

        if (savingPerformanceMode) {
          savingPerformanceMode = false;
          srpanel.writePin(SAVE_LED, LOW);
          displayPatchInfo();
          return;
        }

        parameterController.setDefaultSection();
      }
      break;
  }
}

void flashLED(uint8_t led, int flashes, int intervalMs) {
  for (int i = 0; i < flashes; i++) {
    srpanel.writePin(led, LOW);
    delay(intervalMs);
    srpanel.writePin(led, HIGH);
    delay(intervalMs);
  }
}

void showModeLabel() {
  tft.fillRect(0, 0, 320, 26, TFT_BLACK);  // Clear old label area
  tft.setTextSize(2);
  tft.setTextDatum(1);  // Center text
  tft.setTextColor(TFT_WHITE);

  String label;

  switch (keyboardMode) {
    case WHOLE:
      tft.fillRect(0, 0, 320, 26, TFT_ORANGE);
      tft.setTextColor(TFT_BLACK);
      label = "Whole Mode";
      srpanel.writePin(MODE_RED_LED, LOW);
      srpanel.writePin(MODE_GREEN_LED, LOW);
      break;

    case DUAL:
      tft.fillRect(0, 0, 320, 26, TFT_RED);
      tft.setTextColor(TFT_WHITE);
      label = "Dual Mode";
      srpanel.writePin(MODE_RED_LED, HIGH);
      srpanel.writePin(MODE_GREEN_LED, LOW);
      break;

    case SPLIT:
      tft.fillRect(0, 0, 320, 26, TFT_GREEN);
      tft.setTextColor(TFT_BLACK);
      label = "Split Mode (";
      label += noteName(splitPoint);
      label += ")";
      srpanel.writePin(MODE_RED_LED, LOW);
      srpanel.writePin(MODE_GREEN_LED, HIGH);

      tft.setTextColor(MY_ORANGE);
      const char *xposeLabel = "Xpose";
      tft.drawString(xposeLabel, 270, 140);  // same line as "Lower"

      String transposeStr = (splitTranspose >= 0 ? "+" : "") + String(splitTranspose);
      tft.drawString(transposeStr, 270, 170);

      break;
  }

  tft.setTextColor(TFT_BLACK);
  tft.drawString(label, 160, 6);  // Centered on screen
}

void clearShortcut() {
  activeShortcut = 0;
  for (auto &shortcutButton : shortcutButtons) {
    shortcutButton->setLED(false);
  }
}

void displayMenu() {
  String label;
  tft.fillRect(0, 0, 320, 240, TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextDatum(1);  // Center text
  tft.fillRect(0, 0, 320, 26, TFT_MAGENTA);
  tft.setTextColor(TFT_BLACK);
  label = "Setup Menu";
  tft.drawString(label, 160, 6);  // Centered on screen

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  for (int i = 0; i < MENU_OPTION_COUNT; i++) {
    if (i == currentMenuIndex) {
      tft.setTextColor(TFT_YELLOW);
    } else {
      tft.setTextColor(TFT_WHITE);
    }

    String line = String(menuLabels[i]) + ": ";

    if (i == MENU_MIDI_CHANNEL) line += String(midiChannel);
    if (i == MENU_SPLIT_TRANSPOSE) line += String(splitTranspose);

    tft.drawString(line, 10, 40 + i * 30);
  }
}

void readMainRotaryButton() {
  bool mainRotaryButtonState = (digitalRead(MAIN_ROTARY_BTN_PIN) == LOW);
  if (mainRotaryButtonState != mainRotaryButtonPushed) {
    Serial.println("Encoder button pushed");
    mainRotaryButtonPushed = mainRotaryButtonState;
    mainRotaryButtonChanged(!mainRotaryButtonPushed);
  }
}

void rotaryButtonChanged(Button *btn, bool released) {
  // You can handle the main encoder button here if you like
}

void mainRotaryButtonChanged(bool released) {
  if (!released) return;  // Only act on button *release*

  switch (menuState) {
    case SELECTING:
      menuState = EDITING;
      displayMenu();
      break;

    case EDITING:
      // Save current setting to EEPROM
      switch (currentMenuIndex) {
        case MENU_MIDI_CHANNEL:
          EEPROM.update(EEPROM_ADDR_MIDI_CHANNEL, midiChannel);
          break;

        case MENU_SPLIT_TRANSPOSE:
          EEPROM.update(EEPROM_ADDR_SPLIT_TRANSPOSE, splitTranspose);
          break;
      }

      menuState = SELECTING;
      displayMenu();
      break;

    case INACTIVE:
    default:
      // Do nothing
      break;
  }
}

void loadGlobalSettings() {
  midiChannel = EEPROM.read(EEPROM_ADDR_MIDI_CHANNEL);
  if (midiChannel < 1 || midiChannel > 16) midiChannel = 1;

  splitTranspose = EEPROM.read(EEPROM_ADDR_SPLIT_TRANSPOSE);
  if (splitTranspose > 127) splitTranspose = 0;  // handle signed wrap
  if (splitTranspose > 24) splitTranspose = 24;
  if (splitTranspose < -24) splitTranspose = 0;
}

void upOrDownButtonChanged(Button *btn, bool released) {

  if (!released) {
    if (btn->id == UP_BUTTON) {
      parameterController.upButtonTapped();
    } else {
      parameterController.downButtonTapped();
    }
  }
}
