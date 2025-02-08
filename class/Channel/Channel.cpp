/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:27:35 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:27:37 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief CONSTRUTOR DO STRUCT ClientChannel
/// @param client CLIENTE Q VAI CRIAR O CANAL
Channel::ClientChanell::ClientChanell(Client *client) : client(client), o(false) {

}

/// @brief CONSTRUTOR DA CLASSE Channel
/// @param channel NOME DO PROPRIO CANAL
/// @param client CLIENTE Q VAI CRIAR O CANAL
Channel::Channel(std::string &channel, Client *client) : i(false), t(true), k(false), l(false), topic("") {
	this->newMember(client, channel);
	this->clients[client->nick]->o = true;
}

/// @brief DESTRUTOR DA CLASSE
/// @brief LIEBERA OS CLIENTES DO TIPO "ClientChannel" (NORMALMENTE ELES SAO LIBERADOS PELO COMANDO "PART" MAS EM CASO DE ctrl + c LIBERA TODOS OS CLIENTES)
Channel::~Channel(void) {
	for (std::map<std::string, ClientChanell *>::iterator it = this->clients.begin(); it != this->clients.end(); ++it) {
		delete it->second;
	}
}

/// @brief ADICIONA UM CLIENTE A LISTA DE MEMBROS DO CANAL
/// @param channel NOME DO PROPRIO CANAL
/// @param client CLIENTE A SER ADICIONADO
void Channel::newMember(Client *client, std::string &channel) {
	try {
		this->clients[client->nick] = new ClientChanell(client);
		client->channels[channel] = this;
	} catch (const std::exception &error) {
		throw ;
	}
}