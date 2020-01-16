#!/bin/bash

# this script currently only runs on linux.

build_fasmg () {
    .tmp/fasmg/fasmg .tmp/fasmg/source/$1/$3/fasmg.asm $1/$2
    chmod -x $1/$2
}

cd fasmg-ez80
git pull origin master
cd ..
mkdir -p .tmp
wget --no-verbose https://flatassembler.net/fasmg.zip --output-document=.tmp/fasmg.zip
unzip -od .tmp/fasmg .tmp/fasmg.zip
chmod +x .tmp/fasmg/fasmg

build_fasmg linux   fasmg
build_fasmg windows fasmg.exe
build_fasmg macos   fasmg     x64

rm -rf .tmp

