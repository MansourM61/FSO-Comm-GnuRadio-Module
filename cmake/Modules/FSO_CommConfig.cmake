INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_FSO_COMM FSO_Comm)

FIND_PATH(
    FSO_COMM_INCLUDE_DIRS
    NAMES FSO_Comm/api.h
    HINTS $ENV{FSO_COMM_DIR}/include
        ${PC_FSO_COMM_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    FSO_COMM_LIBRARIES
    NAMES gnuradio-FSO_Comm
    HINTS $ENV{FSO_COMM_DIR}/lib
        ${PC_FSO_COMM_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FSO_COMM DEFAULT_MSG FSO_COMM_LIBRARIES FSO_COMM_INCLUDE_DIRS)
MARK_AS_ADVANCED(FSO_COMM_LIBRARIES FSO_COMM_INCLUDE_DIRS)

