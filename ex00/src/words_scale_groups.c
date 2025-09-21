/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_scale_groups.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:40:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 20:36:57 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/words.h"
#include <stdlib.h>

static int	convert_group(unsigned long long n, unsigned long long scale,
		t_dict *dict, t_convert_state *state)
{
	unsigned long long	group;

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

char	*process_scales(unsigned long long num, t_dict *dict,
		t_convert_state *state)
{
	unsigned long long	scales[6];
	int					i;

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
