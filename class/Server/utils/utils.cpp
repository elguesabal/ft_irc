/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:13 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:28:14 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief VERIFICA SE OUVE QUEBRA DO PROTOCOLO IRC
/// @brief VERIFICA SE O FIM DA TRANSMISSAO TERMINA COM "\r\n"
/// @brief VERIFICA APENAS SE EXISTE "\n" SEM "\r"
bool Server::invalidLine(void) {
	if (this->cmd.size() < 2 || this->cmd[this->cmd.size() - 2] != '\r' || this->cmd[this->cmd.size() - 1] != '\n') {
		return (true);
	}
	for (unsigned int i = 1; i < this->cmd.size(); i++) {
        if (this->cmd[i] == '\n') {
            if (i == 0 || this->cmd[i - 1] != '\r') {
                return (true);
            }
        }
	}
	return (false);
}

/// @brief FUNCAO SPLIT Q SEPARA A STRING POR UM DELIMITADOR
std::vector<std::string> Server::split(std::string &str, char delimiter) {
	std::string token;
	std::istringstream tokenStream(str);
	std::vector<std::string> result;

	while (std::getline(tokenStream, token, delimiter)) {
		result.push_back(token);
	}
	return (result);
}

/// @brief METODO Q SPLITA VARIOS COMANDOS USANDO '\n', REMOVE TODOS OS \r E ARMAZENA O RESULTADO DENTRO DE server.cmds
void Server::splitCmds(void) {
	this->cmd.erase(std::remove(this->cmd.begin(), this->cmd.end(), '\r'), this->cmd.end()); // REMOVE TODOS OS \r
	this->cmds.clear();
	std::istringstream stream(this->cmd);
	std::string line;
	while(std::getline(stream, line, '\n')) {
		this->cmds.push_back(line);
	}
}

/// @brief METODO Q SPLITA UM COMANDO EM ARGUMENTOS USANDO ' ' E REMOVE O \r
/// @return RETORNA UM VECTOR COM OS ARGUMENTOS
void Server::splitCmd(void) {
	this->argsCmd.clear();
	std::istringstream stream(this->cmd);
	std::string line;
	while(std::getline(stream, line, ' ')) {
		if (line[0] == ':') {
			line.erase(0, 1);
			std::string lastLine;
			std::getline(stream, lastLine);
			line += (lastLine.empty()) ? "" : " " + lastLine;
		}
		this->argsCmd.push_back(line);
	}
}

/// @brief VERIFICA SE HA ALGUM CARACTER PROIBIDO OU SE COINCIDEM COM ALGUM COMANDO
/// @param nickChannel NICK OU CANAL A SER ANALIZADO
/// @param charInvalid CARACTERES INVALIDOS
/// @return RETORNA TRUE CASO HA ALGUM CARACTER PROIBIDO E FALSE CASO NAO
bool Server::nickChannelInvalid(std::string &nickChannel, std::string charInvalid) {
	for (unsigned short i = 0; i < charInvalid.size(); i++) {
		if (nickChannel.find(charInvalid[i]) != std::string::npos) {
			return (true);
		}
	}
	if (this->serverCommands.find(nickChannel) != this->serverCommands.end()) {
		return (true);
	}
	return (false);
}

/// @brief METODO PASSA TODOS OS CARACTERES PARA MAIUSCULO
/// @return RETORNA UMA NOVA STRING EM MAIUSCULO
std::string Server::toUpper(std::string &str) {
	std::string ret;

	for (unsigned int i = 0; i < str.size(); i++) {
		ret += ((str[i] >= 'a' && str[i] <= 'z') ? str[i] - 32 : str[i]);
	}
	ret += '\0';
	return (ret);
}

/// @brief VERIFICA SE O CLIENTE AUTENTICOU O PASS NICK E USER E ESTA PRONTO PARA RECEBER AS MENSGENS 001 002 003 004 E A MENSAGEM MOTD
/// @brief CASO ACONTECA O UM ERRO AO ABRIR O ARQUIVO MOTD RESPONDE COM ":<servidor> 422 <nick> :O arquivo MOTD está faltando" E NAO ENVIA MAIS NADA
void Server::authentication(void) {
	if (this->client->auth == true || this->client->authPass == false || this->client->authNick == false || this->client->authUser == false) {
		return ;
	}
	this->client->auth = true;
	this->resClient(":" + this->getIp() + " " + RPL_WELCOME + " " + this->client->nick + " :Bem-vindo ao servidor ft_irc, " + this->client->nick + "!" + this->client->user + "@" + this->client->getIp());
	this->resClient(":" + this->getIp() + " " + RPL_YOURHOST + " " + this->client->nick + " :O host do servidor é " + this->getIp() + ", rodando na versão 42");
	this->resClient(":" + this->getIp() + " " + RPL_CREATED + " " + this->client->nick + " :Este servidor foi criado dia " + this->getDate() + " às " + this->getTime());
	this->resClient(":" + this->getIp() + " " + RPL_MYINFO + " " + this->client->nick + " ft_irc 42 it kol");
	std::ifstream file("./ascii-art/ft_irc.motd");
	if (!file.is_open()) {
		this->resClient(":" + this->getIp() + " " + ERR_NOMOTD + " " + this->client->nick + " :O arquivo MOTD está faltando"); // MOTD File is missing
		return ;
	}
	std::string line;
	this->resClient(":" + this->getIp() + " " + RPL_MOTDSTART + " " + this->client->nick + " :");
	while (std::getline(file, line)) {
		this->resClient(":" + this->getIp() + " " + RPL_MOTD + " " + this->client->nick + " :" + line);
	}
	this->resClient(":" + this->getIp() + " " + RPL_ENDOFMOTD + " " + this->client->nick + ":");
	file.close();
}

/// @brief INFORMA AO CANAL Q O USUARIO SAIU COM A MENSAGEM ":<apelido>!<usuario>@<host> PART <canal> :<mensagem>"
/// @brief DESASSOCIA A VARIAVEL "std::map<std::string, Channel *> channels;" DENTRO DA CLASSE "Client"
/// @brief DESASSOCIA A VARIAVEL "std::map<std::string, ClientChanell *> nickClient;" DENTRO DA CLASSE "Channel"
/// @brief CASO NAO ESXISTA MAIS CLIENTE DENTRO DO CANAL LIBERA A MEMORIA ALOCADA PARA O CANAL E DESASSOCIA A VARIAVEL "std::map<std::string, Channel *> channels;" DENTRO DA CLASSE "Server"
/// @param channel NOME DO CANAL Q O USUARIO QUER SAIR
/// @param message MENSAGEM A SER ENCAMINHADA PARA O CANAL
void Server::exitChannel(std::string channel, std::string message) {
	this->resChannel(":" + this->client->nick + "!" + this->client->user + "@" + this->client->getIp() + " PART " + channel + " :" + message, this->channels[channel]);
	this->client->channels.erase(channel);
	delete this->channels[channel]->clients[this->client->nick];
	this->channels[channel]->clients.erase(this->client->nick);
	if (this->channels[channel]->size() == 0) {
		delete this->channels[channel];
		this->channels.erase(channel);
	}
}