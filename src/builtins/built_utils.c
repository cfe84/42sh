/*
** built_utils.c for built_utils in /u/a1/kadiri_a/tmp/grosli_o-42sh/src/builtins
**
** Made by anass kadiri
** Login   <kadiri_a@epita.fr>
**
** Started on  Sun Jan 16 18:42:47 2005 anass kadiri
** Last update Mon Jan 17 20:36:17 2005 anass kadiri
*/

#include "builtins.h"

static const char oct_tab[] = "01234567";
static const char oct_cmp[] = "76543210";

/*
** my strndup key
*/
char    *my_strndup(const char *src, int n)
{
  char  *res;
  int   i = 0;

  if (src == NULL)
    return NULL;
  if ((res = malloc((n + 1) * sizeof (char))) == NULL)
    return NULL;
  for (i = 0; i < n; i++)
    res[i] = src[i];
  res[i] = '\0';
  return res;
}

/*
** test if str is written in octal
*/
int	is_oct(char *oct)
{
  int		i = 0;
  int		len;

  len = strlen(oct);
  if(len == 0)
    return 0;
  for (i = 0; i < len; i++)
    if (oct[i] < '0' || oct[i] > '7')
      return 0;
  return 1;
}

/*
** calcul x^n
*/
static int     power(int x, int n)
{
  int		res = 1;

  while (n > 0)
    {
      res *= x;
      n--;
    }
  return res;
}

/*
** convert unsigned octal to decimal
*/
int             oct2dec(char *oct)
{
  int           res = 0;
  int           i = 0;
  int           n = 0;
  int		len;

  len = strlen(oct);
  for (i = len - 1, n = 0; i >= 0; i--, n++)
    res += (oct[i] - '0') * power(8, n);
  return res;
}

/*
** test if opt is an option
*/
int	is_opt(char *opt)
{
  if (opt[0] == '-')
    return 1;
  return 0;
}


/* /\* */
/* ** convert oct char to int */
/* *\/ */
/* static int     oc2i(char c) */
/* { */
/*   return c - '0'; */
/* } */


/* /\* */
/* ** convert an int to an oct char */
/* *\/ */
/* static char    i2oc(int n) */
/* { */
/*   return n + '0'; */
/* } */

/* /\* */
/* ** convert signed oct to decimal */
/* *\/ */
/* static int      oct2dec_sig(char *tm) */
/* { */
/*   int           i = 0; */
/*   int           j = 0; */
/*   int           ok = 1; */
/*   int           res; */
/*   int           tmp = 0; */
/*   char          r = '1'; */
/*   int		len; */

/*   len = strlen(tm); */
/*   for (i = 0; i < len; i++) */
/*     { */
/*       ok = 1; */
/*       for (j = 0; j < 8 && ok; j++) */
/*         if (tm[i] == oct_tab[j]) */
/*           { */
/*             ok = 0; */
/*             tm[i] = oct_cmp[j]; */
/*           } */
/*     } */
/*   for (i = len - 1; i >= 0; i--) */
/*     { */
/*       tmp = oc2i(tm[i]) + oc2i(r); */
/*       r = i2oc(tmp / 8); */
/*       tm[i] = i2oc(tmp % 8); */
/*     } */
/*   res = oct2dec_pos(tm); */
/*   free(tm); */
/*   return -res; */
/* } */

/* /\* */
/* ** convert (signed and unsigned) oct to decimal */
/* *\/ */
/* int             oct2dec(char *oct) */
/* { */
/*   char          *tm; */
/*   int           i = 0; */

/* /\*   if (oc2i(oct[0]) > 7) *\/ */
/* /\*     { *\/ */
/* /\*       tm = my_strndup(oct, strlen(oct)); *\/ */
/* /\*       return oct2dec_sig(tm); *\/ */
/* /\*     } *\/ */
/* /\*   else *\/ */
/*     return oct2dec_pos(oct); */
/* } */

