#include "ps4operation/Hand.hpp"

ps4operation::Hand::Hand(ssr::SyncServo & syncServo, uint8_t minAngle, uint8_t maxAngle)
: Resetable(), _syncServo(syncServo), _minAngle(minAngle), _maxAngle(maxAngle), _angle(0) {}

void ps4operation::Hand::begin(uint8_t angle) {
    _angle = max(_maxAngle, min(_minAngle, uint8_t(angle)));
    _syncServo.mirrored = true;
    _syncServo.write(uint8_t(_angle));
}

void ps4operation::Hand::operate(const ssr::PS4Value & value) {
    // _angle += (value.l1 - value.r1) / float(_maxAngle - _minAngle);
    _angle += (value.l1 - value.r1) / 3.0;
    _angle = max(_minAngle, min(_maxAngle, _angle));
    _syncServo.write(uint8_t(_angle));
    #ifdef ps4operation_verbose
    char buffer[256] = "";
    char * ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[ps4operation::Hand] current angle is "));
    dtostrf(_angle, 6, 2, ptr);
    Serial.println(buffer);
    #endif /* ps4operation_verbose */
}

void ps4operation::Hand::reset() {
    _angle = max(_minAngle, min(_maxAngle, _angle - 1));
    _syncServo.write(uint8_t(_angle));
}
