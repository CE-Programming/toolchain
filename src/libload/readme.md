## LibLoad
LibLoad is simply a loader makes it possible to share libraries between different programs, and enforces library versioning.

## Installing
To install LibLoad on your calculator, simply send `LibLoad.8xv` to your calcualtor using TI Connect CE or TILP.

## Download
You can find the latest version of LibLoad here: https://github.com/CE-Programming/libraries/releases/latest

### Building LibLoad
Download `flat assembler g` available [here](https://flatassembler.net/download.php) near the bottom of the page.

Then execute:

	fasmg libload.asm libload.8xv
