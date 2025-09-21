/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 17:43:15 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "dict.h"
#include "utils.h"

int parse_line(char *line, t_dict *dict);

typedef struct s_read_ctx
{
  char *line;
  int j;
  t_dict *dict;
} t_read_ctx;

static int add_entry(t_dict *dict, unsigned long long key, char *key_str,
                     int has_ull, char *val)
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
  dict->entries[dict->count].key_str = key_str;
  dict->entries[dict->count].has_ull = has_ull;
  dict->entries[dict->count].value = val;
  dict->count++;
  return (1);
}

int parse_line(char *line, t_dict *dict)
{
  char *colon;
  char *value;
  char *key_token;
  unsigned long long key;
  int error;

  colon = line;
  while (*colon && *colon != ':')
    colon++;
  if (*colon != ':')
    return (1);
  *colon = '\0';
  key_token = trim_str(line);
  if (!key_token)
    return (0);
  key = parse_ull(key_token, &error);
  value = trim_str(colon + 1);
  if (!value)
  {
    free(key_token);
    return (0);
  }
  if (!add_entry(dict, key, key_token, error ? 0 : 1, value))
  {
    free(key_token);
    free(value);
    return (0);
  }
  return (1);
}

static int process_bytes(char *buffer, int i, t_read_ctx *ctx)
{
  if (buffer[i] == '\n')
  {
    ctx->line[ctx->j] = '\0';
    if (ctx->j > 0 && !parse_line(ctx->line, ctx->dict))
      return (0);
    ctx->j = 0;
  }
  else if (ctx->j < 4095)
    ctx->line[(ctx->j)++] = buffer[i];
  return (1);
}

int read_dict_file(int fd, t_dict *dict)
{
  char buffer[4096];
  char line[4096];
  int bytes;
  int i;
  t_read_ctx ctx;

  ctx.line = line;
  ctx.j = 0;
  ctx.dict = dict;
  bytes = read(fd, buffer, sizeof(buffer) - 1);
  while (bytes > 0)
  {
    i = 0;
    while (i < bytes)
    {
      if (!process_bytes(buffer, i, &ctx))
        return (0);
      i++;
    }
    bytes = read(fd, buffer, sizeof(buffer) - 1);
  }
  if (bytes >= 0)
  {
    if (ctx.j > 0)
    {
      ctx.line[ctx.j] = '\0';
      if (!parse_line(ctx.line, ctx.dict))
        return (0);
    }
    return (1);
  }
  return (0);
}
