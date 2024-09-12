#include <iostream>
using namespace std;


class Products {
private:
    float productPrice;
    string productName;
    string productID;
public:
	Products(float p = 0, string name = "", string ID = "") {
		productPrice = p;
		productName = name;
		productID = ID;
	}

    float getProductPrice() {
        return productPrice;
    }
    string getProductName() {
        return productName;
    }
    string getProductID() {
        return productID;
    }
};

class ShoppingCart {    
	public:
		Products cartItems[20];
		int quantities[20]; 
		int itemCount = 0;
		int total[20];
		int totalamount;
		
    	void addItem(const Products& product, int quantity) {
        	if (itemCount < 20) { 
            	cartItems[itemCount] = product;
            	quantities[itemCount] = quantity;
            	total[itemCount] = cartItems[itemCount].getProductPrice() * quantities[itemCount];
            	totalamount += total[itemCount];
            	itemCount++;
            	cout << "Product added successfully!" << endl;
        	} 
			else {
            cout << "Your Cart is full. Please proceed to checkout." << endl;
        	}
    	}
    
    	void viewCart() {
        	if (itemCount == 0) {
            	cout << "No product has been place" << endl;
        	} 
			else {
            cout << "\n ID\tName\tQuantity\tPrice" << endl;
            cout << "-------------------------------------------" << endl;
            for (int i = 0; i < itemCount; i++) {
                cout << cartItems[i].getProductID() << "\t "
                     << cartItems[i].getProductName() << "\t "
                     << quantities[i] << "\t\t "
                     << total[i] << endl;
            }
            cout << "-------------------------------------------" << endl;
            cout << "Total Amount: " << totalamount << endl << endl;
        }
    }

    int getItemCount() {
        return itemCount;
    }
    
};

class Order {
private:
    Products orderItems[10];  
    int quantities[10];       
    int itemCount;           
    float totalAmount;
    int orderID;

public:
    Order(int id, ShoppingCart& cart) : orderID(id), totalAmount(0), itemCount(cart.getItemCount()) {
        for (int i = 0; i < itemCount; i++) {
            orderItems[i] = cart.cartItems[i];  
            quantities[i] = cart.quantities[i]; 
            totalAmount += orderItems[i].getProductPrice() * quantities[i];
        }
    }

    void displayOrderDetails() {
        cout << "\nOrder ID: " << orderID + 1 << endl;
        cout << "Total Amount: " << totalAmount << endl ;
        cout << "Order Details:" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << " Product ID\t Name\t Quantity\tPrice " << endl;
        cout << "-----------------------------------------------" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout  << orderItems[i].getProductID() 
			<< "\t\t" << orderItems[i].getProductName() 
			<< "\t" << quantities[i]
			<< "\t\t" << orderItems[i].getProductPrice() << endl;
        }
        cout << "-----------------------------------------------" << endl << endl << endl;
    }
};

void viewProducts(Products productList[], int productCount) {
    cout << "========================" << endl;
	cout << "\tProducts\t" << endl;
    cout << "========================" << endl;
    cout << "ID \t Name \t Price" << endl;
    for (int i = 0; i < productCount; i++) {
        cout << productList[i].getProductID() << "\t" << productList[i].getProductName() << "\t " << productList[i].getProductPrice() << endl;
    }
    cout << "========================" << endl;
}


int main() {
    ShoppingCart cart;
    Order* orderHistory[20]; 
    int orderCounter = 0;
    int choice;
	bool Condition = true;
	Products productList[5] = {
		Products(20000, "Laptop", "AB0"),
        Products(10000, "Table", "PS1"),
        Products(5000, "Chair", "DG2"),
        Products(400, "Mirror", "NS3"),
        Products(50, "Marker", "MQ4")
    };
	
    while (Condition) {
    	cout << "=========================";
        cout << "\n|\t---Menu---\t" << endl;
        cout << "|   [1]-View Products" << endl;
        cout << "|   [2]-View Cart" << endl;
        cout << "|   [3]-View Orders" << endl;
        cout << "|   [4]-Exit" << endl;
        cout << "|Input Choice: ";
        
        while (!(cin >> choice)|| choice < 1){
            cin.clear();
            cin.ignore();
            cout << "|Please Enter Positive Number: ";
		} cin.ignore();
        cout << "=========================" << endl; 
        system ("pause");
        system ("cls");
        
        switch (choice) {
        case 1:{
            viewProducts(productList, 5);
            string productID;
            int quantity;
            char addMore;

            do {
            	bool productFound = false;
                while(!productFound){
                	cout << "Enter the Product ID to add to cart: ";
                	getline(cin, productID); 
					for (int i = 0; i < 5; i++) {
                   		if (productList[i].getProductID() == productID) {
                   			cout << "Enter the Quantity: ";
                			while (!(cin >> quantity)|| quantity < 1){
                				cin.clear();
                				cin.ignore();
                				cout << "Please Enter Positive Number: ";
							} 
                			cart.addItem(productList[i], quantity);
                		
                   			productFound = true;
                   		break;
                   		}	
					}
            		if (!productFound){
            			cout << "ID Cannot be found: Invalid ID" << endl;
					}
				}

                cout << "Do you want to add another product? (Y/N): ";
                cin >> addMore;
                cin.ignore();  // Clear the newline character

            } while (tolower(addMore) == 'y');
            system ("cls");
        break;
        }
        case 2: {
            cart.viewCart();
            char checkout;
            do{
            	if (cart.itemCount != 0) {
                	cout << "Do you want to checkout? (Y/N): ";
                	cin >> checkout;
                	cin.ignore();

                	if (tolower(checkout) == 'y') {
                    	if (orderCounter < 20) {
                        	orderHistory[orderCounter++] = new Order(orderCounter, cart);
                        	cout << "You have successfully checked out the products!" << endl;
                    		cart.itemCount =0;
                    		cart.totalamount = 0;
                    	} 
						else {
                        	cout << "Order limit reached!" << endl;
                    	}
                	}
            	}
            	if (!(tolower(checkout)== 'y' ||tolower(checkout)== 'n')){
            		cout << "Error: Choose Y or N"<< endl;
				}
			}while (!(tolower(checkout)== 'y' ||tolower(checkout)== 'n'));
	
        system ("pause");
        system ("cls");
        break;
    	}
        case 3: {
            if (orderCounter == 0) {
                cout << "No orders have been placed yet." << endl << endl;
            } else {
                for (int i = 0; i < orderCounter; i++) {
                    orderHistory[i]->displayOrderDetails();
                }
            }
            system ("pause");
            system ("cls");
        break;
        }
        case 4:{
        	cout << "Exiting..." << endl;
            Condition = false;
			break;
		}
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
