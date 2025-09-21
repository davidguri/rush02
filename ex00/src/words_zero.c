/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_zero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:20:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 19:27:05 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/words.h"
#include <stdlib.h>

char	*handle_zero_case(const char *p, t_dict *dict)
{
	if (!*p)
		return (ft_strdup(dict_get(dict, 0)));
	return (NULL);
}

char	*handle_zero_number(t_dict *dict)
{
	char	*result;
	int		first;

	result = init_result();
	if (!result)
		return (NULL);
	first = 1;
	if (!append_word(&result, dict_get(dict, 0), &first))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
