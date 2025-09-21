/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_parse.c                                       :+:      :+:    :+:   */
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

static int	split_line(char *line, char **key_part)
{
	char	*colon;

	colon = line;
	while (*colon && *colon != ':')
		colon++;
	if (*colon != ':')
		return (0);
	*colon = '\0';
	*key_part = line;
	return (1);
}

static int	create_entry(char *key_str, char *value_str, t_entry *entry)
{
	int	error;

	entry->key = parse_ull(key_str, &error);
	entry->key_str = key_str;
	if (error)
		entry->has_ull = 0;
	else
		entry->has_ull = 1;
	entry->value = value_str;
	return (1);
}

int	parse_line(char *line, t_dict *dict)
{
	char	*key_part;
	char	*key_token;
	char	*value;
	t_entry	entry;

	if (!split_line(line, &key_part))
		return (1);
	key_token = trim_str(key_part);
	if (!key_token)
		return (0);
	value = trim_str(key_part + ft_strlen(key_part) + 1);
	if (!value)
	{
		free(key_token);
		return (0);
	}
	create_entry(key_token, value, &entry);
	if (!add_entry(dict, &entry))
	{
		free(key_token);
		free(value);
		return (0);
	}
	return (1);
}
