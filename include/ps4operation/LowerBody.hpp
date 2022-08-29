/**
 * @file LowerBody.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief 足回りを操作するOperation
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#pragma once

#include <ssr/LowerBody.hpp>
#include <ssr/PS4Operation.hpp>

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {
    /**
     * @brief 足回りを操作するPS4Operation
     */
    class LowerBody : public ssr::PS4Operation {
    private:
        /**
         * @brief 扱う足回り
         */
        ssr::LowerBody _lowerBody;

        /**
         * @brief ルート２
         */
        static constexpr float _sqrt2 = float(2);

        /**
         * @brief センサー値からパワーの出力に適した値に変換する
         * @param v センサー値 0~255
         * @return constexpr int16_t 適した出力パワー
         */
        static int16_t _mapPower(uint8_t v);

    public:
        /**
         * @brief Construct a new Lower Body object
         * @param dir1 モーター1のDIRピン
         * @param pwm1 モーター1のPWMピン
         * @param dir2 モーター2のDIRピン
         * @param pwm2 モーター2のPWMピン
         * @param dir3 モーター3のDIRピン
         * @param pwm3 モーター3のPWMピン
         */
        LowerBody(
            ssr::PinType dir1, ssr::PinType pwm1,
            ssr::PinType dir2, ssr::PinType pwm2,
            ssr::PinType dir3, ssr::PinType pwm3
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
    }; // class LowerBody
} // ps4operation
