#pragma once

/*
STLs used:
    iostream: provides standard input/output stream
    string: provides string to store lines being read in
    fstream: provides ability to read and write onto a text file
    queue: provides queue to store read in lines from text file
    regex: provides support for regular expressions
FILE: Lexer.h
CLASS PROVIDED: Lexer
CLASS BEHAVIOR:    Reads in a text file and stores lines into a queue to be parsed and sorted into tokens
                Provides two constructors (parameters: empty, values read in from text file)
                Includes three member functions that will traverse the queue of stored lines, parse into tokens, and print out the tokens
CONSTRUCTORS for the Lexer class:
    Lexer()
        Postcondition: The Lexer object has been initialized as an empty object
    Lexer(std::string filename)
        Precondition: filename.fail() returns false
        Postcondition: The Lexer object has been initialized and lines read from the text file will be stored into a queue
FUNCTIONS for the Lexer class:
    void parseToken(std::string input)
        Postcondition: Parses a string into tokens according to states delimiters; parsed tokens stored in a queue to preserve order
    void tokenQueue()
        Precondition: queue.empty() returns false
        Postcondition: Steps through queue of lines read in from the text file and passes them to parseTokens function to be parsed and empties queue
    void output()
        Precondition: tokens.emptyu() returns false
        Postcondition: Prints tokens to the screen and empties tokens queue
*/
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <regex>

class Lexer
{
public:
    Lexer();
    Lexer(std::string filename);
    void parseTokens(std::string input);
    void tokenQueue();
    void output();
    
private:
    std::queue<std::string> queue;
    std::queue<std::string> tokens;
    std::string line;
};

Lexer::Lexer()
// Instantiates an object of the Lexer class with empty value for line
// Library facilities used: string, queue, fstream
{
    line = "";
}

Lexer::Lexer(std::string filename)
// Instantiates an object of the Lexer class using values found in the filename text file passed through by the user
// stores the lines being read in in queue
// Library facilities used: string, queue, fstream
{
    std::fstream ifile;
    ifile.open(filename, std::ios::in);

    if (ifile.fail()) {
        throw new std::ios::failure("Error opening file.");
    }
    else {
        line = "";

        while (std::getline(ifile, line, '\n')) {
            queue.push(line);
        }
    }
    ifile.close();
}

void Lexer::parseTokens(std::string input)
// Parse a given string from queue into tokens according to particular delmiters
// Delimiters: punctuation, spaces, brackets, parenthesis
// Parsed tokens will be pushed into a queue to preserve order
// Library facilities used: string, queue, regex
{
    size_t x = 0, y = 0;
    std::string token = "", prev = "";
    std::regex alphaNum("([a-zA-Z]||[0-9])");

    while ((y = input.find_first_of(" ,.(){};[]:!*+-=/><%", x)) != std::string::npos) {
        prev = input[y - 1];
        if (input.size() - y == 1) {
            tokens.push(input.substr(x, y - x));
            tokens.push(input.substr(y, input.size() - y));
            x = y + 1;
        }
        else if (input[y] == '!') {
            x = y + 1;
            y = input.find_first_of('!', x);
            x = y + 1;
        }
        else {
            if (input[y] != ' ') {
                if (std::regex_match(prev, alphaNum)) {
                    tokens.push(input.substr(x, y - x));
                }
                else {
                    token.push_back(input[y]);
                    tokens.push(token);
                    token = "";
                }
            }
            else if (y - x > 0) {
                tokens.push(input.substr(x, y - x));
            }
            x = y + 1;
        }
    }
}

void Lexer::tokenQueue()
// Takes queue of lines one by one and passes to parseTokens function
// Library facilities used: queue, string
{
    line = "";

    while (!queue.empty()) {
        line = queue.front();
        parseTokens(line);
        queue.pop();
    }
}

void Lexer::output()
// Ouputs tokens
// Library facilities used: queue, iostream
{
    while (!tokens.empty()) {
        std::cout << tokens.front() << std::endl;
        tokens.pop();
    }
}
