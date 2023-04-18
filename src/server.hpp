#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstdio>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>

void handle_connection (int);
void parse (FILE*, std::map<std::string, std::string>&, std::string&);
void handle_connect();
void ASErrorHandler (int, const char*);
char* ASMemoryAlloc (unsigned long);

#endif