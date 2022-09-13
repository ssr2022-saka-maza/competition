/**
 * @file Solenoid.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief ソレノイド用のPS4Operation
 * @version 0.1
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef PS4_OPERATOR_SOLENOID_HPP

/**
 * @brief ps4operation/Solenoid.hppがインクルードされていることを示すdefine
 */
#define PS4_OPERATOR_SOLENOID_HPP

#include <ssr/PS4Operation.hpp>
#include <ssr/Solenoid.hpp>
#include <ps4operation/Resetable.hpp>

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {
    /**
     * @brief ソレノイドの用のPS4Operation
     */
    class Solenoid : public ps4operation::Resetable {
    private:
        /**
         * @brief 扱うソレノイド
         */
        ssr::Solenoid _solenoid;

        /**
         * @brief 最後に発射した時間 millis()の値
         */
        uint32_t _lastFireTime;

        /**
         * @brief 発射したフラグ 発射直後はtrue
         */
        bool _fired;

        /**
         * @brief パルス幅 単位はms
         */
        const uint16_t _duration;

    public:
        /**
         * @brief 初期化子
         * @param pin ssr::PinType ソレノイドを繋げたピン
         * @param duration uint8_t パルス幅 単位はms デフォルトは50
         */
        Solenoid(ssr::PinType pin, uint16_t duration = 50);

        /**
         * @brief ソレノイドのセットアップ
         * @warning 全体のsetupで呼ぶこと
         */
        void begin();

        /**
         * @brief ソレノイドの状態更新
         * @warning 全体のloopで呼ぶこと
         */
        void update();

        /**
         * @brief センサー値からソレノイドの操作を行う
         * @param value const ssr::PS4Value & コントローラーのセンサー値
         * @note 丸ボタンで発火する設定になってる 現在
         */
        virtual void operate(const ssr::PS4Value & value) override;

        /**
         * @brief リセット
         */
        virtual void reset() override;
    }; // class Solenoid
} // namespace ps4operator

#endif /* PS4_OPERATOR_SOLENOID_HPP */