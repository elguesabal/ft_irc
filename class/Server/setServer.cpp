/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:44 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:28:45 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief SALVA A SENHA
/// @param password SENHA Q O SERVIDOR ADOTARA
void Server::setPassword(char *password) {
	if (password[0] == '\0') {
		throw std::runtime_error("A senha nao deve estar vazia");
	}
	this->password = password;
}

/// @brief SALVA INFORMACOES DENTRO DE this->pfd
void Server::setPfd(void) {
	this->pfd.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->pfd.fd == -1) {
		throw std::runtime_error("Erro ao criar o socket");
	}
	this->pfd.events = POLLIN;
}

/// @brief SALVA A PORTA (MENTIRA TA SO FAZENDO UMA VERIFICACAO KKKK)
/// @param port PORTA EM Q O SERVIDOR ESTARA ABERTO
void Server::setPort(char *port) {
	if (port[0] == '\0') {
		shutdownServer = true;
		throw std::runtime_error("A porta nao deve estar vazia");
	}
	if (strlen(port) > 5) {
		throw std::runtime_error("A porta deve ter no maximo 5 digitos");
	}
	for (int i = 0; port[i]; i++) {
		if (port[i] < '0' || port[i] > '9') {
			throw std::runtime_error("A porta deve conter apenas números");
		}
	}
	if (std::atoi(port) < 1 || std::atoi(port) > 65535) {
		throw std::runtime_error("Para uma porta ser valida ela deve estar entre 1 e 65535");
	}
}

/// @brief INICIALIZA O SERVIDOR E SALVA AS INFORMACOES EM this->server
/// @param port PORTA EM Q O SERVIDOR ESTARA ABERTO
void Server::setServer(char *port) {
	int opt = 1;

	if (setsockopt(this->pfd.fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		throw std::runtime_error("Erro ao definir opção de socket");
	}
	this->server.sin_family = AF_INET;
	this->server.sin_addr.s_addr = INADDR_ANY;
	this->server.sin_port = htons(std::atoi(port));
	if (bind(this->pfd.fd, (struct sockaddr *)&this->server, sizeof(this->server)) == -1) {
		throw std::runtime_error("Erro ao associar o socket ao endereço e porta");
	}
	if (listen(this->pfd.fd, 5)) {
		throw std::runtime_error("Erro ao colocar o socket em modo de escuta");
	}
	fcntl(this->pfd.fd, F_SETFL, O_NONBLOCK);
}

/// @brief SALVA O this->pfd DO SERVIDOR DENTRO DE this->fds
void Server::setFds(void) {
	this->fds.push_back(this->pfd);
}

/// @brief ADICIONA TODOS OS COMANDOS DISPONIVEIS NO SERVIDOR
void Server::setCmds(void) {
	this->serverCommands["ascii-art"] = &Server::asciiArt;
	this->serverCommands["CAP"] = &Server::CAP;
	this->serverCommands["INVITE"] = &Server::INVITE;
	this->serverCommands["JOIN"] = &Server::JOIN;
	this->serverCommands["KICK"] = &Server::KICK;
	this->serverCommands["LIST"] = &Server::LIST;
	this->serverCommands["luana"] = &Server::luana;
	this->serverCommands["MODE"] = &Server::MODE;
	this->serverCommands["NICK"] = &Server::NICK;
	this->serverCommands["PART"] = &Server::PART;
	this->serverCommands["PASS"] = &Server::PASS;
	this->serverCommands["PING"] = &Server::PING;
	this->serverCommands["PRIVMSG"] = &Server::PRIVMSG;
	this->serverCommands["QUIT"] = &Server::QUIT;
	this->serverCommands["TOPIC"] = &Server::TOPIC;
	this->serverCommands["USER"] = &Server::USER;
	this->serverCommands["WHO"] = &Server::WHO;
}

/// @brief SALVA A DATA DE INICIO DO SERVIDOR
void Server::setTime(void) {
	std::time_t currentTime = std::time(0);

	this->time = std::localtime(&currentTime);
}