##
## Makefile for 42sh in /u/a1/durget_g/grosli_o-42sh/src
##
## Made by gilles durget
## Login   <durget_g@epita.fr>
##
## Started on  Fri Jan  7 14:53:19 2005 gilles durget
## Last update Tue Jan 18 20:14:01 2005 gilles durget
##

include ../Makefile.rules

SOURCES=	lexer.c			\
		lexer2.c		\
		lexer_block_extractor.c	\
		parser.c		\
		buffer.c		\
		struct_parse.c		\
		error.c			\
		launch.c		\
		history.c		\
		global.c		\
		loop.c			\
		read_line.c		\
		prompt.c		\
		is.c			\
		ast.c			\
		display.c		\
		is2.c			\
		parse_cmd.c		\
		parse_lists.c		\
		parse_rules.c		\
		mystrcat.c		\
		expansion/paths.c	\
		expansion/expand.c	\
		expansion/path_treatment.c \
		expansion/unquoting.c	\
		job.c			\
		env_var.c		\
		load_env_var.c		\
		builtins/built_cd.c	\
		builtins/built_echo.c	\
		builtins/built_exit.c	\
		builtins/built_utils.c	\
		builtins/built_shopt.c	\
		eval.c			\
		strings.c		\
		redirections.c		\
		signal/my_signal.c	\
		main.c

HEADERS=	lexer.h				\
		lexer_block_extractor.h		\
		parser.h			\
		buffer.h			\
		struct_parse.h			\
		error.h				\
		launch.h			\
		history.h			\
		global.h			\
		loop.h				\
		read_line.h			\
		prompt.h			\
		is.h				\
		ast.h				\
		display.h			\
		defines.h			\
		mystrcat.h			\
		job.h				\
		env_var.h			\
		load_env_var.h			\
		builtins/builtins.h		\
		expansion/path_treatment.h	\
		eval.h				\
		signal/my_signal.h		\
		strings.h

OUTPUT=$(SOURCES:.c=.o)

EXEC=./42sh

all : $(EXEC)

aff :	clean
	make "FLAGS=-DAFFTREE"

debug :
	gcc -W -Wall -Werror -std=gnu99 -g *.c -o 42sh

$(EXEC) : $(OUTPUT)
	cd libs && make && cd ..
	$(CC) $(SFL) $(CFLAGS) $(OUTPUT) -o $(EXEC) $(LDFLAGS)
	cp $(EXEC) ..

.c.o : Makefile ../Makefile.rules $(HEADERS)
	$(CC) $(CFLAGS) $(FLAGS) -c $< -o $@

clean :
	-cd libs && make distclean && cd -
	-cd expansion && rm -f *~ so_locations *.o && cd -
	-cd builtins && rm -f *~ so_locations *.o && cd -
	-rm -f *~ so_locations *.o
	-rm -f builtins/*~ builtins/*.o

distclean : clean
	-rm -f $(EXEC)
	-rm -f ../$(EXEC)
	-rm -f pit
	-rm -f \#*
	-rm -f *.~*~
