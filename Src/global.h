#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>

// EEPROM split point address
#define EEPROM_SPLITPOINT_ADDR 0

// TFT color definitions
#define TFT_GREY 0x5AEB
#define MY_ORANGE 0xFBA0
#define TFT_BLACK 0x0000
#define TFT_NAVY 0x000F
#define TFT_DARKGREEN 0x03E0
#define TFT_DARKCYAN 0x03EF
#define TFT_MAROON 0x7800
#define TFT_PURPLE 0x780F
#define TFT_OLIVE 0x7BE0
#define TFT_LIGHTGREY 0xD69A
#define TFT_DARKGREY 0x7BEF
#define TFT_BLUE 0x001F
#define TFT_GREEN 0x07E0
#define TFT_CYAN 0x07FF
#define TFT_RED 0xF800
#define TFT_MAGENTA 0xF81F
#define TFT_YELLOW 0xFFE0
#define TFT_WHITE 0xFFFF
#define TFT_ORANGE 0xFDA0
#define TFT_GREENYELLOW 0xB7E0
#define TFT_PINK 0xFE19
#define TFT_BROWN 0x9A60
#define TFT_GOLD 0xFEA0
#define TFT_SILVER 0xC618
#define TFT_SKYBLUE 0x867D
#define TFT_VIOLET 0x915C

// Panel LED identifiers
#define SAVE_LED 0
#define LOWER_LED 3
#define MENU_LED 1
#define ESCAPE_LED 2

// Keyboard modes
enum KeyboardMode { WHOLE, DUAL, SPLIT };
extern KeyboardMode keyboardMode;
extern bool lowerMode;

// Global variables
extern bool awokeByInterrupt;
extern unsigned long lastTransition[9];
extern int currentPatchNumber;
extern int currentPatchNumberU;
extern int currentPatchNumberL;
extern int prevPatchNumberU;
extern int prevPatchNumberL;
extern int activeShortcut;
extern bool saveMode;
extern bool settingSplitPoint;
extern unsigned long splitSetStartTime;
extern uint8_t splitPoint;
extern unsigned long menuButtonPressTime;
extern const unsigned long longPressThreshold;
extern bool menuButtonHeldHandled;
extern bool upperSW;
extern bool lowerButtonPushed;
extern bool mainRotaryButtonPushed;
extern bool suppressLowerDisplay;
extern bool toggle;
extern uint8_t noteTarget[128];

// Function declarations
const char* noteName(uint8_t note);
void loadSplitPointFromEEPROM();
void saveSplitPointToEEPROM(uint8_t value);

#endif
