
cmake_minimum_required(VERSION 3.5)

# This section turns on and off this feature
option( INCLUDE_LIBDBGPRINT "Include libdbgprint" ON )
if( NOT ${INCLUDE_LIBDBGPRINT} )
    return()
endif()

project(dbgprint)

add_library(dbgprint dbgprint.c)

target_include_directories(dbgprint PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(${BUILD_SHARED_LIBS})
    install(TARGETS    dbgprint       DESTINATION /usr/local/lib )
endif()