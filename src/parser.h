/*
** parser.h for 42sh in src
**
** Made by feval_c
** Login   <feval_c@epita.fr>
**
** Started on  Fri Jan  7 14:38:13 2005 feval_c
** Last update Sun Jan 16 21:19:03 2005 feval_c
*/

#ifndef PARSER_H_
# define PARSER_H_

# include "global.h"
# include "lexer.h"
# include "ast.h"

# ifdef SUN
char			*strdup(const char *a);
# endif /* !SUN */

/*
** in parser.c
*/
struct s_ast_list	*parse(int mode, char *file, struct s_glob *g);

/*
** in parse_rules.c
*/
struct s_ast		*rule_if(struct s_parse *p, struct s_glob *g);
struct s_ast		*rule_until(struct s_parse *p, struct s_glob *g);
struct s_ast		*rule_while(struct s_parse *p, struct s_glob *g);
struct s_ast		*rule_for(struct s_parse *p, struct s_glob *g);
struct s_ast		*function_def(struct s_parse *p, struct s_glob *g);

/*
** in parse_cmd.c
*/
struct s_ast		*simple_command(struct s_parse *p, struct s_glob *g);
int			redirection(struct s_parse *p,
				    struct s_redir **redir,
				    struct s_glob *g);
struct s_ast		*shell_command(struct s_parse *p, struct s_glob *g);
struct s_ast_list	*compound_list(struct s_parse *p, struct s_glob *g);
struct s_ast		*command(struct s_parse *p, struct s_glob *g);

/*
** in parse_lists.c
*/
struct s_ast		*and_or(struct s_parse *p, struct s_glob *g);
struct s_ast_list	*simple_list(struct s_parse *p,
				     struct s_glob *g);

#endif /* !PARSER_H_ */
