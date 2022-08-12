#pragma once

#ifndef PS4_LOG_OPERATION_HPP
#define PS4_LOG_OPERATION_HPP

#include <Arduino.h>
#include <ssr/PS4Operation.hpp>

// ssr::PS4Operationを継承したクラス群
namespace ps4operation {

// センサー値のログをシリアルに流すOperation
class Log : public ssr::PS4Operation {
public:
    /**
     * @brief センサー値のログを出力する
     * @param value const ssr::PS4Value & コントローラーのセンサー値
     */
    virtual void operate(const ssr::PS4Value & value) override;
}; // class Log : public ssr::PS4Operation

} // namespace ps4operation

#endif /* PS4_LOG_OPERATION_HPP */
