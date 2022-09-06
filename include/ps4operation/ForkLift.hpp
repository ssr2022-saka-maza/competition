/**
 * @file ForkLift.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief 昇降機構を扱うOperation
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef PS4_OPERATION_FORK_LIFT_HPP

/**
 * @brief ps4operation/ForkLift.hppがインクルードされていることを示すdefine
 */
#define PS4_OPERATION_FORK_LIFT_HPP

#include <Arduino.h>
#include <ssr/SyncServo.hpp>
#include <ssr/PS4Value.hpp>
#include <ssr/PS4Operation.hpp>

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {
    /**
     * @brief 昇降機構を扱うOperation
     */
    class ForkLift : public ssr::PS4Operation {
    private:
        /**
         * @brief 制御する同期サーボ
         */
        ssr::SyncServo & _syncServo;

        /**
         * @brief 現在の角度
         */
        float _angle;

    public:
        /**
         * @brief Construct a new Fork Lift object
         * @param syncServo 制御する同期サーボ
         */
        explicit ForkLift(ssr::SyncServo & syncServo);

        // デフォルトコンストラクタ、コピーを禁止
        ForkLift() = delete;
        ForkLift(const ForkLift &) = delete;
        ForkLift & operator=(const ForkLift &) = delete;

        /**
         * @brief 初期化処理 全体のsetup()内で呼び出すこと
         * @param angle 最初の角度
         */
        void begin(uint8_t angle = 0);

        /**
         * @brief コントローラーのセンサー値で昇降機構を制御
         * @param value コントローラーのセンサー値
         * @details 上ボタンで上昇、下ボタンで下降
         */
        virtual void operate(const ssr::PS4Value & value) override;
    }; // class ForkLift
} // namespace ps4operation

#endif /* PS4_OPERATION_FORK_LIFT_HPP */
