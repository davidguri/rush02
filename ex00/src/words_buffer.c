/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:40:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 19:02:42 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "words.h"
#include <stdlib.h>

char	*init_result(void)
{
	char	*result;
	int		i;

	result = malloc(1024);
	if (!result)
		return (NULL);
	i = 0;
	while (i < 1024)
	{
		result[i] = '\0';
		i++;
	}
	return (result);
}

int	append_word(char **dest, const char *word, int *first)
{
	size_t	len;
	size_t	word_len;
	char	*ptr;

	if (!word)
		return (0);
	len = ft_strlen(*dest);
	word_len = ft_strlen(word);
	if (len + word_len + 2 >= 1024)
		return (0);
	ptr = *dest + len;
	if (!*first)
	{
		*ptr++ = ' ';
	}
	while (*word)
		*ptr++ = *word++;
	*ptr = '\0';
	*first = 0;
	return (1);
}
