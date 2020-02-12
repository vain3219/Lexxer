//
//  main.cpp
//  LexicalAnalysis
//
//  Created by Cody Thompson on 1/28/20.
//  Copyright © 2020 Cody Thompson. All rights reserved.
//

#include "Header.h"

int main( int argc, const char * argv[] ) {
    std::string srcFile = "/Users/codythompson/Documents/Code/MyCompiler/LexicalAnalysis/LexicalAnalysis/myfile.txt";              // This will eventually be passed into the program as an arguement
    std::queue<std::string> readQu;

    if( !queueInit( srcFile, readQu ) )
        std::cerr << "The file specified does not exist in this directory.\n";

    std::queue<std::string> tokenQu;
    initTokenQueue( readQu, tokenQu );

    std::cout << "The queue size is: " << tokenQu.size() << std::endl;
    while( !tokenQu.empty() ) {
        std::cout << tokenQu.front() << std::endl;
        tokenQu.pop();
    }
    
    return 0;
}


/*
 Regular expressions
    Indentifiers    =   ([a-zA-Z])([a-zA-Z0-9$*]*)                              Alphabetic symbol followed by digit, alhpabetic character, or $
    Keywords        =   [a-z]{2,8}
    Separators      =   [\'|\(|\)|\{|\}|\[|\]|\,|\.|\:|\;| ]{1}                 ~ Not sure if this is what we want
    Block Comments  =   !([a-zA-Z0-9 ]*)!                                       "!" symbol followed by 0 >= alaphabetic characters, digits or spaces ending with "!" symbol
 */










