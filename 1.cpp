#include <iostream>
#include <string>
#include <algorithm>

bool isRightLetters(std::string str) {
    std::string checkword = "TINKOFF";

    if (str.length() != checkword.length()) {
        return false;
    }

    for (char sym : checkword) {
        int index = str.find(sym);
        if (index != std::string::npos) {
            str.erase(index, 1);
        }
        else {
            return false;
        }
    }
    return true;
}

int main() {

    std::string str;
    std::cin >> str;

    isRightLetters(str) ? std::cout << "YES\n" : std::cout << "NO\n";

    return 0;
}