/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 10:33:29 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORDS_H
#define WORDS_H

#include "dict.h"

/* Word conversion state */
typedef struct s_convert_state
{
  char **result;
  int *first;
} t_convert_state;

/* Convert number to words using dictionary */
char *convert_to_words(unsigned long long num, t_dict *dict);

/* Helper for building word strings */
int append_word(char **dest, const char *word, int *first);

/* Initialize scale values (internal) */
void init_scales(unsigned long long *scales);

/* Initialize result buffer (internal) */
char *init_result(void);

#endif
