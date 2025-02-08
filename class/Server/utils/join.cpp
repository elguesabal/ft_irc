/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:27:52 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:27:53 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief CRIA O CANAL ADICIONANDO O CRIADOR E DANDO O STATUS DE OPERADOR A ELE
/// @brief ABAIXO UMA LISTA DE RESPOSTA ENVIADAS
/// @brief RESPOSTA CONFIRMANDO A ENTRADA NO CANAL -> ":<apelido>!<usuario>@<host> JOIN :<canal>"
/// @brief RESPOSTA COM O TOPICO -> ":<servidor> 331 <apelido> <canal> :Nenhum tópico está definido" OU ":<servidor> 332 <apelido> <canal> :<tópico>"
/// @brief RESPOSTA COM A LISTA DE USUARIOS -> ":<servidor> 353 <apelido> = #meucanal :@<apelido>"
/// @brief RESPOSTA DE FIM DE LISTA -> ":<servidor> 366 <apelido> #meucanal :Fim da lista de nomes"
/// @brief INFORMA Q O MODO TOPICO ESTA ATIVO COM A RESPOSTA ":<servidor> MODE <canal> <modo>"
/// @param channel NOME DO CANAL Q SERA CRIADO
void Server::creatChannel(std::string &channel) {
	try {
		this->channels[channel] = new Channel(channel, this->client);
		this->resClient(":" + this->client->nick + "!" + this->client->user + "@" + this->client->getIp() + " JOIN :" + channel);
		this->resClient(":" + this->getIp() + " " + RPL_NOTOPIC + " " + this->client->nick + " " + channel + " :Nenhum tópico está definido"); // No topic is set
		this->resClient(":" + this->getIp() + " " + RPL_NAMREPLY + " " + this->client->nick + " = " + channel + " :@" + this->client->nick);
		this->resClient(":" + this->getIp() + " " + RPL_ENDOFNAMES + " " + this->client->nick + " " + channel + " :Fim da lista de nomes"); // End of NAMES list
		this->resClient(":" + this->getIp() + " MODE " + channel + " +t");
	} catch (const std::exception &error) {
		throw ;
	}
}

/// @brief ADICIONA O CLIENTE COMO MEMBRO A UM CANAL JA EXISTE
/// @brief ABAIXO UMA LISTA DE RESPOSTA ENVIADAS
/// @brief RESPOSTA CONFIRMANDO A ENTRADA NO CANAL -> ":<apelido>!<usuario>@<host> JOIN <canal>"
/// @brief ENVIADO RESPOSTA AOS OUTROS MEMBROS DO CANAL -> ":<apelido>!<usuario>@<host> JOIN <canal>"
/// @brief RESPOSTA COM O TOPICO -> ":<servidor> 331 <apelido> <canal> :Nenhum tópico está definido" OU ":<servidor> 332 <apelido> <canal> :<tópico>"
/// @brief RESPOSTA COM A LISTA DE USUARIOS -> ":<servidor> 353 <apelido> = <canal> :[prefixos]<apelido1> [prefixos]<apelido2> ..."
/// @brief RESPOSTA DE FIM DE LISTA -> ":<servidor> 366 <apelido> #meucanal :Fim da lista de nomes"
/// @brief REMOVE O CONVITE DO USUARIO CASO ELE TENHA
/// @param channel NOME DO CANAL Q SERA ADICIONADO O NOVO MEMBRO
void Server::joinChannel(std::string &channel) {
	this->channels[channel]->newMember(this->client, channel);
	this->sendChannel(":" + this->client->nick + "!" + this->client->user + "@" + this->getIp() + " JOIN " + channel, this->channels[channel]);
	this->resClient(":" + this->client->nick + "!" + this->client->user + "@" + this->getIp() + " JOIN " + channel);
	this->resClient(":" + this->getIp() + " " + (this->channels[channel]->topic == "" ? RPL_NOTOPIC : RPL_TOPIC) + " " + this->client->nick + " " + channel + " :" + (this->channels[channel]->topic == "" ? "Nenhum tópico está definido" : this->channels[channel]->topic)); // No topic is set
	for (std::map<std::string, Channel::ClientChanell *>::iterator it = this->channels[channel]->clients.begin(); it != this->channels[channel]->clients.end(); ++it) {
		std::string clients = "";
		for (unsigned int j = 0; j < 10 && it != this->channels[channel]->clients.end(); j++) {
			clients += (it->second->o == true ? "@" : "");
			clients += it->second->client->nick + " ";
			++it;
		}
		--it;
		this->resClient(":" + this->getIp() + " " + RPL_NAMREPLY + " " + this->client->nick + " = " + channel + " :" + clients);
	}
	this->resClient(":" + this->getIp() + " " + RPL_ENDOFNAMES + " " + this->client->nick + " " + channel + " :Fim da lista de nomes"); // End of NAMES list
	if (std::find(this->client->invite.begin(), this->client->invite.end(), channel) != this->client->invite.end()) {
		this->client->invite.erase(std::find(this->client->invite.begin(), this->client->invite.end(), channel));
	}
}