set (CMAKE_SYSTEM_PROCESSOR "aarch64"           CACHE STRING "")
set (MACHINE                "raspi4"            CACHE STRING "")
set (CROSS_PREFIX           "aarch64-none-elf-" CACHE STRING "")

include (cross-freertos-gcc)

# vim: expandtab:ts=2:sw=2:smartindent
