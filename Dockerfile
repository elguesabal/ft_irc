FROM ubuntu:22.04
RUN apt-get update && \
    apt-get install make g++ -y
WORKDIR /ft_irc
COPY /ft_irc .
EXPOSE 4242
ENV PORT="4242"
ENV PASSWORD="abc"
CMD make && ./ircserv "$PORT" "$PASSWORD"