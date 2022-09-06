#include "ps4operation/ForkLift.hpp"

ps4operation::ForkLift::ForkLift(ssr::SyncServo & syncServo)
: _syncServo(syncServo), _angle(0) {}

void ps4operation::ForkLift::begin(uint8_t angle) {
    _angle = angle;
    _syncServo.mirrored = true;
    _syncServo.write(angle);
}

void ps4operation::ForkLift::operate(const ssr::PS4Value & value) {
    _angle += value.up / 3.0 - value.down / 3.0;
    _syncServo.write(int(_angle));
}
