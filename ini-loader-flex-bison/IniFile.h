/*
 * Copyright © 2014 Miroslav Kravec <kravec.miroslav@gmail.com>
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * nd/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details.
 */

#ifndef INIFILE_H
#define INIFILE_H

#include <fstream>
#include "IniLexer.h"

class IniFile {
    public:
    // can instantiate with either a file name or an already open stream
    explicit IniFile ( const char * const fileName ) throw ( std::string );
    explicit IniFile ( std::istream &iniStream ) throw ( std::string );

    // Get a value from section and key
    const char * getValue ( const char * const section, const char * const key ) const;

    void print ( const char * const fileName );
    void print ( std::ostream &out );
    private:
    // supress default constructor
    IniFile();
    // supress default copy constructor
    IniFile ( IniFile const &rhs );
    // supress default assignment operator
    IniFile &operator= ( IniFile const &rhs );

    // the ini data
    IniLoader::mapData iniData;
};

#endif // INIFILE_H

