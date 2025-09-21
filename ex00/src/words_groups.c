/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_groups.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:40:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 19:22:59 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/words.h"
#include <stdlib.h>

static int	read_group_val(const char *s, int start, int end)
{
	int	v;
	int	i;

	v = 0;
	i = start;
	while (i <= end)
	{
		v = v * 10 + (s[i] - '0');
		i++;
	}
	return (v);
}

int	split_groups(const char *s, int *groups, int *count)
{
	int	len;
	int	i;
	int	g;

	len = 0;
	while (s[len])
		len++;
	*count = 0;
	i = len;
	while (i > 0)
	{
		if (i >= 3)
			g = 3;
		else
			g = i;
		groups[*count] = read_group_val(s, i - g, i - 1);
		(*count)++;
		i -= g;
	}
	return (1);
}

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
