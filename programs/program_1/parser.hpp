//
// Created by kotozavr on 04.02.24.
//

#ifndef INFOTECS_PARSER_HPP
#define INFOTECS_PARSER_HPP

#include <iostream>
#include <vector>

class Parser {

public:

    static bool is_valid( std::string  in){
        if (in.size() > 64) return false;
        for ( char a : in){
            if (!std::isdigit(a)){
                return false;
            }
        }
        return true;
    }

    static void even_to_KB ( std::string in, std::vector<char> &buff){
        for ( char a : in){
            if (a%2 == 0) {
                buff.push_back('K');
                buff.push_back('B');
            }
            else buff.push_back(a);
        }
    }


};

#endif //INFOTECS_PARSER_HPP
