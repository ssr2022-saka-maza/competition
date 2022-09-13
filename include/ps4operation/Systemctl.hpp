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
    class Systemctl : public ps4operation::Resetable {
    private:
        enum class State {
            start,
            stop,
            automate,
        };

        uint8_t _childCount;

        Resetable ** _children;

        State _state;

        ssr::PS4Value _lastValue;

        uint64_t _stateUpdateTime;

    public:
        const uint8_t childCapacity;

        Systemctl(uint8_t childCapacity);

        ~Systemctl();

        void reset() noexcept override;

        void addChild(Resetable * child) noexcept;

        void removeChild(Resetable * child) noexcept;

        virtual void operate(const ssr::PS4Value & value) noexcept override;

    }; // class Systemctl
} // namespace ps4operation

#endif /* PS4_OPERATION_SYSTEMCTL_HPP */
