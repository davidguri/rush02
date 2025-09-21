/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 10:28:13 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

static int check_number_part(const char *str, int *i)
{
  if (!str[*i] || str[*i] < '0' || str[*i] > '9')
  {
    return (0);
  }
  return (1);
}

static int process_digits(const char *str, int *i,
                          unsigned long long *result)
{
  unsigned long long prev;

  while (str[*i] >= '0' && str[*i] <= '9')
  {
    prev = *result;
    *result = *result * 10 + (str[*i] - '0');
    if (*result < prev)
    {
      return (0);
    }
    (*i)++;
  }
  return (1);
}

static int finalize_parse(const char *str, int i)
{
  while (ft_isspace(str[i]))
    i++;
  return (str[i] == '\0');
}

static int skip_prefix(const char *str)
{
  int i;

  i = 0;
  while (ft_isspace(str[i]))
    i++;
  if (str[i] == '+')
    i++;
  return (i);
}

unsigned long long parse_ull(const char *str, int *error)
{
  unsigned long long result;
  int i;

  *error = 0;
  result = 0;
  i = skip_prefix(str);
  if (!check_number_part(str, &i))
  {
    *error = 1;
    return (0);
  }
  if (!process_digits(str, &i, &result))
  {
    *error = 1;
    return (0);
  }
  if (!finalize_parse(str, i))
  {
    *error = 1;
    return (0);
  }
  return (result);
}
