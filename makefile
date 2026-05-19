PREFIX = /usr/local

install:
	mkdir -p $(PREFIX)/include $(PREFIX)/share/man/man3
	cp bitutils.h $(PREFIX)/include/
	cp bitutils.3 $(PREFIX)/share/man/man3/

uninstall:
	rm -f $(PREFIX)/include/bitutils.h
	rm -f $(PREFIX)/share/man/man3/bitutils.3