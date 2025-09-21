/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 10:33:29 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "dict.h"
#include "utils.h"

int parse_line(char *line, t_dict *dict);

static int add_entry(t_dict *dict, unsigned long long key, char *val)
{
  t_entry *new_entries;

  if (dict->count >= dict->capacity)
  {
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
  }
  dict->entries[dict->count].key = key;
  dict->entries[dict->count].value = val;
  dict->count++;
  return (1);
}

int parse_line(char *line, t_dict *dict)
{
  char *colon;
  char *value;
  unsigned long long key;
  int error;

  colon = line;
  while (*colon && *colon != ':')
    colon++;
  if (*colon != ':')
    return (1);
  *colon = '\0';
  key = parse_ull(line, &error);
  if (error)
    return (1);
  value = trim_str(colon + 1);
  if (!value)
    return (0);
  if (!add_entry(dict, key, value))
  {
    free(value);
    return (0);
  }
  return (1);
}

static int process_bytes(char *buffer, char *line, int *j, int i, t_dict *dict)
{
  if (buffer[i] == '\n')
  {
    line[*j] = '\0';
    if (*j > 0 && !parse_line(line, dict))
      return (0);
    *j = 0;
  }
  else if (*j < 4095)
    line[(*j)++] = buffer[i];
  return (1);
}

int read_dict_file(int fd, t_dict *dict)
{
  char buffer[4096];
  char line[4096];
  int bytes;
  int j;
  int i;

  j = 0;
  bytes = read(fd, buffer, sizeof(buffer) - 1);
  while (bytes > 0)
  {
    i = 0;
    while (i < bytes)
    {
      if (!process_bytes(buffer, line, &j, i, dict))
        return (0);
      i++;
    }
    bytes = read(fd, buffer, sizeof(buffer) - 1);
  }
  return (bytes >= 0);
}
