#include "SynthParameter.h"

SynthParameter::SynthParameter(std::string name) {
    this->_name = name;
}

ParameterType SynthParameter::getType() const {
    return _type;
}

const std::string &SynthParameter::getName() const {
    return _name;
}

int SynthParameter::getNumber() const {
    return _numbers[0];
}

uint8_t SynthParameter::getBitNumber() const {
    return _bitNumbers[0];
}

uint8_t SynthParameter::getBitNumber(int index) const {
    if (index < static_cast<int>(_bitNumbers.size())) {
        return _bitNumbers[index];
    }

    return _bitNumbers[0];
}

int SynthParameter::getNumber(int index) const {
    if (_numbers.empty()) return -1;  // No numbers at all
    if (index < static_cast<int>(_numbers.size()))
        return _numbers[index];       // Valid index
    return _numbers[0];               // Fallback
}

int SynthParameter::getMin() const {
    return _min;
}

int SynthParameter::getMax() const {
    return _max;
}

const std::vector<std::string> &SynthParameter::getDescriptions() const {
    return _descriptions;
}

SynthParameter &SynthParameter::type(const ParameterType type) {
    _type = type;
    return *this;
}

SynthParameter &SynthParameter::min(int min) {
    _min = min;
    return *this;
}

SynthParameter &SynthParameter::max(const int max) {
    _max = max;
    return *this;
}

SynthParameter &SynthParameter::number(const int number) {
    _numbers.push_back(number);
    return *this;
}

SynthParameter &SynthParameter::numbers(const std::initializer_list<const int> numbers) {
    for (const auto &item : numbers) {
        _numbers.push_back(item);
    }
    return *this;
}

SynthParameter &SynthParameter::bitNumber(const int bitNumber) {
    _bitNumbers.push_back(bitNumber);
    return *this;
}

SynthParameter &SynthParameter::bitNumbers(const std::initializer_list<const int> bitNumbers) {
    for (const auto &item : bitNumbers) {
        _bitNumbers.push_back(item);
    }
    return *this;
}

SynthParameter &SynthParameter::descriptions(const std::initializer_list<const std::string> descriptions) {
    for (const auto &item : descriptions) {
        _descriptions.push_back(item);
    }
    return *this;
}

SynthParameter &SynthParameter::performanceControlType(const int paramNumber1, const int paramNumber2) {
    _type = PERFORMANCE_CTRL;
    _numbers.push_back(paramNumber1);
    _numbers.push_back(paramNumber2);
    return *this;
}

SynthParameter &SynthParameter::asciiCharacterType(int paramNumber) {
    _type = ASCII_CHAR;
    _numbers.push_back(paramNumber);
    _min = 32;
    _max = 254;
    return *this;
}
