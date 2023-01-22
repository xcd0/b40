#!/bin/sh
rm keyboards/b40/keymaps/via/keymap.c
cp  keyboards/b40/keymaps/default/keymap.c keyboards/b40/keymaps/via/keymap.c
make b40:default
make b40:via
