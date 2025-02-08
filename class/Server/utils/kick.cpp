/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:27:58 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:27:59 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief REMOVE O CLIENTE DO CANAL E NOTIFICA TODOS OS MEMBROS COM ":<kicker_apelido>!<user>@<host> KICK <canal> <apelido> :<mensagem>"
/// @brief DESASSOCIA A VARIAVEL "std::map<std::string, Channel *> channels;" DENTRO DA CLASSE "Client"
/// @brief DESASSOCIA A VARIAVEL "std::map<std::string, ClientChanell *> nickClient;" DENTRO DA CLASSE "Channel"
/// @brief CASO NAO ESXISTA MAIS CLIENTE DENTRO DO CANAL LIBERA A MEMORIA ALOCADA PARA O CANAL E DESASSOCIA A VARIAVEL "std::map<std::string, Channel *> channels;" DENTRO DA CLASSE "Server"
/// @param channel CANAL Q O CLIENTE SERA KICKADO
/// @param client CLIENTE A SER KICKADO DO CANAL
/// @param message MENSAGEM A SER ENCAMINHADA PARA O CANAL
void Server::removeClient(std::string &channel, std::string &client, std::string &message) {
	this->resChannel(":" + this->client->nick + "!" + this->client->user + "@" + this->client->getIp() + " KICK " + channel + " " + client + " :" + message, this->channels[channel]);
	this->nickClient[client]->channels.erase(channel);
	delete this->channels[channel]->clients[client];
	this->channels[channel]->clients.erase(client);
	if (this->channels[channel]->size() == 0) {
		delete this->channels[channel];
		this->channels.erase(channel);
	}
}