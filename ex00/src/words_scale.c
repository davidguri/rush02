/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_scale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:40:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 19:27:05 by davidguri        ###   ########.fr       */
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
