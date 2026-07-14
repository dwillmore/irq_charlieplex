# Comments in Makefiles start with hashes

# This file instructs the build system how everything is related and what's expected of it
# It's invoked by running the 'make' command.  If nothing else is specified on the command 
# line, then the default is to 'make all'.  This is the 'all' target which says we need
# to execute the 'flash' step
all : flash

# This tells the build scripts what the name of the binary we're trying to build is called.
# It assumes there will be a .c file with this name which needs to be compiled.  This is
# the 'base name' for everything made by the build scripts.  The .bin and .lst files will
# be named after this value.
TARGET:=my_blink

# This tells the build scripts what chip we're building for.  It's just the base name of 
# the chip.  As you can see there are a lot of options.  Pick the one specific chip that
# you are targeting.  If you set more than one, only the last one will be in effect.
# You cannot build for multiple chips at once.
TARGET_MCU:=CH32V003
# TARGET_MCU:=CH32V002
# TARGET_MCU:=CH32V006
# TARGET_MCU:=CH32X033
# TARGET_MCU:=CH32X035
# TARGET_MCU:=CH32L103
# TARGET_MCU:=CH32V103
# TARGET_MCU:=CH32V203
# TARGET_MCU:=CH32V208
# TARGET_MCU:=CH32V303
# TARGET_MCU:=CH32V305
# TARGET_MCU:=CH32V307
# TARGET_MCU:=CH32H417
# TARGET_MCU:=CH570
# TARGET_MCU:=CH572
# TARGET_MCU:=CH573
# TARGET_MCU:=CH582
# TARGET_MCU:=CH585
# TARGET_MCU:=CH592

# Some chiops have multiple ways to configure their memory--between code and data
# This value controls that.  If you're using one of these chips, you'll need to study
# the data sheet and the rest of the build scripts carefully.  This is a fairly
# advanced feature.  If you don't understand this so far, you likely do not need this.
# TARGET_MCU_MEMORY_SPLIT:=3

# Sometimes the build system needs to do things differently for different versions
# of chips found in different packages--different inherent memory amounts, etc.
# You can set the value here and the build scripts will do the right thing--usually.
# TARGET_MCU_PACKAGE:=CH32V203F8
# TARGET_MCU_PACKAGE:=CH32V203F8 #64K version
# TARGET_MCU_PACKAGE:=CH32V203G6U6
# TARGET_MCU_PACKAGE:=CH32V208GB
# TARGET_MCU_PACKAGE:=CH32V208GBU6
# TARGET_MCU_PACKAGE:=CH32V208WBU6
# TARGET_MCU_PACKAGE:=CH32V303
# TARGET_MCU_PACKAGE:=CH32V303CBT6
# TARGET_MCU_PACKAGE:=CH32V305RBT6
# TARGET_MCU_PACKAGE:=CH32V307VCT6
# TARGET_MCU_PACKAGE:=CH32V307WCU6
# TARGET_MCU_PACKAGE:=CH570D
# TARGET_MCU_PACKAGE:=CH572Q
# TARGET_MCU_PACKAGE:=CH573F
# TARGET_MCU_PACKAGE:=CH582F
# TARGET_MCU_PACKAGE:=CH585F
# TARGET_MCU_PACKAGE:=CH585M
# TARGET_MCU_PACKAGE:=CH592F

# This incorporates the rest of the build system scripts.  You may wish to read
# through them to see what options they support.  Options, as you may have noticed
# are traditionally in ALLCAPS--which makes them easier to spot when reading through 
# code.
include ch32fun/ch32fun/ch32fun.mk

# These tell the build system that there are additional commands called 'flash' and
# 'clean'.  It then tells them you need to run the "cv_flash" and "cv_clean" targets
# to accomplish them.  You could just say "Make cv_flash" instead, but build systems
# exist to hide some details and to automate others.  Let it.
flash : cv_flash
clean : cv_clean


