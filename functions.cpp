//
//  functions.cpp
//  LexicalAnalysis
//
//  Created by Cody Thompson on 1/29/20.
//  Copyright © 2020 Cody Thompson. All rights reserved.
//

#include "Header.h"

/*
        This function will initialize a queue from a specified filepath.  File elements will be read in as entire lines (delimitted by '/n') and placed into the queue to perserve order.  If the file is not found the, the function will return a false value.
 
        Parameters: string file     :       contains the file path
                    queue           :       reference to the queue from main
 
        Return values:      true or false depending on failbit status of fstream
 */
bool queueInit( std::string file, std::queue<std::string>& queue ) {
    std::fstream ifile;
    ifile.open( file, std::ios::in );
    
    if( ifile.fail() ) {  // if the file fails to open
        return false;
    } else {   // the file is found; starting reading lines into a vector
        std::string line = "";
       
        while( std::getline( ifile, line,'\n' ) ) {       // read a single line
            queue.push( line );
        }
        ifile.close();
    }
    return true;
}

/*
        This function will parse a given string into tokens according to particular delimiting factors.  These factors include: punctuation symbols, spaces, brackets, parenthesis and possibly more will be added.  The parsed tokens will then be pushed into a queue to perserve order.
 
        Parameters: string line     :       string of characters to be parsed into tokens
                    queue           :       the queue the parsed tokens will be placed into
 
        Return values  :       no returns
 */
void parseTokens( std::string line, std::queue<std::string>& queue ) {
    size_t x=0,y=0;
    std::string tkn = "", prev = "";
    std::regex alphaNum ("([a-zA-Z])");
    
    while(( y = line.find_first_of(" ,.(){};[]:!", x)) != std::string::npos ) {
        prev = line[y-1];
        if( line[y] == '!') {                                       // if ther delimter found is a comment symboly ( ! )
            x = y + 1;
            y = line.find_first_of("!", x);                         // skip dat shit
            x = y + 1;
        } else {
            if( line[y] == '(' || line[y] == ')' || line[y] == '{' || line[y] == '}' ) {
                if ( std::regex_match( prev, alphaNum ) ) {         // if the previous character alphabetic or a digit
                    queue.push( line.substr( x, y - x ) );          // go back and pick up that identifier
                } else {
                    tkn.push_back( line[y] );
                    queue.push( tkn );
                    tkn = "";
                }
            } else if( y - x > 0 ) {                         // token must be at least 1 unit long
                queue.push( line.substr( x, y - x ) );
            }
            x = y + 1;                                       // set search starting point to the location of first found delimiter
        }
    }
}

/*
        This function will initialize a queue using data from the 'queueIn' structure.  The elements will first be parsed into tokens using particular delimiting factors (those such as punctuation, brackets and spaces).  Tokens will be placed into a refernced queue to perseve order.
 
        Parameters: queueIn         :       queue initialized from file  (queueInit)
                    queueOut        :       queue in which parsed tokens will be placed
 
        Return values:      no returns
 */
void initTokenQueue( std::queue<std::string>& queueIn, std::queue<std::string>& queueOut ) {
    std::string line = "";
    
    while( !queueIn.empty() ) {
        line = queueIn.front();
        parseTokens(line, queueOut);
        queueIn.pop();
    }
}

