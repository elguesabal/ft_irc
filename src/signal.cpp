/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:29:05 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:29:06 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/// @brief FUNCAO RESPONSAVEL POR MANIPULAR SINAIS
void handler(int signal) {
	if (signal == SIGINT) {
		std::cout << std::endl << "Fechando servidor..." << std::endl;
		shutdownServer = true;
	}
}