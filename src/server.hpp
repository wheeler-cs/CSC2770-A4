#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstring>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>

#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

// Global variables needed for error-handling
bool Req_Error = false;
std::string Req_Estr = "";

const unsigned int MAX_FILE_SIZE = (20 * 1024); // 20 KiB

void handle_connection (int);
void parse (FILE*, std::map<std::string, std::string>&, std::string&);
void handle_connect();
void ASErrorHandler (int, const char*);
char* ASMemoryAlloc (unsigned long);

#endif