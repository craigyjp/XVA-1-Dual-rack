#include <stdint.h>  // Add this at the top if it's not already there
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <ST7735_t3.h>  // Hardware-specific library
#include <ST7789_t3.h>  // Hardware-specific library
#include <st7735_t3_font_Arial.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include "SynthParameter.h"
#include "Button.h"
#include "Hardware.h"
#include <MIDI.h>
#include <ShiftRegister74HC595.h>
#include "global.h"
#include <EEPROM.h>

/* function prototypes */

void handleMainEncoder(bool clockwise, int speed);

void initOLEDDisplays();

void pollAllMCPs();

//void IRAM_ATTR interruptCallback();
void interruptCallback();

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

void handleInterrupt();

void attachInterrupts();

void detachInterrupts();

int getEncoderSpeed(int id);

ShiftRegister74HC595<1> srpanel(28, 29, 30);

void setup() {
  Serial.begin(115200);

  // pulup i2c pins
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);

  //while the serial stream is not open, do nothing:
  //    while (!Serial);

  Serial.println("\n");
  Serial.println("===================");
  Serial.println("XVA1 User Interface");
  Serial.println("===================\n");

  //MIDI 5 Pin DIN
  MIDI.begin();
  MIDI.setHandleControlChange(myControlChange);
  MIDI.setHandleProgramChange(myProgramChange);
  MIDI.setHandleAfterTouchChannel(myAfterTouch);
  MIDI.setHandlePitchBend(DinHandlePitchBend);
  MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.turnThruOn(midi::Thru::Mode::Off);
  Serial.println("MIDI In DIN Listening");

  //USB Client MIDI
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleProgramChange(myProgramChange);
  usbMIDI.setHandleAfterTouchChannel(myAfterTouch);
  usbMIDI.setHandlePitchChange(DinHandlePitchBend);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleNoteOff(myNoteOff);
  Serial.println("USB Client MIDI Listening");

  MIDI6.begin();
  MIDI6.turnThruOn(midi::Thru::Mode::Off);

  MIDI8.begin();
  MIDI8.turnThruOn(midi::Thru::Mode::Off);

  loadSplitPointFromEEPROM();

  mcp1.begin(0);
  mcp2.begin(1);
  mcp3.begin(2);
  mcp4.begin(3);
  mcp5.begin(4);

  synthesizer.begin();

  initMainScreen();
  clearMainScreen();

  initRotaryEncoders();
  initOLEDDisplays();
  initButtons();

  attachInterrupts();

  synthesizer.selectPatchU(1);
  synthesizer.selectPatchL(1);
  parameterController.setDefaultSection();
  displayPatchInfo();
}

void loop() {
  pollAllMCPs();

  if (awokeByInterrupt) {
    handleInterrupt();
  }
  MIDI.read();
  //usbMIDI.read();
}

void myProgramChange(uint8_t channel, uint8_t value) {
  if (channel == 1) {
    synthesizer.selectPatchU(value + 1);
  }
  if (channel == 2) {
    synthesizer.selectPatchL(value + 1);
  }
  parameterController.setDefaultSection();
  parameterController.clearScreen();
  clearShortcut();
  displayPatchInfo();
}

void myControlChange(uint8_t channel, uint8_t controller, uint8_t value) {
  MIDI6.sendControlChange(controller, value, channel);
  MIDI8.sendControlChange(controller, value, channel);
}

void myAfterTouch(uint8_t channel, uint8_t value) {
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

void DinHandlePitchBend(uint8_t channel, int pitch) {
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

void myNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {

  if (settingSplitPoint) {
    splitPoint = note;
    saveSplitPointToEEPROM(splitPoint);
    settingSplitPoint = false;

    Serial.print("[SPLIT] Split point set to: ");
    Serial.println(splitPoint);

    // Flash confirmation
    tft.fillRect(0, 0, 320, 26, TFT_GREEN);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextDatum(1);
    tft.drawString("Split Set: " + String(noteName(note)), 153, 6);

    // Wait a moment then restore header
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
      noteTarget[note] = 0;  // both received
      break;

    case SPLIT:
      if (note < splitPoint) {
        MIDI6.sendNoteOn(note, velocity, channel);
        noteTarget[note] = 6;
      } else {
        MIDI8.sendNoteOn(note, velocity, channel);
        noteTarget[note] = 8;
      }
      break;
  }
}

void myNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  uint8_t target = noteTarget[note];

  switch (keyboardMode) {
    case WHOLE:
    case SPLIT:
      if (target == 6) {
        MIDI6.sendNoteOff(note, velocity, channel);
      } else if (target == 8) {
        MIDI8.sendNoteOff(note, velocity, channel);
      } else {
        // fallback: send to both
        MIDI6.sendNoteOff(note, velocity, channel);
        MIDI8.sendNoteOff(note, velocity, channel);
      }
      break;

    case DUAL:
      MIDI6.sendNoteOff(note, velocity, channel);
      MIDI8.sendNoteOff(note, velocity, channel);
      break;
  }

  // Clear the note tracking
  noteTarget[note] = 0;
}

/**
   The interrupt callback will just signal that an interrupt has occurred.
   All work will be done from the main loop, to avoid watchdog errors
*/


void interruptCallback() {
  awokeByInterrupt = true;
}

void readMainRotaryEncoder() {
  unsigned char result = mainRotaryEncoder.process();
  if (result) {
    int speed = getEncoderSpeed(0);

    bool clockwise = result == DIR_CW;
    if (activeShortcut != 0) {
      bool consumed = parameterController.rotaryEncoderChanged(0, clockwise, 1);
      if (!consumed) {
        handleMainEncoder(clockwise, speed);
      }
    } else {
      handleMainEncoder(clockwise, speed);
    }
  }
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

  mainRotaryEncoder.begin(true);
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

  pinMode(MAIN_ROTARY_BTN_PIN, INPUT_PULLUP);
}

void handleInterrupt() {
  // Disable interrupts while handling them
  detachInterrupts();

  readMainRotaryButton();
  readMainRotaryEncoder();

  // Enable interrupts again
  awokeByInterrupt = false;
  attachInterrupts();
}

void attachInterrupts() {
  attachInterrupt(MAIN_ROTARY_BTN_PIN, interruptCallback, CHANGE);
  attachInterrupt(MAIN_ROTARY_ENCODER_PIN_A, interruptCallback, CHANGE);
  attachInterrupt(MAIN_ROTARY_ENCODER_PIN_B, interruptCallback, CHANGE);
}

void detachInterrupts() {
  detachInterrupt(MAIN_ROTARY_BTN_PIN);
  detachInterrupt(MAIN_ROTARY_ENCODER_PIN_A);
  detachInterrupt(MAIN_ROTARY_ENCODER_PIN_B);
}

void handleMainEncoder(bool clockwise, int speed) {
  // Get current patch number
  if (!lowerMode) {
    currentPatchNumber = synthesizer.getPatchNumberU();
  } else {
    currentPatchNumber = synthesizer.getPatchNumberL();
  }

  int oldValue = currentPatchNumber;

  // Adjust patch number based on encoder direction
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

  // Save the new patch number to the correct layer
  if (!lowerMode) {
    currentPatchNumberU = currentPatchNumber;
  } else {
    currentPatchNumberL = currentPatchNumber;
  }

  Serial.print("Selecting patch: ");
  Serial.println(currentPatchNumber);

  if (!saveMode) {
    Serial.print("Loading the patch: ");
    Serial.println(currentPatchNumber);

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
      // Send CC123 to both synths to clear stuck notes
      MIDI6.sendControlChange(123, 127, 1);  // Lower synth
      MIDI8.sendControlChange(123, 127, 1);  // Upper synth

      clearShortcut();
      parameterController.setDefaultSection();
      displayPatchInfo();
    }
  }

  if (saveMode) {
    Serial.print("Scroll through patches: ");
    Serial.println(currentPatchNumber);

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

void sendPatchToLowerOnly(int currentPatchNumber) {
  //String* data = getPatchDataU(patchNumber);
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
  Serial.print("Shortcut-button #");
  Serial.print(btn->id);
  Serial.print(" ");
  Serial.println((released) ? "RELEASED" : "PRESSED");

  if (!released) {
    if (activeShortcut > 0) {
      parameterController.clearScreen();
    }

    activeShortcut = (lowerButtonPushed && btn->id <= 4) ? btn->id + 8 : btn->id;

    Serial.print("Active Shortcut: ");
    Serial.println(activeShortcut);
    for (auto &shortcutButton : shortcutButtons) {
      shortcutButton->setLED(shortcutButton->id == btn->id);
    }

    displayPatchInfo(true);

    parameterController.setSection(activeShortcut);
  }
}

void mainButtonChanged(Button *btn, bool released) {
  Serial.print("Main-button #");
  Serial.print(btn->id);
  Serial.print(" ");
  Serial.println((released) ? "RELEASED" : "PRESSED");

  switch (btn->id) {
    case MENU_BUTTON:
      if (!released) {
        // Start tracking press time
        menuButtonPressTime = millis();
        menuButtonHeldHandled = false;
      } else {
        unsigned long heldTime = millis() - menuButtonPressTime;

        // === SPLIT MODE: SET SPLIT POINT ===
        if (keyboardMode == SPLIT && heldTime >= 500 && !menuButtonHeldHandled) {
          Serial.println("[SPLIT] Entering split point set mode");
          settingSplitPoint = true;
          menuButtonHeldHandled = true;

          // Flash message
          tft.fillRect(0, 0, 320, 26, TFT_RED);
          tft.setTextColor(TFT_WHITE);
          tft.setTextSize(2);
          tft.setTextDatum(1);
          tft.drawString("Press Note to Set Split", 153, 6);
          return; // Skip normal mode cycle
        }

        // === NORMAL SHORT PRESS: CYCLE MODES ===
        if (!menuButtonHeldHandled) {
          switch (keyboardMode) {
            case WHOLE:
              keyboardMode = DUAL;
              Serial.println("[MODE] Switched to DUAL");

              if (currentPatchNumberL < 1 || currentPatchNumberL > 128) {
                currentPatchNumberL = 1;
              }
              synthesizer.selectPatchL(currentPatchNumberL);
              displayPatchInfo();
              break;

            case DUAL:
              keyboardMode = SPLIT;
              Serial.println("[MODE] Switched to SPLIT");
              displayPatchInfo();
              break;

            case SPLIT:
              keyboardMode = WHOLE;
              Serial.println("[MODE] Switched to WHOLE");

              // Force exit lower mode
              lowerMode = false;
              lowerButtonPushed = false;
              srpanel.set(LOWER_LED, LOW);

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
          Serial.println("[INFO] Lower button ignored in WHOLE mode");
          return;
        }
        lowerButtonPushed = !lowerButtonPushed;
      }

      if (lowerButtonPushed) {
        srpanel.set(LOWER_LED, HIGH);
        lowerMode = true;
        if (!saveMode) {
          synthesizer.selectPatchL(currentPatchNumberL);
          parameterController.setDefaultSection();
        }
      }

      if (!lowerButtonPushed) {
        srpanel.set(LOWER_LED, LOW);
        lowerMode = false;
        if (!saveMode) {
          synthesizer.selectPatchU(currentPatchNumberU);
          parameterController.setDefaultSection();
        }
      }
      break;

    case SAVE_BUTTON:
      if (!released) {
        saveMode = !saveMode;
        if (saveMode) {
          if (activeShortcut > 0) {
            parameterController.clearScreen();
            clearShortcut();
            displayPatchInfo();
          }
          srpanel.set(SAVE_LED, HIGH);
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
            int currentPatchNumber = synthesizer.getPatchNumberU();
            synthesizer.setAllParameterU(currentPatchNumberU);
            synthesizer.savePatchDataU(currentPatchNumberU);
          } else {
            int currentPatchNumber = synthesizer.getPatchNumberL();
            synthesizer.setAllParameterL(currentPatchNumberL);
            synthesizer.savePatchDataL(currentPatchNumberL);
          }

          delay(1000);
          displayPatchInfo();
          showModeLabel();
          srpanel.set(SAVE_LED, LOW);
        }
      }
      break;

    case ESC_BUTTON:
      if (!released) {
        if (activeShortcut > 0) {
          parameterController.clearScreen();
          clearShortcut();
          displayPatchInfo();
        }

        if (saveMode) {
          saveMode = false;
          tft.fillRect(0, 160, 240, 26, TFT_BLACK);
          parameterController.clearScreen();
          clearShortcut();
          displayPatchInfo();
          srpanel.set(SAVE_LED, LOW);
        }

        parameterController.setDefaultSection();
      }
      break;
  }
}

void showModeLabel() {
  tft.fillRect(0, 0, 320, 26, TFT_BLACK); // Clear old label area
  tft.setTextSize(2);
  tft.setTextDatum(1); // Center text
  tft.setTextColor(TFT_WHITE);

  String label;

  switch (keyboardMode) {
    case WHOLE:
      tft.fillRect(0, 0, 320, 26, TFT_ORANGE);
      tft.setTextColor(TFT_BLACK);
      label = "Whole Mode";
      break;

    case DUAL:
      tft.fillRect(0, 0, 320, 26, TFT_BLUE);
      tft.setTextColor(TFT_WHITE);
      label = "Dual Mode";
      break;

    case SPLIT:
      tft.fillRect(0, 0, 320, 26, TFT_GREEN);
      tft.setTextColor(TFT_BLACK);
      label = "Split Mode (";
      label += noteName(splitPoint);
      label += ")";
      break;
  }

  tft.drawString(label, 160, 6); // Centered on screen
}

void clearShortcut() {
  activeShortcut = 0;
  for (auto &shortcutButton : shortcutButtons) {
    shortcutButton->setLED(false);
  }
}

void readMainRotaryButton() {
  bool mainRotaryButtonState = (digitalRead(MAIN_ROTARY_BTN_PIN) == LOW);
  if (mainRotaryButtonState != mainRotaryButtonPushed) {
    mainRotaryButtonPushed = mainRotaryButtonState;
    mainRotaryButtonChanged(!mainRotaryButtonPushed);
  }
}

void rotaryButtonChanged(Button *btn, bool released) {
  Serial.print("Rotary-button #");
  Serial.print(btn->id);
  Serial.print(" ");
  Serial.println((released) ? "RELEASED" : "PRESSED");
}

void upOrDownButtonChanged(Button *btn, bool released) {
  Serial.print((btn->id == UP_BUTTON) ? "Up" : "Down");
  Serial.print("-button");
  Serial.print(" ");
  Serial.println((released) ? "RELEASED" : "PRESSED");

  if (!released) {
    if (btn->id == UP_BUTTON) {
      parameterController.upButtonTapped();
    } else {
      parameterController.downButtonTapped();
    }
  }
}

void mainRotaryButtonChanged(bool released) {
  Serial.print("MAIN-Rotary-button ");
  Serial.println((released) ? "RELEASED" : "PRESSED");
}
