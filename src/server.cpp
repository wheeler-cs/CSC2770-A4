#include "server.hpp"


void handle_connect (int data_socket)
{
    /*
	// parameters: ns - data socket
	create file stream fp from ns // use fdopen
	// Note: header and doc are of type string
	//       options is a map of string to string
	call parse, passing it fp,options,
	    and doc
	if parse throws an exception then
		create error message 
		  and send error message to client
		close fp
		return
	fi
	initialize parmeter to the empty string
	for each (key,value) pair in options where key is not "SIZE"
		make a string key + "=" + value + "\n"
		    and append it to parameter
	rof
	call AStyleMain and pass it parameter
		// see below for special parameters
	if an error occurred
		create error message and send msg to
		    client
	else
		create OK message and send to client
	fi
	close fp
    */
}


void parse (FILE* f_ptr, std::map<std::string, std::string>& options, std::string& doc)
{
    /*
	// in:    fp      - file stream fp
	// in/out:
	//        header  - if header is not null, what header
	// out:
	//        options - a map of options as key,value pairs
	//        doc     - The document from the message body
	read (fgets) the first line from fp into head  // trim the newline
	if eof then
		throw runtime error "Unpected end of file when reading header"
	fi
	
	if head is not "ASTYLE" then
			throw runtime error "Expected header ASTYLE, but got $head"
	fi
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

void handle_connect()
{
    /*
    // in handle_connect()...

    // code before call to AStyleMain ...
     
    Req_Error = false;
    Req_Estr = "";
    char* textOut = AStyleMain(doc.c_str(), opts.c_str(), ASErrorHandler, ASMemoryAlloc);
    if (Req_Error) {
        std::string ret_message("ERR\nSIZE=" + std::to_string(Req_Estr.size()) + "\n\n" + Req_Estr.c_str());
        fprintf(fp, "%s", ret_message.c_str());
    } else {
        std::string ret_message("OK\nSIZE=" + std::to_string(strlen(textOut)) + "\n\n" + textOut);
        fprintf(fp, "%s", ret_message.c_str());
    }
	// now check Req_Error, and if it is true, send back an error to client.  See handle_connect()
    // pseudocode.
  
    // more code in handle connect after call to AStyleMain ...
    */
}

void ASErrorHandler (int err_num, const char* err_msg)
{
    /*
    //NOTE: Req_Error and Req_Estr are global variables
    //std::cout << "astyle error " << errorNumber << "\n"
    //     << errorMessage << std::endl;
    Req_Error = true;
    Req_Estr += errorMessage + std::string("\n");
    */
}

char* ASMemoryAlloc (unsigned long req_mem)
{
    /*
    // Error condition is checked after return 
    char* buffer = new (std::nothrow) char [memoryNeeded];
    return buffer;
    */
}
