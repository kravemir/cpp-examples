/*
 * Copyright © 2014 Miroslav Kravec <kravec.miroslav@gmail.com>
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * nd/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details.
 */

#include <iostream>
#include <cstring>

#include "IniFile.h"

int main ( int argc, char * argv[] ) {
    // check we got filename argument
    if ( argc != 2 ) {
        std::cerr << "Usage: ./ini-loader-flex-bison <config-filename>" << std::endl;
        return 255;
    }

    // try and open the INI file
    IniFile * iniFile;
    try {
        // - means stdin, not a file named '-'
        if ( strcmp ( argv[1], "-" ) == 0 ) {
            iniFile = new IniFile ( std::cin );
        } else {
            iniFile = new IniFile ( argv[1] );
        }
    } catch ( std::string error ) {
        std::cerr << "ERROR: " << error << std::endl;
        return 255;
    }

    // print it to a stream
    iniFile->print ( std::cout );

    delete iniFile;
    return 0;
}
