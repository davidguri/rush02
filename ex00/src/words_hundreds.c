/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_hundreds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:40:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 17:27:58 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "words.h"

int convert_hundreds(unsigned long long n, t_dict *dict, t_convert_state *state)
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
