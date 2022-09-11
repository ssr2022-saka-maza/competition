#include <Arduino.h>
#include <Servo.h>
#include <ssr/PS4Controller.hpp>
#include <ps4operation/Log.hpp>
#include <ps4operation/Solenoid.hpp>
// #include <ps4operation/LowerBody.hpp>
#include <ps4operation/LowerBody_MovAve.hpp>
#include <ps4operation/ForkLift.hpp>
#include <ps4operation/Hand.hpp>
#include <ps4operation/Reloader.hpp>

#ifdef use_bluetooth
#warning build in bluetooth
ssr::PS4Controller_Bluetooth ps4Controller(true);
#else /* use_bluetooth */
ssr::PS4Controller_USB ps4Controller{};
#endif /* use_bluetooth */

ssr::SyncServo liftServo{}, handServo{}, reloadServo{};
ps4operation::Solenoid * solenoid = nullptr;

void setup() {
    Serial.begin(115200);
    if (ps4Controller.begin() == -1) {
        Serial.println(F("failed to initialize"));
        while (1);
    }
    /* log */
    // ps4Controller.addOperation(new ps4operation::Log());
    /* solenoid */
    solenoid = new ps4operation::Solenoid(A8, 1000);
    solenoid->begin();
    ps4Controller.addOperation(solenoid);
    /* lower body */
    // ps4operation::LowerBody * lowerBody = new ps4operation::LowerBody(6, 7, 4, 5, 2, 3);
    ps4operation::LowerBody_MovAve * lowerBody = new ps4operation::LowerBody_MovAve(6, 7, 4, 5, 2, 3);
    lowerBody->begin();
    ps4Controller.addOperation(lowerBody);
    /* fork lift */
    ps4operation::ForkLift * forkLift = new ps4operation::ForkLift(liftServo);
    liftServo.attach(23, 25);
    forkLift->begin(90);
    ps4Controller.addOperation(forkLift);
    /* hand */
    ps4operation::Hand * hand = new ps4operation::Hand(handServo, 70, 120);
    handServo.attach(27, 29);
    hand->begin();
    ps4Controller.addOperation(hand);
    /* reloader */
    ps4operation::Reloader * reloader = new ps4operation::Reloader(reloadServo, 0, 150);
    reloadServo.attach(31, 33);
    reloader->begin();
    ps4Controller.addOperation(reloader);
    /* PWM frequency */
    // pin:   7, 5, 3
    // timer: 4, 3, 3
    TCCR3B = (TCCR3B & 0b11111000) | 0x01; // Timer3 31.37255[kHz]
    TCCR4B = (TCCR4B & 0b11111000) | 0x01; // Timer4 31.37255[kHz]
    /* end of setup */
    Serial.println(F("start"));
}

void loop() {
    /* solenoid */
    solenoid->update();
    ps4Controller.update();
    if (!ps4Controller.connected()) {
        Serial.println(F("not connected"));
    }
}
