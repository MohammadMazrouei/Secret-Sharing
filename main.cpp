#include "main.h"
#include <cstdint>

std::string get_type() {
    std::string type;
    do {
        std::cout << "Enter type[string(s), number(n)]: ";
        std::cin >> type;

        if (type[0] == 's') {
            type = "string";
            break;
        }
        else if (type[0] == 'n') {
            type = "number";
            break;
        }
    } while (true);

    return type;
}

std::string get_text() {
    std::string text;
    std::cout << "Enter text: ";
    getline(std::cin, text);

    return text;
}

void get_values(int &s, int &t) {
    std::cout << "Enter s: ";
    std::cin >> s;

    std::cout << "Enter t: ";
    std::cin >> t;
}

void get_values(int &s, int &t, int64_t &number, int64_t &mod) {
    std::cout << "Enter s: ";
    std::cin >> s;

    std::cout << "Enter t: ";
    std::cin >> t;

    std::cout << "Enter number: ";
    std::cin >> number;

    std::cout << "Enter mod: ";
    std::cin >> mod;
}

void print_line() {
    std::cout << BLUE << "\n----------------------------------------------------------------" << WHITE << std::endl;
}

void encode(int s, int t, int64_t number, int64_t mod) {

}

void encode_string(int s, int t, std::string text) {

}

int main(int argc, char* argv[]) {
    std::string option = DEFAULT_OPTION;
    if (argc > 1) {
        std::string option = argv[1];
    }

    if (option == ENCODE_OPTION) {
        std::string type = get_type();
        if (type == "string") {
            std::string text = get_text();
            int s, t;
            get_values(s, t);
            print_line();

            encode_string(s, t, text); 
        }
        else if (type == "number") {
            int s, t;
            int64_t number, mod;
            get_values(s, t, number, mod);
            print_line();

            encode(s, t, number, mod);
        }
    }
    else if (option == DECODE_OPTION) {
        std::string type = get_type();
        if (type == "string") {

        }
        else if (type == "number") {

        }
    }
    else {
        std::cerr << RED << "Option Error: Option is invalid." << WHITE << std::endl;
        return FAILIURE;
    }

    return SUCCESS; 
}
