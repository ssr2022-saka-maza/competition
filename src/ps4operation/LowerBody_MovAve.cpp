#include "ps4operation/LowerBody_MovAve.hpp"

const float ps4operation::LowerBody_MovAve::_sqrt2 = sqrtf(2.0f);

float ps4operation::LowerBody_MovAve::_mapPower(uint8_t v) {
    int16_t trans = v - 128;
    return abs(trans) <= 8 ? 0 : static_cast<float>(trans) * _sqrt2;
}

ps4operation::LowerBody_MovAve::LowerBody_MovAve(
    ssr::PinType dir1, ssr::PinType pwm1,
    ssr::PinType dir2, ssr::PinType pwm2,
    ssr::PinType dir3, ssr::PinType pwm3,
    uint8_t movAveCount
) : Resetable(), _lowerBody(dir1, pwm1, dir2, pwm2, dir3, pwm3),
    _movAve_x(movAveCount), _movAve_y(movAveCount), _movAve_r(movAveCount) {}

void ps4operation::LowerBody_MovAve::begin() {
    _lowerBody.begin();
}

void ps4operation::LowerBody_MovAve::operate(const ssr::PS4Value & value) {
    _movAve_x.write(_mapPower(value.lstick.y));
    _movAve_y.write(_mapPower(value.lstick.x));
    _movAve_r.write(-_mapPower(value.rstick.x));
    float x = _movAve_x.read();
    float y = _movAve_y.read();
    float r = _movAve_r.read();
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

void ps4operation::LowerBody_MovAve::reset() {
    _movAve_x.write(0);
    _movAve_y.write(0);
    _movAve_r.write(0);
    float x = _movAve_x.read();
    float y = _movAve_y.read();
    float r = _movAve_r.read();
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
