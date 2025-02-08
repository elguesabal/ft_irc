/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:18 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:28:19 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief RESPONDE COM UMA LISTA DE USUARIOS DENTRO DO CANAL
/// @brief PARA CADA USUARIO ENVIA A RESPOSTA ":<servidor> 352 <apelido_solicitante> <canal> <usuario> <host> <servidor> <apelido_destino> <flags> :<hops> <realname>"
/// @brief FINALIZA A LISTA RESPONDENDO COM ":<servidor> 315 <apelido> <canal> :End of WHO list"
/// @param channel NOME DO CANAL A SER BUSCADO
void Server::listChannel(std::string &channel) {
	if (this->channels[channel]->i == false || this->channels[channel]->clients.count(this->client->nick) == 1) {
		for (std::map<std::string, Channel::ClientChanell *>::iterator it = this->channels[channel]->clients.begin(); it != this->channels[channel]->clients.end(); ++it) {
			this->resClient(":" + this->getIp() + " " + RPL_WHOREPLY + " " + this->client->nick + " " + channel + " " + it->second->client->user + " ~" + it->second->client->getIp() + " " + this->getIp() + " " + it->second->client->nick + " H :0 " + it->second->client->user);
		}
	}
	this->resClient(":" + this->getIp() + " " + RPL_ENDOFWHO + " " + this->client->nick + " " + channel + " :End of WHO list");
}

/// @brief RESPONDE COM INFORMACOES DE USUARIOS DO SERVIDOR
/// @brief RESPONDE COM INFORMACOES DO USUARIO ESPECIFICO ":<servidor> 352 <apelido_solicitante> * <usuario> <host> <servidor> <apelido_destino> <flags> :<hops> <realname>"
/// @brief FINALIZA A LISTA RESPONDENDO COM ":<servidor> 315 <apelido_solicitante> <apelido_destino> :End of WHO list"
/// @param client NOME DO CLIENTE A SER BUSCADO
void Server::searchClient(std::string &client) {
	this->resClient(":" + this->getIp() + " " + RPL_WHOREPLY + " " + this->client->nick + " * " + this->nickClient[client]->user + " ~" + this->nickClient[client]->getIp() + " " + this->getIp() + " " + this->nickClient[client]->nick + " H :0 " + this->nickClient[client]->user);
	this->resClient(":" + this->getIp() + " " + RPL_ENDOFWHO + " " + this->client->nick + " " + client + " :End of WHO list");
}

/// @brief LISTA INFORMACOES DE TODOS OS USUARIOS DO SERVIDOR
/// @brief RESPONDE COM INFORMACOES DE UM USUARIO ESPECIFICO ":<servidor> 352 <apelido_solicitante> * <usuario> <host> <servidor> <apelido_destino> <flags> :<hops> <realname>"
/// @brief FINALIZA A LISTA RESPONDENDO COM ":<servidor> 315 <apelido> * :End of WHO list"
void Server::listClients(void) {
	for (std::map<std::string, Client *>::iterator it = this->nickClient.begin(); it != this->nickClient.end(); ++it) {
		this->resClient(":" + this->getIp() + " " + RPL_WHOREPLY + " " + this->client->nick + " * " + it->second->user + " ~" + it->second->getIp() + " " + this->getIp() + " " + it->second->nick + " H :0 " + it->second->user);
	}
	this->resClient(":" + this->getIp() + " " + RPL_ENDOFWHO + " " + this->client->nick + " * :End of WHO list");
}