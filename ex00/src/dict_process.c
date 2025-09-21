/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:30:00 by davidguri         #+#    #+#             */
/*   Updated: 2025/09/21 19:32:58 by davidguri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dict.h"
#include "../include/utils.h"
#include <unistd.h>

int	process_bytes(char *buffer, int i, t_read_ctx *ctx)
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

int	process_remaining(t_read_ctx *ctx)
{
	if (ctx->j > 0)
	{
		ctx->line[ctx->j] = '\0';
		if (!parse_line(ctx->line, ctx->dict))
			return (0);
	}
	return (1);
}

int	read_chunk(int fd, char *buffer, t_read_ctx *ctx)
{
	int	bytes;
	int	i;

	bytes = read(fd, buffer, 4095);
	if (bytes <= 0)
		return (bytes);
	i = 0;
	while (i < bytes)
	{
		if (!process_bytes(buffer, i, ctx))
			return (-1);
		i++;
	}
	return (bytes);
}
