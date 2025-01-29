#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdexcept>
using namespace std;
const int MAX_USERS = 10;
const int MAX_MENU_ITEMS = 15;
// Structures for Users and Menu Items
struct User {
    string username, password, role;
};
struct MenuItem {
    string name;
    double price;
    string category;
};
// Restaurant Management Class
class RestaurantManagementSystem {
private:
User users[MAX_USERS];
MenuItem menu[MAX_MENU_ITEMS];
int userCount = 0, menuCount = 0;
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
public:
RestaurantManagementSystem() {
try {
loadUsers();
loadMenu();
} catch (const exception& e) {
cerr << e.what() << endl;
exit(1);
}
}
void registerUser() {
if (userCount >= MAX_USERS) {
cout << "User limit reached. Cannot register more users.\n";
return;
}
string newUsername, newPassword, newRole;
cout << "Enter new username: ";
cin >> newUsername;
cout << "Enter new password: ";
cin >> newPassword;
cout << "Enter role (Admin/Waitstaff): ";
cin >> newRole;
for (int i = 0; i < userCount; i++) {
if (users[i].username == newUsername) {
cout << "Username already exists! Try again.\n";
return;
}
}
ofstream file("users.txt", ios::app);
if (!file) {
cout << "Error opening users file.\n";
return;
}
file << newUsername << " " << newPassword << " " << newRole << endl;
file.close();
users[userCount].username = newUsername;
users[userCount].password = newPassword;
users[userCount].role = newRole;
userCount++;
cout << "Registration successful! You can now log in.\n";
}
bool authenticateUser(const string& username, const string& password, string& role) {
for (int i = 0; i < userCount; i++) {
if (users[i].username == username && users[i].password == password) {
role = users[i].role;
return true;
}
}
return false;
}
void displayMenu() {
cout << "\nMenu:\n";
for (int i = 0; i < menuCount; i++) {
cout << "- " << menu[i].name << ": $" << fixed << setprecision(2) << menu[i].price << " (" << menu[i].category << ")\n";
}
}
void takeOrder() {
cout << "\nPlace an Order\n";
int numItems;
double totalAmount = 0;
cout << "Enter number of items to order: ";
cin >> numItems;
if (cin.fail() || numItems <= 0) {
cout << "Invalid input. Please enter a positive integer.\n";
return;
}
for (int i = 0; i < numItems; i++) {
string itemName;
cout << "Enter item name: ";
cin >> itemName;
bool itemFound = false;
for (int j = 0; j < menuCount; j++) {
if (menu[j].name == itemName) {
totalAmount += menu[j].price;
itemFound = true;
break;
}
}
if (!itemFound) {
cout << "Item not found on the menu. Try again.\n";
i--;
}
}
double tax = totalAmount * 0.1;
double discount = (totalAmount > 100) ? totalAmount * 0.05 : 0;
double finalAmount = totalAmount + tax - discount;
cout << "\nOrder Summary:\n";
cout << "Total (before tax/discount): $" << fixed << setprecision(2) << totalAmount << "\n";
cout << "Tax: $" << tax << "\n";
cout << "Discount: $" << discount << "\n";
cout << "Final Total: $" << finalAmount << "\n";
}
};
int main() {
    try {
RestaurantManagementSystem rms;
string username, password, role;
int loginChoice;
cout << "Welcome to the Restaurant Management System\n";
do {
cout << "1. Register\n2. Login\n3. Exit\nChoose an option: ";
cin >> loginChoice;
if (loginChoice == 1) {
rms.registerUser();
} else if (loginChoice == 2) {
cout << "Username: ";
cin >> username;
cout << "Password: ";
cin >> password;
if (rms.authenticateUser(username, password, role)) {
cout << "Login successful! Role: " << role << "\n";
if (role == "Admin") {
int choice;
do {
cout << "\nAdmin Menu:\n1. View Menu\n2. Logout\nChoose an option: ";
cin >> choice;
if (choice == 1) {
rms.displayMenu();
}
} while (choice != 2);
} else if (role == "Waitstaff") {
int choice;
do {
cout << "\nWaitstaff Menu:\n1. View Menu\n2. Take Order\n3. Logout\nChoose an option: ";
cin >> choice;
if (choice == 1) {
rms.displayMenu();
} else if (choice == 2) {
rms.takeOrder();
}
} while (choice != 3);
}
} else {
cout << "Invalid username or password!\n";
}
}
} while (loginChoice != 3);
} catch (const exception& e) {
cerr << "Error: " << e.what() << endl;
}
return 0;
}