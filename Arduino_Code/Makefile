#Avrdude related variables
COM_PORT = /dev/ttyUSB0
BAUD_RATE = 115200
ARDUINO_VERSION = 187
ARDUINO_MODEL = atmega328p
ARDUINO_PROGRAMMER = arduino

#Paths
ARDUINO_BASE_DIR = /usr/local/arduino
ARDUINO_TOOLS_BIN_DIR = ${ARDUINO_BASE_DIR}/hardware/tools/avr/bin
ARDUINO_TOOLS_ETC_DIR = ${ARDUINO_BASE_DIR}/hardware/tools/avr/etc
ARDUINO_PINS_DIR = ${ARDUINO_BASE_DIR}/hardware/arduino/avr/variants/standard
ARDUINO_CORE_DIR = ${ARDUINO_BASE_DIR}/hardware/arduino/avr/cores/arduino
ARDUINO_LIB_DIR = ${ARDUINO_BASE_DIR}/libraries
ifndef MAKEFILE_DIR
    export MAKEFILE_DIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
endif

#Tools
AVR_DUDE = avrdude -C ${ARDUINO_TOOLS_ETC_DIR}/avrdude.conf
#AVR_CC = avr-gcc ${CFLAGS} ${INCLUDES}
AVR_CC = avr-gcc
#AVR_CXX = avr-g++ ${CXXFLAGS} ${INCLUDES}
AVR_CXX = avr-g++
AVR_AR = avr-ar rcs

#Checking for configuration
ifndef CONF
    $(warning The CONF variable not set. Setting it to Debug)
    CONF := Debug
endif

ifeq ($(filter Debug Release, $(CONF)),)
    $(error The CONF variable set to a different value than "Debug" or "Release")
endif
#At this point the CONF variable is either Debug or Release

#Project specific variables
BIN_NAME := onetouchm3
BIN_DIR := ${MAKEFILE_DIR}${CONF}
BIN_PATH = ${CONF}/${BIN_NAME}

#Build flags
ifeq ($(CONF), Debug)
#    ADDITIONAL_CORE_LIBS := Firmata
endif

#assumes that the headers and sources are within src subfolder of each project specific library

INCLUDES = -I${ARDUINO_CORE_DIR} \
-I${ARDUINO_PINS_DIR} \
$(patsubst %,-I${ARDUINO_LIB_DIR}/%,$(subst ;, ,$(ADDITIONAL_CORE_LIBS)))

CFLAGS_DEFS := -DUSB_VID=null -DUSB_PID=null -DARDUINO=${ARDUINO_VERSION} -DF_CPU=16000000L -DARDUINO_ARCH_AVR
CFLAGS_GEN1 := -c -Os -Wall
#CFLAGS_GEN1 := -c -Wall
CFLAGS_GEN2 := -ffunction-sections -fdata-sections -mmcu=${ARDUINO_MODEL} -MMD
ifeq ($(CONF), Debug)
#Since we debug using traces, for now, there is no need for -g param
#    CFLAGS_GEN1 := ${CFLAGS_GEN1} -g
#    CFLAGS_GEN1 := ${CFLAGS_GEN1} -Og
    CXXFLAGS_DEFS_PRJ:=-D_TRACE
#    LDFLAG := -g
#else
#    CFLAGS_GEN1 := ${CFLAGS_GEN1} -Os
    #Project specific defs
 #   CXXFLAGS_DEFS_PRJ :=
endif
CFLAGS := ${CFLAGS_GEN1} ${CFLAGS_DEFS} ${INCLUDES}${CFLAGS_GEN2}
CXXFLAGS_SPECIFIC := -fno-exceptions -std=c++14
CXXFLAGS := ${CFLAGS} ${CXXFLAGS_SPECIFIC}
LDFLAGS := ${LDFLAG} -Os -Wl,--gc-sections,--relax -mmcu=${ARDUINO_MODEL}
#LDFLAGS := ${LDFLAGS} -Wl,--gc-sections,--relax -mmcu=${ARDUINO_MODEL}
#ifeq ($(CONF), Debug)
#    LDFLAGS := ${LDFLAGS} -Og
#else
#    LDFLAGS := ${LDFLAGS} -Os
#endif

LD_LIBS = ${ARDUINO_LIBS} -lm

CORE_CPP_SOURCES := $(wildcard ${ARDUINO_CORE_DIR}/*.cpp)
CORE_C_SOURCES := $(wildcard ${ARDUINO_CORE_DIR}/*.c)
CORE_OBJECTS =$(subst ${ARDUINO_CORE_DIR},${BUILD_LIBS_DIR},$(CORE_CPP_SOURCES:.cpp=.cpp.o) $(CORE_C_SOURCES:.c=.c.o))

LIBS_CPP_SOURCES = $(wildcard $(patsubst %,${ARDUINO_LIB_DIR}/%/*.cpp,$(subst ;, ,$(ADDITIONAL_CORE_LIBS))))
#LIBS_CPP_SOURCES
LIBS_C_SOURCES = $(wildcard $(patsubst %,${ARDUINO_LIB_DIR}/%/*.c,$(subst ;, ,$(ADDITIONAL_CORE_LIBS))) )
LOBJECTS = $(LIBS_CPP_SOURCES:.cpp=.cpp.o) $(LIBS_C_SOURCES:.c=.c.o)
LIB_OBJECTS = $(subst ${ARDUINO_LIB_DIR},${BUILD_LIBS_DIR},${LOBJECTS})

#Libs within the project, usually from github, with just a bunch of .ccp files winthin theirs' src subfolders
PRJ_LIBS := WatchDog

#Add the libraries src subfolders as includes
PRJ_LIBS_BUILD_DIRS := $(PRJ_LIBS:%=$(CONF)/libs/%)
PRJ_LIBS_INCLUDES := $(PRJ_LIBS:%=-Ilibs/%) -Ilibs/PinChangeInt
PRJ_LIBS_SOURCES := $(wildcard $(PRJ_LIBS:%=libs/%/*.cpp)) #$(foreach prjLib, $(PRJ_LIBS), $(wildcard $(prjLib)/src/*.cpp))
PRJ_LIBS_OBJS := $(patsubst %.cpp, $(CONF)/%.o, $(PRJ_LIBS_SOURCES))

CXXFLAGS_PRJ := ${CFLAGS_GEN1} ${CFLAGS_DEFS} ${CXXFLAGS_DEFS_PRJ} ${INCLUDES} ${PRJ_LIBS_INCLUDES} ${CFLAGS_GEN2} ${CXXFLAGS_SPECIFIC} -fno-threadsafe-statics

#BUILD_LIBS_DIR_BASE := ${MAKEFILE_DIR}${CONF}/lib
BUILD_LIBS_DIR := ${CONF}/libs
ARDUINO_LIBS = ${BUILD_LIBS_DIR}/arduinolibs.a
ADDITIONAL_BUILD_LIBS_DIRS := $(foreach lib, $(ADDITIONAL_CORE_LIBS), ${BUILD_LIBS_DIR}/$(lib))

OBJS_LIST := main.o DbgUtils.o OneTouchM3.o Pins.o
OBJS := $(foreach obj,${OBJS_LIST},$(CONF)/$(obj))

# Environment 
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin

#add the avr tools in path so that they will be found while building
PATH := $(PATH):$(ARDUINO_TOOLS_BIN_DIR)

#the default make rule
all: .build-post

.build-post: build

# build
build: .build-pre ${CONF} ${BIN_PATH}.hex

${BIN_PATH}: $(OBJS)
	${AVR_CXX} ${LDFLAGS} ${OBJS} ${LD_LIBS} -o ${BIN_PATH}

.build-pre: .build-pre-check-arduino-base-dir libraries

#Unconditional Build
.build-pre-check-arduino-base-dir:
#	echo === $(wildcard $(ARDUINO_BASE_DIR)/*)
#The ARDUINO_BASE_DIR must refer to an existing folder on the disk
ifeq "$(wildcard $(ARDUINO_BASE_DIR)/*)" ""
	@echo Folder \"$(ARDUINO_BASE_DIR)\" not found or is not a folder. Please fill the ARDUINO_BASE_DIR variable at the top of Makefile accordingly. Remember the path must not contain spaces.
endif

#$(info === ${ARDUINO_LIBS}: ${BUILD_LIBS_DIR} --- ${ADDITIONAL_BUILD_LIBS_DIRS} ---- ${CORE_OBJECTS} ---- ${PRJ_LIBS_OBJS})
	
#Rules for building the additional libraries
${ARDUINO_LIBS}: ${BUILD_LIBS_DIR} ${ADDITIONAL_BUILD_LIBS_DIRS} ${PRJ_LIBS_BUILD_DIRS} ${CORE_OBJECTS} ${LIB_OBJECTS} ${PRJ_LIBS_OBJS}
	${AVR_AR} ${ARDUINO_LIBS} ${CORE_OBJECTS} ${LIB_OBJECTS} ${PRJ_LIBS_OBJS}

#Rules for building project's libraries
libraries: ${ARDUINO_LIB_CORE} ${ARDUINO_LIBS}

#Rules for  folders creation
${BUILD_LIBS_DIR} ${ADDITIONAL_BUILD_LIBS_DIRS} ${CONF} ${PRJ_LIBS_BUILD_DIRS}:
	$(MKDIR) -p $@

#Rules for building core and arduino libs (c++ files)
${BUILD_LIBS_DIR}/%.cpp.o: ${ARDUINO_CORE_DIR}/%.cpp
	${AVR_CXX} ${CXXFLAGS} $< -o $@

#Rules for building core and arduino libs (c files)
${BUILD_LIBS_DIR}/%.c.o: ${ARDUINO_CORE_DIR}/%.c
	${AVR_CC} ${CFLAGS} $< -o $@

#Rules for building the additional arduino libs like Firmata (c++ files)
${BUILD_LIBS_DIR}/%.cpp.o: ${ARDUINO_LIB_DIR}/%.cpp
	${AVR_CXX} ${CXXFLAGS} $< -o $@

#Rules for building the additional arduino libs like Firmata (c files)
${BUILD_LIBS_DIR}/%.c.o: ${ARDUINO_LIB_DIR}/%.c
	${AVR_CC} ${CFLAGS} $< -o $@
	
#Rules for building project's specific objects
${CONF}/%.o: %.cpp
	${AVR_CXX} ${CXXFLAGS_PRJ} $< -o $@

#Rules for building Bounce2 objects
${CONF}/libs/Bounce2/%.o: libs/Bounce2/src/%.cpp
	${AVR_CXX} ${CXXFLAGS_PRJ} $< -o $@

${BIN_PATH}.hex: ${BIN_PATH}
	avr-objcopy -O ihex ${BIN_PATH} ${BIN_PATH}.hex
	avr-size --mcu=${ARDUINO_MODEL} -C ${BIN_PATH}
	
#Rule for post build actions
.build-post:	
#Add here post-build actions

upload: 
	${AVR_DUDE} -v -p${ARDUINO_MODEL} -c${ARDUINO_PROGRAMMER} -P ${COM_PORT} -b${BAUD_RATE} -D -Uflash:w:${BIN_PATH}.hex:i

#Extra care must be taken while deleting files. Only absolute paths should be used or paths relative to the makefile location
# clean
clean:
	-rm ${BIN_DIR}/*.o ${BIN_DIR}/*.d ${BIN_PATH} ${BIN_PATH}.hex # ${ARDUINO_LIBS}

clean-all: clean
	-rm -r ${BIN_DIR}
#	-rm -r ${BUILD_LIBS_DIR_BASE}

# help. To be implemented
help:

#internale makefile targets. Do not consider them files on the disk
.PHONY: all Makefile build .build-post .build-pre .build-pre-check-arduino-base-dir libraries clean clean-all help
