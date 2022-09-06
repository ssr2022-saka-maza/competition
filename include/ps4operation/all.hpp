/**
 * @file all.hpp
 * @author H1rono (hronok66@gmail.com)
 * @brief ps4operation内のヘッダファイル全てをインクルードするファイル
 * @copyright Copyright (c) 2022 ssr2022-saka-maza
 */

#pragma once

#ifndef PS4_OPERATION_ALL_HPP

/**
 * @brief ps4operation/all.hppがインクルードされていることを示すdefine
 */
#define PS4_OPERATION_ALL_HPP

/**
 * @brief ssr::PS4Operationを継承したクラス群
 */
namespace ps4operation {}

#include "ps4operation/Log.hpp"
#include "ps4operation/LowerBody.hpp"
#include "ps4operation/Servo.hpp"
#include "ps4operation/SingleMotor.hpp"
#include "ps4operation/Solenoid.hpp"
#include "ps4operation/ForkLift.hpp"
#include "ps4operation/Hand.hpp"
#include "ps4operation/Reloader.hpp"

#endif /* PS4_OPERATION_ALL_HPP */
