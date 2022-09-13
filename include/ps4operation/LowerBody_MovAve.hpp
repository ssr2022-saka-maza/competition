/**
 * @file LowerBody_MovAve.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief 移動平均でモーター値を更新する足回り
 * @version 0.1
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#pragma once

#ifndef PS4_OPERATION_LOWER_BODY_MOV_AVE_HPP

/**
 * @brief ps4operation/LowerBody_MovAve.hppがインクルードされていることを示すdefine
 */
#define PS4_OPERATION_LOWER_BODY_MOV_AVE_HPP

#include <Arduino.h>
#include <ssr/MovingAverage.hpp>
#include <ssr/LowerBody.hpp>
#include <ssr/PS4Operation.hpp>
#include <ps4operation/Resetable.hpp>

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {
    /**
     * @brief 足回りを操作するPS4Operation
     */
    class LowerBody_MovAve : public ps4operation::Resetable {
    private:
        /**
         * @brief 扱う足回り
         */
        ssr::LowerBody _lowerBody;

        /**
         * @brief x軸方向の移動平均
         */
        ssr::MovingAverage<float> _movAve_x;

        /**
         * @brief y軸方向の移動平均
         */
        ssr::MovingAverage<float> _movAve_y;

        /**
         * @brief 回転方向の移動平均
         */
        ssr::MovingAverage<float> _movAve_r;

        /**
         * @brief ルート２
         */
        static const float _sqrt2;

        /**
         * @brief センサー値からパワーの出力に適した値に変換する
         * @param v センサー値 0~255
         * @return constexpr int16_t 適した出力パワー
         */
        static float _mapPower(uint8_t v);

    public:
        /**
         * @brief Construct a new Lower Body object
         * @param dir1 モーター1のDIRピン
         * @param pwm1 モーター1のPWMピン
         * @param dir2 モーター2のDIRピン
         * @param pwm2 モーター2のPWMピン
         * @param dir3 モーター3のDIRピン
         * @param pwm3 モーター3のPWMピン
         * @param movAveCount 移動平均のサンプル数
         */
        LowerBody_MovAve(
            ssr::PinType dir1, ssr::PinType pwm1,
            ssr::PinType dir2, ssr::PinType pwm2,
            ssr::PinType dir3, ssr::PinType pwm3,
            uint8_t movAveCount = 128
        );

        /**
         * @brief 初期化処理 全体のsetup()内で呼び出すこと
         */
        void begin();

        /**
         * @brief 足回りを操作する
         * @param value コントローラーのセンサー値
         */
        virtual void operate(const ssr::PS4Value & value) override;

        /**
         * @brief 足回りを停止する
         */
        virtual void reset() override;
    }; // class LowerBody_MovAve
} // namespace ps4operation

#endif /* PS4_OPERATION_LOWER_BODY_MOV_AVE_HPP */
