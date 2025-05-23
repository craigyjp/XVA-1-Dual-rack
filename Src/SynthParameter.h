//
// Created by André Mathlener on 04/04/2021.
//

#ifndef XVA1USERINTERFACE_SYNTHPARAMETER_H
#define XVA1USERINTERFACE_SYNTHPARAMETER_H


#include <string>
#include <utility>
#include <vector>
#include "ParameterType.h"

class SynthParameter {
    ParameterType _type = NUMERIC;
    std::string _name;
    // This will contain one or more parameter numbers (4 for XVA1 oscillators, 8 for XFM2 operators, 2 for Performance controls),
    std::vector<int> _numbers;
    std::vector<uint8_t> _bitNumbers;
    int _min = 0;
    int _max = 255;
    std::vector<std::string> _descriptions;

public:
    explicit SynthParameter(std::string name);

    friend class SynthParameterBuilder;

    ParameterType getType() const;

    const std::string &getName() const;

    int getNumber() const;

    int getNumber(int index) const;

    uint8_t getBitNumber() const;

    uint8_t getBitNumber(int index) const;

    int getMin() const;

    int getMax() const;

    const std::vector<std::string> &getDescriptions() const;

    SynthParameter &type(ParameterType type);

    SynthParameter &min(int min);

    SynthParameter &max(int max);

    SynthParameter &number(int number);

    SynthParameter &numbers(std::initializer_list<const int> numbers);

    SynthParameter &bitNumber(int bitNumber);

    SynthParameter &bitNumbers(std::initializer_list<const int> bitNumbers);

    SynthParameter &descriptions(std::initializer_list<const std::string> descriptions);

    SynthParameter &performanceControlType(int paramNumber1, int paramNumber2);

    SynthParameter &asciiCharacterType(int paramNumber);

};


#endif //XVA1USERINTERFACE_SYNTHPARAMETER_H
