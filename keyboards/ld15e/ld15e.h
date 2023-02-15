// Copyright 2023 xcd0 (@xcd0)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define NOP KC_NO

#define LAYOUT( \
 K00, K01, K02, K03, \
 K10, K11, K12, K13,   ENC, \
 K20, K21, K22, K23, \
      K31, K32, K33  \
  ) \
  { \
    { K00, K01, K02, K03 }, \
    { K10, K11, K12, K13 }, \
    { K20, K21, K22, K23 }, \
    { ENC, K31, K32, K33 }  \
 }

