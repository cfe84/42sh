##
## Makefile for getln in /goinfre/getln
##
## Made by olivier grosliere
## Login   <grosli_o@epita.fr>
##
## Started on  Mon Sep 20 16:24:09 2004 olivier grosliere
## Last update Tue Jan 18 15:01:02 2005 olivier grosliere
##
include ../../Makefile.rules

SRC = my_fnmatch.c
OBJS = $(SRC:.c=.o)

all: $(OBJS)
	@echo "Compilation of the libfnmatch for `uname -s`"
	ar cr libmy_fnmatch_`uname -m`-`uname -s`.a $(OBJS)
	ranlib libmy_fnmatch_`uname -m`-`uname -s`.a

.c.o:
	uname -s
	$(CC) $(CFLAGS) -c -DOS=`uname -s` $<

clean:
	rm -rf *.o *~ *\#

distclean:
	rm -rf *.a *.so *.o *.rules *\# *~ os.h