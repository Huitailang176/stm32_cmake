#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.20)
 
# specify cross compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
 
# project settings
project(Project  C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
 
#Uncomment for hardware floating point
#add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
#add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
#add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
 
#Uncomment for software floating point
#add_compile_options(-mfloat-abi=soft)
 
add_compile_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
 
# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(VERBOSE "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(VERBOSE "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(VERBOSE "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(VERBOSE "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()
add_definitions(-DUSE_HAL_DRIVER -DSTM32F103xE -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD )

#头文件
include_directories(
    ./User 
    ./Code
    ./Drivers/CMSiS
    ./Drivers/CMSIS/Include #HAL头文件
    ./Drivers/CMSIS/Device/ST/STM32F1xx/Include
    ./Drivers/STM32F1xx_HAL_Driver/Inc
    ./Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    ./Drivers/SYSTEM
    ./Drivers/SYSTEM/sys
    ./Drivers/SYSTEM/delay
    ./Drivers/SYSTEM/usart
    ./Drivers/BSP/LED
    ./STM32F10x_FWLib/inc 
    ./Project/Code-Cmake
)

file(GLOB_RECURSE SOURCES 
    ./User/*.c 
    ./Code/*.c
    ./Drivers/BSP
    ./Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
    ./Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xe.s
    ./Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/linker/STM32F103XE_FLASH.ld
    ./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c  #库源文件，用什么添加什么
    ./Drivers/SYSTEM/delay/delay.c
    ./Drivers/SYSTEM/sys/sys.c
    ./Drivers/SYSTEM/usart/usart.c
    ./Project/Code-Cmake/*.*
    ./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    ./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    ./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    ./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    ./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    ./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    ./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    ./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c


    ./Drivers/BSP/LED/led.c

)
 
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/linker/STM32F103XE_FLASH.ld)
 
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

add_link_options(-specs=nano.specs -specs=nosys.specs -u _printf_float)
 
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
 
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
 
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")