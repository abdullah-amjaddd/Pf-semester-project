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