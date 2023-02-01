#!/bin/sh

rm keyboards/b50/keymaps/via/keymap.c
cp  keyboards/b50/keymaps/default/keymap.c keyboards/b50/keymaps/via/keymap.c
make b50:default
make b50:via

#rm keyboards/s56/keymaps/via/keymap.c
#cp  keyboards/s56/keymaps/default/keymap.c keyboards/s56/keymaps/via/keymap.c
#make s56:default
#make s56:via

#rm keyboards/b40/keymaps/via/keymap.c
#cp  keyboards/b40/keymaps/default/keymap.c keyboards/b40/keymaps/via/keymap.c
#make b40:default
#make b40:via
