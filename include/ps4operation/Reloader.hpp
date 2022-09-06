/**
 * @file Reloader.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief 把持機構を扱うOperation
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#pragma once

#ifndef PS4_OPERATION_RELOADER_HPP

/**
 * @brief ps4operation/Reloader.hppがインクルードされていることを示すdefine
 */
#define PS4_OPERATION_RELOADER_HPP

#include <Arduino.h>
#include <ssr/SyncServo.hpp>
#include <ssr/PS4Operation.hpp>

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {
    class Reloader : public ssr::PS4Operation {
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

        /**
         * @brief 角度の差分 -1, 0, 1のどれか
         */
        int8_t _dAngle;

    public:
        /**
         * @brief Construct a new Reloader object
         * @param syncServo ssr::SyncServo & 制御する同期サーボ
         * @param minAngle uint8_t とれる角度の最小値
         * @param maxAngle uint8_t とれる角度の最大値
         */
        explicit Reloader(ssr::SyncServo & syncServo, uint8_t minAngle = 0, uint8_t maxAngle = 150);

        // デフォルトコンストラクタ、コピーを禁止
        Reloader() = delete;
        Reloader(const Reloader &) = delete;
        Reloader & operator=(const Reloader &) = delete;

        /**
         * @brief 初期化処理 全体のsetup()内で呼び出すこと
         * @param angle 最初の角度
         */
        void begin(uint8_t angle = 0);

        /**
         * @brief コントローラーのセンサー値で装填をコントロール
         * @param value コントローラーのセンサー値
         * @details 三角ボタンで装填、バツボタンで戻る
         */
        virtual void operate(const ssr::PS4Value & value) override;
    };
} // namespace ps4operation

#endif /* PS4_OPERATION_RELOADER_HPP */
