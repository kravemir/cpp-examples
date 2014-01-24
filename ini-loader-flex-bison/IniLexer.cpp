/*
 * Copyright © 2014 Miroslav Kravec <kravec.miroslav@gmail.com>
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * nd/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details.
 */

#include "IniLexer.h"

using namespace IniLoader;

// all our overloaded version does is save yylval and yylloc to member variables
// and invoke the generated scanner
int IniLexer::yylex ( Parser::semantic_type * lval,
                      Parser::location_type * lloc ) {
    yylval = lval;
    yylloc = lloc;
    return yylex();
}
