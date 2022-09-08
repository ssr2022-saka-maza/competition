/**
 * @file Resetable.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief 初期状態つきのOperation
 * @version 0.1
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#pragma once

#ifndef PS4_OPERATION_RESETABLE_HPP

/**
 * @brief ps4operation/Resetable.hpp
 */
#define PS4_OPERATION_RESETABLE_HPP

#include <ssr/PS4Operation.hpp>

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {
    /**
     * @brief 初期状態つきのOperation
     */
    class Resetable : public ssr::PS4Operation {
    public:
        virtual void reset() = 0;
    }; // class Resetable
} // namespace ps4operation

#endif /* PS4_OPERATION_RESETABLE_HPP */
