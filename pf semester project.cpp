#include<iostream>
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
using namespace std;
// User Class
class User {
public:
static bool login(const string& uname, const string& pass, string& role) {
ifstream file("users.txt");
if (!file.is_open()) {
throw runtime_error("Failed to open users.txt");
}
string line;
while (getline(file, line)) {
size_t firstComma = line.find(',');
size_t secondComma = line.find(',', firstComma + 1);
if (firstComma == string::npos || secondComma == string::npos) {
continue; // Skip invalid lines
}
string username = line.substr(0, firstComma);
string password = line.substr(firstComma + 1, secondComma - firstComma - 1);
string userRole = line.substr(secondComma + 1);
if (uname == username && pass == password) {
role = userRole;
file.close();
return true;
}
}
file.close();
return false;
    }
};
int main() {



return 0;
}