/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_groups.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:40:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 20:36:57 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/words.h"
#include <stdlib.h>

static int	calc_number_params(const char *p, int *len_digits, int *max_groups)
{
	*len_digits = 0;
	while (p[*len_digits] >= '0' && p[*len_digits] <= '9')
		(*len_digits)++;
	if (*len_digits <= 0)
		return (0);
	*max_groups = (*len_digits + 2) / 3;
	return (1);
}

static int	allocate_groups(int **groups, int max_groups)
{
	*groups = (int *)malloc(sizeof(int) * (size_t)max_groups);
	return (*groups != NULL);
}

static int	init_convert_state(t_convert_state *st)
{
	st->result = (char **)malloc(sizeof(char *));
	if (!st->result)
		return (0);
	*st->result = init_result();
	if (!*st->result)
	{
		free(st->result);
		return (0);
	}
	st->first = (int *)malloc(sizeof(int));
	if (!st->first)
	{
		free(*st->result);
		free(st->result);
		return (0);
	}
	*st->first = 1;
	return (1);
}

int	init_conversion(const char *p, int **groups, int *n, t_convert_state *st)
{
	int	len_digits;
	int	max_groups;

	if (!calc_number_params(p, &len_digits, &max_groups))
		return (0);
	if (!allocate_groups(groups, max_groups))
		return (0);
	if (!init_convert_state(st))
	{
		free(*groups);
		return (0);
	}
	if (n)
		*n = 0;
	return (1);
}

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

int	assemble_from_groups(int *groups, int n, t_dict *dict, t_convert_state *st)
{
	int	i;

	i = n - 1;
	while (i >= 0)
	{
		if (groups[i] > 0)
		{
			if (!convert_hundreds((unsigned long long)groups[i], dict, st))
				return (0);
			if (i > 0)
			{
				if (!append_scale_word(i, dict, st))
					return (0);
			}
		}
		i--;
	}
	return (1);
}
