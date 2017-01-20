#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Code_struct], [0.90], [wang691234@gmail.com])
AC_CONFIG_SRCDIR([src/code_struct.c])
#AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE(Code_struct,0.90)
# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_PROG_RANLIB
# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memmove memset strchr strncasecmp strrchr])

AC_CONFIG_FILES([Makefile
                 header/Makefile
                 src/Makefile])
AC_OUTPUT
