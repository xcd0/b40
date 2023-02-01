// Copyright 2023 xcd0 (@xcd0)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define NOP KC_NO

/*
#define LAYOUT( \
 K00, K01, K002, K03, K04,           K59, K58, K57, K56, K65, \
 K10, K11, K112, K13, K14,           K69, K68, K67, K76, K75, \
 K20, K21, K232, K23, K24,           K79, K78, K87, K86, K85, \
      K30, K341, K42, K43, K34, K89, K98, K97, K96, K95       \
  ) \
  { \
    { NOP, K01, K02, K03, K04, NOP, NOP, NOP, NOP, NOP }, \
    { K10, NOP, K12, K13, K14, NOP, NOP, NOP, NOP, NOP }, \
    { K20, K21, NOP, K23, K24, NOP, NOP, NOP, NOP, NOP }, \
    { K30, K31, K32, NOP, K34, NOP, NOP, NOP, NOP, NOP }, \
    { K40, K41, K42, K43, NOP, NOP, NOP, NOP, NOP, NOP }, \
    { NOP, NOP, NOP, NOP, NOP, NOP, K56, K57, K58, K59 }, \
    { NOP, NOP, NOP, NOP, NOP, K65, NOP, K67, K68, K69 }, \
    { NOP, NOP, NOP, NOP, NOP, K75, K76, NOP, K78, K79 }, \
    { NOP, NOP, NOP, NOP, NOP, K85, K86, K87, NOP, K89 }, \
    { NOP, NOP, NOP, NOP, NOP, K95, K96, K97, K98, NOP }  \
 }

// "cols": ["F7", "B1", "B3", "B2", "B6", "B5", "B4", "E6", "D7", "C6"],
// "cols": ["C6", "D7", "E6", "B4", "B5", "B6", "B2", "B3", "B1", "F7"],
// "cols": ["C6", "D7", "E6", "B4", "B5", "F7", "B1", "B3", "B2", "B6"],

*/

#define LAYOUT( \
 L07, L06, L05, L04, L03, L02, L01, L00,    R00, R01, R02, R03, R04, R05, R06, R07, \
 L17, L16, L15, L14, L13, L12, L11, L10,    R10, R11, R12, R13, R14, R15, R16, R17, \
 L27, L26, L25, L24, L23, L22, L21, L20,    R20, R21, R22, R23, R24, R25, R26, R27, \
                     L33, L32, L31, L30,    R30, R31, R32, R33                      \
  ) \
  { \
    { L00, L01, L02, L03, L04, L05, L06, L07 }, \
    { L10, L11, L12, L13, L14, L15, L16, L17 }, \
    { L20, L21, L22, L23, L24, L25, L26, L27 }, \
    { L30, L31, L32, L33, NOP, NOP, NOP, NOP }, \
    { R00, R01, R02, R03, R04, R05, R06, R07 }, \
    { R10, R11, R12, R13, R14, R15, R16, R17 }, \
    { R20, R21, R22, R23, R24, R25, R26, R27 }, \
    { R30, R31, R32, R33, NOP, NOP, NOP, NOP }, \
 }

/*
    { L07, L06, L05, L04, L03, L02, L01, L00 }, \
    { L17, L16, L15, L14, L13, L12, L11, L10 }, \
    { L27, L26, L25, L24, L23, L22, L21, L20 }, \
    { L37, L36, L35, L34, L33, L32, L31, L30 }, \
    { R07, R06, R05, R04, R03, R02, R01, R00 }, \
    { R17, R16, R15, R14, R13, R12, R11, R10 }, \
    { R27, R26, R25, R24, R23, R22, R21, R20 }, \
    { R37, R36, R35, R34, R33, R32, R31, R30 }, \
 */
