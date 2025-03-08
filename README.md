# ft_irc
- [ft_irc](#ft_irc)
- [0. Description](#0-Sobre-o-Projeto)
- [1. Funcionalidades Implementadas](#1-Funcionalidades-Implementadas)
- [2. Tecnologias Utilizadas](#2-Tecnologias-Utilizadas)
- [3. Como Compilar e Executar](#3-Como-Compilar-e-Executar)
- [4. Estrutura do Projeto](#4-Estrutura-do-Projeto)
- [5. Comandos-Implementados](#5-Comandos-Implementados)

## 0. Sobre o Projeto

O **ft_irc** é uma implementação de um servidor IRC desenvolvido em C++. O objetivo do projeto é criar um servidor que implemente funcionalidades básicas do protocolo IRC (Internet Relay Chat), permitindo conexão de clientes, gerenciamento de canais e interação entre usuários.

## 1. Funcionalidades Implementadas

- Aceita conexões de múltiplos clientes via protocolo IRC
- Suporte a autenticação e registro de usuários
- Criação e gerenciamento de canais
- Envio de mensagens privadas e em grupo
- Gerenciamento de operadores e permissões
- Implementação de comandos IRC básicos
- Sistema de controle de permissões nos canais

## 2. Tecnologias Utilizadas

- **Linguagem:** C++
- **Padrão:** C++98
- **Script:** Makefile
- **Sockets:** Uso da API de sockets para comunicação em rede

## 3. Como Compilar e Executar

### Requisitos

- Um compilador C++ compatível com C++98
- Sistema Unix-based (Linux ou macOS) recomendado

### Compilando o Servidor

```sh
make
```

### Executando o Servidor

```sh
./ircserver <port> <password>
```

- **port**: Porta onde o servidor será iniciado
- **password**: Senha necessária para conexão de clientes

### Conectando ao Servidor

Para testar o servidor, você pode usar um cliente IRC como `netcat` ou `HexChat`:

```sh
nc <ip> <port>
```

![Image](https://github.com/user-attachments/assets/17598cff-013a-4624-9282-5a1083070d5e)
![Image](https://github.com/user-attachments/assets/d616618d-864f-4d22-88cb-ade40564e4e9)

## 4. Estrutura do Projeto

```
ft_irc/
├── ascii-art/          # Alguns arquivos com ascii-art
├── class/              # Classes criadas
├── include/            # Arquivos de cabeçalho
├── src/                # Código fonte do servidor
├── ft_irc.cpp          # Arquivo contendo função main
├── Makefile            # Script de compilação
└── README.md           # Este arquivo
```

## 5. Comandos Implementados

- `PASS <password>` - Define a senha de conexão
- `NICK <nickname>` - Define o apelido do usuário
- `USER <username> <hostname> <servername> <realname>` - Registra o usuário
- `JOIN <channel>` - Entra em um canal
- `PART <channel>` - Sai de um canal
- `PRIVMSG <user/channel> <message>` - Envia uma mensagem privada
- `MODE <channel> <flags> [parameters]` - Configura modos de canal
- `TOPIC <channel> [topic]` - Define ou exibe o título do canal
- `KICK <channel> <user> [reason]` - Expulsa um usuário de um canal
