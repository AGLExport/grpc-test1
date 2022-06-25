# autoconf sample

AC_PREREQ([2.69])

AC_INIT([exsample], [1.0])

AM_INIT_AUTOMAKE([foreign subdir-objects])

#AC_CONFIG_SRCDIR([src/uinputdev.c])

AC_CONFIG_HEADERS([include/config.h])

AC_CONFIG_MACRO_DIR([m4])


AC_ARG_ENABLE([userdebug],
  [AS_HELP_STRING([--enable-userdebug], [Enable user debuging function (default is no)])],
  [:],
  [enable_userdebug=no])
AM_CONDITIONAL([ENABLE_USERDEBUG], [test "$enable_userdebug" = "yes"])

AC_ARG_ENABLE([printfdebug],
  [AS_HELP_STRING([--enable-printfdebug], [Enable user printf debug (default is no)])],
  [:],
  [enable_printfdebug=no])
AM_CONDITIONAL([ENABLE_PRINTFDEBUG], [test "$enable_printfdebug" = "yes"])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL

AC_DISABLE_STATIC

# Checks for libraries.
LT_INIT
AM_PROG_LIBTOOL 

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([PROTOBUF], [protobuf])
PKG_CHECK_MODULES([GRPCPP], [grpc++_unsecure])

AC_CHECK_PROG([PROTOC], [protoc], [protoc])
AS_IF([test "x${PROTOC}" == "x"],
    [AC_MSG_ERROR([ProtoBuf compiler "protoc" not found.])])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile 
				src/Makefile ])
AC_OUTPUT

AC_MSG_RESULT([
Configure Information:
  C Compiler        : $CC
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CFLAGS          :   $CFLAGS
  C++ Compiler      : $CXX
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CXXFLAGS        :   $CXXFLAGS
  Linker            : $LD
    LDFLAGS         :   $LDFLAGS
    LIBS            :   $LIBS
])

