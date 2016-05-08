lib_LTLIBRARIES = dalkom.uno.la

BUILT_SOURCES = includes

dalkom_uno_la_SOURCES = \
	dalkom-hwp-import-filter.cxx \
	dalkom-hwp-import-filter.hxx \
	dalkom-generic-filter.cxx

dalkom_uno_la_CPPFLAGS = \
	-Wall -Werror \
	-I/usr/include/libreoffice \
	-fvisibility=hidden \
	-DUNX -DGCC -DLINUX -DCPPU_ENV=gcc3 -DHAVE_GCC_VISIBILITY_FEATURE \
	-I$(srcdir)/includes

dalkom_uno_la_LDFLAGS = \
	-avoid-version -module \
	-L$(OO_SDK_HOME)/lib \
	-L$(OO_SDK_URE_HOME)/lib \
	-Wl,-z,origin -Wl,-rpath,'$$ORIGIN' \
	-luno_cppuhelpergcc3 -luno_cppu -luno_sal

includes:
	mkdir -p includes
	$(AM_V_GEN) $(IDLC) -I$(OO_SDK_HOME)/idl dalkom.idl
	$(AM_V_GEN) $(REGMERGE) $(srcdir)/dalkom.uno.rdb /UCR $(srcdir)/dalkom.urd
	$(AM_V_GEN) $(CPPUMAKER) -Gc -O$(srcdir)/includes \
		$(OO_SDK_URE_HOME)/share/misc/types.rdb \
		$(OFFICE_HOME)/program/types/offapi.rdb
	$(AM_V_GEN) $(CPPUMAKER) -Gc \
		-O$(srcdir)/includes $(srcdir)/dalkom.uno.rdb \
		-X$(OO_SDK_URE_HOME)/share/misc/types.rdb \
		-X$(OFFICE_HOME)/program/types/offapi.rdb

clean-local:
	-rm -rf includes

DISTCLEANFILES = Makefile.in dalkom.uno.rdb dalkom.urd includes
