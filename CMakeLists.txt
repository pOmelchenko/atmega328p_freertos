cmake_minimum_required(VERSION 3.24)

set(F_CPU 16000000UL)
set(MCU atmega328p)
set(BAUD 115200)
set(PORT /dev/tty.usbmodem14101)
set(PROG_TYPE arduino)

set(E_FUSE 0xfd)
set(H_FUSE 0xda)
set(L_FUSE 0xfd)
set(LOCK_BIT 0xff)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_ASM_COMPILER avr-gcc)
set(CMAKE_OBJCOPY avr-objcopy)

project(arduino_uno_freertos
        LANGUAGES C
)

set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

add_compile_options(
        -DF_CPU=${F_CPU}
        -DBAUD=${BAUD}
        -mmcu=${MCU} # MCU
        -std=c17 # C17 standard
        -Os # optimize
        -Wall # enable warnings
        -Wno-main
#        -Wundef
        -pedantic
        -Wstrict-prototypes
#        -Werror
        -Wfatal-errors
        -Wl,--relax,--gc-sections
        -g
        -gdwarf-2
        -funsigned-char # a few optimizations
        -funsigned-bitfields
        -fpack-struct
        -fshort-enums
        -ffunction-sections
        -fdata-sections
        -fno-split-wide-types
        -fno-tree-scev-cprop
)

add_executable(${PROJECT_NAME} src/main.c)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}.elf)

file(GLOB FreeRTOS_src FreeRTOS/*.c)

add_library(FreeRTOS STATIC
        ${FreeRTOS_src}
        FreeRTOS/portable/GCC/ATMega328/port.c
        FreeRTOS/portable/MemMang/heap_4.c
)

target_include_directories(FreeRTOS PUBLIC
        include
        FreeRTOS/include
        FreeRTOS/portable/GCC/ATMega328
)

file(GLOB led_src Drivers/led/*.c)

add_library(led STATIC
        ${led_src}
)

target_include_directories(led PUBLIC
        Drivers/led
)

target_link_libraries(${PROJECT_NAME}
        FreeRTOS
        led
)

add_custom_target(upload avrdude
        -c ${PROG_TYPE}
        -p ${MCU}
        -P${PORT}
        -D
        -U flash:w:${PROJECT_NAME}.elf
        DEPENDS ${PROJECT_NAME}
)
