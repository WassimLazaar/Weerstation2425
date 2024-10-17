# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
set(BOARD nucleo_f091rc)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(Weerstation)

# Voeg de include-directory toe aan de target zodat Weerstation.h gevonden kan worden
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Voeg alle C bestanden uit de src directory toe aan de target
FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
