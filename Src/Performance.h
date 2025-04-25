#ifndef PERFORMANCE_H
#define PERFORMANCE_H

// 1. Declare the struct first
struct Performance {
  uint16_t upperPatchNo;
  uint16_t lowerPatchNo;
  uint8_t mode;
  uint8_t splitPoint;
  int8_t splitTranspose;   // ±24 or so
  char name[21];
};

// 2. Declare global externs
extern bool inPerformanceMode;
extern int performanceIndex;
extern Performance currentPerformance;

// 3. Declare functions using Performance
void loadPerformance(uint8_t index);
void savePerformance(uint8_t index, const Performance &perf);
void saveCurrentStateToPerformance();

#endif
