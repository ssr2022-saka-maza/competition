/**
 * @file Systemctl.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief Start/Stopボタン
 * @version 0.1
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#pragma once

#ifndef PS4_OPERATION_SYSTEMCTL_HPP

/**
 * @brief ps4operation/Systemctl.hppがインクルードされていることを示すdefine
 */
#define PS4_OPERATION_SYSTEMCTL_HPP

#include <Arduino.h>
#include <ssr/PS4Operation.hpp>
#include <ps4operation/Resetable.hpp>

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {
    /**
     * @brief Start/Stop/自動装填ボタン
     */
    class Systemctl : public ps4operation::Resetable {
    private:
        /**
         * @brief 状態の種類
         */
        enum class State {
            /**
             * @brief 動作中
             */
            moving,
            /**
             * @brief 停止中
             */
            stop,
            /**
             * @brief 自動装填中
             */
            automate,
        }; // enum class State

        /**
         * @brief 制御するps4operation::Resetableの数
         */
        uint8_t _childCount;

        /**
         * @brief 制御するps4operation::Resetableの配列
         */
        Resetable ** _children;

        /**
         * @brief 状態
         */
        State _state;

        /**
         * @brief 自動装填の間隔
         */
        ssr::PS4Value _lastValue;

        /**
         * @brief 最後にstateが変更された時刻[msec]
         */
        uint64_t _stateUpdateTime;

    public:
        /**
         * @brief 制御できるps4operation::Resetableの最大数
         */
        const uint8_t childCapacity;

        /**
         * @brief コンストラクタ
         * @param childCapacity 制御できるps4operation::Resetableの最大数
         */
        explicit Systemctl(uint8_t childCapacity = 16);

        /**
         * @brief デストラクタ
         */
        ~Systemctl();

        // コピーコンストラクタを禁止
        Systemctl(const Systemctl &) = delete;
        // コピー代入演算子を禁止
        Systemctl & operator=(const Systemctl &) = delete;
        // ムーブコンストラクタを許可
        Systemctl(Systemctl &&) = default;
        // ムーブ代入演算子を許可
        Systemctl & operator=(Systemctl &&) = default;

        /**
         * @brief 初期化
         */
        void reset() noexcept override;

        /**
         * @brief ps4operation::Resetableを追加する
         * @param child 追加するps4operation::Resetable
         */
        void addChild(Resetable * child) noexcept;

        /**
         * @brief ps4operation::Resetableを削除する
         * @param child 削除するps4operation::Resetable
         */
        void removeChild(Resetable * child) noexcept;

        /**
         * @brief コントローラーの入力を処理する
         * @param value コントローラーの入力
         */
        virtual void operate(const ssr::PS4Value & value) noexcept override;
    }; // class Systemctl
} // namespace ps4operation

#endif /* PS4_OPERATION_SYSTEMCTL_HPP */
