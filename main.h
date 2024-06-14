#include <iostream>
#include <string>

#define SUCCESS 0
#define FAILIURE 1
#define FILE_ERROR 2

#define DEFAULT_OPTION "-e"
#define ENCODE_OPTION "-e"
#define DECODE_OPTION "-d"

#define COLORED_ERRORS true
const std::string WHITE = COLORED_ERRORS ? "\033[0;m" : "";
const std::string RED = COLORED_ERRORS ? "\033[0;31m" : "";
