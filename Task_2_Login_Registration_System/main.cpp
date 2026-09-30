#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include <cctype>

using namespace std;

const string USER_FILE = "users.txt";

uint32_t rotateRight(uint32_t x, uint32_t n) {
    return (x >> n) | (x << (32 - n));
}

string sha256(const string& input) {
    static const uint32_t k[] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    uint32_t h[] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    string data = input;

    uint64_t bitLength = static_cast<uint64_t>(data.size()) * 8;

    data += static_cast<char>(0x80);

    while ((data.size() % 64) != 56)
        data += static_cast<char>(0x00);

    for (int i = 7; i >= 0; i--)
        data += static_cast<char>((bitLength >> (i * 8)) & 0xff);

    for (size_t chunk = 0; chunk < data.size(); chunk += 64) {

        uint32_t w[64] = {};

        for (int i = 0; i < 16; i++) {
            size_t index = chunk + i * 4;

            w[i] =
                (static_cast<uint32_t>(
                    static_cast<unsigned char>(data[index])) << 24) |
                (static_cast<uint32_t>(
                    static_cast<unsigned char>(data[index + 1])) << 16) |
                (static_cast<uint32_t>(
                    static_cast<unsigned char>(data[index + 2])) << 8) |
                static_cast<uint32_t>(
                    static_cast<unsigned char>(data[index + 3]));
        }

        for (int i = 16; i < 64; i++) {
            uint32_t s0 =
                rotateRight(w[i - 15], 7) ^
                rotateRight(w[i - 15], 18) ^
                (w[i - 15] >> 3);

            uint32_t s1 =
                rotateRight(w[i - 2], 17) ^
                rotateRight(w[i - 2], 19) ^
                (w[i - 2] >> 10);

            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        uint32_t a = h[0];
        uint32_t b = h[1];
        uint32_t c = h[2];
        uint32_t d = h[3];
        uint32_t e = h[4];
        uint32_t f = h[5];
        uint32_t g = h[6];
        uint32_t hh = h[7];

        for (int i = 0; i < 64; i++) {

            uint32_t S1 =
                rotateRight(e, 6) ^
                rotateRight(e, 11) ^
                rotateRight(e, 25);

            uint32_t choice =
                (e & f) ^ ((~e) & g);

            uint32_t temp1 =
                hh + S1 + choice + k[i] + w[i];

            uint32_t S0 =
                rotateRight(a, 2) ^
                rotateRight(a, 13) ^
                rotateRight(a, 22);

            uint32_t majority =
                (a & b) ^ (a & c) ^ (b & c);

            uint32_t temp2 =
                S0 + majority;

            hh = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += hh;
    }

    stringstream result;

    for (uint32_t value : h) {
        result << hex << setw(8) << setfill('0') << value;
    }

    return result.str();
}

string generateSalt() {
    static random_device rd;
    static mt19937 generator(rd());

    uniform_int_distribution<int> distribution(0, 255);

    stringstream salt;

    for (int i = 0; i < 16; i++) {
        salt << hex << setw(2) << setfill('0')
             << distribution(generator);
    }

    return salt.str();
}

bool validUsername(const string& username) {

    if (username.length() < 3 || username.length() > 20)
        return false;

    for (char ch : username) {
        if (!isalnum(static_cast<unsigned char>(ch)) &&
            ch != '_' &&
            ch != '.') {
            return false;
        }
    }

    return true;
}

bool validPassword(const string& password) {

    if (password.length() < 8)
        return false;

    bool hasLetter = false;
    bool hasDigit = false;

    for (char ch : password) {

        if (isalpha(static_cast<unsigned char>(ch)))
            hasLetter = true;

        if (isdigit(static_cast<unsigned char>(ch)))
            hasDigit = true;
    }

    return hasLetter && hasDigit;
}

bool usernameExists(const string& username) {

    ifstream file(USER_FILE);

    string storedUsername;
    string salt;
    string hash;

    while (file >> storedUsername >> salt >> hash) {

        if (storedUsername == username)
            return true;
    }

    return false;
}

bool registerUser() {

    string username;
    string password;

    cout << "\n===== Registration =====\n";

    cout << "Enter username: ";
    cin >> username;

    if (!validUsername(username)) {
        cout << "Invalid username.\n";
        cout << "Use 3-20 characters: letters, numbers, _ or .\n";
        return false;
    }

    if (usernameExists(username)) {
        cout << "Username already exists.\n";
        return false;
    }

    cout << "Enter password: ";
    cin >> password;

    if (!validPassword(password)) {
        cout << "Invalid password.\n";
        cout << "Password must contain at least 8 characters, "
                "including a letter and a number.\n";
        return false;
    }

    string salt = generateSalt();

    string hash =
        sha256(salt + password);

    ofstream file(USER_FILE, ios::app);

    if (!file) {
        cout << "Unable to open user database.\n";
        return false;
    }

    file << username << ' '
         << salt << ' '
         << hash << '\n';

    file.close();

    cout << "Registration successful.\n";

    return true;
}

bool loginUser() {

    string username;
    string password;

    cout << "\n===== Login =====\n";

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream file(USER_FILE);

    if (!file) {
        cout << "No registered users found.\n";
        return false;
    }

    string storedUsername;
    string salt;
    string storedHash;

    while (file >> storedUsername >> salt >> storedHash) {

        if (storedUsername == username) {

            string enteredHash =
                sha256(salt + password);

            if (enteredHash == storedHash) {
                cout << "Login successful. Welcome, "
                     << username << "!\n";
                return true;
            }

            cout << "Incorrect password.\n";
            return false;
        }
    }

    cout << "Username not found.\n";
    return false;
}

int main() {

    int choice;

    while (true) {

        cout << "\n============================\n";
        cout << " Login & Registration System\n";
        cout << "============================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";

        cin >> choice;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Please enter a valid option.\n";
            continue;
        }

        switch (choice) {

            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                cout << "Goodbye!\n";
                return 0;

            default:
                cout << "Invalid option.\n";
        }
    }
}