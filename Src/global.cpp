#include "global.h"
#include <EEPROM.h>

bool lowerMode = false;  // initialize
KeyboardMode keyboardMode = WHOLE;
bool awokeByInterrupt = false;
unsigned long lastTransition[9] = {0};
int currentPatchNumber = 1;
int currentPatchNumberU = 1;
int currentPatchNumberL = 1;
int prevPatchNumberU = 0;
int prevPatchNumberL = 0;
int activeShortcut = 0;
bool saveMode = false;
bool settingSplitPoint = false;
unsigned long splitSetStartTime = 0;
uint8_t splitPoint = 60;
unsigned long modeButtonPressTime = 0;
const unsigned long longPressThreshold = 1000;
bool modeButtonHeldHandled = false;
bool upperSW = true;
bool lowerButtonPushed = false;
bool mainRotaryButtonPushed = false;
bool suppressLowerDisplay = true;
bool toggle = false;
EXTMEM uint8_t noteTarget[128] = {0};

// #include "Performance.h"

// bool inPerformanceMode = false;
// int performanceIndex = 0;
// Performance currentPerformance;

const char* noteName(uint8_t note) {
  static const char* names[] = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
  };
  static char buf[5];
  snprintf(buf, sizeof(buf), "%s%d", names[note % 12], (note / 12) - 1);
  return buf;
}

void loadSplitPointFromEEPROM() {
  uint8_t value = EEPROM.read(EEPROM_SPLITPOINT_ADDR);
  if (value >= 0 && value <= 127) {
    splitPoint = value;
  }
}

void saveSplitPointToEEPROM(uint8_t value) {
  EEPROM.write(EEPROM_SPLITPOINT_ADDR, value);
}