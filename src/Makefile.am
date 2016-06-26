extensiondir = /usr/lib/libreoffice/share/extensions/dalkom
extension_LTLIBRARIES = dalkom.uno.la

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
	-I$(srcdir)/includes \
	$(LIBHWP_CFLAGS)

dalkom_uno_la_LDFLAGS = \
	-avoid-version -module \
	-L$(OO_SDK_HOME)/lib \
	-L$(OO_SDK_URE_HOME)/lib \
	-Wl,-z,origin -Wl,-rpath,'$$ORIGIN' \
	-luno_cppuhelpergcc3 -luno_cppu -luno_sal \
	$(LIBHWP_LIBS)

includes:
	mkdir -p includes
	$(AM_V_GEN) $(CPPUMAKER) -Gc -O$(srcdir)/includes \
		$(TYPES_RDB) $(OFFICE_HOME)/program/types/offapi.rdb

install-data-hook:
	rm -f $(DESTDIR)$(extensiondir)/dalkom.uno.la

uninstall-hook:
	 rm    -f $(DESTDIR)$(extensiondir)/dalkom.uno.so
	-rmdir -p $(DESTDIR)$(extensiondir)

clean-local:
	-rm -rf includes

DISTCLEANFILES = Makefile.in dalkom.uno.rdb dalkom.urd includes
