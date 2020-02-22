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
#include <vector>
#include <regex>

enum state{NONE, ENTRY, IDENTIFIER, INTEGER, IN_FLOAT, FLOAT, UNKNOWN, OPERATOR, SEPARATOR};
std::string keyAr[] = {"int", "float", "bool", "true", "false", "if", "else", "then", "endif", "while", "whileend", "do", "doend", "for", "forend", "input", "output", "and", "or", "not"};
std::vector<std::string> op{"*", "+", "-", "=", "/", ">", "<", "%"};
std::vector<std::string> sep{"'", "(" ,")" ,"{" ,"}" ,"[" ,"]" ,"," ,"." ,":" ,";"};

class Lexer
{
public:
    Lexer();
    Lexer(std::string filename);
    void parseTokens(std::string input);
    void tokenQueue();
    void output();
    void FSM();
    bool isKeyword(std::string ident);
    
private:
    std::queue<std::string> queue;
    std::queue<std::string> tokens;
    std::queue<std::pair < std::string, std::string > > tokenLex;
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
    std::string token = "", prev = "", next = "";
    
    while ((y = input.find_first_of(" ,.(){};[]:!*+-=/><%", x)) != std::string::npos) {
        prev = input[y - 1];
        next = input[y + 1];
        if (input.size() - y == 1) {                            // if line[y] is just before ';'
            tokens.push(input.substr(x, y - x));                // get lexeme before ';'
            tokens.push(input.substr(y, input.size() - y));     // get ';'
        }
        else if (input[y] == '!') {                             // if the delimiter is a comment symbol
            x = y + 1;
            y = input.find_first_of('!', x);                    // find the enclosing comment symbol to skip over it
        }
        else {
            if (input[y] != ' ') {
                if(input[y] == '.') {                                       // if the delimiter is a "."
                    if(std::regex_match(next, std::regex("[0-9]"))) {       // if the next token is a number
                        y = input.find_first_of(" ;", x);                   // find the next seperator
                        tokens.push(input.substr(x, y - x));                // get float
                    }
                }
                else if (std::regex_match(prev, std::regex("([a-zA-Z]||[0-9])"))) {         // if the previous character is alphabetic or a digit
                    tokens.push(input.substr(x, y - x));        // go back and pick up the lexeme
                }
                else {
                    token.push_back(input[y]);                  // otherwise get the single lexeme
                    tokens.push(token);
                    token = "";
                }
            }
            else if (y - x > 0) {
                tokens.push(input.substr(x, y - x));            // get any other lexeme that is at least 1 character long
            }
        }
        x = y + 1;                                              // update the starting index for string.find_first_of()
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
    std::pair<std::string, std::string> printMe;
    std::cout << std::setw(15) << std::left << "Token" << "\t|\tLexeme" << "\n________________|___________\n";
    while(!tokenLex.empty()) {
        printMe = tokenLex.front();
        std::cout << std::setw(15) << printMe.first << "\t|\t" << printMe.second << std::endl;
        tokenLex.pop();
    }
}

bool Lexer::isKeyword(std::string ident)
// Compares the string passed to an array of legal keywords.  Returns true if the string matches any string in the keyword array.
// Library facilities used: string
{
    for(std::string e : keyAr) {
        if( ident == e)
            return true;
    }
    return false;
}

void Lexer::FSM()
// Identifies the token of all given lexemes from the tokens queue.  Once identified, the token and lexeme are placed into a queue of pairs (tokenLex) of type <string, string>
// Library facilities used: queue, iostream, regex, string
{
    int curState;
    size_t i = 0;
    std::string target;
    
    while(!tokens.empty()) {
        line = tokens.front();
        curState = ENTRY;
        do{
            target = line[i];
            switch(curState) {
                case ENTRY: //1
                    if(std::regex_match(target, std::regex("[0-9]"))) {         //digit
                        curState = 3;
                    }
                    else if(std::regex_match(target, std::regex("[a-zA-Z]"))) { //letter
                        curState = 2;
                    }
                    else if(target == ".") {                                    //decimal
                        curState = 6;
                    }
                    else if (target == "$") {                                   //dollar sign
                        curState = 6;
                    }
                    /*   -- Delete this comment after documentation --
                     std::count(begin, end, findMe) searches a vector from the given iterators "begin" to "end" to find "findMe" in the vector.  returns true if found
                     */
                    else if(std::count(op.begin(), op.end(), target)) {         //operator
                        curState = 7;
                    }
                    else if(std::count(sep.begin(), sep.end(), target)) {       //separator
                        curState = 8;
                    }
                    else {                                                      //any other unchecked character
                        curState = 6;
                    }
                    break;
                    
                case IDENTIFIER: //2
                    if(std::regex_match(target, std::regex("[0-9]"))) {         //digit
                        curState = 2;
                    }
                    else if(std::regex_match(target, std::regex("[a-zA-Z]"))) { //letter
                        curState = 2;
                    }
                    else if(target == ".") {                                    //decimal
                        curState = 6;
                    }
                    else if (target == "$") {                                   //dollar sign
                        curState = 2;
                    }
                    else if(std::count(op.begin(), op.end(), target)) {         //operator
                        curState = 6;
                    }
                    else if(std::count(sep.begin(), sep.end(), target)) {       //separator
                        curState = 6;
                    }
                    break;
                    
                case INTEGER: //3
                    if(std::regex_match(target, std::regex("[0-9]"))) {         //digit
                        curState = 3;
                    }
                    else if(std::regex_match(target, std::regex("[a-zA-Z]"))) { //letter
                        curState = 6;
                    }
                    else if(target == ".") {                                    //decimal
                        curState = 4;
                    }
                    else if (target == "$") {                                   //dollar sign
                        curState = 6;
                    }
                    else if(std::count(op.begin(), op.end(), target)) {         //operator
                        curState = 6;
                    }
                    else if(std::count(sep.begin(), sep.end(), target)) {       //separator
                        curState = 6;
                    }
                    break;
                    
                case IN_FLOAT: //4
                    if(std::regex_match(target, std::regex("[0-9]"))) {         //digit
                        curState = 5;
                    }
                    else if(std::regex_match(target, std::regex("[a-zA-Z]"))) { //letter
                        curState = 6;
                    }
                    else if(target == ".") {                                    //decimal
                        curState = 6;
                    }
                    else if (target == "$") {                                   //dollar sign
                        curState = 6;
                    }
                    else if(std::count(op.begin(), op.end(), target)) {         //operator
                        curState = 6;
                    }
                    else if(std::count(sep.begin(), sep.end(), target)) {       //separator
                        curState = 6;
                    }
                    break;
                    
                case FLOAT: //5
                    if(std::regex_match(target, std::regex("[0-9]"))) {         //digit
                        curState = 5;
                    }
                    else if(std::regex_match(target, std::regex("[a-zA-Z]"))) { //letter
                        curState = 6;
                    }
                    else if(target == ".") {                                    //decimal
                        curState = 6;
                    }
                    else if (target == "$") {                                   //dollar sign
                        curState = 6;
                    }
                    else if(std::count(op.begin(), op.end(), target)) {         //operator
                        curState = 6;
                    }
                    else if(std::count(sep.begin(), sep.end(), target)) {       //separator
                        curState = 6;
                    }
                    break;
                    
                case UNKNOWN: //6
                    if(std::regex_match(target, std::regex("[0-9]"))) {         //digit
                        curState = 6;
                    }
                    else if(std::regex_match(target, std::regex("[a-zA-Z]"))) { //letter
                        curState = 6;
                    }
                    else if(target == ".") {                                    //decimal
                        curState = 6;
                    }
                    else if (target == "$") {                                   //dollar sign
                        curState = 6;
                    }
                    else if(std::count(op.begin(), op.end(), target)) {         //operator
                        curState = 6;
                    }
                    else if(std::count(sep.begin(), sep.end(), target)) {       //separator
                        curState = 6;
                    }
                    break;
                    
                case OPERATOR: //7
                    if(std::regex_match(target, std::regex("[0-9]"))) {         //digit
                        curState = 6;
                    }
                    else if(std::regex_match(target, std::regex("[a-zA-Z]"))) { //letter
                        curState = 6;
                    }
                    else if(target == ".") {                                    //decimal
                        curState = 6;
                    }
                    else if (target == "$") {                                   //dollar sign
                        curState = 6;
                    }
                    else if(std::count(op.begin(), op.end(), target)) {         //operator
                        curState = 6;
                    }
                    else if(std::count(sep.begin(), sep.end(), target)) {       //separator
                        curState = 6;
                    }
                    break;
                    
                case SEPARATOR: //8
                    if(std::regex_match(target, std::regex("[0-9]"))) {         //digit
                        curState = 6;
                    }
                    else if(std::regex_match(target, std::regex("[a-zA-Z]"))) { //letter
                        curState = 6;
                    }
                    else if(target == ".") {                                    //decimal
                        curState = 6;
                    }
                    else if (target == "$") {                                   //dollar sign
                        curState = 6;
                    }
                    else if(std::count(op.begin(), op.end(), target)) {         //operator
                        curState = 6;
                    }
                    else if(std::count(sep.begin(), sep.end(), target)) {       //separator
                        curState = 6;
                    }
                    break;
            }
            i++;
        } while(i != line.length() && curState != 6);
        
        tokens.pop();
        
        switch(curState) {
            case INTEGER:
                tokenLex.push(std::make_pair("Integer", line));
                break;
                
            case IDENTIFIER:
                if(isKeyword(line))
                    tokenLex.push(std::make_pair("Keyword", line));
                else
                    tokenLex.push(std::make_pair("Identifier", line));
                break;
                
            case FLOAT:
                tokenLex.push(std::make_pair("Float", line));
                break;
                
            case UNKNOWN:
                tokenLex.push(std::make_pair("Unknown", line));
                break;
                
            case SEPARATOR:
                tokenLex.push(std::make_pair("Separator", line));
                break;
                
            case OPERATOR:
                tokenLex.push(std::make_pair("Operator", line));
                break;
        }
        i = 0;
    }
}
