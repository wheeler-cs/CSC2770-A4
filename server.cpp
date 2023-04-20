#include "server.hpp"

void handle_connect (int data_socket)
{
    // Variables needed for `parse` call
    std::map <std::string, std::string> option_map;
    std::string file_text = "";
    FILE* f_desc = fdopen (data_socket, "r+");

    // Attempt to read data sent and process accordingly
    try
    {
        parse (f_desc, option_map, file_text);
    }
    catch (...) // For now, just catch any exception and return an error
    {
        ASErrorHandler (0, "");
        fclose (f_desc);
        return;
    }

	// Get all map options (excluding SIZE) and store them in a single string
	std::string parameter = "";
	std::map<std::string, std::string>::iterator it = option_map.begin();
	for (; it != option_map.end(); it++)
	{
		if (it->first != "SIZE")
		{
			parameter += (it->first + "=" + it->second + "\n");
		}
	}


	std::string options = "";

    Req_Error = false;
    Req_Estr = "";

	// TODO: Figure out why this won't work
    char* styled_text = AStyleMain(file_text.c_str(), options.c_str(), ASErrorHandler, ASMemoryAlloc);
    if (Req_Error) {
        std::string ret_message("ERR\nSIZE=" + std::to_string(Req_Estr.size()) + "\n\n" + Req_Estr.c_str());
        fprintf(f_desc, "%s", ret_message.c_str());
    } else {
        std::string ret_message("OK\nSIZE=" + std::to_string(strlen(styled_text)) + "\n\n" + styled_text);
        fprintf(f_desc, "%s", ret_message.c_str());
    }

	// Check if an error occurred during the execution of AStyleMain
	if (Req_Error)
	{
		// If an error occurred, create err msg and send msg to client
		fclose (f_desc);
	}
	else
	{
		// Create OK message and send to client
	}
	fclose (f_desc);
}


void parse (FILE* f_ptr, std::map<std::string, std::string>& options, std::string& doc)
{
	char* head = new char[255];
	fgets (head, 255, f_ptr);
	std::string head_str = head;
	if (feof (f_ptr))
	{
		throw std::runtime_error ("Unexpected end of file when reading header");
	}
	else if (head_str != "ASTYLE")
	{
		std::string bad_header = head; // Cast from C-string to C++ string to allow concat
		throw std::runtime_error ("Expceted header ASTYLE, but got " + bad_header);
	}
	delete[] head;

	char* buffer = new char[255];
	do
	{
		fgets (buffer, 255, f_ptr);
		if (buffer[0] == '\n')
			break;

		
	} while (!feof (f_ptr));
	delete[] buffer;
	/*
	for each line read from fp
		if line is a newline then
			break
		trim the line
		if line is the form key=value then
			parse the key and value
  			if key is not one of "SIZE", "mode", or "style" then
      			throw error "Bad option"
		else 
			throw error "Bad option "
		fi
		if key is "SIZE" then
			convert value to integer and store in size
		fi
		insert (key,value) into options map
	rof
	if size < 0 then
		thow error "Bad code size"
	fi
	if size > MAX_FILE_SIZE then
		throw error "Bad code size"
	fi
	read size bytes into string doc
    */
}

// Note Req_Error and Req_Estr are global variables
void ASErrorHandler(int errorNumber, const char* errorMessage) {   
    //std::cout << "astyle error " << errorNumber << "\n"
    //     << errorMessage << std::endl;
    Req_Error = true;
    Req_Estr += errorMessage + std::string("\n");

}

char* ASMemoryAlloc (unsigned long memoryNeeded) {   // error condition is checked after return from AStyleMain
    char* buffer = new (std::nothrow) char [memoryNeeded];
    return buffer;
}
