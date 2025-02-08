/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:27:39 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:27:40 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief CRIA UM NOVO CLIENTE DPS Q A FUNCAO poll DETECTAR UM EVENTO DE NOVA CONEXAO (PREENCHE TODAS AS VARIAVEIS DENTRO DA CLASSE COM BASE NA LEITURA DO SOCKET DO SERVIDOR)
/// @param sever REFERENCIA Q CONTEM AS INFORMACOES DO SERVIDOR
Client::Client(Server &server) {
	try {
		this->setPfd(server);
		this->authPass = false;
		this->authNick = false;
		this->authUser = false;
		this->auth = false;
		this->nick = "*";
	} catch (const std::exception &error) {
		if (this->getFd() != -1) {
			close(this->getFd());
		}
		throw ;
	}
	std::cout << "Conexao aceita do ip " << inet_ntoa(this->client.sin_addr) << " na porta " << ntohs(this->client.sin_port) << std::endl;
}

/// @brief RESPONSAVEL POR FECHAR O FD DO CLIENTE
Client::~Client(void) {
	close(this->getFd());
	std::cout << "Conexao encerrada do ip " << inet_ntoa(this->client.sin_addr) << " na porta " << ntohs(this->client.sin_port) << std::endl;
}