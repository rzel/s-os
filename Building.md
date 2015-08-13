## Introduction ##

If you make any changes to the source code of SoS, you will need to compile and link it to be able to run the new version.

## Prerequisites ##

To build SoS, you need the following:
  * GCC version 4.1 or greater
  * GNU Binutils
  * GNU Make
  * mkisofs
  * and the SoS Source Code

## Building the Code ##

The following command compiles and assembles the source files, and then links them into a binary. The kernel binary can be found in the folder `image/system/kernel.sys`. To build the file, navigate to your working copy of SoS with your terminal, and then run:
```
make
```

## Generating a CD image ##

To generate a cd image, enter the following into your terminal, after completing the previous step.
```
make install
```

## Cleaning Up ##

To delete all the object files created by the compiler and assembler, simply run:
```
make clean
```