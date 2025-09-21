/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 10:28:13 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"
#include "words.h"
#include "utils.h"

static int validate_number_str(const char *str)
{
  int i;

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

static int convert_and_print(unsigned long long num, t_dict *dict)
{
  char *words;

  words = convert_to_words(num, dict);
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

static int process_number(char *num_str, char *dict_path)
{
  t_dict *dict;
  unsigned long long num;
  int error;

  if (!validate_number_str(num_str))
  {
    ft_putstr("Error\n");
    return (1);
  }
  num = parse_ull(num_str, &error);
  if (error)
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
  return (convert_and_print(num, dict));
}

int main(int argc, char **argv)
{
  if (argc == 2)
    return (process_number(argv[1], "numbers.dict"));
  else if (argc == 3)
    return (process_number(argv[2], argv[1]));
  else
  {
    ft_putstr("Error\n");
    return (1);
  }
}

/*
# Testing commands (comment block for validation)
# make re
# ./rush-02 0            # zero
# ./rush-02 42           # forty two
# ./rush-02 1000000      # one million
# ./rush-02 numbers.dict 18446744073709551615
# ./rush-02 10.4         # Error
# ./rush-02 bad.dict 7   # Dict Error (if dict unreadable or missing keys)
*/
