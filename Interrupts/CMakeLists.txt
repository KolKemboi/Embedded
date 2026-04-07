cmake_minimum_required(VERSION 3.10)
project(embedded C)

set(MCU atmega328p)
set(F_CPU 16000000UL)


set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(CMAKE_C_COMPILER avr-gcc)
# set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(
	main.elf

	src/main.c
)

target_compile_options(main.elf PRIVATE
	-mmcu=${MCU}
	-DF_CPU=${F_CPU}
	-Os
	-Wall
)

target_link_options(main.elf PRIVATE
	-mmcu=${MCU}
	)

add_custom_command(
	TARGET main.elf
	POST_BUILD COMMAND avr-objcopy -O ihex -R .eeprom $<TARGET_FILE:main.elf> ${CMAKE_BINARY_DIR}/main.hex
)
