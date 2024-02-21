//
// Created by kotozavr on 04.02.24.
//

#include "receiver.hpp"

int main(){

        Receiver receiver;
        receiver.init();
        try {
            while (true) {
                receiver.run_receiver();
            }
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        return 0;
}