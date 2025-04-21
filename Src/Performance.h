#ifndef PERFORMANCE_H
#define PERFORMANCE_H

struct Performance {
  uint8_t upperPatchNo;
  uint8_t lowerPatchNo;
  uint8_t keyboardMode;     // WHOLE, DUAL, SPLIT = 0, 1, 2
  uint8_t splitPoint;       // MIDI note number (0–127)
  char name[17];            // 16-char performance name + null
};

#endif