/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 10:33:53 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "words.h"
#include "utils.h"
#include <stdlib.h>

char *init_result(void)
{
  char *result;
  int i;

  result = malloc(1024);
  if (!result)
    return (NULL);
  i = 0;
  while (i < 1024)
  {
    result[i] = '\0';
    i++;
  }
  return (result);
}

void init_scales(unsigned long long *scales)
{
  scales[0] = 1000000000000000000ULL;
  scales[1] = 1000000000000000ULL;
  scales[2] = 1000000000000ULL;
  scales[3] = 1000000000ULL;
  scales[4] = 1000000ULL;
  scales[5] = 1000ULL;
}

int append_word(char **dest, const char *word, int *first)
{
  size_t len;
  size_t word_len;
  char *ptr;

  if (!word)
    return (0);
  len = ft_strlen(*dest);
  word_len = ft_strlen(word);
  if (len + word_len + 2 >= 1024)
    return (0);
  ptr = *dest + len;
  if (!*first)
  {
    *ptr++ = ' ';
    len++;
  }
  while (*word)
    *ptr++ = *word++;
  *ptr = '\0';
  *first = 0;
  return (1);
}

static int convert_hundreds(unsigned long long n, t_dict *dict,
                            t_convert_state *state)
{
  if (n >= 100)
  {
    if (!append_word(state->result, dict_get(dict, n / 100), state->first))
      return (0);
    if (!append_word(state->result, dict_get(dict, 100), state->first))
      return (0);
    n %= 100;
  }
  if (n >= 20)
  {
    if (!append_word(state->result, dict_get(dict, (n / 10) * 10),
                     state->first))
      return (0);
    n %= 10;
  }
  if (n > 0)
  {
    if (!append_word(state->result, dict_get(dict, n), state->first))
      return (0);
  }
  return (1);
}

static int convert_group(unsigned long long n, unsigned long long scale,
                         t_dict *dict, t_convert_state *state)
{
  unsigned long long group;

  if (n >= scale)
  {
    group = n / scale;
    if (!convert_hundreds(group, dict, state))
      return (0);
    if (!append_word(state->result, dict_get(dict, scale), state->first))
      return (0);
  }
  return (1);
}

static char *process_scales(unsigned long long num, t_dict *dict,
                            t_convert_state *state)
{
  unsigned long long scales[6];
  int i;

  init_scales(scales);
  i = 0;
  while (i < 6)
  {
    if (!convert_group(num, scales[i], dict, state))
    {
      free(*state->result);
      return (NULL);
    }
    num %= scales[i];
    i++;
  }
  if (!convert_hundreds(num, dict, state))
  {
    free(*state->result);
    return (NULL);
  }
  return (*state->result);
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
