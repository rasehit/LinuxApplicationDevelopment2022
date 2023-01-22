#!/bin/sh

temp1=$(mktemp)
temp2=$(mktemp)
delay=$1

pos=0
mpos=0
line=0
sclines=$(tput lines)
sccols=$(tput cols)

cat | od -v -t x1 -An | tr -d ' \n' > $temp1

while read -n 2 char
do 
    if [ "${char}" = '0a' ]
    then
        pos=0
        line=$(($line+1))
        continue
    fi

    if [ "${char}" = '20' ]
    then
        pos=$(($pos+1))
        continue
    fi

    pos=$(($pos+1))

    if ((pos > mpos))
    then 
        mpos=$pos
    fi
    echo $char $pos $line >> $temp2
done < $temp1

cat $temp2 | shuf > $temp1

sclines=$(($sclines/2-$line/2))
sccols=$(($sccols/2-$mpos/2))

tput clear
while read -r char tpos tline
do 
    if [ $tline ]
    then
        tput cup $(($sclines+$tline)) $(($sccols+$tpos))
        echo "\x${char}"
        sleep $delay
    fi
done < $temp1

tput cup $(($sclines+$line+1)) 0

rm $temp1
rm $temp2