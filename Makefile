##
## Makefile for 42sh in /u/a1/grosli_o/grosli_o-42sh
##
## Made by gilles durget
## Login   <durget_g@epita.fr>
##
## Started on  Sat Dec 11 18:30:27 2004 gilles durget
## Last update Fri Jan 14 14:19:01 2005 gilles durget
##

EXEC=42sh
VERSION=1
PROJDIR=grosli_o-42sh
TARBALL=$(PROJDIR)-$(VERSION).tar.bz2
TARBALLGZ=$(PROJDIR)-$(VERSION).tar.gz
TAROPT=-cvyf

all :
	cd src && $(MAKE)

clean :
	cd src && $(MAKE) clean

check : all
	cd test && ./check.sh list && ./clean.sh && cd -

distclean : clean
	cd src && $(MAKE) distclean
	-rm -f Makefile.rules
	-rm -f config.h
	-rm -f *.~*~
	-rm -f \#*
	-rm -f ../$(TARBALL)

tar : distclean
	cd .. && tar --exclude "CVS" $(TAROPT) $(TARBALL) $(PROJDIR)

targz : distclean
	cd .. && tar --exclude "CVS" -zcvf $(TARBALLGZ) $(PROJDIR)