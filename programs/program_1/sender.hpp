//
// Created by kotozavr on 04.02.24.
//

#ifndef INFOTECS_SENDER_H
#define INFOTECS_SENDER_H

#include "parser.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <arpa/inet.h>
#include <cstring>
#include <mutex>
#include <condition_variable>


class Sender {
    std::vector <char> buff;
    std::mutex mutex;
    std::condition_variable cv;
    int server_socket;
    sockaddr_in serve_address;
    bool stop_flag;
    void socket_init(){
        server_socket = socket(AF_INET, SOCK_DGRAM, 0);
        if (server_socket == -1){
            std::cerr << "error in socket creation";
            exit(EXIT_FAILURE);
        }
        std::memset(&serve_address,0,sizeof(serve_address));
        serve_address.sin_family = AF_INET;
        serve_address.sin_addr.s_addr = INADDR_ANY;
        serve_address.sin_port = htons(12345);
    }

public:

    void run_parser(){
        std::unique_lock<std::mutex> ul(mutex);
        std::cout << "enter string: ";
        std::string input;
        std::cin >> input;
        if (!Parser::is_valid( input)){
            std::cerr << "wrong input!" << std::endl;
        }
        std::sort(input.begin(), input.end(), [](char a, char b) {return a > b;});
        Parser::even_to_KB(input, buff);
        stop_flag = true;
        cv.notify_all();
    }

    void run_sender(){
        std::unique_lock<std::mutex> ul(mutex);
        cv.wait(ul, [=]() { return stop_flag; });
        int summ = 0;
        std::cout << "sorted and modified string:" << std::endl;
        for ( char a : buff){
            if ( isdigit(a)) summ += a -'0';
            std::cout << a << " ";
        }
        buff.clear();
        std::cout << std::endl << "summ of digitst - " << summ << std::endl;
        stop_flag = false;
        socket_init();
        sendto(server_socket, &summ, sizeof(int),
               MSG_CONFIRM, (const struct sockaddr *) &serve_address,
               sizeof(serve_address));

    }

};



#endif //INFOTECS_SENDER_H
