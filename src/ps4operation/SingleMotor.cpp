/**
 * @file SingleMotor.cpp
 * @author H1rono (hronok66@gmail.com)
 * @brief include/ps4operation/SingleMotor.hppの実装
 * @date 2022-08-29
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#include "ps4operation/SingleMotor.hpp"

ps4operation::SingleMotor::SingleMotor(ssr::PinType dir, ssr::PinType pwm)
: PS4Operation(), _motorDriver(dir, pwm) {}

void ps4operation::SingleMotor::begin(int16_t power) {
    _motorDriver.begin(power);
}

void ps4operation::SingleMotor::operate(const ssr::PS4Value & value) {
    // value.lstick.x: 0 ~ 255
    // cut last 3 bit -> 0 ~ 248
    int16_t v = value.lstick.x & 0xf8;
    v -= 124;
    v *= 2;
    _motorDriver.setPower(v);
    #ifdef ps4operation_verbose
    char buffer[256] = "";
    char * ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[ps4operation::SingleMotor] set power %d"), v);
    Serial.println(buffer);
    #endif /* ps4operation_verbose */
}
