/*
** my_fnmatch.c for fnmatch in /u/a1/durget_g/fnmatch
**
** Made by gilles durget
** Login   <durget_g@epita.fr>
**
** Started on  Sun Sep 19 17:13:29 2004 gilles durget
** Last update Tue Jan 18 15:14:10 2005 olivier grosliere
*/
#include <stdlib.h>
#include "my_fnmatch.h"

static int parse(const char *pat, int p, const char *str, int s);

static int isregular(char c, int esc)
{
  return esc || (c != '*' && c != '?' && c != '[' && c != '\\');
}

static int chk_interv_fst(char cp, char cs, int *p, int *neg)
{
  if (cp == ']' || cp == '-' || cp == '!')
    {
      (*p)++;
      if (cp == '!')
	{
	  *neg = 1;
	  return 0;
	}
      else
	if (cp == cs)
	  return 1;
    }
  return 0;
}

static int	chk_interv(const char *pat, int p, const char *str, int s)
{
  int		neg = 0;
  int		ok = 0;

  ok = chk_interv_fst(pat[p], str[s], &p, &neg);
  while (pat[p] != '\0' && pat[p] != ']')
    {
      if (pat[p + 1] == '-' && pat[p + 2] != ']')
	{
	  if (pat[p] <= str[s] && pat[p + 2] >= str[s] && (ok = 1))
	    if (neg)
	      return 0;
	  ++p;
	}
      else
	if (pat[p] == str[s] && (ok = 1))
	  if (neg)
	    return 0;
      ++p;
    }
  return (ok || neg) && pat[p] == ']' && parse(pat, p + 1, str, s + 1);
}

static int chk_star(const char *pat, int p, const char *str, int s)
{
  if (!pat[p])
    return 1;
  if (str[s])
    {
      if (parse(pat, p, str, s))
	return 1;
      else
	return chk_star(pat, p, str, s + 1);
    }
  else
    return 0;
}

static int	parse(const char *pat, int p, const char *str, int s)
{
  int		esc = 0;

  if (!pat[p] && !str[s])
    return 1;
  if (str[s])
    {
      if (pat[p] == '\\' && (esc = 1))
	++p;
      if (isregular(pat[p], esc))
	{
	  if (str[s] == pat[p])
	    return parse(pat, p + 1, str, s + 1);
	  return 0;
	}
      if (pat[p] == '[')
	return chk_interv(pat, p + 1, str, s);
      if (pat[p] == '*')
	return chk_star(pat, p + 1, str, s);
      return parse(pat, p + 1, str, s + 1);
    }
  if (pat[p] == '*')
    return chk_star(pat, p + 1, str, s);
  return 0;
}

int my_fnmatch(const char *pattern, const char *string, int flags)
{
  if (pattern == NULL || string == NULL)
    return 1;
  flags = 0;
  return parse(pattern, 0, string, 0) ? 0 : MY_FNM_NOMATCH;
}
