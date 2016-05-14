extensiondir = /usr/lib/libreoffice/share/extensions/dalkom
extension_DATA = \
	description.xml \
	filters.xcu \
	types.xcu

meta_infdir = $(extensiondir)/META-INF
meta_inf_DATA = META-INF/manifest.xml

uninstall-hook:
	-rmdir -p $(DESTDIR)$(meta_infdir)

DISTCLEANFILES = Makefile.in
