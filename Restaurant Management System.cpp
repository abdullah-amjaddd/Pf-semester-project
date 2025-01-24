#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdexcept>
using namespace std;
const int MAX_USERS = 100;
const int MAX_MENU_ITEMS = 50;
const int MAX_INVENTORY_ITEMS = 50;
struct User {
    string username, password, role;
};
struct MenuItem {
    string name;
    double price;
    string category;
};
struct InventoryItem {
    string itemName;
    int quantity;
};
struct Order {
    string customerName;
    MenuItem items[MAX_MENU_ITEMS];
    int itemCount;
    double totalAmount;
};
class RestaurantManagementSystem {
private:
    User users[MAX_USERS];
    MenuItem menu[MAX_MENU_ITEMS];
    InventoryItem inventory[MAX_INVENTORY_ITEMS];
    Order orders[MAX_USERS];
    int userCount = 0, menuCount = 0, inventoryCount = 0, orderCount = 0;
    string trim(const string& str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}
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
    void loadInventory() {
        ifstream file("inventory.txt");
        if (!file) {
            throw runtime_error("Error: inventory.txt file not found.");
        }
        while (file >> inventory[inventoryCount].itemName >> inventory[inventoryCount].quantity) {
            if (inventoryCount >= MAX_INVENTORY_ITEMS) {
                throw overflow_error("Error: Exceeded maximum inventory item capacity.");
            }
            inventoryCount++;
        }
        file.close();
    }
    double applyTaxAndDiscount(double amount) {
        double tax = amount * 0.1;          // 10% tax
        double discount = (amount > 100) ? amount * 0.05 : 0; // 5% discount for orders above 100
        return amount + tax - discount;
    }
public:
    RestaurantManagementSystem() {
        try {
            loadUsers();
            loadMenu();
            loadInventory();
        } catch (const exception& e) {
    cerr << e.what() << endl;
    exit(1);
    }
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
        cout << menu[i].name << " - $" << fixed << setprecision(2) << menu[i].price
        << " (" << menu[i].category << ")\n";
    }
    }
    void takeOrder(const string& customerName) {
        try {
            Order newOrder;
            newOrder.customerName = customerName;
            newOrder.itemCount = 0;
            newOrder.totalAmount = 0;
            cout << "\nEnter the number of items to order: ";
            int numItems;
            cin >> numItems;
            if (cin.fail() || numItems <= 0) {
                throw invalid_argument("Invalid input! Please enter a positive integer.");
            }
            for (int i = 0; i < numItems; i++) {
                string itemName;
                cout << "Enter item name: ";
                cin >> itemName;
                bool itemFound = false;
                for (int j = 0; j < menuCount; j++) {
                    if (menu[j].name == itemName) {
                    newOrder.items[newOrder.itemCount] = menu[j];
                    newOrder.totalAmount += menu[j].price;
                    newOrder.itemCount++;
                    itemFound = true;
                break;
                }
                }
            if (!itemFound) {
            cout << "Item not found on the menu. Try again.\n";
            i--; // Retry the current item
            }
            }
            if (orderCount >= MAX_USERS) {
            throw overflow_error("Error: Exceeded maximum order capacity.");
            }
        orders[orderCount++] = newOrder;
        cout << "Order placed successfully!\n";
    } catch (const exception& e) {
    cerr << e.what() << endl;
    }
    }
    void displayBill(const string& customerName) {
        try {
            for (int i = 0; i < orderCount; i++) {
            if (orders[i].customerName == customerName) {
    Order& order = orders[i];
    double finalAmount = applyTaxAndDiscount(order.totalAmount);
    cout << "\nBill for " << customerName << ":\n";
    cout << "Items ordered:\n";
    for (int j = 0; j < order.itemCount; j++) {
    cout << "- " << order.items[j].name << ": $" << fixed << setprecision(2)
    << order.items[j].price << "\n";
    }
    cout << "Total (before tax/discount): $" << fixed << setprecision(2) << order.totalAmount << "\n";
    cout << "Final Total (after tax/discount): $" << fixed << setprecision(2) << finalAmount << "\n";
    return;
    }
    }
    throw runtime_error("No orders found for customer: " + customerName);
    } catch (const exception& e) {
    cerr << e.what() << endl;
    }
    }
};
int main() {
try {
RestaurantManagementSystem rms;
string username, password, role;
    cout << "Login\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
if (rms.authenticateUser(username, password, role)) {
cout << "Login successful. Role: " << role << "\n";
if (role == "Admin") {
cout << "Admin role detected.\n";
rms.displayMenu();
} else if (role == "Waitstaff") {
string customerName;
cout << "\nEnter customer name: ";
cin >> customerName;
rms.takeOrder(customerName);
rms.displayBill(customerName);
}
} else {
throw runtime_error("Invalid username or password!");
}
} catch (const exception& e) {
cerr << e.what() << endl;
}
return 0;
}