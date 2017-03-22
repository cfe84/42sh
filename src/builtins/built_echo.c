/*
** built_echo.c for built_echo in ~/tmp/grosli_o-42sh/src/builtins
**
** Made by anass kadiri
** Login   <kadiri_a@epita.fr>
**
** Started on  Sun Jan 16 15:54:29 2005 anass kadiri
** Last update Mon Jan 17 21:16:30 2005 anass kadiri
*/

#include "builtins.h"

static const struct s_esc esc[] =
  {
    {'a', "\a"},
    {'b', "\b"},
    {'f', "\f"},
    {'n', "\n"},
    {'r', "\r"},
    {'t', "\t"},
    {'t', "\t"},
    {'v', "\v"},
    {'\\', "\\"},
    {' ', NULL}
  };


/*
** if opt is valid then interpret the option
** else print it
*/
static int	is_valid_opt(char *opt)
{
  int		i = 1;

  if (strlen(opt) == 1)
    return 0;
  while (opt[i] != '\0')
    {
      if (opt[i] != 'e' && opt[i] != 'E' && opt[i] != 'n')
	return 0;
      i++;
    }
  return 1;
}

/*
** extract option from opt
*/
static void	extract_opt(char *str, struct s_opt *opt)
{
  int		i = 1;

  while (str[i] != '\0')
    {
      if (str[i] == 'n')
	opt->n = 1;
      if (str[i] == 'e')
	opt->e = 1;
      if (str[i] == 'E')
	opt->E = 1;
      i++;
    }
}

/*
** get options from cmd
*/
static int	get_options(char **cmd, struct s_opt *opt)
{
  int		i = 1;

  while (cmd[i] != NULL && is_opt(cmd[i]))
    {
      if (is_opt(cmd[i]) && is_valid_opt(cmd[i]))
	extract_opt(cmd[i], opt);
      i++;
    }
  return i;
}

/*
** init the opt struct
*/
static void	init_opt(struct s_opt *opt)
{
  opt->n = 0;
  opt->e = 0;
  opt->E = 0;
}

/*
** my write func
** n < 0 -> write all the string
** n > 0 -> write n character of the string
*/
static void	my_write(char *str, int n)
{
  int		lenstr;

  if (n < 0)
    {
      lenstr = strlen(str);
      write(STDOUT_FILENO, str, lenstr);
    }
  else
    write(STDOUT_FILENO, str, n);
}

/*
** test if c is matched with the
** backslash-escaped characters
*/
static int	is_matched(char c)
{
  int		i = 0;

  while (esc[i].str != NULL)
    {
      if (esc[i].c == c)
	return 1;
      i++;
    }
  return 2;
}

/*
** match escaped characters
*/
static char	*match_key(char c)
{
  int		i = 0;
  char		*str;

  while (esc[i].str != NULL)
    {
      if (esc[i].c == c)
	return esc[i].str;
      i++;
    }
  if ((str = malloc(3 * sizeof (char))) == NULL)
    return NULL;
  str[0] = '\\';
  str[1] = c;
  str[2] = '\0';
  return str;
}

/*
** write a octal character
*/
static int	my_write_oct(char *str)
{
  int		i = 0;
  char		*tmp = NULL;
  char		c;
  int		oct;

  while (str[i] != '\0' && i < 3  && (str[i] >= '0' && str[i] <= '7'))
    i++;
  tmp = my_strndup(str, i);
  if (is_oct(tmp))
    {
      oct = oct2dec(tmp);
      c = oct;
      my_write(&c, 1);
      free(tmp);
    }
  else
    {
      my_write("\\", 1);
      my_write(tmp, -1);
    }
  return i;
}

/*
** interpretation of the  following  backslash-escaped
** characters in the strings:
**
**   \a     alert (bell)
**   \b     backspace
**   \c     suppress trailing newline
**   \f     form feed
**   \n     new line
**   \r     carriage return
**   \t     horizontal tab
**   \v     vertical tab
**   \\     backslash
**   \nnn   the   character  whose  ASCII  code  is  nnn (octal)
**
*/
static void	interp_str(char *str, struct s_opt *opt)
{
  int		i = 0;

  while (str[i] != '\0')
    {
      if (str[i] != '\\')
	{
	  write(STDOUT_FILENO, &(str[i]), 1);
	  i++;
	}
      else
	{
	  if (str[i + 1] != '\0')
	    {
	      if (str[i + 1] == 'c')
		opt->n = 1;
	      else
		{
		  if (isdigit(str[i + 1]))
		    i += my_write_oct(str + i + 1) - 1;
		  else
		    my_write(match_key(str[i + 1]), is_matched(str[ i + 1]));
		}
	    }
	  i += 2;
	}
    }
}

/*
** my echo builtins
** -n : Do not output the trailing newline.
** -e : Enable interpretation of the backslash-escaped characters
** -E : ?????? xpg_echo
*/
void		built_echo(char **command, struct s_glob *g)
{
  struct s_opt	opt;
  int		i = 1;
  int		e;

  g = g;
  init_opt(&opt);
  e = get_options(command, &opt);
  while (command[i] != NULL)
    {
      if (!is_opt(command[i]) || !is_valid_opt(command[i]) || i >= e)
	{
	  if (opt.e)
	    interp_str(command[i], &opt);
	  else
	    my_write(command[i], -1);
	  if (command[i + 1] != NULL &&
	      (!is_opt(command[i + 1]) || !is_valid_opt(command[i + 1])
	       || i + 1 >= e))
	    my_write(" ", 1);
	}
      i++;
    }
  if (!opt.n)
    my_write("\n", 1);
}

