#!/bin/bash
CC_ARGS_="-llua5.3 -lpthread"
EXE_NAME="ceu_test"
echo $CEU_DIR #set this in bashrc
CEU_SRC=$PWD/clock_gen.ceu
ceu --pre --pre-input=$CEU_SRC --pre-args=\"-I.$CEU_DIR/include\"                \
	        --ceu --ceu-features-os=true --ceu-features-pool=true --ceu-features-thread=true --ceu-features-dynamic=true --ceu-err-unused=pass --ceu-features-async=true\
		    --env --env-types=$CEU_DIR/env/types.h --env-threads=$CEU_DIR/env/threads.h --env-main=$CEU_DIR/env/main.c --env-output=tmp/_ceu_app.c\
            --cc --cc-args="$CC_ARGS_" --cc-output=tmp/$EXE_NAME;

if [ "$1" == "run" ]
then
./tmp/$EXE_NAME
fi