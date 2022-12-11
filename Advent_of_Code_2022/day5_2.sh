#!/bin/bash

board=()
for i in `seq 1 9`
do
    board+=""
done

# 標準入力から1行読み取る
while read line; do
    # endと入力された場合はプログラムを終了する
    if [ "$line" = "end" ]; then
        break
    fi

    IFS=' '
    set -- $line

    if [ "$1" == "move" ]; then
        # echo "${board[@]}"
        # echo "$2 $4 $6"
        # $2個、$4から、$6へ
        len=${#board[$4-1]}
        # echo "${len-$2+1}"
        tmp=${board[$4-1]:len-$2:$2}
        # tmp=$(echo $tmp | rev)
        # echo "tmp: $tmp"
        board[$6-1]=${board[$6-1]}$tmp
        board[$4-1]=${board[$4-1]:0:len-$2}
    elif [ "${1:0:1}" == "[" ]; then
        for i in 1 5 9 13 17 21 25 29 33
        do
            # echo "${line:i:1}"
            # echo "${board[i/4]}"
            if [ ${line:i:1} <> " " ]; then
                board[i/4]=${line:i:1}${board[i/4]}
            fi
        done
    fi
done

# 配列の各要素をループ処理する
for i in "${board[@]}"; do
  # 最後の文字を取り出す
  c=${i: -1}
  # 取り出した文字を標準出力する
  echo -n $c
done
# 改行する
echo ""
