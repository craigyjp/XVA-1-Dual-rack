//
// Created by André Mathlener on 07/04/2021.
//

#ifndef XVA1USERINTERFACE_SYNTHESIZER_H
#define XVA1USERINTERFACE_SYNTHESIZER_H

#include <string>
#include <Arduino.h>
#include "Envelope.h"

using namespace std;

class Synthesizer {
private:

  int currentPatchNumber = 1;
  int currentPatchNumberU = 1;
  int currentPatchNumberL = 1;
  std::string currentPatchName = "";
  std::string currentPatchNameU = "";
  std::string currentPatchNameL = "";
  uint8_t currentPatchData[512] = {};

public:

  void begin();

  void selectPatchU(int number);

  void selectPatchL(int number);

  void changePatchU(int number);

  void changePatchL(int number);

  void loadPatchDataU();

  void loadPatchDataL();

  void savePatchDataU(int number);

  void savePatchDataL(int number);

  int getPatchNumberU() const;

  int getPatchNumberL() const;

  const string &getPatchNameU() const;

  const string &getPatchNameL() const;

  uint8_t getParameterU(int number) const;

  uint8_t getParameterL(int number) const;

  void setAllParameterU(int number);

  void setAllParameterL(int number);

  void setParameterU(int number, int value);

  void setParameterL(int number, int value);

  void setCurrentPatchNameU();

  void setCurrentPatchNameL();

  Envelope getEnvelopeValues(Envelope &envelope);
};


#endif  //XVA1USERINTERFACE_SYNTHESIZER_H
