/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/09/21 10:28:13 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void ft_putchar(char c)
{
  write(1, &c, 1);
}

void ft_putstr(const char *s)
{
  if (s)
    write(1, s, ft_strlen(s));
}
