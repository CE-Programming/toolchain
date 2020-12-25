#!/bin/bash

cd fasmg-ez80
git checkout main
git pull origin main
cd ..
mkdir -p .tmp
wget --no-verbose https://flatassembler.net/$(wget --no-verbose https://flatassembler.net/download.php --output-document=- | grep --only-matching --max-count=1 fasmg\\.[0-9a-z]\\+\.zip) --output-document=.tmp/fasmg.zip
unzip -od .tmp/fasmg .tmp/fasmg.zip
chmod +x .tmp/fasmg/fasmg.x64

.tmp/fasmg/fasmg.x64 .tmp/fasmg/source/linux/x64/fasmg.asm linux/fasmg
.tmp/fasmg/fasmg.x64 .tmp/fasmg/source/windows/fasmg.asm windows/fasmg.exe
.tmp/fasmg/fasmg.x64 .tmp/fasmg/source/macos/x64/fasmg.asm macos/fasmg

chmod +x windows/fasmg.exe
chmod +x macos/fasmg
chmod +x linux/fasmg

rm -rf .tmp
