/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:39 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:28:40 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief CONSTRUTOR Q INICIALIZA O SERVIDOR
/// @param port PORTA EM Q O SERVIDOR ESTARA ABERTO
/// @param password SENHA Q O SERVIDOR ADOTARA
Server::Server(char *port, char *password) {
	try {
		this->setPassword(password);
		this->setPfd();
		this->setPort(port);
		this->setServer(port);
		this->setFds();
		this->setCmds();
		this->setTime();
		std::cout << "Servidor iniciado na porta " << port << " as " << this->getTime() << " do dia " << this->getDate() << std::endl << "Senha: " << password << std::endl << std::endl;
	} catch (const std::exception &error) {
		shutdownServer = true;
		if (this->getFd() != -1) {
			close(this->getFd());
		}
		throw ;
	}
}

/// @brief DESTRUTOR DA CLASSE Q LIBERA A MEMORIA ALOCADA DINAMICAMENTE DE TODOS OS CLIENTES
Server::~Server(void) {
	while (!this->clients.empty()) {
		this->client = this->clients.front();
		this->deleteClient();
	}
	if (this->getFd() != -1) {
		close(this->getFd());
	}
}

/// @brief CRIA UM NOVO CLIENTE E SALVA O FD NO VECTOR DE FDS E O CLIENTE NO VECTOR DE CLIENTES
void Server::newClient(void) {
	try {
		Client *newClient = new Client(*this);

		this->fds.push_back(newClient->pfd);
		this->clients.push_back(newClient);
	} catch (const std::exception &error) {
		std::cout << "\033[33mWarning:\033[0m " << error.what() << std::endl;
	}
}

/// @brief REMOVE UM CLIENTE DO FD NO VECTOR DE FDS E O CLIENTE NO VECTOR DE CLIENTES ALEM DE FECHAR O FD DO CLIENTE
void Server::deleteClient(void) {
	unsigned int i = std::find(this->clients.begin(), this->clients.end(), client) - this->clients.begin() + 1;

	while (this->client->channels.empty() == false) {
		std::map<std::string, Channel *>::iterator it = this->client->channels.begin();
		this->exitChannel(it->first, "Saiu do servidor");
	}
	this->fds.erase(this->fds.begin() + i);
	this->nickClient.erase(this->client->nick);
	this->cmds.clear();
	delete this->client;
	this->clients.erase(this->clients.begin() + i - 1);
}

/// @brief METODO Q COMECA A MONITORAR TODOS OS FDS USANDO poll() E GERENCIA QUAL O DESTINO DO DADO RECEBIDO (SE E UM NOVO CLIENTE, UM CLIENTE DESCONECTANDO)
void Server::listener(void) {
	newComand:
	int ret = poll(this->fds.data(), this->fds.size(), -1);
	if (ret == -1) {
		if (shutdownServer == false) {
			throw std::runtime_error("Erro no poll");
		}
		throw std::runtime_error("SIGINT recebido");
	}
	if (this->fds[0].revents & POLLIN) {
		this->newClient();
		goto newComand;
	}
	for (unsigned int i = 1; i < this->fds.size(); i++) {
		if (this->fds[i].revents & POLLIN) {
			this->client = this->clients[i - 1];
			memset(this->buffer, 0, 512);
			ssize_t bytes_received = recv(this->fds[i].fd, this->buffer, 512, 0);
			if (bytes_received > 0) {
				this->newBuffer();
			} else if (bytes_received == 0) {
				this->deleteClient();
			} else if (bytes_received < 0) {
				if (errno == EAGAIN || errno == EWOULDBLOCK) {
					std::cout << "\033[33mWarning:\033[0m Erro ao receber mensagem" << std::endl;
				} else {
					std::cerr << "\033[33mWarning:\033[0m O cliente desconectou antes de ser respondido (" << strerror(errno) << ")" << std::endl;
				}
			}
			goto newComand;
		}
	}
}

/// @brief METODO Q ENCAMINHA COMO O BUFFER RECEBIDO POR UM CLIENTE ESPECIFICO VAI SER TRATADO
void Server::newBuffer(void) {
	this->cmd = this->buffer;
	if (this->invalidLine()) {
		this->resClient("Quebra do protocolo IRC...");
		this->deleteClient();
		return ;
	}
	this->splitCmds();
	for (unsigned int i = 0; i < this->cmds.size(); i++) {
		this->cmd = this->cmds[i];
		this->splitCmd();
		if (this->serverCommands.find(this->cmd.substr(0, this->cmd.find(' '))) != this->serverCommands.end()) {
			if (this->client->auth == true || this->argsCmd[0] == "CAP" || this->argsCmd[0] == "PASS" || this->argsCmd[0] == "NICK" || this->argsCmd[0] == "USER" || this->argsCmd[0] == "QUIT") {
				(this->*serverCommands[this->cmd.substr(0, this->cmd.find(' '))])();
			} else {
				this->resClient(":" + this->getIp() + " " + ERR_NOTREGISTERED + " PRIVMSG :Você não se registrou"); // You have not registered
			}
		} else {
			std::cout << "\033[33mWarning:\033[0m comando nao encontrado -> '" << this->cmd << "'" << std::endl;
			this->resClient(":" + this->getIp() + " " + ERR_UNKNOWNCOMMAND + " " + this->client->nick + " " + this->argsCmd[0] + " :Comando desconhecido");
		}
	}
}