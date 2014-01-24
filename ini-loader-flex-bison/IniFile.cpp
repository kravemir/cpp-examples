/*
 * Copyright © 2014 Miroslav Kravec <kravec.miroslav@gmail.com>
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * nd/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details.
 */

#include "IniFile.h"

/**
 * Open and parse a file
 */
IniFile::IniFile ( const char * const fileName ) throw ( std::string ) {
    std::ifstream inFile ( fileName );
    if ( !inFile.good() ) {
        throw std::string ( "Unable to open file" );
    }

    IniLoader::IniLexer scanner ( &inFile );
    IniLoader::Parser parser ( scanner, "", iniData );
    parser.parse();
}

/**
 * Parse an already open stream
 */
IniFile::IniFile ( std::istream &iniStream ) throw ( std::string ) {
    IniLoader::IniLexer scanner ( &iniStream );
    IniLoader::Parser parser ( scanner, "", iniData );
    parser.parse();
}


/**
 * Retrieve a value
 */
char const * IniFile::getValue ( const char * const section, const char * const key ) const {
    // find the section
    IniLoader::mapData::const_iterator iSection = iniData.find ( section );
    if ( iSection == iniData.end() ) {
        return 0;
    }

    // find the value
    std::map<std::string, std::string>::const_iterator iValue = iSection->second.find ( key );
    if ( iValue == iSection->second.end() ) {
        return 0;
    }

    // return the result
    return iValue->second.c_str();
}

void IniFile::print ( std::ostream& out ) {
    IniLoader::mapData::const_iterator iSection;
    std::map<std::string,std::string>::const_iterator iValue;

    for ( iSection = iniData.begin(); iSection != iniData.end(); iSection++ ) {
        std::cout << "[" << iSection->first << "]" << std::endl;
        for ( iValue = iSection->second.begin(); iValue != iSection->second.end(); iValue++ ) {
            std::cout << iValue->first << " = " << iValue->second << std::endl;
        }
        std::cout << std::endl;
    }
}
