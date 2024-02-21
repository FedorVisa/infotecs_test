//
// Created by kotozavr on 04.02.24.
//

#include "sender.hpp"


int main(){
    Sender sender;
    try {
        while (true){
            std::thread thread_1 (&Sender::run_parser, std::ref(sender));
            std::thread thread_2 (&Sender::run_sender, std::ref(sender));
            thread_1.join();
            thread_2.join();
        }

    } catch (std::exception &e){
        std::cerr << e.what() << std::endl;
    }

}