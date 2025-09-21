/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 10:28:13 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

int is_printable(char c)
{
  return (c >= 32 && c <= 126);
}

static void copy_trimmed(char *result, const char *start, size_t len)
{
  size_t i;

  i = 0;
  while (i < len)
  {
    result[i] = start[i];
    i++;
  }
  result[i] = '\0';
}

static int validate_content(const char *start, const char *end)
{
  size_t i;

  i = 0;
  while (start + i < end)
  {
    if (!is_printable(start[i]) && !ft_isspace(start[i]))
      return (0);
    i++;
  }
  return (1);
}

char *trim_str(const char *s)
{
  const char *start;
  const char *end;
  char *result;
  size_t len;

  start = s;
  while (*start && ft_isspace(*start))
    start++;
  end = start;
  while (*end)
    end++;
  while (end > start && ft_isspace(*(end - 1)))
    end--;
  if (!validate_content(start, end))
    return (NULL);
  len = end - start;
  result = malloc(len + 1);
  if (!result)
    return (NULL);
  copy_trimmed(result, start, len);
  return (result);
}
