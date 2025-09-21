/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:30:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 19:32:58 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dict.h"
#include "../include/utils.h"
#include <stdlib.h>

static int	resize_dict(t_dict *dict)
{
	t_entry	*new_entries;

	new_entries = malloc(sizeof(t_entry) * dict->capacity * 2);
	if (!new_entries)
		return (0);
	while (dict->count > 0)
	{
		dict->count--;
		new_entries[dict->count] = dict->entries[dict->count];
	}
	free(dict->entries);
	dict->entries = new_entries;
	dict->capacity *= 2;
	dict->count = dict->capacity / 2;
	return (1);
}

int	add_entry(t_dict *dict, t_entry *new_entry)
{
	if (dict->count >= dict->capacity)
	{
		if (!resize_dict(dict))
			return (0);
	}
	dict->entries[dict->count] = *new_entry;
	dict->count++;
	return (1);
}
