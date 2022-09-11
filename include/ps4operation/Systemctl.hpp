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

#include <ps4operation/Resetable.hpp>

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {
    class Systemctl : public ps4operation::Resetable {
    private:

    public:

    }; // class Systemctl
} // namespace ps4operation

#endif /* PS4_OPERATION_SYSTEMCTL_HPP */
