#include <Arduino.h>
#include <Servo.h>
#include <ssr/PS4Controller.hpp>
#include <ps4operation/Log.hpp>
#include <ps4operation/Solenoid.hpp>
#include <ps4operation/LowerBody.hpp>
#include <ps4operation/ForkLift.hpp>
#include <ps4operation/Hand.hpp>
#include <ps4operation/Reloader.hpp>

#ifdef use_bluetooth
#warning build in bluetooth
ssr::PS4Controller_Bluetooth ps4Controller(true);
#else /* bluetooth */
ssr::PS4Controller_USB ps4Controller{};
#endif /* bluetooth */

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
    solenoid = new ps4operation::Solenoid(A8, 100);
    solenoid->begin();
    ps4Controller.addOperation(solenoid);
    /* lowerbody */
    // ps4operation::LowerBody * lowerBody = new ps4operation::LowerBody(6, 7, 4, 5, 2, 3);
    // lowerBody->begin();
    // ps4Controller.addOperation(lowerBody);
    /* fork lift */
    ps4operation::ForkLift * forkLift = new ps4operation::ForkLift(liftServo);
    liftServo.attach(23, 25);
    forkLift->begin(90);
    ps4Controller.addOperation(forkLift);
    /* hand */
    ps4operation::Hand * hand = new ps4operation::Hand(handServo, 60, 120);
    handServo.attach(27, 29);
    hand->begin();
    ps4Controller.addOperation(hand);
    /* reloader */
    ps4operation::Reloader * reloader = new ps4operation::Reloader(reloadServo, 0, 150);
    reloadServo.attach(31, 33);
    reloader->begin();
    ps4Controller.addOperation(reloader);
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
