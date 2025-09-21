/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 19:00:11 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORDS_H
# define WORDS_H

# include "dict.h"

typedef struct s_convert_state
{
	char			**result;
	int				*first;
}					t_convert_state;

char				*convert_to_words(unsigned long long num, t_dict *dict);
char				*convert_to_words_str(const char *num_str, t_dict *dict);

int					append_word(char **dest, const char *word, int *first);

char				*init_result(void);

void				init_scales(unsigned long long *scales);
unsigned long long	get_scale_value(int idx);
char				*build_scale_key_string(int idx);

int					split_groups(const char *s, int *groups, int *count);

int					convert_hundreds(unsigned long long n, t_dict *dict,
						t_convert_state *state);
char				*process_scales(unsigned long long num, t_dict *dict,
						t_convert_state *state);

#endif
