/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:01 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:28:02 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief ENVIA A INFORMACOES DE TODOS OS CANAIS
/// @brief ENVIA O CABECALHO ":<servidor> 321 <apelido> Channel :Users  Name" (CAIU EM DESUSO MAS DECIDI DEIXAR)
/// @brief ENVIA AS INFORMACOES DE CADA CANAL COM A MENSAGEM ":<servidor> 322 <apelido> <canal> <número de usuários> :<modos> <tópico>"
/// @brief ENVIA A INFORMACAO Q A LISTA TERMINOU ":<servidor> 323 <apelido> :End of /LIST"
void Server::listChannels(void) {
	std::string host = this->getIp();
	std::string nick = this->client->nick;

	this->resClient(":" + host + " " + RPL_LISTSTART + " " + nick + " Channel :Users  Name");
	for (std::map<std::string, Channel *>::iterator it = this->channels.begin(); it != this->channels.end(); ++it) {
		if (it->second->i == false) {
			std::stringstream size;
			size << it->second->size();
			this->resClient(":" + host + " " + RPL_LIST + " " + nick + " " + it->first + " " + size.str() + " :[+" + (it->second->t ? "t" : "") + (it->second->k ? "k" : "") + (it->second->l ? "l" : "") + "] " + it->second->topic);
		}
	}
	this->resClient(":" + host + " " + RPL_LISTEND + " " + nick + " :End of /LIST");
}

/// @brief ENVIA A INFORMACOES DOS CANAIS ESPECIFICADOS
/// @brief ENVIA O CABECALHO ":<servidor> 321 <apelido> Channel :Users  Name" (CAIU EM DESUSO MAS DECIDI DEIXAR)
/// @brief ENVIA AS INFORMACOES DE CADA CANAL EXISTENTE COM A MENSAGEM ":<servidor> 322 <apelido> <canal> <número de usuários> :<modos> <tópico>"
/// @brief ENVIA A INFORMACAO Q A LISTA TERMINOU ":<servidor> 323 <apelido> :End of /LIST"
/// @param channels NOMES DOS CANAIS A SEREM CONSULTADOS
void Server::searchChannels(std::vector<std::string> channels) {
	std::string host = this->getIp();
	std::string nick = this->client->nick;

	this->resClient(":" + host + " " + RPL_LISTSTART + " " + nick + " Channel :Users  Name");
	for (unsigned int i = 0; i < channels.size(); i++) {
		if (this->channels.count(channels[i]) == 1 && this->channels[channels[i]]->i == false) {
			std::stringstream size;
			size << this->channels[channels[i]]->size();
			this->resClient(":" + host + " " + RPL_LIST + " " + nick + " " + channels[i] + " " + size.str() + " :[+" + (this->channels[channels[i]]->t ? "t" : "") + (this->channels[channels[i]]->k ? "k" : "") + (this->channels[channels[i]]->l ? "l" : "") + "] " + this->channels[channels[i]]->topic);
		}
	}
	this->resClient(":" + host + " " + RPL_LISTEND + " " + nick + " :End of /LIST");
}