# Copyright 2011,2012,2016 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND FSO_Comm_sources
    Channel_Analyser_ff_impl.cc
    Geometric_Loss_ff_impl.cc
    Laser_ff_impl.cc
    Optical_Receiver_ff_impl.cc
    Pointing_Errors_ff_impl.cc
    Turbulence_ff_impl.cc
    FogSmoke_Loss_ff_impl.cc )

set(FSO_Comm_sources "${FSO_Comm_sources}" PARENT_SCOPE)
if(NOT FSO_Comm_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT FSO_Comm_sources)

add_library(gnuradio-FSO_Comm SHARED ${FSO_Comm_sources})
target_link_libraries(gnuradio-FSO_Comm ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-FSO_Comm PROPERTIES DEFINE_SYMBOL "gnuradio_FSO_Comm_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-FSO_Comm PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-FSO_Comm RUNTIME_COMPONENT "FSO_Comm_runtime" DEVEL_COMPONENT "FSO_Comm_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})
list(APPEND test_FSO_Comm_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_FSO_Comm.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_FSO_Comm.cc
    )

add_executable(test-FSO_Comm ${test_FSO_Comm_sources})

target_link_libraries(
  test-FSO_Comm
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-FSO_Comm
)

GR_ADD_TEST(test_FSO_Comm test-FSO_Comm)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

