/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:40:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 17:39:08 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "words.h"
#include "utils.h"
#include <stdlib.h>

static const char *skip_prefix_zeros(const char *s)
{
  const char *p;

  p = s;
  while (*p && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' || *p == '\v' || *p == '\f'))
    p++;
  if (*p == '+')
    p++;
  while (*p == '0')
    p++;
  return (p);
}

static int assemble_from_groups(int *groups, int n, t_dict *dict,
                                t_convert_state *st)
{
  int i;

  i = n - 1;
  while (i >= 0)
  {
    if (groups[i] > 0)
    {
      if (!convert_hundreds((unsigned long long)groups[i], dict, st))
        return (0);
      if (i > 0)
      {
        char *scale_key = build_scale_key_string(i);
        char *scale_word;
        if (!scale_key)
          return (0);
        scale_word = dict_get_str(dict, scale_key);
        free(scale_key);
        if (!append_word(st->result, scale_word, st->first))
          return (0);
      }
    }
    i--;
  }
  return (1);
}

char *convert_to_words_str(const char *num_str, t_dict *dict)
{
  const char *p;
  int *groups;
  int n;
  char *res;
  int first;
  t_convert_state st;
  size_t len;
  int ok;

  p = skip_prefix_zeros(num_str);
  if (!*p)
    return (ft_strdup(dict_get(dict, 0)));
  res = init_result();
  if (!res)
    return (NULL);
  first = 1;
  st.result = &res;
  st.first = &first;
  len = ft_strlen(p);
  n = (int)((len + 2) / 3);
  groups = (int *)malloc(sizeof(int) * (size_t)n);
  if (!groups)
  {
    free(res);
    return (NULL);
  }
  ok = split_groups(p, groups, &n);
  if (!ok)
  {
    free(groups);
    free(res);
    return (NULL);
  }
  ok = assemble_from_groups(groups, n, dict, &st);
  free(groups);
  if (!ok)
  {
    free(res);
    return (NULL);
  }
  return (res);
}

char *convert_to_words(unsigned long long num, t_dict *dict)
{
  char *result;
  int first;
  t_convert_state state;

  result = init_result();
  if (!result)
    return (NULL);
  first = 1;
  state.result = &result;
  state.first = &first;
  if (num == 0)
  {
    if (!append_word(&result, dict_get(dict, 0), &first))
    {
      free(result);
      return (NULL);
    }
    return (result);
  }
  return (process_scales(num, dict, &state));
}
