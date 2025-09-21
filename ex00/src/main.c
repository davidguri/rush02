/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 19:27:05 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dict.h"
#include "../include/utils.h"
#include "../include/words.h"

static int	validate_number_str(const char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	while (ft_isspace(str[i]))
		i++;
	return (str[i] == '\0');
}

static int	convert_and_print_str(const char *num_str, t_dict *dict)
{
	char	*words;

	words = convert_to_words_str(num_str, dict);
	if (!words)
	{
		ft_putstr("Dict Error\n");
		free_dict(dict);
		return (1);
	}
	ft_putstr(words);
	ft_putchar('\n');
	free(words);
	free_dict(dict);
	return (0);
}

static int	process_number(char *num_str, char *dict_path)
{
	t_dict	*dict;

	if (!validate_number_str(num_str))
	{
		ft_putstr("Error\n");
		return (1);
	}
	dict = load_dict(dict_path);
	if (!dict)
	{
		ft_putstr("Dict Error\n");
		return (1);
	}
	return (convert_and_print_str(num_str, dict));
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		return (process_number(argv[1], "numbers.dict"));
	}
	else if (argc == 3)
	{
		return (process_number(argv[2], argv[1]));
	}
	else
	{
		ft_putstr("Error\n");
		return (1);
	}
}
