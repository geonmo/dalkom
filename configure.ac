AC_INIT(dalkom, 0.1)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([-Wall -Werror])
AM_MAINTAINER_MODE([disable])
AM_SILENT_RULES([no])

AM_PROG_AR
AC_PROG_CC
AC_PROG_CXX

LT_INIT([disable-static])

dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************

IT_PROG_INTLTOOL([0.35.0])
GETTEXT_PACKAGE=dalkom
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT

dnl ***************************************************************************
dnl OO SDK environment
dnl ***************************************************************************

OFFICE_HOME=/usr/lib/libreoffice
OO_SDK_HOME=$OFFICE_HOME/sdk
OO_SDK_URE_HOME=$OFFICE_HOME/ure-link

AC_PATH_PROG(CPPUMAKER, cppumaker, [no], $OO_SDK_HOME/bin)
AC_PATH_PROG(IDLC,      idlc,      [no], $OO_SDK_HOME/bin)
AC_PATH_PROG(REGMERGE,  regmerge,  [no], $OO_SDK_URE_HOME/bin)

if test "x$CPPUMAKER" = "xno"; then
  AC_MSG_ERROR([cppumaker not found, please install libreoffice-dev])
fi

if test "x$REGMERGE" = "xno"; then
  AC_MSG_ERROR([regmerge not found, please install libreoffice-dev])
fi

AC_SUBST(OFFICE_HOME)
AC_SUBST(OO_SDK_HOME)
AC_SUBST(OO_SDK_URE_HOME)

dnl ***************************************************************************
dnl Check libhwp
dnl ***************************************************************************

PKG_CHECK_MODULES(LIBHWP, libhwp)

dnl ***************************************************************************

AC_OUTPUT([
  Makefile
  data/Makefile
  src/Makefile
  po/Makefile.in])
