/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:27:28 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:27:29 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief CONTA QUANTOS CLIENTES O CANAL TEM
/// @return RETORNA O TAMANHO DO CANAL
unsigned int Channel::size(void) const {
	return (this->clients.size());
}