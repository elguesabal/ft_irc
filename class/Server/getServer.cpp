/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:34 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:28:35 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief PEGA O FD DO SERVIDOR
/// @return RETORNA O FD DO SERVIDOR
int Server::getFd(void) const {
	return (this->pfd.fd);
}

/// @brief METODO Q BUSCA O IP DO SERVIDOR
/// @return RETORNA O IP DO SERVIDOR
std::string Server::getIp(void) const {
	return ("ft_irc.com");
}

/// @brief PEGA A DATA Q INICIOU O SERVIDOR
/// @return RETORNA A DATA NO FORMATO "DD/MM/AAAA"
std::string Server::getDate(void) const {
	std::ostringstream date;

	date << std::setfill('0') << std::setw(2) << this->time->tm_mday << "/" << std::setfill('0') << std::setw(2) << this->time->tm_mon + 1 << "/" << std::setfill('0') << std::setw(4) << this->time->tm_year + 1900;
	return (date.str());
}

/// @brief PEGA A HORA Q INICIOU O SERVIDOR
/// @return RETORNA A HORA NO FORMATO "HH\:MM\:SS"
std::string Server::getTime(void) const {
	std::ostringstream time;

	time << std::setfill('0') << std::setw(2) << this->time->tm_hour << ":" << std::setfill('0') << std::setw(2) << this->time->tm_min << ":" << std::setfill('0') << std::setw(2) << this->time->tm_sec;
	return (time.str());
}
