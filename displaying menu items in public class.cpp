#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdexcept>
using namespace std;
const int MAX_USERS = 100;
const int MAX_MENU_ITEMS = 50;
// Structures for Users and Menu Items
struct User {
string username, password, role;
};
struct MenuItem {
    string name;
    double price;
    string category;
};
// Restaurant Management Classclass RestaurantManagementSystem s
private:
User users[MAX_USERS];
MenuItem menu[MAX_MENU_ITEMS];
int userCount = 0, menuCount = 0;
// Helper function to load users from file
void loadUsers() {
ifstream file("users.txt");
if (!file) {
throw runtime_error("Error: users.txt file not found.");
}
while (file >> users[userCount].username >> users[userCount].password >> users[userCount].role) {
if (userCount >= MAX_USERS) {
throw overflow_error("Error: Exceeded maximum user capacity.");
}
userCount++;
}
file.close();
}
// Helper function to load menu from file
void loadMenu() {
ifstream file("menu.txt");
if (!file) {
throw runtime_error("Error: menu.txt file not found.");
}
while (file >> menu[menuCount].name >> menu[menuCount].price >> menu[menuCount].category) {
if (menuCount >= MAX_MENU_ITEMS) {
throw overflow_error("Error: Exceeded maximum menu item capacity.");
}
menuCount++;
}
file.close();
}
public://public class involving exception handling
RestaurantManagementSystem() {
try {
loadUsers();
loadMenu();
} catch (const exception& e) {
cerr << e.what() << endl;
exit(1);
}
}
// User Authentication
bool authenticateUser(const string& username, const string& password, string& role) {
for (int i = 0; i < userCount; i++) {
if (users[i].username == username && users[i].password == password) {
role = users[i].role;
return true;
}
}
return false;
}
// Display Menu Items
void displayMenu() {
cout << "\nMenu:\n";
for (int i = 0; i < menuCount; i++) {
cout << "- " << menu[i].name << ": $" << fixed << setprecision(2) << menu[i].price<< " (" << menu[i].category << ")\n";
}
}