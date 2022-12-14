/**
 * @file LowerBody.cpp
 * @author H1rono (hronok66@gmail.com)
 * @brief include/ps4operation/LowerBody.hppの実装
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#include "ps4operation/LowerBody.hpp"

const float ps4operation::LowerBody::_sqrt2 = sqrtf(2.0f);

float ps4operation::LowerBody::_mapPower(uint8_t v)  {
    int16_t trans = v - 128;
    return abs(trans) <= 8 ? 0 : float(trans) * _sqrt2;
}

ps4operation::LowerBody::LowerBody(
    ssr::PinType dir1, ssr::PinType pwm1,
    ssr::PinType dir2, ssr::PinType pwm2,
    ssr::PinType dir3, ssr::PinType pwm3
) : Resetable(), _lowerBody(dir1, pwm1, dir2, pwm2, dir3, pwm3) {}

void ps4operation::LowerBody::begin() {
    _lowerBody.begin();
}

void ps4operation::LowerBody::operate(const ssr::PS4Value & value) {
    float x = _mapPower(value.lstick.y);
    float y = _mapPower(value.lstick.x);
    float r = -_mapPower(value.rstick.x);
    #ifdef ps4operation_verbose
    char buffer[256] = "";
    char * ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[ps4operation::LowerBody] twist "));
    dtostrf(x, 6, 2, ptr); ptr += 6;
    ptr[0] = ','; ptr[1] = ' '; ptr += 2;
    dtostrf(y, 6, 2, ptr); ptr += 6;
    ptr[0] = ','; ptr[1] = ' '; ptr += 2;
    dtostrf(r, 6, 2, ptr); ptr += 6;
    Serial.println(buffer);
    #ifndef SSR_VERBOSE
    #define ndef_SSR_VERBOSE
    #define SSR_VERBOSE
    #endif /* SSR_VERBOSE */
    #endif /* ps4operation_verbose */
    _lowerBody.twist(x, y, r);
    #ifdef ps4operation_verbose
    #ifdef ndef_SSR_VERBOSE
    #undef SSR_VERBOSE
    #undef ndef_SSR_VERBOSE
    #endif /* ndef_SSR_VERBOSE */
    #endif /* ps4operation_verbose */
}

void ps4operation::LowerBody::reset() {
    _lowerBody.twist(0, 0, 0);
}
