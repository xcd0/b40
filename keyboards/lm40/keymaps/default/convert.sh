#!/bin/bash


# keymap.cをprk firmwareのレイヤー表記に変換する
# prkにはLAYOUTマクロに相当する機能がない

filename=keymap.c

# LAYOUT(を含む行番号を得る
lines=`sed -n '/LAYOUT(/=' $filename`
echo layer define lines = $lines

# 上で取得した行番号の個数を得る
numOfLayer=`echo "$lines" | wc -l`
#echo numOfLayer = $numOfLayer

# ),で終わる行の行番号を得る
endlines=`sed -n "/),$/=" $filename`
# )で終わる行の行番号を得る
# マクロの閉じ括弧を無視したいので最後のレイヤー定義より後ろの行で、"  )\n"のある行を探す
n=`echo "$lines" | sed -n ${numOfLayer}P` # 最後のレイヤー定義開始行番号
nn=`cat $filename | awk "NR>=$n {print}" | sed -n "/  )$/="` # そこから閉じ括弧のある行までの行数
endlines="$endlines $(($n + $nn - 1))" # 最後のレイヤー定義開始行番号 + そこから閉じ括弧のある行までの行数
echo endlines = $endlines

for ((i=1;i<=$numOfLayer;i++)); do
echo -- i = $i ---
n=`echo "$lines" | sed -n ${i}P`
s=$(($n + 1))
n=`echo "$endlines" | sed -n ${i}P`
e=$(($n - 1))

echo s = $s, e = $e

cat $filename | awk "NR==$s,NR==$e {print}"
done
