#include <Arduino.h>
#include <Servo.h>
#include <ssr/PS4.hpp>
#include <ssr/PS4Controller.hpp>
#include <ps4operation/Log.hpp>
#include <ps4operation/SingleMotor.hpp>
#include <ps4operation/Solenoid.hpp>
#include <ps4operation/LowerBody.hpp>
#include <ps4operation/Servo.hpp>

Servo servo;
//ssr::PS4Controller_Bluetooth ps4Controller(true);
ssr::PS4Controller_USB ps4Controller{};
ps4operation::SingleMotor * motor = nullptr;
ps4operation::Solenoid * solenoid = nullptr;
ps4operation::LowerBody * lowerBody = nullptr;

void setup() {
    Serial.begin(115200);
    if (ps4Controller.begin() == -1) {
        Serial.println(F("failed to initialize"));
        while (1);
    }
    /* log */
    ps4Controller.addOperation(new ps4operation::Log());
    /* motor */
    motor = new ps4operation::SingleMotor(3, 4);
    ps4Controller.addOperation(motor);
    motor->begin();
    /* solenoid */
    solenoid = new ps4operation::Solenoid(7, 100);
    solenoid->begin();
    ps4Controller.addOperation(solenoid);
    /* lowerbody */
    lowerBody = new ps4operation::LowerBody(6, 7, 4, 5, 2, 3);
    lowerBody->begin();
    ps4Controller.addOperation(lowerBody);
    /* servo */
    ps4operation::Servo * servoOperation = new ps4operation::Servo(servo);
    ps4Controller.addOperation(servoOperation);
    servo.attach(23);
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
