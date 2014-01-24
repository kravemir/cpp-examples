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
	
	using TOKEN = IniLoader::Parser::token;
%}

%option nodefault yyclass="IniLexer" noyywrap c++

%%

%{
	yylloc->step();
%}

[^\[\]\n= \t][^\[\]\n=]+[^\[\]\n= \t]  { *yylval = yytext; return IniLoader::Parser::token::STRING; }

"["          { return TOKEN::SECTION_START; }
"]"          { return TOKEN::SECTION_END; }
"="          { return TOKEN::ASSIGNMENT; }
.            { yylloc->step(); }
"\n"+        { yylloc->lines(yyleng); yylloc->step(); }

