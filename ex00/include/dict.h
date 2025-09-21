/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 10:33:53 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
#define DICT_H

#include <stdlib.h>

/* Dictionary entry structure */
typedef struct s_entry
{
  unsigned long long key;
  char *value;
} t_entry;

/* Dictionary container */
typedef struct s_dict
{
  t_entry *entries;
  size_t count;
  size_t capacity;
} t_dict;

/* Dictionary operations */
t_dict *load_dict(const char *path);
char *dict_get(t_dict *dict, unsigned long long key);
void free_dict(t_dict *dict);
int parse_line(char *line, t_dict *dict);
int read_dict_file(int fd, t_dict *dict);

#endif
