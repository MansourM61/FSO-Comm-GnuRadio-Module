# Install script for directory: /home/mojtaba/Documents/gr-FSO_Comm/include/FSO_Comm

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FSO_Comm" TYPE FILE FILES
    "/home/mojtaba/Documents/gr-FSO_Comm/include/FSO_Comm/api.h"
    "/home/mojtaba/Documents/gr-FSO_Comm/include/FSO_Comm/Channel_Analyser_ff.h"
    "/home/mojtaba/Documents/gr-FSO_Comm/include/FSO_Comm/Geometric_Loss_ff.h"
    "/home/mojtaba/Documents/gr-FSO_Comm/include/FSO_Comm/Laser_ff.h"
    "/home/mojtaba/Documents/gr-FSO_Comm/include/FSO_Comm/Optical_Receiver_ff.h"
    "/home/mojtaba/Documents/gr-FSO_Comm/include/FSO_Comm/Pointing_Errors_ff.h"
    "/home/mojtaba/Documents/gr-FSO_Comm/include/FSO_Comm/Turbulence_ff.h"
    "/home/mojtaba/Documents/gr-FSO_Comm/include/FSO_Comm/FogSmoke_Loss_ff.h"
    )
endif()

