# Toolchain
Toolchain for C programming on the TI CE calculators (TI-84 Plus CE / TI-83 Premium CE)

# Installation
1. Extract the .zip file in the lateset release (you should see a folder inside called 'CEdev')
   
**Note:** Place the CEdev folder somewhere close to your root directory, i.e. `C:\CEdev` and ensure **no spaces** in the path name for best results.

2. Add a user environment variable called `CEDEV`, pointing to the CEdev folder _(instructions on how to do that on: [Windows](http://www.computerhope.com/issues/ch000549.htm), [Mac](http://stackoverflow.com/a/7502061/378298), [Linux](http://unix.stackexchange.com/a/117470))_
3. Edit the system environment variable called `PATH` to append the `bin` folder in the CEdev folder (`CEdev/bin`) _(instructions on how to do that on: [Windows](http://www.computerhope.com/issues/ch000549.htm), [Mac](http://stackoverflow.com/a/7502061/378298), [Linux](http://unix.stackexchange.com/a/117470))_
4. If you are running under Linux or macOS, [wine](https://www.winehq.org/) is required to build. Usually using the absolute path to make.exe in the CEdev/bin directory works the best, i.e. 'wine ~/CEdev/make.exe'

Included you will find the [Standard CE C Libraries](https://github.com/CE-Programming/libraries/releases/latest). These perform efficient and easy support for graphics, file I/O, and keypad input. You can find examples in `CEdev/examples/library_examples`

For more information on how to use this toolchain, please see the documentation page:
https://ce-programming.github.io/documentation/
