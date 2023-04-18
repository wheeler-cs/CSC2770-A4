#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstdio>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>

// Global variables needed for error-handling
bool Req_Error = false;
std::string Req_Estr = "";

void handle_connection (int);
void parse (FILE*, std::map<std::string, std::string>&, std::string&);
void handle_connect();
void ASErrorHandler (int, const char*);
char* ASMemoryAlloc (unsigned long);

#endif