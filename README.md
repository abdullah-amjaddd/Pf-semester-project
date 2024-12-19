pf semester project
Description of the project and what it does
1. User Authentication
Users can log in with specific credentials and have different roles:
Admin: Can manage the menu, view orders, and manage inventory.
Waitstaff: Can place and update customer orders and manage billing.
Credentials are verified against a file (users.txt) to ensure security and persistence.
2. Menu Management (Admin only)
Admin can add new menu items, remove existing items, and view the current menu.
Each menu item contains a name, price, and category (e.g., "Main Course", "Drink").
Menu items are saved to and loaded from menu.txt.
3. Order Management (Waitstaff only)
Waitstaff can create and modify customer orders.
Orders can have multiple items, and the status of each order is updated (e.g., "In Progress", "Completed").
Order data is saved in orders.txt.
4. Billing and Payment (Admin/Waitstaff)
Once the order is placed, a bill is generated with the total amount, tax, and discounts applied.
Waitstaff or Admin can view and process payments.
Billing information is displayed directly on the console, including taxes and discounts.
Bill data is handled dynamically and could be saved to a file if extended.
5. Inventory Management (Admin/Waitstaff)
Track the quantity of items available in the restaurant's inventory (e.g., ingredients).
Alert when stock levels are low (e.g., less than 5 items remaining).
Inventory data is saved and loaded from inventory.txt.
6. File Handling
All user data, menu items, orders, and inventory are saved in text files to ensure persistence.
The system reads and writes to the following files:
users.txt: Stores user credentials (username, password, role).
menu.txt: Stores the list of menu items.
orders.txt: Stores customer orders and their statuses.
inventory.txt: Stores inventory items and their quantities.
