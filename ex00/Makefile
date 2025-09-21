# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davidguri <davidguri@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/21 10:00:00 by student           #+#    #+#              #
#    Updated: 2025/09/21 19:42:04 by davidguri        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= rush-02

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -Iinclude

SRCDIR		= src
OBJDIR		= obj

SRCS		= $(SRCDIR)/main.c \
			  $(SRCDIR)/dict.c \
			  $(SRCDIR)/dict_read.c \
			  $(SRCDIR)/dict_process.c \
			  $(SRCDIR)/words_buffer.c \
			  $(SRCDIR)/words_scale.c \
			  $(SRCDIR)/words_hundreds.c \
			  $(SRCDIR)/words_groups.c \
			  $(SRCDIR)/words_convert.c \
			  $(SRCDIR)/words_prefix.c \
			  $(SRCDIR)/words_zero.c \
			  $(SRCDIR)/utils.c \
			  $(SRCDIR)/string.c \
			  $(SRCDIR)/parse.c \
			  $(SRCDIR)/output.c

OBJS		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
