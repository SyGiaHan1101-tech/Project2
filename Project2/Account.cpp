
#include "Account.h"

using namespace std;

Account::Account() {
    username = "";
    password = "";
}

Account::Account(string username, string password) {
    this->username = username;
    this->password = password;
}

string Account::getUsername() const {
    return username;
}

string Account::getPassword() const {
    return password;
}

void Account::setUsername(string username) {
    this->username = username;
}

void Account::setPassword(string password) {
    this->password = password;
}
