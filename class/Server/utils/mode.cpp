/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:05 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:28:06 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief GERENCIA O MODE i ENVIANDO UMA MENSAGEM AO CANAL INFORMANDO SE O MODE i ESTA ESTA HABILITADO OU NAO ":<apelido>!<usuario>@<host> MODE <canal> <mode>"
/// @param channel NOME DO CANAL Q VAI SER MODIFICADO
/// @param mode BOOLEAN Q REPRESENTA AS BANDEIRAS MODE + (true) E - (false)
void Server::i(std::string &channel, bool mode) {
	this->channels[channel]->i = mode;
	this->resChannel(":" + this->client->nick + "!" + this->client->user + "@" + this->client->getIp() + " MODE " + channel + " " + (mode ? "+" : "-") + "i", this->channels[channel]);
}

/// @brief GERENCIA O MODE t ENVIANDO UMA MENSAGEM AO CANAL INFORMANDO SE O MODE t ESTA ESTA HABILITADO OU NAO ":<apelido>!<usuario>@<host> MODE <canal> <mode>"
/// @param channel NOME DO CANAL Q VAI SER MODIFICADO
/// @param mode BOOLEAN Q REPRESENTA AS BANDEIRAS MODE + (true) E - (false)
void Server::t(std::string &channel, bool mode) {
	this->channels[channel]->t = mode;
	this->resChannel(":" + this->client->nick + "!" + this->client->user + "@" + this->client->getIp() + " MODE " + channel + " " + (mode ? "+" : "-") + "t", this->channels[channel]);
}

/// @brief GERENCIA O MODE k ENVIANDO UMA MENSAGEM INFORMANDO A SENHA DEFINIDA (OU INFORMANDO A REMOCAO DA SENHA) ":<apelido>!<usuario>@<host> MODE <canal> <mode> :<senha>"
/// @brief SE A SENHA FOR UMA STRING VAZIA RESPONDE COM ":<servidor> 461 A PRIVMSG :Parâmetros insuficientes"
/// @param channel NOME DO CANAL Q VAI SER MODIFICADO
/// @param mode BOOLEAN Q REPRESENTA AS BANDEIRAS MODE + (true) E - (false)
/// @param password SENHA Q SERA DEFINIDA NO CANAL (CASO A BANDEIRA DO MODE SEJA +)
void Server::k(std::string &channel, bool mode, std::string password) {
	if (mode == true && password == "") {
		this->resClient(":" + this->getIp() + " " + ERR_NEEDMOREPARAMS + " " + this->client->nick + " MODE :Parâmetros insuficientes"); // Not enough parameters
	} else {
		this->channels[channel]->k = mode;
		this->channels[channel]->password = (mode ? password : "");
		this->resChannel(":" + this->client->nick + "!" + this->client->user + "@" + this->client->getIp() + " MODE " + channel + " " + (mode ? "+" : "-") + "k" + (mode ? " " + password : ""), this->channels[channel]);
	}
}

/// @brief ENVIA UMA MENSAGEM PARA TODOS DO CANAL (INCLUINDO O OPERADOR Q PROMOVEU O MEMBRO) INFORMANDO Q ALGUEM VIROU OPERADOR ":<apelido>!<usuario>@<host> MODE <canal> +o <usuario>"
/// @brief SE O NICK FOR UMA STRING VAZIA RESPONDE COM ":<servidor> 461 A PRIVMSG :Parâmetros insuficientes"
/// @brief CASO O NICK NAO ESTEJA NO CANAL RESPONDE COM ":<servidor> 441 <operador> <usuario> <canal> :Este nick não está no canal"
/// @brief CASO A O NICK ESTEJA DENTRO DO CANAL MANDA UMA MENSAGEM PARA TODOS OS MEMBROS DO CANAL ":<apelido>!<usuario>@<host> MODE #canal +o usuario"
/// @param channel NOME DO CANAL Q VAI ACONTECER A PROMOCAO DE MEMBRO
/// @param mode BOOLEAN Q REPRESENTA AS BANDEIRAS MODE + (true) E - (false)
/// @param nick NICK DO USUARIO Q VAI GANHAR OU PEDER O STATUS DE OPERADOR
void Server::o(std::string &channel, bool mode, std::string nick) {
	if (nick == "") {
		this->resClient(":" + this->getIp() + " " + ERR_NEEDMOREPARAMS + " " + this->client->nick + " MODE :Parâmetros insuficientes"); // Not enough parameters
	} else if (this->channels[channel]->clients.count(nick) == 0) {
		this->resClient(":" + this->getIp() + " " + ERR_USERNOTINCHANNEL + " " + this->client->nick + " " + nick + " " + channel + " :Este nick não está no canal"); // They aren't on that channel
	} else {
		this->channels[channel]->clients[nick]->o = mode;
		this->resChannel(":" + this->client->nick + "!" + this->client->user + "@" + this->client->getIp() + " MODE " + channel + " " + (mode == true ? "+" : "-") + "o " + nick, this->channels[channel]);
	}
}

/// @brief GERENCIA O MODE l ENVIANDO UMA MENSAGEM INFORMANDO QUAL O MAXIMO DE USUARIOS O CANAL ESTA LIMITADO (OU REMOVENDO A LIMITACAO) ":<nickname>!<user>@<host> MODE #canal +l <limite>"
/// @brief SE O LIMITE NAO FOR INFORMADO RESPONDE COM ":<servidor> 461 A PRIVMSG :Parâmetros insuficientes"
/// @param channel NOME DO CANAL Q VAI SER MODIFICADO
/// @param mode BOOLEAN Q REPRESENTA AS BANDEIRAS MODE + (true) E - (false)
/// @param password LIMTE DE USUARIO PARA O CANAL (CASO A BANDEIRA DO MODE SEJA +)
void Server::l(std::string &channel, bool mode, std::string limit) {
	if (mode == true && limit == "0") {
		this->resClient(":" + this->getIp() + " " + ERR_NEEDMOREPARAMS + " " + this->client->nick + " MODE :Parâmetros insuficientes"); // Not enough parameters
	} else {
		this->channels[channel]->l = mode;
		this->channels[channel]->limit = (mode ? std::atoi(limit.c_str()) : 0);
		this->resChannel(":" + this->client->nick + "!" + this->client->user + "@" + this->client->getIp() + " MODE " + channel + " " + (mode ? "+" : "-") + "l" + (mode ? " " + limit : ""), this->channels[channel]);
	}
}