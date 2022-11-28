cmake_minimum_required(VERSION 3.1...3.22)

set(MYLIB_VERSION 0.1.0)

message("\n[Configuring mylib version ${MYLIB_VERSION}]\n")
project(
  mylib
  VERSION ${MYLIB_VERSION}
  LANGUAGES CXX)

option(BUILD_STATIC_LIBS "Build static libraries" ON)
option(BUILD_DYNAMIC_LIBS "Build dynamic libraries" ON)
option(BUILD_EXAMPLE_PROGRAMS "Build example program" ON)
option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_INSTALL_LIBDIR "lib" CACHE PATH "library install dir (lib)")
set(CMAKE_INSTALL_INCLUDEDIR "include" CACHE PATH "header base install dir (include)")
set(CMAKE_INSTALL_BINDIR "bin" CACHE PATH "user executables (bin)")

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /Wall")
    set(LIB_CFLAGS "/TP /W4")
    set(EXAMPLE_CFLAGS "/W4")
    set(TEST_CFLAGS "${LIB_CFLAGS}")
    set(TEST_LDFLAGS " ")
    set(LIBM " ")
else()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Werror -pedantic")
    set(LIB_CFLAGS "-std=c++14 -fvisibility=hidden -Wall -Werror=strict-prototypes -Werror=old-style-definition -Werror=missing-prototypes -D_REENTRANT -D_POSIX_C_SOURCE=200809L -Wno-missing-braces")
    set(EXAMPLE_CFLAGS "-std=c++14 -Wall")
    set(TEST_CFLAGS "${LIB_CFLAGS} -fprofile-arcs -ftest-coverage")
    set(TEST_LDFLAGS "-fprofile-arcs -ftest-coverage")
    set(LIBM "m")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Choose the type of build, options are: Debug Release" FORCE)
endif()

set(MYLIB_STATIC_LIBNAME mylib)

set(MYLIB_SOURCES
    "${mylib_SOURCE_DIR}/src/mylib.cpp"
)

set(MYLIB_HEADERS
    "${mylib_SOURCE_DIR}/mylib/mylib.h"
)

include_directories(
    ${mylib_SOURCE_DIR}
    "${mylib_SOURCE_DIR}/examples"
    "${mylib_SOURCE_DIR}/test"
    "${mylib_SOURCE_DIR}/src"
    "${mylib_SOURCE_DIR}/mylib"
)

if(BUILD_DYNAMIC_LIBS)
    add_library(mylib_shared SHARED ${MYLIB_SOURCES})
    set_target_properties(mylib_shared PROPERTIES
        OUTPUT_NAME mylib
        VERSION ${MYLIB_VERSION}
        COMPILE_FLAGS ${LIB_CFLAGS}
        LINKER_LANGUAGE CXX
    )
    install(TARGETS mylib_shared DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

if(BUILD_STATIC_LIBS)
    add_library(mylib_static STATIC ${MYLIB_SOURCES})
    set_target_properties(mylib_static PROPERTIES
        OUTPUT_NAME ${MYLIB_STATIC_LIBNAME}
        COMPILE_FLAGS ${LIB_CFLAGS}
        LINKER_LANGUAGE CXX
    )
    install(TARGETS mylib_static DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

if(BUILD_EXAMPLE_PROGRAMS)
    add_executable(example examples/example.cpp)
    set_target_properties(example PROPERTIES
        LINKER_LANGUAGE CXX
        COMPILE_FLAGS ${EXAMPLE_CFLAGS})
        target_link_libraries(example mylib_shared ${LIBM})
    install(TARGETS example DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()


if(BUILD_TESTS)
    # TODO
endif()

message("\n"
    "Installation Summary\n"
    "--------------------\n"
    "* Install Directory            : ${CMAKE_INSTALL_PREFIX}\n"
    "* Build Type                   : ${CMAKE_BUILD_TYPE}\n"
    "* Build static libs            : ${BUILD_STATIC_LIBS}\n"
    "* Build dynamic libs           : ${BUILD_DYNAMIC_LIBS}\n"
    "* Build examples               : ${BUILD_EXAMPLE_PROGRAMS}\n"
    "* Build tests                  : ${BUILD_TESTS}\n"
)
