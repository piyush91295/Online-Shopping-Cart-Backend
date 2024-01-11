#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// Product class representing a product with ID, name, and price
class Product {
public:
    int id;             // Unique identifier for the product
    string name;        // Name of the product
    int price;          // Price of the product

    //Default Constructor
    Product(){}
    
    // Constructor to initialize product properties
    Product(int u_id, string u_name, int u_price) : id(u_id), name(u_name), price(u_price) {}

    // Method to get a formatted display name of the product
    string getDisplayName() const {
        return name + " : Rs " + to_string(price) + "\n";
    }

    // Method to get the short name (first character) of the product
    string getShortName() const {
        return name.substr(0, 1);
    }
};



// Item class representing a product associated with a quantity
class Item {
public:
    Product product;    // Product associated with this item
    int quantity;       // Quantity of this item in the cart

    // Default constructor initializing item with default values
    //Item() : product(Product(0, "", 0)), quantity(0) {}
    Item(){}

    // Constructor to initialize item properties with given product and quantity
    Item(const Product& p, int q) : product(p), quantity(q) {}

    // Method to calculate the price of the item(s)
    int getItemPrice() const {
        return quantity * product.price;
    }

    // Method to get a string representation of the item
    string getItemInfo() const {
        return to_string(quantity) + " x " + product.name + " Rs. " + to_string(getItemPrice()) + "\n";
    }
};



// Cart class representing a cart with items stored in an unordered map
class Cart {
public:
    unordered_map<int, Item> items; // Map to store items in the cart (mapped by product ID)

    // Method to add a product to the cart
    void addProduct(const Product& product) {
        if (items.count(product.id) == 0) {
            Item newItem(product, 1);   // Create a new item with quantity 1
            items[product.id] = newItem; // Add the new item to the cart
        }
        else {
            items[product.id].quantity += 1; // Increment the quantity of an existing item
        }
    }

    // Method to calculate the total price of all items in the cart
    int getTotal() const {
        int total = 0;
        for (const auto& itemPair : items) {
            const auto& item = itemPair.second;
            total += item.getItemPrice();   // Accumulate prices of all items in the cart
        }
        return total;
    }

    // Method to generate a string representation of the cart
    string viewCart() const {
        if (items.empty()) {
            return "Cart is empty";
        }

        string itemizedList;
        int cartTotal = getTotal(); // Get the total cart value

        for (const auto& itemPair : items) {
            const auto& item = itemPair.second;
            itemizedList.append(item.getItemInfo()); // Generate information for each item in the cart
        }

        return itemizedList + "\nTotal Amount : Rs. " + to_string(cartTotal) + '\n';
    }

    // Method to check if the cart is empty
    bool isEmpty() const {
        return items.empty();
    }
};



// Function to display available products
void displayProducts(const vector<Product>& products) {
    cout << "Available Products " << endl;
    for (const Product& product : products) {
        cout << product.getShortName() << ": " << product.getDisplayName();
    }
}


// Function to add a product to the cart
void addProductToCart(Cart& cart, const vector<Product>& allProducts) {
    displayProducts(allProducts);

    cout << "Enter the short name of the product you want to add: ";
    string choice;
    cin >> choice;

    bool productFound = false;
    for (const Product& product : allProducts) {
        if (product.getShortName() == choice) {
            cart.addProduct(product);
            cout << "Added to the Cart: " << product.getDisplayName() << endl;
            productFound = true;
            break;
        }
    }

    if (!productFound) {
        cout << "Product not found!" << endl;
    }
}


// Function to view the cart
void viewCart(const Cart& cart) {
    cout << "------------------" << endl;
    cout << cart.viewCart();
    cout << "------------------" << endl;
}


// Function to perform the checkout process
void checkout(Cart& cart) {
    if (cart.isEmpty()) {
        cout << "Cart is empty. Add items before checking out." << endl;
        
    } 
    else {
        cout << "Total Amount: Rs. " << cart.getTotal() << endl;
        cout << "Pay in Cash: ";
        int paid;
        cin >> paid;

        if (paid >= cart.getTotal()) {
            cout << "Change: Rs. " << paid - cart.getTotal() << endl;
            cout << "Thank you for shopping!" << endl;
            
        } 
        else {
            cout << "Not enough cash. Please pay the full amount." << endl;
            
        }
    }
}



// Main function for user interaction
int main() {
    // Initialization of available Products
    vector<Product> allProducts = {
        Product(1, "Apple", 26),
        Product(2, "Mango", 16),
        Product(3, "Guava", 36),
        Product(4, "Banana", 56),
        Product(5, "Strawberry", 29),
        Product(6, "Pineapple", 20),
    };

    Cart cart;

    // Continuous loop for user interaction until the user decides to quit
    while (true) {
        cout << "Select an action - (a)dd item, (v)iew cart, (c)heckout, (q)uit" << endl;
        char action;
        cin >> action;

        switch (action) {
            case 'a':
                addProductToCart(cart, allProducts);
                break;
            case 'v':
                viewCart(cart);
                break;
            case 'c':
                checkout(cart);
                return 0; // Exiting after checkout
            case 'q':
                cout << "Goodbye!" << endl;
                return 0; // Exiting
            default:
                cout << "Invalid action. Please choose a valid action (a, v, c, q)." << endl;
                break;
        }
    }

    return 0;
}
