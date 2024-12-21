#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
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
            cerr << "Error: users.txt file not found.\n";
            exit(1);
        }
        while (file >> users[userCount].username >> users[userCount].password >> users[userCount].role) {
            userCount++;
        }
        file.close();
    }
    void loadMenu() {
        ifstream file("menu.txt");
        if (!file) {
            cerr << "Error: menu.txt file not found.\n";
            exit(1);
        }
        while (file >> menu[menuCount].name >> menu[menuCount].price >> menu[menuCount].category) {
            menuCount++;
        }
        file.close();
    }
    void loadInventory() {
        ifstream file("inventory.txt");
        if (!file) {
            cerr << "Error: inventory.txt file not found.\n";
            exit(1);
        }
        while (file >> inventory[inventoryCount].itemName >> inventory[inventoryCount].quantity) {
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
        loadUsers();
        loadMenu();
        loadInventory();
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
        Order newOrder;
        newOrder.customerName = customerName;
        newOrder.itemCount = 0;
        newOrder.totalAmount = 0;
        cout << "\nEnter the number of items to order: ";
        int numItems;
        cin >> numItems;
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
        orders[orderCount++] = newOrder;
        cout << "Order placed successfully!\n";
}
void displayBill(const string& customerName) {
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
        cout << "No orders found for customer: " << customerName << "\n";
}
};
int main() {
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
cout << "Invalid username or password!\n";
}
return 0;
}