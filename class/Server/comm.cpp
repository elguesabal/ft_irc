/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:30 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:28:31 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief RESPONDE UM CLIENTE DE FORMA SIMPLES
/// @param res RESPOSTA JA PRONTO PARA SER ENVIADA PARA O CLIENTE
void Server::resClient(std::string res) {
	res += "\r\n";
	send(this->client->getFd(), res.c_str(), res.size(), 0);
}

/// @brief MANDA UMA MENSAGEM PARA OUTRO CLIENTE
/// @param res MENSAGEM JA PRONTA PARA SER ENVIADA PARA O CLIENTE
/// @param receiver INFORMACOES DO CLIENTE Q VAI RECEBER A MENSAGEM
void Server::sendClient(std::string res, Client *receiver) {
	res += "\r\n";
	send(receiver->getFd(), res.c_str(), res.size(), 0);
}

/// @brief MANDA UMA MENSAGEM PARA UM CANAL
/// @param res MENSAGEM JA PRONTA PARA SER ENVIADA PARA O CANAL
void Server::resChannel(std::string res, Channel *channel) {
	res += "\r\n";
	for (std::map<std::string, Channel::ClientChanell *>::iterator it = channel->clients.begin(); it != channel->clients.end(); ++it) {
		this->sendClient(res, it->second->client);
	}
}

/// @brief MANDA UMA MENSAGEM PARA UM CANAL (EXCETO PARA SI MESMO)
/// @param res MENSAGEM JA PRONTA PARA SER ENVIADA PARA O CANAL
void Server::sendChannel(std::string res, Channel *channel) {
	res += "\r\n";
	for (std::map<std::string, Channel::ClientChanell *>::iterator it = channel->clients.begin(); it != channel->clients.end(); ++it) {
		if (this->client != it->second->client) {
			this->sendClient(res, it->second->client);
		}
	}
}