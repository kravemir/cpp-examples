project(ini-loader-flex-bison)
cmake_minimum_required(VERSION 2.8)

# Create target for the parser
ADD_CUSTOM_TARGET(ini-loader-flex-bisonParser echo "Creating parser.cpp, lexer.cpp")

set ( FLEX_EXECUTABLE flex )
set ( BISON_EXECUTABLE bison )

# Create custom command for flex/lex (note the outputs)
ADD_CUSTOM_COMMAND(
   SOURCE ${ini-loader-flex-bison_SOURCE_DIR}/lexer.l
   COMMAND ${FLEX_EXECUTABLE} 
   ARGS    -o ${ini-loader-flex-bison_BINARY_DIR}/lexer.cpp
             ${ini-loader-flex-bison_SOURCE_DIR}/lexer.l
   TARGET ini-loader-flex-bisonParser
   OUTPUTS ${ini-loader-flex-bison_BINARY_DIR}/lexer.cpp)

# Create custom command for bison/yacc (note the DEPENDS)
ADD_CUSTOM_COMMAND(
    SOURCE ${ini-loader-flex-bison_SOURCE_DIR}/parser.y
    COMMAND ${BISON_EXECUTABLE} 
    ARGS    -y ${ini-loader-flex-bison_SOURCE_DIR}/parser.y
            -o ${ini-loader-flex-bison_BINARY_DIR}/parser.cpp
    TARGET ini-loader-flex-bisonParser
    DEPENDS ${ini-loader-flex-bison_BINARY_DIR}/lexer.cpp
    OUTPUTS ${ini-loader-flex-bison_BINARY_DIR}/parser.cpp
)

# Add parser.c to the list of sources
SET(ini-loader-flex-bison_SRCS 
    ${ini-loader-flex-bison_BINARY_DIR}/parser.cpp 
    ${ini-loader-flex-bison_BINARY_DIR}/lexer.cpp
    IniLexer.cpp
    IniFile.cpp
    main.cpp
)

# Since parser.cpp, lexer.cpp do not exists yet when cmake is run, 
# mark them as generated
SET_SOURCE_FILES_PROPERTIES( 
    ${ini-loader-flex-bison_BINARY_DIR}/parser.cpp
    ${ini-loader-flex-bison_BINARY_DIR}/lexer.cpp 
    
    GENERATED
)

# Include binary directory to include lexer.c in parser.c
INCLUDE_DIRECTORIES(${ini-loader-flex-bison_BINARY_DIR})
INCLUDE_DIRECTORIES(${ini-loader-flex-bison_SOURCE_DIR})

add_executable(ini-loader-flex-bison ${ini-loader-flex-bison_SRCS})
