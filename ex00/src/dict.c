/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 19:41:36 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dict.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <unistd.h>

static t_dict	*init_dict(void)
{
	t_dict	*dict;

	dict = malloc(sizeof(t_dict));
	if (!dict)
		return (NULL);
	dict->entries = malloc(sizeof(t_entry) * 128);
	if (!dict->entries)
	{
		free(dict);
		return (NULL);
	}
	dict->count = 0;
	dict->capacity = 128;
	return (dict);
}

t_dict	*load_dict(const char *path)
{
	t_dict	*dict;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	dict = init_dict();
	if (!dict)
	{
		close(fd);
		return (NULL);
	}
	if (!read_dict_file(fd, dict))
	{
		free_dict(dict);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (dict);
}

char	*dict_get(t_dict *dict, unsigned long long key)
{
	size_t	i;

	i = 0;
	while (i < dict->count)
	{
		if (dict->entries[i].has_ull && dict->entries[i].key == key)
			return (dict->entries[i].value);
		i++;
	}
	return (NULL);
}

char	*dict_get_str(t_dict *dict, const char *key_str)
{
	size_t		i;
	const char	*a;
	const char	*b = key_str;
	size_t		j;

	i = 0;
	a = dict->entries[i].key_str;
	while (i < dict->count)
	{
		if (dict->entries[i].key_str && key_str)
		{
			j = 0;
			while (a[j] && b[j] && a[j] == b[j])
				j++;
			if (a[j] == '\0' && b[j] == '\0')
				return (dict->entries[i].value);
		}
		i++;
	}
	return (NULL);
}

void	free_dict(t_dict *dict)
{
	size_t	i;

	if (!dict)
		return ;
	i = 0;
	while (i < dict->count)
	{
		free(dict->entries[i].value);
		free(dict->entries[i].key_str);
		i++;
	}
	free(dict->entries);
	free(dict);
}
