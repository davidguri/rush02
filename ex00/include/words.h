/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 19:19:10 by davidguri        ###   ########.fr       */
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

// Main conversion functions
char				*convert_to_words(unsigned long long num, t_dict *dict);
char				*convert_to_words_str(const char *num_str, t_dict *dict);

// Zero handling functions
char				*handle_zero_case(const char *p, t_dict *dict);
char				*handle_zero_number(t_dict *dict);

// Group handling functions
int					init_conversion(const char *p, int **groups, int *n,
						t_convert_state *st);
int					assemble_from_groups(int *groups, int n, t_dict *dict,
						t_convert_state *st);
int					split_groups(const char *s, int *groups, int *count);

// Scale handling functions
int					append_scale_word(int i, t_dict *dict, t_convert_state *st);
void				init_scales(unsigned long long *scales);
unsigned long long	get_scale_value(int idx);
char				*build_scale_key_string(int idx);

// Prefix handling functions
const char			*skip_prefix_zeros(const char *s);

// Utility functions
int					append_word(char **dest, const char *word, int *first);
char				*init_result(void);
int					convert_hundreds(unsigned long long n, t_dict *dict,
						t_convert_state *state);
char				*process_scales(unsigned long long num, t_dict *dict,
						t_convert_state *state);

#endif
