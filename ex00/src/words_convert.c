/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_convert.c                                    :+:      :+:    :+:   */
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

char	*convert_to_words_str(const char *num_str, t_dict *dict)
{
	const char		*p;
	int				*groups;
	int				n;
	t_convert_state	st;
	char			*zero_result;

	p = skip_prefix_zeros(num_str);
	zero_result = handle_zero_case(p, dict);
	if (zero_result)
		return (zero_result);
	if (!init_conversion(p, &groups, &n, &st))
		return (NULL);
	if (!split_groups(p, groups, &n)
		|| !assemble_from_groups(groups, n, dict, &st))
	{
		free(groups);
		free(*st.result);
		free(st.first);
		return (NULL);
	}
	free(groups);
	free(st.first);
	return (*st.result);
}

char	*convert_to_words(unsigned long long num, t_dict *dict)
{
	t_convert_state	state;

	if (num == 0)
		return (handle_zero_number(dict));
	state.result = malloc(sizeof(char *));
	if (!state.result)
		return (NULL);
	*state.result = init_result();
	if (!*state.result)
	{
		free(state.result);
		return (NULL);
	}
	state.first = malloc(sizeof(int));
	if (!state.first)
	{
		free(*state.result);
		free(state.result);
		return (NULL);
	}
	*state.first = 1;
	return (process_scales(num, dict, &state));
}
