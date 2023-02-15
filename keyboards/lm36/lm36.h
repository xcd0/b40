// Copyright 2023 xcd0 (@xcd0)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define NOP KC_NO

#define LAYOUT( \
 K10, K01, K02, K03, K04,  K59, K58, K57, K56, K65, \
 K20, K21, K12, K13, K14,  K69, K68, K67, K76, K75, \
 K30, K31, K32, K23, K24,  K79, K78, K87, K86, K85, \
      K41, K42, K43, K34,  K89, K98, K97, K96       \
  ) \
 { \
    { NOP, K01, K02, K03, K04, NOP, NOP, NOP, NOP, NOP }, \
    { K10, NOP, K12, K13, K14, NOP, NOP, NOP, NOP, NOP }, \
    { K20, K21, NOP, K23, K24, NOP, NOP, NOP, NOP, NOP }, \
    { K30, K31, K32, NOP, K34, NOP, NOP, NOP, NOP, NOP }, \
    { NOP, K41, K42, K43, NOP, NOP, NOP, NOP, NOP, NOP }, \
    { NOP, NOP, NOP, NOP, NOP, NOP, K56, K57, K58, K59 }, \
    { NOP, NOP, NOP, NOP, NOP, K65, NOP, K67, K68, K69 }, \
    { NOP, NOP, NOP, NOP, NOP, K75, K76, NOP, K78, K79 }, \
    { NOP, NOP, NOP, NOP, NOP, K85, K86, K87, NOP, K89 }, \
    { NOP, NOP, NOP, NOP, NOP, NOP, K96, K97, K98, NOP }  \
 }
