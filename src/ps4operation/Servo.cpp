/**
 * @file Servo.cpp
 * @author H1rono (hronok66@gmail.com)
 * @brief include/ps4operation/Servo.hppの実装
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#include "ps4operation/Servo.hpp"

ps4operation::Servo::Servo(::Servo & servo)
: PS4Operation(), _servo(servo), _angle(0) {}

void ps4operation::Servo::operate(const ssr::PS4Value & value) {
    float v = -value.l2 / 768.0 + value.r2 / 768.0;
    _angle = max(0, min(180, _angle + v));
    _servo.write(int(_angle));
    // Serial.println(_angle);
}
