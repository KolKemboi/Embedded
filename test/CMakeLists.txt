cmake_minimum_required(VERSION 3.10)
project(blink C)

# MCU settings
set(MCU atmega328p)
set(F_CPU 16000000UL)

# Compiler
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Sources
add_executable(blink.elf blink.c)

# Convert to HEX after build
add_custom_command(TARGET blink.elf POST_BUILD
    COMMAND avr-objcopy -O ihex -R .eeprom blink.elf blink.hex
    COMMENT "Building HEX file"
)

# Upload target
add_custom_target(upload
    COMMAND avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:blink.hex:i
    DEPENDS blink.hex
    COMMENT "Flashing Arduino..."
)
