/*
 * Copyright © 2014 Miroslav Kravec <kravec.miroslav@gmail.com>
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * nd/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details.
 */

%require "2.4.1"
%skeleton "lalr1.cc"
%defines
%locations
%define namespace "IniLoader"
%define parser_class_name "Parser"
%parse-param { IniLoader::IniLexer &lexer }
%parse-param { std::string currentSection }
%parse-param { IniLoader::mapData &iniData }
%lex-param   { IniLoader::IniLexer &lexer }

%code requires {
#include <string>
#include <sstream>
#include <map>

    // We want to return a string
#define YYSTYPE std::string

    namespace IniLoader {
    // Forward-declare the IniLexer class; the Parser needs to be assigned a
    // IniLexer, but the IniLexer can't be declared without the Parser
    class IniLexer;

    // We use a map to store the INI data
    typedef std::map<std::string, std::map<std::string, std::string> > mapData;
    }

}

%code {
    // Prototype for the yylex function
    static int yylex(IniLoader::Parser::semantic_type * yylval,
    IniLoader::Parser::location_type * yylloc,
    IniLoader::IniLexer &lexer);
}

%token STRING SECTION_START SECTION_END ASSIGNMENT

%%

input
    : input line
    | line
    ;

line
    : section
    | value
    ;

section 
    : SECTION_START STRING SECTION_END { currentSection = $2; }
    ;

value 
    : STRING ASSIGNMENT STRING { iniData[currentSection][$1] = $3; }
    ;

%%

// Error function throws an exception (std::string) with the location and error message
void IniLoader::Parser::error(const IniLoader::Parser::location_type &loc,
                              const std::string &msg) {
    std::ostringstream ret;
    ret << "Parser Error at " << loc << ": " << msg;
    throw ret.str();
}

// Now that we have the Parser declared, we can declare the IniLexer and implement
// the yylex function
#include "IniLexer.h"
static int yylex(IniLoader::Parser::semantic_type * yylval,
                 IniLoader::Parser::location_type * yylloc,
                 IniLoader::IniLexer &lexer) {
    return lexer.yylex(yylval, yylloc);
}

