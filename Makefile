# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 13:29:11 by joseanto          #+#    #+#              #
#    Updated: 2025/02/07 13:29:12 by joseanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILER = c++
INCLUDE = -I ./includes
FLAGS = -Wall -Wextra -Werror -std=c++98 $(INCLUDE) -o
NAME = ircserv
FILE = ./ft_irc.cpp\
		./src/signal.cpp\
		./class/Server/Server.cpp\
		./class/Server/comm.cpp\
		./class/Server/cmdsServer.cpp\
		./class/Server/getServer.cpp\
		./class/Server/setServer.cpp\
		./class/Server/utils/invite.cpp\
		./class/Server/utils/join.cpp\
		./class/Server/utils/kick.cpp\
		./class/Server/utils/list.cpp\
		./class/Server/utils/mode.cpp\
		./class/Server/utils/nick.cpp\
		./class/Server/utils/who.cpp\
		./class/Server/utils/utils.cpp\
		./class/Client/Client.cpp\
		./class/Client/getClient.cpp\
		./class/Client/setClient.cpp\
		./class/Channel/Channel.cpp\
		./class/Channel/utils/utils.cpp
RM = rm

all: $(NAME)

$(NAME):
		$(COMPILER) $(FLAGS) $(NAME) $(FILE)

clean:
		$(RM) $(NAME)

re: clean all

fclean:	clean

.PHONY: all clean re