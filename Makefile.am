## Process this file with automake to produce Makefile.in

SUBDIRS = src data po

ACLOCAL_AMFLAGS = -I m4

DISTCLEANFILES = \
	Makefile.in \
	po/Makefile.in.in \
	INSTALL \
	aclocal.m4 \
	config.h.in \
	config.h.in~ \
	configure

clean-local:
	-debian/rules clean

distclean-local:
	rm -rf autom4te.cache build-aux m4 .anjuta .anjuta_sym_db.db

ChangeLog:

.PHONY: ChangeLog
