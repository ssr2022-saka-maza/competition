#include "ps4operation/Reloader.hpp"

ps4operation::Reloader::Reloader(ssr::SyncServo & syncServo, uint8_t minAngle, uint8_t maxAngle)
: Resetable(), _syncServo(syncServo), _minAngle(minAngle), _maxAngle(maxAngle), _angle(0), _dAngle(0) {}

void ps4operation::Reloader::begin(uint8_t angle) {
    _angle = min(_maxAngle, max(_minAngle, angle));
    _syncServo.mirrored = true;
    _syncServo.write(angle);
}

void ps4operation::Reloader::operate(const ssr::PS4Value & value) {
    int8_t d = value.triangle - value.cross;
    if (d != 0) _dAngle = d;
    _angle += _dAngle / 3.0;
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

void ps4operation::Reloader::reset() {
    _angle = max(_minAngle, min(_maxAngle, _angle - 1));
    _syncServo.write(uint8_t(_angle));
}
