/*
 * Copyright © 2014 Miroslav Kravec <kravec.miroslav@gmail.com>
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * nd/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details.
 */

#ifndef INILEXER_H
#define INILEXER_H

// Only include FlexLexer.h if it hasn't been already included
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

// Override the interface for yylex since we namespaced it
#undef YY_DECL
#define YY_DECL int IniLoader::IniLexer::yylex()

// Include Bison for types / tokens
#include "parser.hpp"


namespace IniLoader {

    class IniLexer : public yyFlexLexer {
        public:
        // constructor accepts the input and output streams
        // 0 means std equivilant (stdin, stdout)
        IniLexer ( std::istream * in = 0, std::ostream * out = 0 ) : yyFlexLexer ( in, out ) { }

        // overloaded version of yylex - we need a pointer to yylval and yylloc
        int yylex ( Parser::semantic_type * lval,
        Parser::location_type * lloc );

        private:
        // Scanning function created by Flex; make this private to force usage
        // of the overloaded method so we can get a pointer to Bison's yylval
        int yylex();

        // point to yylval (provided by Bison in overloaded yylex)
        Parser::semantic_type * yylval;

        // pointer to yylloc (provided by Bison in overloaded yylex)
        Parser::location_type * yylloc;

        // block default constructor
        IniLexer();
        // block default copy constructor
        IniLexer ( IniLexer const &rhs );
        // block default assignment operator
        IniLexer &operator= ( IniLexer const &rhs );
    };


}

#endif // INILEXER_H
