/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 19:32:58 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

# include <stdlib.h>

/* Dictionary entry structure */
typedef struct s_entry
{
	unsigned long long	key;
	char				*key_str;
	int					has_ull;
	char				*value;
}						t_entry;

typedef struct s_dict
{
	t_entry				*entries;
	size_t				count;
	size_t				capacity;
}						t_dict;

typedef struct s_read_ctx
{
	char	*line;
	int		j;
	t_dict	*dict;
}			t_read_ctx;

/* Main dictionary operations */
t_dict					*load_dict(const char *path);
char					*dict_get(t_dict *dict, unsigned long long key);
char					*dict_get_str(t_dict *dict, const char *key_str);
void					free_dict(t_dict *dict);

/* Dictionary entry management */
int						add_entry(t_dict *dict, t_entry *new_entry);

/* Dictionary parsing */
int						parse_line(char *line, t_dict *dict);

/* Dictionary file processing */
int						read_dict_file(int fd, t_dict *dict);
int						process_bytes(char *buffer, int i, t_read_ctx *ctx);
int						process_remaining(t_read_ctx *ctx);
int						read_chunk(int fd, char *buffer, t_read_ctx *ctx);

#endif
