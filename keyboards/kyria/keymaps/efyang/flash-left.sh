#!/bin/sh
cp config.h config.h.tmp
echo "#define COMPILE_LEFT
$(cat config.h.tmp)" > config.h
qmk flash -kb kyria -km efyang -bl avrdude-split-left -e COMPILE_LEFT=yes
mv -f config.h.tmp config.h
rm config.h.tmp
