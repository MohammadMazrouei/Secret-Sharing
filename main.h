#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <chrono>
#include <random>

#define SUCCESS 0
#define FAILIURE 1
#define FILE_ERROR 2

#define DEFAULT_OPTION "-e"
#define ENCODE_OPTION "-e"
#define DECODE_OPTION "-d"

#define COLORED_OUTPUT true
const std::string WHITE = COLORED_OUTPUT ? "\033[0;m" : "";
const std::string RED = COLORED_OUTPUT ? "\033[0;31m" : "";
const std::string GREEN = COLORED_OUTPUT ? "\033[0;32m" : "";
const std::string BLUE = COLORED_OUTPUT ? "\033[0;34m" : "";

#define uid(a, b) std::uniform_int_distribution<int>(a, b)(rng)
