//
//  Header.h
//  LexicalAnalysis
//
//  Created by Cody Thompson on 1/29/20.
//  Copyright © 2020 Cody Thompson. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <fstream>
#include <queue>
#include <regex>

bool queueInit(std::string file, std::queue<std::string>& queue);

void parseTokens(std::string line, std::queue<std::string>& queue);

void initTokenQueue(std::queue<std::string>& queueIn, std::queue<std::string>& queueOut);


#endif /* Header_h */
