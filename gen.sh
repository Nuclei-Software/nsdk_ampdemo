#!/bin/env bash

LINUXSDK=${1:-~/workspace/software/nuclei-linux-sdk}
SOC=${2:-evalsoc}

AMPDIR=$LINUXSDK/conf/$SOC/amp

echo "Generate amp binaries for SOC=$SOC, linux sdk $LINUXSDK"

for i in $(seq 1 7)
do
    make SOC=$SOC BOOT_HARTID=$i SILENT=1 clean bin
    echo "Copy ampdemo.bin -> $AMPDIR/amp_c$i.bin"
    cp -f ampdemo.bin $AMPDIR/amp_c$i.bin
done
