Requires the Ceu language: https://github.com/ceu-lang/ceu
I have been running this on Ubuntu 20.04 under WSL without any major dramas, after resolving various dependencies through apt. You will only be able to run many of the Ceu examples if you forward your xserver and pulseaudio output, but that should not be necessary for running this simulator.
Make sure your environment variable "CEU_DIR" is set to the location of your Ceu binary.

The bittide simulator can be built with the `./make_all.sh` command, which will produce a C source file and corresponding binary in the 'tmp' folder. You can run this binary directly, or use `./make_all.sh run`.
