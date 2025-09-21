/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_prefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:20:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 19:27:05 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include "../include/words.h"

const char	*skip_prefix_zeros(const char *s)
{
	const char	*p;

	p = s;
	while (*p && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r'
			|| *p == '\v' || *p == '\f'))
		p++;
	if (*p == '+')
		p++;
	while (*p == '0')
		p++;
	return (p);
}
