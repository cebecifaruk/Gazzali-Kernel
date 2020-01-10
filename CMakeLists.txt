cmake_minimum_required(VERSION 3.7)
project(gazzali-kernel C)

#Config Spesific
set(ARCH i386)



# Arch Spesific
if(${ARCH} STREQUAL armcm3)
  set(CMAKE_C_COMPILER arm-none-eabi-gcc)
  #set(OBJCOPY arm-none-eabi-objcopy)
  #  set(OUTFORMAT elf32-littlearm)
  #  set(ARCHBINFORMAT arm)
    set(ARCH_SRCS arch/cm3.s)
    set_property(SOURCE arch/cm3.s PROPERTY LANGUAGE C)
    #-nostartfiles -mthumb-interwork
    set(ARCH_C_FLAGS  "-mlittle-endian -mthumb -mcpu=cortex-m3 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
    if(${CMAKE_C_COMPILER} STREQUAL clang)
        set(ARCH_C_FLAGS "-target armv7m-none-eabi ${ARCH_C_FLAGS}")
    endif()
	  
elseif(ARCH STREQUAL i386)
    set(CMAKE_C_COMPILER clang)
    #set(OBJCOPY i686-elf-objcopy)
    #set(OUTFORMAT elf32-i386)
    #set(ARCHBINFORMAT i386)
    set(ARCH_C_FLAGS "-ffreestanding -O2 -Wall -fno-exceptions -fno-rtti")
    set(ARCH_SRCS arch/i386.s)
    set_property(SOURCE arch/i386.s PROPERTY LANGUAGE C)
    #set_property(SOURCE arch/x86/x86.s PROPERTY LANGUAGE C)
	if(${CMAKE_C_COMPILER} STREQUAL clang)
        set(ARCH_C_FLAGS "--target=i686-pc-none-elf -march=i686 ${ARCH_C_FLAGS}")
    endif()
	  
endif()



set(ARCH_LDSCRIPT  "${CMAKE_CURRENT_SOURCE_DIR}/arch/linker-${ARCH}.ld")





#Standart

#initrd
find_program(GENROMFS_COMMAND genromfs)
add_custom_target(initrd 
    COMMAND mkdir -p ./initrd/
    COMMAND cd initrd/ && mkdir	-p bin home etc dev usr lib proc tmp usr/bin usr/lib
    COMMAND ${GENROMFS_COMMAND} -f initrd.img -d initrd/ -V ramfs
    COMMENT "ROMfs is been generating..."
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/initrd.o
    COMMAND ${OBJCOPY} -I binary -O ${OUTFORMAT} -B ${ARCHBINFORMAT} --rename-section .data=.text initrd.img initrd.o
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS initrd)

# Sources
set(MODULES_SRCS )


file(GLOB KERNEL_SRCS kernel/*.c fs/*.c)


add_executable(kernel ${KERNEL_SRCS} ${ARCH_SRCS} ${MODULES_SRCS}) #${CMAKE_BINARY_DIR}/initrd.o)


target_include_directories(kernel PUBLIC include/ kernel/ arch/)

set_target_properties(kernel PROPERTIES
    COMPILE_FLAGS "${COMPILE_FLAGS} ${CMAKE_C_FLAGS} ${ARCH_C_FLAGS} -O0 -g -Wall -I. -std=c99 -nostdlib -fno-builtin -nodefaultlibs"
    LINK_FLAGS "-T${ARCH_LDSCRIPT} ${CMAKE_C_FLAGS} ${ARCH_C_FLAGS}  -O0 -g -Wall -I. -std=c99 -nostdlib -fno-builtin -nodefaultlibs -nostartfiles")
#-Wl,-M=${EXECUTABLE_OUTPUT_PATH}/$(kernel).map 

