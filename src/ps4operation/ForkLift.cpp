#include "ps4operation/ForkLift.hpp"

ps4operation::ForkLift::ForkLift(ssr::SyncServo & syncServo)
: PS4Operation(), _syncServo(syncServo), _angle(0) {}

void ps4operation::ForkLift::begin(uint8_t angle) {
    _angle = angle;
    _syncServo.mirrored = true;
    _syncServo.write(angle);
}

void ps4operation::ForkLift::operate(const ssr::PS4Value & value) {
    _angle += value.up / 3.0 - value.down / 3.0;
    _angle =
        _angle <=   0 ?   0 :
        _angle >= 180 ? 180 :
        _angle;
    _syncServo.write(int(_angle));
    #ifdef ps4operation_verbose
    char buffer[256] = "";
    char * ptr = buffer;
    ptr += snprintf_P(ptr, 200, PSTR("[ps4operation::ForkLift] current angle is "));
    dtostrf(_angle, 6, 2, ptr);
    Serial.println(buffer);
    #endif /* ps4operation_verbose */
}
