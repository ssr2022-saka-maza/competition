#include "ps4operation/Solenoid.hpp"

ps4operation::Solenoid::Solenoid(ssr::PinType pin, uint8_t duration)
: PS4Operation(), _solenoid(pin), _lastFireTime(0), _fired(false), _duration(duration) {}

void ps4operation::Solenoid::begin() {
    _solenoid.begin();
}

void ps4operation::Solenoid::update() {
    if (!_fired) return;
    if (millis() - _lastFireTime < _duration) return;
    _solenoid.update();
    _fired = false;
}

void ps4operation::Solenoid::operate(const ssr::PS4Value & value) {
    if (!value.circle) return;
    _solenoid.fire();
    _lastFireTime = millis();
    _fired = true;
    #ifdef ps4operation_verbose
    Serial.println(F("fire"));
    #endif /* ps4operation_verbose */
}
