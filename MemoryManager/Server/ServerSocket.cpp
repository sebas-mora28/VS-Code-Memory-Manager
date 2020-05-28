//
// Created by david on 27/5/20.
//

#include "ServerSocket.h"

#include "ServerSocket.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


#include "../GarbageCollector/GarbageCollector.h"
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#define PORT 54000


int ServerSocket::createSocket() {
    int opt = true;
    int master_socket, addrlen, new_socket, client_socket[30],
            max_clients = 30, activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address{};


    fd_set readfds;


    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }

    //create a master socket
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt,
                   sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //bind the socket to localhost port 54000
    if (bind(master_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while (true) {

        FD_ZERO(&readfds);


        FD_SET(master_socket, &readfds);
        max_sd = master_socket;


        for (i = 0; i < max_clients; i++) {

            sd = client_socket[i];


            if (sd > 0)
                FD_SET(sd, &readfds);

            if (sd > max_sd)
                max_sd = sd;
        }


        activity = select(max_sd + 1, &readfds, nullptr, nullptr, nullptr);

        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }

        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket,
                                     (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %\n", new_socket,
                   inet_ntoa(address.sin_addr),
                   ntohs(address.sin_port));

            //send new connection greeting message
            char *message = "You`ve connected to the GC Server.";
            if (send(new_socket, message, strlen(message), 0) != strlen(message)) {
                perror("send");
            }

            puts("Welcome message sent successfully");

            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++) {
                //if position is empty
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                char buf[4096];
                valread = read(sd, buf, 1024);
                std::string data = std::string(buf, 0, valread);
                std::cout << data << std::endl;
                if (valread == 0) {
                    getpeername(sd, (struct sockaddr *) &address,
                                (socklen_t *) &addrlen);
                    printf("Host disconnected , ip %s , port %d \n",
                           inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                    close(sd);
                    client_socket[i] = 0;
                } else {
                    Json::Reader reader;
                    Json::Value obj;
                    reader.parse(data, obj);

                    buf[valread] = '\0';
                    sendMessage(sd, buf);
                }
            }
        }
    }
}

void ServerSocket::sendMessage(int clientServer, char buf[4096]) {
    send(clientServer, buf, strlen(buf) + 1, 0);
}

void ServerSocket::increment(std::string id) {
    GarbageCollector::getGarbageCollectorInstance()->incrementRefCount(id);
}

void ServerSocket::decrement(std::string id) {
    GarbageCollector::getGarbageCollectorInstance()->decrementRedCount(id);
}