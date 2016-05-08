oxtdir = $(top_srcdir)
oxt_DATA = \
	META-INF/manifest.xml \
	dalkom.uno.so \
	description.xml \
	filters.xcu \
	types.xcu

dalkom.uno.so:
	cp $(top_srcdir)/src/.libs/dalkom.uno.so .

dalkom.oxt:
	$(AM_V_GEN) zip -r dalkom.oxt $(oxt_DATA)

CLEANFILES = dalkom.uno.so dalkom.oxt

DISTCLEANFILES = Makefile.in dalkom.uno.so dalkom.oxt
