#include "global.h"
#include <EEPROM.h>
#include "Performance.h"

#include "Synthesizer.h"
extern Synthesizer synthesizer;  // External reference to the above instance

bool inPerformanceMode = false;
int performanceIndex = 0;
Performance currentPerformance;

bool lowerMode = false;  // initialize
KeyboardMode keyboardMode = WHOLE;
KeyboardMode previousKeyboardMode = KeyboardMode::WHOLE;  // default fallback
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
bool splitPointChanged = false;
bool splitTransposeChanged = false;
int splitTranspose = 0;     // -24 to +24
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


const int PERFORMANCE_SIZE = sizeof(Performance);
const int MAX_PERFORMANCES = 128;
const int PERFORMANCE_EEPROM_BASE = 1;  // EEPROM[0] = global patch split point

void saveCurrentStateToPerformance() {
  currentPerformance.upperPatchNo = currentPatchNumberU;
  currentPerformance.lowerPatchNo = currentPatchNumberL;
  currentPerformance.mode = static_cast<uint8_t>(keyboardMode);
  currentPerformance.splitPoint = splitPoint;
  currentPerformance.splitTranspose = splitTranspose;

  // Optional: Auto-generate a name if not already set
  snprintf(currentPerformance.name, sizeof(currentPerformance.name), "Perf %03d", performanceIndex + 1);

  savePerformance(performanceIndex, currentPerformance);

  Serial.print(F("[PERF] Saved performance "));
  Serial.print(performanceIndex);
  Serial.print(F(": "));
  Serial.println(currentPerformance.name);
}

void savePerformance(uint8_t index, const Performance &perf) {
  if (index >= MAX_PERFORMANCES) return;
  int address = PERFORMANCE_EEPROM_BASE + index * PERFORMANCE_SIZE;
  EEPROM.put(address, perf);
}

void loadPerformance(uint8_t index) {
  if (index >= MAX_PERFORMANCES) return;
  int address = PERFORMANCE_EEPROM_BASE + index * PERFORMANCE_SIZE;
  EEPROM.get(address, currentPerformance);

  // Apply performance settings
  keyboardMode = static_cast<KeyboardMode>(currentPerformance.mode);
  splitPoint = currentPerformance.splitPoint;
  splitTranspose = currentPerformance.splitTranspose;

  synthesizer.selectPatchU(currentPerformance.upperPatchNo);
  synthesizer.selectPatchL(currentPerformance.lowerPatchNo);

}

const char* noteName(uint8_t note) {
  FLASHMEM static const char* names[] = {
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
