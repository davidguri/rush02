/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_scale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:40:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 20:33:47 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/words.h"
#include <stdlib.h>

void	init_scales(unsigned long long *scales)
{
	scales[0] = 1000000000000000000ULL;
	scales[1] = 1000000000000000ULL;
	scales[2] = 1000000000000ULL;
	scales[3] = 1000000000ULL;
	scales[4] = 1000000ULL;
	scales[5] = 1000ULL;
}

unsigned long long	get_scale_value(int idx)
{
	if (idx == 1)
		return (1000ULL);
	if (idx == 2)
		return (1000000ULL);
	if (idx == 3)
		return (1000000000ULL);
	if (idx == 4)
		return (1000000000000ULL);
	if (idx == 5)
		return (1000000000000000ULL);
	if (idx == 6)
		return (1000000000000000000ULL);
	return (0ULL);
}

char	*build_scale_key_string(int idx)
{
	int		total_zeroes;
	int		i;
	char	*s;

	if (idx <= 0)
		return (NULL);
	total_zeroes = idx * 3;
	s = malloc((size_t)total_zeroes + 2);
	if (!s)
		return (NULL);
	s[0] = '1';
	i = 0;
	while (i < total_zeroes)
	{
		s[1 + i] = '0';
		i++;
	}
	s[1 + total_zeroes] = '\0';
	return (s);
}

int	append_scale_word(int i, t_dict *dict, t_convert_state *st)
{
	unsigned long long	scale_value;
	char				*word;
	char				*key;

	word = NULL;
	if (i >= 1 && i <= 6)
	{
		scale_value = get_scale_value(i);
		word = dict_get(dict, scale_value);
	}
	else if (i > 6)
	{
		key = build_scale_key_string(i);
		if (!key)
			return (0);
		word = dict_get_str(dict, key);
		free(key);
	}
	if (!word)
		return (0);
	return (append_word(st->result, word, st->first));
}
