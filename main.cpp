//
//  main.cpp
//  LexicalAnalysis
//
//  Created by Cody Thompson on 1/28/20.
//  Copyright © 2020 Cody Thompson. All rights reserved.
//

#include "Lexer.h"

int main( int argc, const char * argv[] ) {
    std::string srcFile = "/Users/codythompson/Documents/Code/MyCompiler/LexicalAnalysis/LexicalAnalysis/myfile.txt";              // This will eventually be passed into the program as an arguement
    Lexer lex(srcFile);
    
    lex.output();
    
    return 0;
}
