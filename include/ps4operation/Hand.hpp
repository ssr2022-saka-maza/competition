/**
 * @file Hand.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief 把持機構を扱うOperation
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#pragma once

#ifndef PS4_OPERATION_HAND_HPP

/**
 * @brief ps4operation/Hand.hppがインクルードされていることを示すdefine
 */
#define PS4_OPERATION_HAND_HPP

#include <Arduino.h>
#include <ssr/SyncServo.hpp>
#include <ssr/PS4Operation.hpp>
#include <ps4operation/Resetable.hpp>

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {
    /**
     * @brief 把持機構を扱うOperation
     */
    class Hand : public ps4operation::Resetable {
    private:
        /**
         * @brief 制御する同期サーボ
         */
        ssr::SyncServo & _syncServo;

        /**
         * @brief とれる角度の最小値
         */
        const uint8_t _minAngle;

        /**
         * @brief とれる角度の最大値
         */
        const uint8_t _maxAngle;

        /**
         * @brief 現在の角度
         */
        float _angle;

    public:
        /**
         * @brief Construct a new Hand object
         * @param syncServo ssr::SyncServo & 制御する同期サーボ
         * @param minAngle uint8_t とれる角度の最小値
         * @param maxAngle uint8_t とれる角度の最大値
         */
        explicit Hand(ssr::SyncServo & syncServo, uint8_t minAngle = 60, uint8_t maxAngle = 120);

        // デフォルトコンストラクタ、コピーを禁止
        Hand() = delete;
        Hand(const Hand &) = delete;
        Hand & operator=(const Hand &) = delete;

        /**
         * @brief 初期化処理 全体のsetup()内で呼び出すこと
         * @param angle 最初の角度
         */
        void begin(uint8_t angle = 90);

        /**
         * @brief コントローラーのセンサー値でハンドを制御
         * @param value コントローラーのセンサー値
         * @details L1ボタンで開く、R2ボタンで閉じる
         */
        virtual void operate(const ssr::PS4Value & value) override;

        /**
         * @brief ハンドを閉じる
         */
        virtual void reset() override;
    }; // class Hand
} // namespace ps4operation

#endif /* PS4_OPERATION_HAND_HPP */
