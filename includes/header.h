/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseanto <joseanto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:56 by joseanto          #+#    #+#             */
/*   Updated: 2025/02/07 13:28:57 by joseanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <csignal>
#include <algorithm>
#include <sstream>
#include <map>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>

#include "macros.h"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

extern bool shutdownServer;

// ./src/signal.cpp
void handler(int signal);

#endif