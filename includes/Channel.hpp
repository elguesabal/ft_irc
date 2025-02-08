/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:50 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:28:51 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CHANNEL_HPP
#define CHANNEL_HPP

class Client;

class Channel {
	public:
		struct ClientChanell {
			Client *client;
			bool o;

			ClientChanell(Client *client);
		};

		Channel(std::string &channel, Client *client);
		~Channel(void);

		// ./class/Channel/Channel.cpp
		void newMember(Client *client, std::string &channel);

		// ./class/Channel/utils/utils.cpp
		unsigned int size(void) const;

		// INFORMACOES DOS CANAL
		bool i;
		bool t;
		bool k;
		bool l;
		std::string topic;
		std::string password;
		unsigned int limit;

		// INFORMACOES DOS CLIENTES
		std::map<std::string, ClientChanell *> clients;
};

#endif