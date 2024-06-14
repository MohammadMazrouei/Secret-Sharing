#include "main.h"

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

int main(int argc, char* argv[]) {
    std::string option = DEFAULT_OPTION;
    if (argc > 1) {
        std::string option = argv[1];
    }

    if (option == ENCODE_OPTION) {
        std::string type = get_type();
        if (type == "string") {

        }
        else if (type == "number") {

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
