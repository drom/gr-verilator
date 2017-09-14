INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_VERILATOR verilator)

FIND_PATH(
    VERILATOR_INCLUDE_DIRS
    NAMES verilator/api.h
    HINTS $ENV{VERILATOR_DIR}/include
        ${PC_VERILATOR_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    VERILATOR_LIBRARIES
    NAMES gnuradio-verilator
    HINTS $ENV{VERILATOR_DIR}/lib
        ${PC_VERILATOR_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VERILATOR DEFAULT_MSG VERILATOR_LIBRARIES VERILATOR_INCLUDE_DIRS)
MARK_AS_ADVANCED(VERILATOR_LIBRARIES VERILATOR_INCLUDE_DIRS)

