/* 
 * Copyright © 2014 Miroslav Kravec <kravec.miroslav@gmail.com>
 * 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * nd/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details.
 */

%{
	#include "IniLexer.h"
	// used to keep track of location
	#define YY_USER_ACTION yylloc->columns(yyleng);
%}

%option nodefault yyclass="Scanner" noyywrap c++

%%

%{
	yylloc->step();
%}

[^\[\]\n= \t][^\[\]\n=]+[^\[\]\n= \t]  { *yylval = yytext; return IniLoader::Parser::token::STRING; }

"["          { return IniLoader::Parser::token::SECTION_START; }
"]"          { return IniLoader::Parser::token::SECTION_END; }
"="          { return IniLoader::Parser::token::ASSIGNMENT; }
.            { yylloc->step(); }
"\n"+        { yylloc->lines(yyleng); yylloc->step(); }

