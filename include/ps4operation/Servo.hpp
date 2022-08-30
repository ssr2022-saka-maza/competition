/**
 * @file Servo.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief サーボモーター1つを扱うOperation
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#pragma once

#ifndef PS4_OPERATION_SERVO_HPP

/**
 * @file Servo.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief ps4operation/Servo.hppがインクルードされていることを示すdefine
 * @copyright Copyright (c) 2022
 */
#define PS4_OPERATION_SERVO_HPP

#include <Arduino.h>
#include <Servo.h>

#include <ssr/PinType.hpp>
#include <ssr/PS4Operation.hpp>

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {
    /**
     * @brief サーボモーターを扱うOperation
     */
    class Servo : public ssr::PS4Operation {
    private:
        /**
         * @brief 制御対象のサーボモーター
         */
        ::Servo & _servo;

        /**
         * @brief 現在の制御角度
         */
        float _angle;

    public:
        /**
         * @brief Construct a new Servo object
         * @param servo ::Servo & 制御するサーボモーター
         */
        Servo(::Servo & servo);

        // デフォルトコンストラクタ、コピーを禁止
        Servo() = delete;
        Servo(const Servo &) = delete;
        Servo & operator=(const Servo &) = delete;

        /**
         * @brief
         * @param value コントローラーのセンサー値
         */
        virtual void operate(const ssr::PS4Value & value) override;
    }; // class Servo
} // namespace ps4operation

#endif /* PS4_OPERATION_SERVO_HPP */
