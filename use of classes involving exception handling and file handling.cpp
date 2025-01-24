#include<iostream>
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
// Menu Class
class Menu {
public:
static void viewMenu() {
ifstream file("menu.txt");
if (!file.is_open()) {
throw runtime_error("Failed to open menu.txt");
}
cout << "Menu Items:\n";
string line;
while (getline(file, line)) {
cout << line << endl;
}
file.close();
}
static void addMenuItem(const string& name, double price, const string& category) {
ofstream file("menu.txt", ios::app);
if (!file.is_open()) {
throw runtime_error("Failed to open menu.txt");
}
file << name << "," << price << "," << category << endl;
file.close();
cout << "Menu item added successfully.\n";
}
static void removeMenuItem(const string& name) {
ifstream file("menu.txt");
if (!file.is_open()) {
throw runtime_error("Failed to open menu.txt");
}
ofstream tempFile("temp.txt");
if (!tempFile.is_open()) {
throw runtime_error("Failed to open temp.txt");
}
string line;
bool found = false;
while (getline(file, line)) {
size_t firstComma = line.find(',');
if (firstComma == string::npos) continue;
string itemName = line.substr(0, firstComma);
if (itemName != name) {
tempFile << line << endl;
} else {
found = true;
}
}
file.close();
tempFile.close();
if (found) {
remove("menu.txt");
rename("temp.txt", "menu.txt");
cout << "Item removed successfully.\n";
} else {
remove("temp.txt");
cout << "Item not found in the menu.\n";
}
}
};
int main() {



return 0;
}