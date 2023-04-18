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
	char* head = ASMemoryAlloc (255);
	fgets (head, 255, f_ptr);
	if (feof (f_ptr))
	{
		throw std::runtime_error ("Unexpected end of file when reading header");
	}
	else if (head != "ASTYLE")
	{
		std::string bad_header = head; // Cast from C-string to C++ string to allow concat
		throw std::runtime_error ("Expceted header ASTYLE, but got " + bad_header);
	}

	char* buffer = ASMemoryAlloc (255);
	do
	{
		fgets (buffer, 255, f_ptr);
		if (buffer[0] == '\n')
			break;

		
	} while (!feof (f_ptr));
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


/**
 * @fn ASErrorHandler
 * @brief Handles errors thrown by assigning values to global error variables.
 * 
 * @param err_num The number identifier of the error.
 * @param err_msg The message that accompanies the error.
 * 
 * @see server.hpp
 * 
 */
void ASErrorHandler (int err_num, const char* err_msg)
{
    //NOTE: Req_Error and Req_Estr are global variables
    //std::cerr << "astyle error " << err_num << "\n"
    //          << err_msg << std::endl;
    Req_Error = true;
    Req_Estr += err_msg + std::string("\n");
}


/**
 * @fn ASMemoryAlloc
 * @brief Allocates a character buffer and returns the pointer.
 * 
 * @param req_mem Memory (in bytes) that needs to be allocated for the buffer.
 * @returns A pointer to the chunk of memory allocated.
 * 
 */
char* ASMemoryAlloc (unsigned long req_mem)
{
    // Error condition is checked after return 
    char* buffer = new (std::nothrow) char [req_mem];
    return buffer;
}
