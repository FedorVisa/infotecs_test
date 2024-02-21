//
// Created by kotozavr on 04.02.24.
//

#ifndef INFOTECS_RECEIVER_HPP
#define INFOTECS_RECEIVER_HPP

#include <arpa/inet.h>
#include <iostream>
#include <cstring>

class Receiver {

    int min_lenght = 100; // first number, which contains > 2 digits
    sockaddr_in socket_addr;
    int client_socket;

    void init_socket() {
        client_socket = socket(AF_INET, SOCK_DGRAM, 0);
        if (client_socket == -1) {
            std::cerr << "Error in socket creation";
            exit(EXIT_FAILURE);
        }
        std::memset(&socket_addr, 0, sizeof(socket_addr));

        socket_addr.sin_family    = AF_INET;
        socket_addr.sin_addr.s_addr = INADDR_ANY;
        socket_addr.sin_port = htons(12345);

        if ( bind(client_socket, (const struct sockaddr *)&socket_addr,sizeof(socket_addr)) < 0 ){
            std::cerr << "bind error"<< std::endl;
            exit(EXIT_FAILURE);
        } else std::cout << "bind completed"<< std::endl;
    }


public:
    void init(){
        init_socket();
    }
    void run_receiver(){

        int sum;
        recv(client_socket, &sum, sizeof(int), 0);
        std::cout << sum << std::endl;r
        if( sum >= min_lenght && sum%32 == 0){
            std::cout << "Data received successfully" << std::endl;
        } else  std::cout << "Error: wrong data" << std::endl;
    }

};


#endif //INFOTECS_RECEIVER_HPP
