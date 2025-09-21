/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 18:59:45 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>

/* String utilities */
size_t				ft_strlen(const char *s);
int					ft_isspace(char c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *s);

/* Output utilities */
void				ft_putchar(char c);
void				ft_putstr(const char *s);

/* String manipulation */
char				*trim_str(const char *s);
int					is_printable(char c);

/* Number parsing */
unsigned long long	parse_ull(const char *str, int *error);

#endif
