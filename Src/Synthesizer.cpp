#include "Synthesizer.h"
int read_status;

#define HWSERIAL4 Serial4
#define HWSERIAL3 Serial3

//
// READ PATCH N FROM UPPER SYNTH
//

void Synthesizer::selectPatchU(int number) {
  int synthPatchNumber = number - 1;

  Serial.print("Selecting patch #");
  Serial.print(synthPatchNumber);
  Serial.print(" on Synth...");

  HWSERIAL3.write('r');  // 'r' = Read program
  HWSERIAL3.write(synthPatchNumber);



  int bytesRead = 0;
  int retry = 0;
  while (bytesRead == 0 && retry != 100) {
    if (HWSERIAL3.available()) {
      read_status = HWSERIAL3.read();
      bytesRead++;
      retry = 0;
    } else {
      retry++;
      delay(1);
    }
  }

  Serial.print("Status=");
  Serial.println(read_status, DEC);

  loadPatchDataU();
  currentPatchNumberU = number;
}

//
// READ PATCH N FROM LOWER SYNTH
//

void Synthesizer::selectPatchL(int number) {
  int synthPatchNumber = number - 1;

  Serial.print("Selecting patch #");
  Serial.print(synthPatchNumber);
  Serial.print(" on Synth...");

  HWSERIAL4.write('r');  // 'r' = Read program
  HWSERIAL4.write(synthPatchNumber);

  int bytesRead = 0;
  int retry = 0;
  while (bytesRead == 0 && retry != 100) {
    if (HWSERIAL4.available()) {
      read_status = HWSERIAL4.read();
      bytesRead++;
      retry = 0;
    } else {
      retry++;
      delay(1);
    }
  }

  Serial.print("Status=");
  Serial.println(read_status, DEC);

  loadPatchDataL();
  currentPatchNumberL = number;
}

void Synthesizer::changePatchU(int number) {
  currentPatchNumberU = number;
}

void Synthesizer::changePatchL(int number) {
  currentPatchNumberL = number;
}

//
// LOADS CURRENT PATCH FROM UPPER SYNTH
//

void Synthesizer::loadPatchDataU() {
  HWSERIAL3.write('d');  // 'd' = Display program

  Serial.println("Reading patch data from Synth...");

  int bytesRead = 0;
  int retry = 0;
  while (bytesRead != 512 && retry != 100) {
    if (HWSERIAL3.available()) {
      uint8_t b = HWSERIAL3.read();
      currentPatchData[bytesRead] = b;
      bytesRead++;
      retry = 0;
    } else {
      retry++;
      delay(1);
    }
  }
  HWSERIAL3.flush();
  setCurrentPatchNameU();
}

//
// LOADS CURRENT PATCH FROM LOWER SYNTH
//

void Synthesizer::loadPatchDataL() {
  HWSERIAL4.write('d');  // 'd' = Display program

  Serial.println("Reading patch data from Synth...");

  int bytesRead = 0;
  int retry = 0;
  while (bytesRead != 512 && retry != 100) {
    if (HWSERIAL4.available()) {
      uint8_t b = HWSERIAL4.read();
      currentPatchData[bytesRead] = b;
      bytesRead++;
      retry = 0;
    } else {
      retry++;
      delay(1);
    }
  }
  HWSERIAL4.flush();
  setCurrentPatchNameL();
}

//
// WRITES CURRENT PATCH TO UPPER SYNTH (NO DATA TRANSFER)
//

void Synthesizer::savePatchDataU(int number) {
  int synthPatchNumber = number - 1;

  Serial.println("Writing patch data from Synth...");
  Serial.println(number);
  HWSERIAL3.write('w');  // 'w' = Write program
  HWSERIAL3.write(synthPatchNumber);
}

//
// WRITES CURRENT PATCH TO LOWER SYNTH (NO DATA TRANSFER)
//

void Synthesizer::savePatchDataL(int number) {
  int synthPatchNumber = number - 1;

  Serial.println("Writing patch data from Synth...");
  Serial.println(number);
  HWSERIAL4.write('w');  // 'w' = Write program
  HWSERIAL4.write(synthPatchNumber);
}

//
// READS CURRENT PATCHNAME FOR UPPER SYNTH
//

void Synthesizer::setCurrentPatchNameU() {
  string patchName = "";

  for (int i = 480; i <= 504; i++) {
    patchName += (char)currentPatchData[i];
  }
  currentPatchNameU = patchName;

  Serial.print("Patch name: ");
  Serial.println(patchName.c_str());
}

//
// READS CURRENT PATCHNAME FOR LOWER SYNTH
//

void Synthesizer::setCurrentPatchNameL() {
  string patchName = "";

  for (int i = 480; i <= 504; i++) {
    patchName += (char)currentPatchData[i];
  }
  currentPatchNameL = patchName;

  Serial.print("Patch name: ");
  Serial.println(patchName.c_str());
}

int Synthesizer::getPatchNumberU() const {
  return currentPatchNumberU;
}

int Synthesizer::getPatchNumberL() const {
  return currentPatchNumberL;
}

const string &Synthesizer::getPatchNameU() const {
  return currentPatchNameU;
}

const string &Synthesizer::getPatchNameL() const {
  return currentPatchNameL;
}

uint8_t Synthesizer::getParameterU(int number) const {
  return currentPatchData[number];
}

uint8_t Synthesizer::getParameterL(int number) const {
  return currentPatchData[number];
}

//
// test transfer of patch upper
//

void Synthesizer::setAllParameterU(int number) {
  Serial.println("Writing all patch data to upper Synth...");
  Serial.println(number);
  HWSERIAL3.flush();
  int bytesSent = 0;
  int retry = 0;
  while (bytesSent != 512 && retry != 100) {
      HWSERIAL3.write('s');  // 's' = Set Parameter

      if (bytesSent > 255) {
        // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
        HWSERIAL3.write(255);
        HWSERIAL3.write(bytesSent - 256);
        HWSERIAL3.write(currentPatchData[bytesSent]);
      } else {
        HWSERIAL3.write(bytesSent);
        HWSERIAL3.write(currentPatchData[bytesSent]);
      }
      bytesSent++;
      retry = 0;
  }
  setCurrentPatchNameU();
}

//
// test transfer of patch lower
//

void Synthesizer::setAllParameterL(int number) {
  Serial.println("Writing all patch data to lower Synth...");
  Serial.println(number);
  HWSERIAL4.flush();
  int bytesSent = 0;
  int retry = 0;
  while (bytesSent != 512 && retry != 100) {

    HWSERIAL4.write('s');  // 's' = Set Parameter

    if (bytesSent > 255) {
      // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
      HWSERIAL4.write(255);
      HWSERIAL4.write(bytesSent - 256);
      HWSERIAL4.write(currentPatchData[bytesSent]);
    } else {
      HWSERIAL4.write(bytesSent);
      HWSERIAL4.write(currentPatchData[bytesSent]);
    }
    bytesSent++;
    retry = 0;
  }
  setCurrentPatchNameL();
}

//
// SETS PARAMETER FOR UPPER SYNTH
//

void Synthesizer::setParameterU(int number, int value) {
  HWSERIAL3.write('s');  // 's' = Set Parameter

  if (number > 255) {
    // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
    HWSERIAL3.write(255);
    HWSERIAL3.write(number - 256);
    HWSERIAL3.write(value);
  } else {
    HWSERIAL3.write(number);
    HWSERIAL3.write(value);
  }

  currentPatchData[number] = value;

  if (number >= 480 && number <= 504) {
    setCurrentPatchNameU();
  }
}

//
// SETS PARAMETER FOR LOWER SYNTH
//

void Synthesizer::setParameterL(int number, int value) {
  HWSERIAL4.write('s');  // 's' = Set Parameter

  if (number > 255) {
    // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
    HWSERIAL4.write(255);
    HWSERIAL4.write(number - 256);
    HWSERIAL4.write(value);
  } else {
    HWSERIAL4.write(number);
    HWSERIAL4.write(value);
  }

  currentPatchData[number] = value;

  if (number >= 480 && number <= 504) {
    setCurrentPatchNameL();
  }
}

void Synthesizer::begin() {
  HWSERIAL3.begin(500000, SERIAL_8N1);  // XVA1 Serial
  HWSERIAL4.begin(500000, SERIAL_8N1);  // XVA1 Serial
}

Envelope Synthesizer::getEnvelopeValues(Envelope &envelope) {
  Envelope returnEnvelope = Envelope();

  for (int i = 0; i < 6; ++i) {
    returnEnvelope.level[i] = getParameterU(envelope.level[i]);
    returnEnvelope.rate[i] = getParameterU(envelope.rate[i]);
  }

  return returnEnvelope;
}