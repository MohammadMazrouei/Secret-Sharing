#include "main.h"
// TODO use getline for get text and string keys

std::string get_type() {
    std::string type;
    while (true) {
        std::cout << "Enter type[string(s), number(n)]: ";
        std::cin >> type;

        if (type[0] == 's') {
            return "string";
        }
        else if (type[0] == 'n') {
            return "number";
        }
    }
}

int input_s() {
    int s;
    std::cout << "Enter s: ";
    std::cin >> s;
    return s;
}

int input_t() {
    int t;
    std::cout << "Enter t: ";
    std::cin >> t;
    return t;
}

int64_t input_number() {
    int64_t number;
    std::cout << "Enter number: ";
    std::cin >> number;
    return number;
}

int64_t input_mod() {
    int64_t mod;
    std::cout << "Enter mod: ";
    std::cin >> mod;
    return mod;
}

std::string input_text() {
    std::string text;
    std::cout << "Enter text: " << std::endl;
    std::cin >> text;
    return text;
}

std::vector<std::pair<int, std::string>> input_string_keys(int t) {
    std::vector<std::pair<int, std::string>> keys(t);
    for (int i = 0; i < t; i++) {
        std::cout << "Enter No, key " << i + 1 << ": "; 
        std::cin >> keys[i].first >> keys[i].second;
    }
    return keys;
}

std::vector<std::pair<int, int64_t>> input_number_keys(int t) {
    std::vector<std::pair<int, int64_t>> keys(t);
    for (int i = 0; i < t; i++) {
        std::cout << "Enter No, key " << i + 1 << ": "; 
        std::cin >> keys[i].first >> keys[i].second;
    }
    return keys;
}

void print_line() {
    std::cout << BLUE << "\n----------------------------------------------------------------" << WHITE << std::endl;
}

template <typename T>
class Encoder {
    private:
        int s, t;
        T secret, mod;
        std::vector<T> keys;

    public:
        Encoder(int _s, int _t, T _secret, T _mod = T()) {
            s = _s;
            t = _t;
            secret = _secret;
            mod = _mod;
        }

        int get_s() {
            return s;
        }
        void set_s(int _s) {
            s = _s;
        }
        int get_t() {
            return t;
        }
        void set_t(int _t) {
            t = _t;
        }
        T get_secret() {
            return secret;
        }
        void set_secret(T _secret) {
            secret = _secret();
        }
        T get_mod() {
            return mod;
        }
        void set_mod(T _mod) {
            mod = _mod;
        }

        void generate_keys() {

        }
};

template <typename T>
class Decoder {
    private:
        int t;
        T secret, mod;
        std::vector<std::pair<int, T>> keys;

    public:
        Decoder(int _t, std::vector<std::pair<int, T>> _keys, T _mod = T()) {
            t = _t;
            keys = _keys;
            mod = _mod;
        }
        Decoder(std::vector<T> _keys, T _mod = T()) {
            t = (int)keys.size();
            keys = _keys;
            mod = _mod;
        }

        int get_t() {
            return t;
        }
        void set_t(int _t) {
            t = _t;
        }
        std::vector<std::pair<int, T>> get_keys() {
            return keys;
        }
        void set_keys(std::vector<std::pair<int, T>> _secret) {
            secret = _secret();
        }
        T get_mod() {
            return mod;
        }
        void set_mod(T _mod) {
            mod = _mod;
        }

        void generate_secret() {

        }
};

int main(int argc, char* argv[]) {
    std::string option = DEFAULT_OPTION;
    if (argc > 1) {
        option = argv[1];
    }

    if (option == ENCODE_OPTION) {
        std::string type = get_type();
        if (type == "string") {
            int s = input_s(), t = input_t();
            std::string secret = input_text();
            print_line();

            Encoder<std::string> encoder(s, t, secret);
            encoder.generate_keys();
        }
        else if (type == "number") {
            int s = input_s(), t = input_t();
            int64_t secret = input_number(), mod = input_mod();
            print_line();

            Encoder<int64_t> encoder(s, t, secret, mod);
            encoder.generate_keys();
        }
    }
    else if (option == DECODE_OPTION) {
        std::string type = get_type();
        if (type == "string") {
            int t = input_t();
            std::vector<std::pair<int, std::string>> keys = input_string_keys(t);
            print_line();

            Decoder<std::string> decoder(t, keys);;
            decoder.generate_secret();
        }
        else if (type == "number") {
            int t = input_t();
            int64_t mod = input_mod();
            std::vector<std::pair<int, int64_t>> keys = input_number_keys(t);
            print_line();

            Decoder<int64_t> decoder(t, keys, mod);
            decoder.generate_secret();
        }
    }
    else {
        std::cerr << RED << "Option Error: Option is invalid." << WHITE << std::endl;
        return FAILIURE;
    }

    return SUCCESS; 
}
