#include "main.h"
#include <cstdint>
// TODO use getline for get text and string keys
// MOD must be prime

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

using u128 = __uint128_t;
int64_t binpow(int64_t a, int64_t b, int64_t m) {
    int64_t res = 1;
    a %= m;
    while (b) {
        if (b & 1) {
            res = (u128)res * a % m;
        }
        a = (u128)a * a % m;
        b >>= 1;
    }
    return res;
}

bool check_composite(int64_t n, int64_t a, int64_t d, int s) {
    int64_t x = binpow(a, d, n);
    if (x == 1 || x == n - 1) {
        return false;
    }
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1) {
            return false;
        }
    }
    return true;
}

bool miller_rabin(int64_t n) { // returns true if n is prime
    if (n < 2) {
        return false;
    }

    int r = 0;
    int64_t d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) {
            return true;
        }
        if (check_composite(n, a, d, r)) {
            return false;
        }
    }
    return true;
}

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
    while (true) {
        std::cout << "Enter mod: ";
        std::cin >> mod;
        if (miller_rabin(mod)) {
            return mod;
        }
    }
}

std::vector<std::pair<int, int64_t>> input_keys(int t) {
    std::vector<std::pair<int, int64_t>> keys(t);
    for (int i = 0; i < t; i++) {
        std::cout << "Enter No, key " << i + 1 << ": "; 
        std::cin >> keys[i].first >> keys[i].second;
    }
    return keys;
}

void print_line() {
    std::cout << BLUE << "\n----------------------------------------------------------------\n" << WHITE << std::endl;
}

int64_t MOD = 1e9 + 7;
class Mint {
    private:
        int64_t v; 

    public:
        Mint() { 
            v = 0; 
        }
        Mint(int64_t _v) {
            v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
            if (v < 0) {
                v += MOD;
            }
        }

        explicit operator int64_t() const { 
            return v;
        }
        explicit operator int() const { 
            return v;
        }

        friend bool operator == (const Mint &a, const Mint &b) { 
            return a.v == b.v;
        }
        friend bool operator != (const Mint &a, const Mint &b) { 
            return !(a == b);
        }
        friend bool operator < (const Mint &a, const Mint &b) { 
            return a.v < b.v;
        }
        friend bool operator > (const Mint &a, const Mint &b) { 
            return a.v > b.v;
        }
        friend bool operator <= (const Mint &a, const Mint &b) { 
            return a.v <= b.v;
        }
        friend bool operator >= (const Mint &a, const Mint &b) { 
            return a.v >= b.v;
        }

        friend Mint operator + (Mint a, const Mint &b) { 
            return a += b;
        }
        friend Mint operator - (Mint a, const Mint &b) { 
            return a -= b;
        }
        friend Mint operator * (Mint a, const Mint &b) { 
            return a *= b;
        }
        friend Mint operator / (Mint a, const Mint &b) { 
            return a /= b;
        }
        Mint& operator += (const Mint &m) { 
            if ((v += m.v) >= MOD) {
                v -= MOD;
            }
            return *this;
        }
        Mint& operator -= (const Mint &m) { 
            if ((v -= m.v) < 0) {
                v += MOD; 
            }
            return *this; 
        }
        Mint& operator *= (const Mint &m) { 
            v = v * m.v % MOD;
            return *this; 
        }
        Mint& operator /= (const Mint &m) { 
            return (*this) *= inv(m); 
        }

        Mint operator - () const { 
            return Mint(-v);
        }
        Mint& operator ++ () { 
            return *this += 1;
        }
        Mint& operator -- () { 
            return *this -= 1;
        }
        Mint operator ++ (int) { 
            Mint temp; 
            temp.v = v++; 
            return temp; 
        }
        Mint operator -- (int) { 
            Mint temp; 
            temp.v = v--; 
            return temp; 
        }

        friend Mint pow(Mint a, int64_t b) {
            assert(b >= 0);
            Mint res = 1;
            while (b) {
                if (b & 1) {
                    res *= a;
                }
                a *= a;
                b >>= 1;
            }
            return res;
        }
        friend Mint inv(const Mint &a) {
            assert(a.v != 0);
            return pow(a, MOD - 2);
        }

        friend std::ostream& operator << (std::ostream &os, const Mint &m) {
            os << m.v; 
            return os;
        }
        friend std::istream& operator >> (std::istream &is, Mint &m) {
            int64_t x; 
            is >> x;
            m.v = x;
            return is;
        }
};

class Encoder {
    private:
        int s, t;
        int64_t secret, mod;
        std::vector<std::pair<int, int64_t>> keys;

    public:
        Encoder(int _s, int _t, int64_t _secret, int64_t _mod) {
            s = _s;
            t = _t;
            secret = _secret;
            mod = _mod;
            MOD = mod;
            keys.resize(s);
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
        int64_t get_secret() {
            return secret;
        }
        void set_secret(int64_t _secret) {
            secret = _secret;
        }
        int64_t get_mod() {
            return mod;
        }
        void set_mod(int64_t _mod) {
            mod = _mod;
        }

        int64_t f(int x, std::vector<int64_t> coefficients) {
            Mint mi = secret;
            for (int i = 0; i < t - 1; i++) {
                mi += Mint(coefficients[i]) * pow(Mint(x), i + 1); 
            }

            return int64_t(mi);
        }

        void generate_keys() {
            std::vector<int64_t> coefficients(t - 1);
            for (int i = 0; i < t - 1; i++) {
                coefficients[i] = uid(1, 1000000000);
            }
            for (int i = 0; i < s; i++) {
                keys[i] = {i + 1, f(i + 1, coefficients)};
            }
        }
        std::vector<std::pair<int, int64_t>> get_keys() {
            return keys;
        }
};

class Decoder {
    private:
        int t;
        int64_t secret, mod;
        std::vector<std::pair<int, int64_t>> keys;

    public:
        Decoder(int _t, std::vector<std::pair<int, int64_t>> _keys, int64_t _mod) {
            t = _t;
            keys = _keys;
            mod = _mod;
            MOD = mod;
        }
        Decoder(std::vector<std::pair<int, int64_t>> _keys, int64_t _mod) {
            t = (int)keys.size();
            keys = _keys;
            mod = _mod;
            MOD = mod;
        }

        int get_t() {
            return t;
        }
        void set_t(int _t) {
            t = _t;
        }
        std::vector<std::pair<int, int64_t>> get_keys() {
            return keys;
        }
        void set_keys(std::vector<std::pair<int, int64_t>> _keys) {
            keys = _keys;
        }
        int64_t get_mod() {
            return mod;
        }
        void set_mod(int64_t _mod) {
            mod = _mod;
        }

        void generate_secret() {
            Mint mi = 0;
            for (int i = 0; i < t; i++) {
                Mint product = 1;
                for (int j = 0; j < t; j++) {
                    if (i != j) {
                        Mint xi = keys[i].first, xj = keys[j].first;
                        product *= xj / (xj - xi);
                    }
                }
                mi += product * Mint(keys[i].second);
            }
            secret = int64_t(mi);
        }
        int64_t get_secret() {
            return secret;
        }
};

int main(int argc, char* argv[]) {
    std::string option = DEFAULT_OPTION;
    if (argc > 1) {
        option = argv[1];
    }

    if (option == ENCODE_OPTION) {
        int s = input_s(), t = input_t();
        int64_t secret = input_number(), mod = input_mod();
        print_line();

        Encoder encoder(s, t, secret, mod);
        encoder.generate_keys();

        std::vector<std::pair<int, int64_t>> keys = encoder.get_keys();
        std::cout << "Keys: " << std::endl;
        for (auto &key : keys) {
            std::cout << "Key " << key.first << ' ' << key.second << std::endl;
        }
    }
    else if (option == DECODE_OPTION) {
        int t = input_t();
        int64_t mod = input_mod();
        std::vector<std::pair<int, int64_t>> keys = input_keys(t);
        print_line();

        Decoder decoder(t, keys, mod);
        decoder.generate_secret();

        int64_t secret = decoder.get_secret();
        std::cout << "Secret: " << secret << std::endl;
    }
    else {
        std::cerr << RED << "Option Error: Option is invalid." << WHITE << std::endl;
        return FAILIURE;
    }

    return SUCCESS; 
}
