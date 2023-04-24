AC_PREREQ([2.69])
AC_INIT([phosphor-settingsd], [1.0], [https://github.com/openbmc/phosphor-settingsd/issues])
AC_LANG([C++])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign dist-xz])
AM_SILENT_RULES([yes])

AC_PROG_CXX
AM_PROG_AR
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AM_PATH_PYTHON([3], [AC_SUBST([PYTHON], [echo "$PYTHON"])], [AC_MSG_ERROR(
    [Could not find python-3 installed...python-3 is required])])

PKG_CHECK_MODULES([PHOSPHOR_DBUS_INTERFACES], [phosphor-dbus-interfaces])
PKG_CHECK_MODULES([SDBUSPLUS], [sdbusplus])
PKG_CHECK_MODULES([PHOSPHOR_LOGGING], [phosphor-logging])

LT_INIT

AX_CXX_COMPILE_STDCXX([20], [noext])
AX_APPEND_COMPILE_FLAGS([-Wall -Werror], [CXXFLAGS])

AS_IF([test "x$SETTINGS_YAML" == "x"], [SETTINGS_YAML="settings_example.yaml"])
SETTINGSGEN="$PYTHON $srcdir/settings.py -i $SETTINGS_YAML"
AC_SUBST(SETTINGSGEN)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
