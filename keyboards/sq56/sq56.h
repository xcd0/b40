// Copyright 2023 xcd0 (@xcd0)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define NOP KC_NO

#define LAYOUT( \
K00, K01, K02, K03, K04, K05,             K50, K51, K52, K53, K54, K55, \
K10, K11, K12, K13, K14, K15,             K60, K61, K62, K63, K64, K65, \
K20, K21, K22, K23, K24, K25, ENC1, ENC3, K70, K71, K72, K73, K74, K75, \
K30, K31, K32, K33, K34, K35, ENC2, ENC4, K80, K81, K82, K83, K84, K85, \
          K42, K43, K44, K45,             K90, K91, K92, K93, \
                      ENC1U,               ENC3U,       \
               ENC2U, ENC1D, ENC2D, ENC4U, ENC3D, ENC4D \
  ) \
  { \
    { K00, K01, K02, K03, K04, K05 }, \
    { K10, K11, K12, K13, K14, K15 }, \
    { K20, K21, K22, K23, K24, K25 }, \
    { K30, K31, K32, K33, K34, K35 }, \
    { ENC1, ENC2, K42, K43, K44, K45 }, \
    { ENC1U, ENC1D, ENC2U, ENC2D, NOP, NOP }, \
    { K55, K54, K53, K52, K51, K50 }, \
    { K65, K64, K63, K62, K61, K60 }, \
    { K75, K74, K73, K72, K71, K70 }, \
    { K85, K84, K83, K82, K81, K80 }, \
    { ENC4, ENC3, K93, K92, K91, K90 },  \
    { ENC3U, ENC3D, ENC4U, ENC4D, NOP, NOP } \
  }
/*

    { K50, K51, K52, K53, K54, K55  }, \
    { K60, K61, K62, K63, K64, K65  }, \
    { K70, K71, K72, K73, K74, K75  }, \
    { K80, K81, K82, K83, K84, K85  }, \
    { K90, K91, K92, K93, NOP, NOP  }  \

 */
