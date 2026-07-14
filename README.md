# External CH32FUN example

This repo is meant as an example on how to incorporate the ch32fun system into a stand alone project.

It is meant to be used as a template.  The Makefile and the funconfig.h files are necessary parts of the ch32fun system and each needs to contain the correct code to specify what board/chip/package you're using and how you want the ch32fun system to work.  You can control various chip functions such as the clock speed, clock source, etc. as well as debug options such as debug over UART, programming interface (SWDIO), or USB.  It is meant to help new and experienced users utilize ch32fun easily and efficiently.

## Getting started

The first step is to clone this repo.  We will want to use the --recurse-submodules option as ch32fun is treated as a submodule of this repo.  This serves several purposes.  For one, it pins the version of ch32fun which the version of ch32fun will not change relative to your code which could possibly break things if ch32fun were to introduce an incompatability in the future.  Also, it fetches the ch32fun code for us.

You will need to become a bit familiar with git so that you can name your project as you wish and store it on github.
