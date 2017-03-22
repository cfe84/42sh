/*
** defines.h for 42sh in /u/a1/grosli_o/projet/grosli_o-42sh
**
** Made by olivier grosliere
** Login   <grosli_o@epita.fr>
**
** Started on  Tue Jan  4 22:20:37 2005 olivier grosliere
** Last update Tue Jan 18 18:16:21 2005 gilles durget
*/
#ifndef DEFINES_H_
# define DEFINES_H_

/*
** Printable tokens
*/
# define EOL			0
# define PVIRG			1
# define BANG			2
# define AMPAMP			3
# define AMP			4
# define PIPEPIPE		5
# define PIPE			6
# define R_CH			7
# define L_CH			8
# define D_R_CH			9
# define D_L_CH			10
# define S_D_L_CH		11
# define L_PAR			12
# define R_PAR			13
# define L_BRA			14
# define R_BRA			15
# define IF			16
# define THEN			17
# define ELSE			18
# define ELIF			19
# define FI			20
# define FOR			21
# define IN			22
# define DONE			23
# define DO			24
# define WHILE			25
# define UNTIL			26

/*
** Type tokens
*/
# define END_OF_FILE		27
# define ERROR			28
# define WORD			29
# define COMMAND		30
# define EMPTY			31
# define FUNC			32

/*
** Buffer
*/
# define BUF_SIZE		10

/*
** Mode of the shell
*/
# define MODE_INTER		1
# define MODE_FILE		2
# define MODE_PIPE		3

/*
** Size of static const arrays.
*/
# define NB_BLANKS		5
# define NB_STOPS		17
# define NB_QUOTES		4
# define NB_PRINT_TOKENS	27
# define NB_UNPRINT_TOKENS	6

/*
** Default prompt
*/
# ifdef JOLIPROMPT
#  define DEFAULT_PROMPT	"\033[31mHyppie 42sh\033[32m$\033[0m "
# else
#  define DEFAULT_PROMPT	"42$ "
# endif /* !JOLIPROMPT */

/*
** element function results
*/
# define EL_STOP		0
# define EL_WORD		1
# define EL_REDIR		2

/*
** errors message
*/
# define L_UNX_EOF		0
# define L_UNX_EOF_MSG		"unexpected end of file"
# define L_UNX_EOF_RET		2
# define L_UNX_DISPCUR		0

# define P_TOKEN_ERROR		1
# define P_TOKEN_MSG		"syntax error near unexpected"
# define P_TOKEN_RET		258
# define P_TOKEN_DISPCUR	1

# define P_DONE_EX		2
# define P_DONE_EX_MSG		"done expected near unexpected"
# define P_DONE_RET		258
# define P_DONE_DISPCUR		1

# define P_DO_EX		3
# define P_DO_EX_MSG		"do expected near unexpected"
# define P_DO_RET		258
# define P_DO_DISP_CUR		1

# define P_THEN_EX		4
# define P_THEN_EX_MSG		"then expected near unexpected"
# define P_THEN_RET		258
# define P_THEN_DISP_CUR	1

# define P_FI_EX		5
# define P_FI_EX_MSG		"fi expected near unexpected"
# define P_FI_RET		258
# define P_FI_DISP_CUR		1

# define P_EL_EX		6
# define P_EL_EX_MSG		"else or elif expected near unexpected"
# define P_EL_RET		258
# define P_EL_DISP_CUR		1

#endif /* !DEFINES_H_ */
