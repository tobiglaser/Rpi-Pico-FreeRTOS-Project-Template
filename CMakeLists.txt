cmake_minimum_required(VERSION 3.12)

set(project_name "Hello_RTOS")

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(${project_name} C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

# initialize the Pico SDK
pico_sdk_init()

add_executable(${project_name}
    src/main.cpp 
)



# Add pico_stlib library which aggregates commonly used features
target_link_libraries(${project_name} pico_stdlib)

# Add FreeRTOS with Arm CM0 Port
target_link_libraries(${project_name} FreeRTOS)
add_library(FreeRTOS STATIC FreeRTOS-Kernel/croutine.c
FreeRTOS-Kernel/event_groups.c
FreeRTOS-Kernel/list.c
FreeRTOS-Kernel/queue.c
FreeRTOS-Kernel/stream_buffer.c
FreeRTOS-Kernel/tasks.c
FreeRTOS-Kernel/timers.c FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c FreeRTOS-Kernel/portable/MemMang/heap_4.c src/FreeRTOS_Support_Files/IdleMemory.c)
target_include_directories(FreeRTOS PUBLIC FreeRTOS-Kernel/include include/ FreeRTOS-Kernel/portable/GCC/ARM_CM0)



# enable usb output, disable uart output
pico_enable_stdio_usb(${project_name} 0)
pico_enable_stdio_uart(${project_name} 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${project_name})
add_custom_command(TARGET ${project_name}
        POST_BUILD
        COMMAND arm-none-eabi-size ${project_name}.elf
        )
# rest of your project