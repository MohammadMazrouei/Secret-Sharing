#include "main.h"

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

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

void set_mod() {
    while (true) {
        std::cout << "Enter mod: ";
        std::cin >> MOD;
        if (miller_rabin(MOD)) {
            return;
        }
    }
}

std::vector<std::pair<int, Mint>> input_keys(int t) {
    std::vector<std::pair<int, Mint>> keys(t);
    for (int i = 0; i < t; i++) {
        std::cout << "Enter No, key " << i + 1 << ": "; 
        std::cin >> keys[i].first >> keys[i].second;
    }
    return keys;
}

void print_line() {
    std::cout << BLUE << "\n----------------------------------------------------------------\n" << WHITE << std::endl;
}

class Encoder {
    private:
        int s, t;
        Mint secret;
        std::vector<std::pair<int, Mint>> keys;

    public:
        Encoder(int _s, int _t, Mint _secret) {
            s = _s;
            t = _t;
            secret = _secret;
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
        Mint get_secret() {
            return secret;
        }
        void set_secret(Mint _secret) {
            secret = _secret;
        }

        Mint f(int x, std::vector<Mint> coefficients) {
            Mint res = secret;
            for (int i = 0; i < t - 1; i++) {
                res += coefficients[i] * pow(Mint(x), i + 1); 
            }
            return res;
        }

        void generate_keys() {
            std::vector<Mint> coefficients(t - 1);
            for (int i = 0; i < t - 1; i++) {
                coefficients[i] = uid(1, 1000000000);
            }
            for (int i = 0; i < s; i++) {
                keys[i] = {i + 1, f(i + 1, coefficients)};
            }
        }
        std::vector<std::pair<int, Mint>> get_keys() {
            return keys;
        }
};

class Decoder {
    private:
        int t;
        Mint secret;
        std::vector<std::pair<int, Mint>> keys;

    public:
        Decoder(int _t, std::vector<std::pair<int, Mint>> _keys) {
            t = _t;
            keys = _keys;
        }
        Decoder(std::vector<std::pair<int, Mint>> _keys) {
            t = (int)keys.size();
            keys = _keys;
        }

        int get_t() {
            return t;
        }
        void set_t(int _t) {
            t = _t;
        }
        std::vector<std::pair<int, Mint>> get_keys() {
            return keys;
        }
        void set_keys(std::vector<std::pair<int, Mint>> _keys) {
            keys = _keys;
        }

        void generate_secret() {
            secret = 0;
            for (int i = 0; i < t; i++) {
                Mint product = 1;
                for (int j = 0; j < t; j++) {
                    if (i != j) {
                        Mint xi = keys[i].first, xj = keys[j].first;
                        product *= xj / (xj - xi);
                    }
                }
                secret += product * keys[i].second;
            }
        }
        Mint get_secret() {
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
        int64_t number = input_number();
        set_mod();
        Mint secret = number;
        print_line();

        Encoder encoder(s, t, secret);
        encoder.generate_keys();

        std::vector<std::pair<int, Mint>> keys = encoder.get_keys();
        std::cout << "Keys: " << std::endl;
        for (auto &key : keys) {
            std::cout << "Key " << key.first << ' ' << key.second << std::endl;
        }
        std::cout << std::endl;
    }
    else if (option == DECODE_OPTION) {
        int t = input_t();
        set_mod();
        std::vector<std::pair<int, Mint>> keys = input_keys(t);
        print_line();

        Decoder decoder(t, keys);
        decoder.generate_secret();

        Mint secret = decoder.get_secret();
        std::cout << "Secret: " << secret << std::endl << std::endl;
    }
    else {
        std::cerr << RED << "Option Error: Option is invalid." << WHITE << std::endl;
        return FAILIURE;
    }

    return SUCCESS; 
}
