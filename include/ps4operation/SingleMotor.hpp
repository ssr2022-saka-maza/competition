/**
 * @file SingleMotor.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief モータードライバ MD10C R3(CYTRON TECHNOLOGY)1つを扱うOperation
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#pragma once

#ifndef PS4_OPERATION_SINGLE_MOTOR_HPP

/**
 * @brief ps4operation/SingleMotor.hppがincludeされていることを示すdefine
 */
#define PS4_OPERATION_SINGLE_MOTOR_HPP

#include <ssr/MotorDriver.hpp>
#include <ssr/PS4Operation.hpp>

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {
    /**
     * @brief モータードライバ MD10C R3(CYTRON TECHNOLOGY)1つを扱うOperation
     */
    class SingleMotor : public ssr::PS4Operation {
    private:
        /**
         * @brief モータードライバ本体
         */
        ssr::MotorDriver _motorDriver;

    public:
        /**
         * @brief Construct a new Single Motor object
         * @param dir モータードライバのdirピン
         * @param pwm モータードライバのpwmピン
         */
        SingleMotor(ssr::PinType dir, ssr::PinType pwm);

        /**
         * @brief 初期化処理 全体のsetup()で必ず呼び出すこと
         * @param power モーターに流すパワーの初期値
         */
        void begin(int16_t power = 0);

        /**
         * @brief センサー値からパワーを出力する
         * @param value const ssr::PS4Value & コントローラーのセンサー値
         */
        virtual void operate(const ssr::PS4Value & value) override;
    }; // class SingleMotor : ssr::PS4Operation
} // namespace ps4operation

#endif /* PS4_OPERATION_SINGLE_MOTOR_HPP */