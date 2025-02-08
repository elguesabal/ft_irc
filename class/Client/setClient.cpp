/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:27:46 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:27:47 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief SALVA INFORMACOES NO pfd
void Client::setPfd(Server &server) {
	socklen_t client_address_len = sizeof(this->client);

	this->pfd.fd = accept(server.getFd(), (struct sockaddr *)&this->client, &client_address_len);
	if (this->getFd() == -1) {
		throw std::runtime_error("Erro ao aceitar conexão");
	}
	this->pfd.events = POLLIN;
}

/// @brief ATUALIZA O NICK EM TODOS OS CANAIS E NA PROPRIA CLASSE
void Client::setNick(std::string &nick) {
	for (std::map<std::string, Channel *>::iterator it = this->channels.begin(); it != this->channels.end(); ++it) {
		it->second->clients[nick] = it->second->clients[this->nick];
		it->second->clients.erase(this->nick);
	}
	this->nick = nick;
}