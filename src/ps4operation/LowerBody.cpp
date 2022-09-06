/**
 * @file LowerBody.cpp
 * @author H1rono (hronok66@gmail.com)
 * @brief include/ps4operation/LowerBody.hppの実装
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#include "ps4operation/LowerBody.hpp"

int16_t ps4operation::LowerBody::_mapPower(uint8_t v)  {
    int16_t trans = v - 128;
    return abs(trans) <= 8 ? 0 : trans * 2;
}

ps4operation::LowerBody::LowerBody(
    ssr::PinType dir1, ssr::PinType pwm1,
    ssr::PinType dir2, ssr::PinType pwm2,
    ssr::PinType dir3, ssr::PinType pwm3
) : PS4Operation(), _lowerBody(dir1, pwm1, dir2, pwm2, dir3, pwm3) {}

void ps4operation::LowerBody::begin() {
    _lowerBody.begin();
}

void ps4operation::LowerBody::operate(const ssr::PS4Value & value) {
    int16_t x = _mapPower(value.lstick.x);
    int16_t y = _mapPower(value.lstick.y);
    int16_t r = _mapPower(value.rstick.x);
    _lowerBody.twist(x / _sqrt2, y / _sqrt2, r / _sqrt2);
}
