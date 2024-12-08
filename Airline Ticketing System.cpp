#include<iostream>
#include <string>
//to use the function stringstream(string)
//that converts string to int 
#include <sstream>

//to use function sleep for(seconds(int))
#include <thread>/*requires using c++11 which can be used by adding it
Tools -> Compiler Options...
then write -std=c++11 in the first box -> then click OK
this should allow the compiler to ues c++11*/
#include <chrono>

//Defining the maximum number of flights the customer can have
#define maxFlights 10

using namespace std;
//helps in controling the thread that is currently running.
using namespace this_thread;
//helps for working with duration
using namespace chrono;

//Define the structure of Flight Reservations
struct FlightReservation{
	int number;
	string destination;
};

//Define the structure of Customers
struct Customer{
	string name;
	int id;
	int age;
	string mobileNumber;
	
	int flightCounter;
	FlightReservation flights[maxFlights];
};

//Define the structure of Nodes
struct Node{
	Customer customer;
	Node *left;
	Node *right;
};

//used to delete uneccessary information outputed to screen
void deleteText(int rows, int time){
	/*sleep_for(seconds(time)) is used to sleep the particular 
	thread (single sequential flow of control within a program) for a period of time*/ 
	sleep_for(seconds(time));
	
	//By using ANSI escape codes, we can delete text from the output
	//"\033[nA" is used to move the cursor up n lines
	//"\r" is used to move the cursor to the beginning of the current line
	//"\033[J" is used to clear outputed text from the cursor to the end of the screen 
	cout << "\033[" << rows << "A" << "\r" << "\033[J";
}

//required for several functions
//Check if the node is empty
bool isEmpty(Node *root){
	if(root == NULL)
		return true;
	else
		return false;
};

//checkID duplication
bool IDExist(Node *root, int id){
	
	//If the system is not empty check if there is a customer with the same id entered
	if(!isEmpty(root)){
		Node *curr = root;
		Node *prev = NULL;
		
		while (!isEmpty(curr)) 
		{
			//check for existing customer with the same id entered
			if(curr->customer.id == id){
				cout << "There exist a customer with this ID. Try again!"<< endl;
				cout << "------------------------" << endl;
				//delete some text from the screen
				deleteText(3,4);
				return true;
			}
			/*if this node does not equal the id provided
			keep checking next nodes*/ 
	        prev = curr;
	        if (id < curr->customer.id)
	            curr = curr->left;
	        else
	            curr = curr->right;
	    }
	}
	
	//when the system is empty or
	//there is no customer in the system with that id	
    return false;
}

/*check if the number entered, such as id or age,
is in the correct form and within the acceptable range */
bool isCorrect(int number){
	if(number <= 0)
		return false;
	else
		return true;
}

bool FlightExist(FlightReservation flight, Customer &customer){
    for (int i = 0; i < customer.flightCounter; i++) {
    	
        if (customer.flights[i].number == flight.number) {
        	if(customer.flights[i].destination == flight.destination)
            	return true; // Flight already exists for the customer
        }
        
    }
    return false; // Flight does not exist
}

//input integer number, such as ID, using exception handling
int inputInt(string info){
	
	string input;
	int number;
	
	do{
			//taking the input as string to avoid some errors in input
			cout << "Enter " << info << ": ";
			getline(cin, input);
			
			// Convert string to int
			stringstream(input) >> number;
			
			for(int i = 0; i < input.length(); i++){
				//check if the charachter is not a digit
				if(!isdigit(input.at(i))){
					number = 0;
					break;
				}
			}
			
			if(isCorrect(number)){
				return number;
			}
			
			//if it is not correct display this message
			cout << "Invalid input try again!" << endl;
			cout << "------------------------";
			
			//erase the last 3 lines from screen before asking the user to enter int again
			deleteText(2, 3);
			
	}while(true);//repeat until it is correct
}

//input ID and check for duplication, until the id is unique
int inputID(Node *root){
	int id;
	do
	{
		//call the method inputInt to take a number from the user
		id = inputInt("customer ID");	
	}while(IDExist(root, id));/*check if this id exists
	in the system, repeat until it is unique*/
	
	return id;
}

/*input string of characters and
check if it is containing digit,
or empty input*/
string inputString(string info){
	string input;
	do{
		cout << "Enter " << info << " : ";
		getline(cin, input);
		
		for(int i = 0; i < input.length(); i++){
			/*check if the charachter is
			not a letter or not a space*/
			if((!isalpha(input.at(i)) && input.at(i) != ' ')
			 	|| input.at(0) == ' '){
				//make the string empty
				input.clear();
				break;
			}
		}
		
		if(!input.empty()){
			break;
		}
		
		//message will be displayed for 3 seconds then it will be deleted
		cout << "Invalid " << info << ". Try again!";
		deleteText(1,3);
		
	}while(true);//until the entered string is in the correct form
	
	return input;
}

//the actual implementation of inputting the name
void inputName(Customer &customer, string info){
        customer.name = inputString(info + " Name");
}

//the actual implementation of inputing the age
void inputAge(Customer &customer, string info){
	customer.age = inputInt(info + " Age");
}

/*input string that represent mobile number
and check if it is all digits*/
void inputMobileNumber(Customer &customer, string info){
	string input;
	do{
		cout << "Enter " << info << " Mobile Number: ";
		getline(cin, input);
		
		for(int i = 0; i < input.length(); i++){
			//check if the charachter is not a digit
			if(!isdigit(input.at(i))){
				//make the string empty
				input.clear();
				break;
			}
		}
		
		if(!input.empty()){
			break;
		}
		
		//message will be displayed for 3 seconds then it will be deleted
		cout << "Invalid Mobile Number. Try again!";
		deleteText(1,3);
		
	}while(true);//until the entered string is in the correct form
    
    //assign the value to the customer
    customer.mobileNumber= input;
}

//used to update the name of a specific customer
void updateName(Customer &customer){
            cout << "Old Name: " << customer.name << endl;
            inputName(customer, "New");
            cout << "Name updated successfully.\n";
}

// used to update the age of a specific customer
void updateAge(Customer &customer){
        cout << "Old Age: " << customer.age << endl;
        inputAge(customer, "new");
        cout << "Age updated successfully.\n";
}

// used to update the mobile number of a specific customer
void updateMobileNumber(Customer &customer){
	    cout << "Old Mobile Number: " << customer.mobileNumber << endl;
	    inputMobileNumber(customer, "new");
        cout << "Mobile number updated successfully.\n";
}

void add1Flight(Customer &customer){
	
    if (customer.flightCounter == maxFlights) {
        cout << "Cannot add more flights. Maximum limit reached.";
        return;
    }
    
    FlightReservation newFlight;
	do{
		cout << "_________Flight " << customer.flightCounter + 1 << " information_________" << endl;
		newFlight.number = inputInt("flight number");
		
		newFlight.destination = inputString("Flight destination");
	    
	    if(!FlightExist(newFlight, customer))
	    	break;
	    	
	    cout << "Flight already exists for the customer!";
		deleteText(3, 3);
	    
	}while(FlightExist(newFlight, customer));
    

    customer.flights[customer.flightCounter] = newFlight;
    customer.flightCounter++;

    cout << "Flight " << customer.flightCounter << " is added successfully." << endl;
    cout << "--------------------------------------" << endl;
}

//used for asking the user if he want to add more flights
bool addMore(){
	int choice;
	do{
			cout << "Do you want to add another flight?" << endl;
			choice = inputInt("1 for yes, 2 for no");
			
			//if the choice is outside the range display this message
			if(choice != 1 && choice != 2){
				cout << "Invalid input try again!" << endl;
				cout << "------------------------" << endl;
				
				deleteText(4,3);
				continue;
			}
			
			//used to delet some rows from the output
			deleteText(2,0);
			
			if(choice == 1)
				return true;
			else{
				deleteText(0,0);
				return false;
			}
							
		}while(true);
}

//Used to add more flights to the customer
void addExtraFlights(Customer &customer){
	
	int flightCounter;
	do{
		cout << endl;
		
		if(!addMore())
			break;
			
		flightCounter = customer.flightCounter;
		add1Flight(customer);
		
		//check the flight counter of the customer
		if(flightCounter + 1 > maxFlights){
			deleteText(2,3);
			break;
		}		
	}while(true);
}

/*A list displaying options for updating information
about a specific customer who can be accessed by the ID*/
void updateCustomerInfo(Customer &customer){
	int choice ;
	int updateCounter = 0; 
	int flightCounter;
	
	cout << endl;
	do
	{
		cout << "________Update Menu_________" << endl;
		cout << "1-Update Name" << endl;
		cout << "2-Update Age" << endl;
		cout << "3-Update Moblie Number" << endl;
		cout << "4-Add extra Flight" << endl;
		cout << "5-Stop updating" << endl;
		cout << "----------------------------" << endl;
		choice = inputInt("Your chioce");
		cout<<endl;
		
		//this will change the value of the update counter
		//that is used in the stop editing feature
		if(choice != 5){
			updateCounter = 1;
		}
	
		switch ( choice )
		{
			case 1 :
				updateName(customer) ;
				break ;
			
			case 2 :
				updateAge(customer);	
				break;
			
			case 3 :
		        updateMobileNumber(customer) ;
		        break ;
			
		    case 4:
		    	flightCounter = customer.flightCounter;
		        add1Flight(customer);
		        //check if it will exceed the maximum number of flights
				if(flightCounter + 1 > maxFlights){
					deleteText(9,3);
				}
				else{
					cout << endl;
				}
				continue;	
			
			case 5:
				/*the purpose of using this is just to organize
				 the output before stopping the update*/
				if(updateCounter == 0){
					deleteText(13,0);
				}
				deleteText(9,0);
				return;			  
			
		    default :
		         cout << "Invalid choice. Please try again.";
		         deleteText(9,3);
		         continue;
		}
		cout << "----------------------------" << endl << endl;
	}while(choice != 5);
}

//Initialize a node with customer information
Node *getNewNode(Node *root){
	
	//creat a new node with dynamic allocation
	Node *newCustomer = new Node;
	//Initialize the node left, right pointers to NULL
	newCustomer->left = NULL;
	newCustomer->right = NULL;
	
	//Initialize the customer flight Counter to 0
	newCustomer->customer.flightCounter = 0;
	
	//using input methods to insert information about the Customer
	inputName(newCustomer->customer, "Customer");
	
	newCustomer->customer.id = inputID(root);
	
	inputAge(newCustomer->customer, "Customer");
	
	inputMobileNumber(newCustomer->customer, "Customer");
	
	cout << endl;
	add1Flight(newCustomer->customer);
	addExtraFlights(newCustomer->customer);
	
	return newCustomer;
}

//Add a new customer to the Binary search tree
/*Node *&root is written like this so the pointer is passed 
by reference and can be changed directly*/
void addCustomer(Node *&root){
	//creat a new node and add new customer information
    Node *newNode = getNewNode(root);
    
    //check if it is the first node to be inserted
    if(isEmpty(root)){
    	root = newNode;
    	return;
	}
    
	Node *curr = root; //child node
    Node *prev = NULL;//parent or father node
 
    while (!isEmpty(curr)) //To reach to the right place to insert
	{
        prev = curr;
        if (newNode->customer.id < curr->customer.id)
            curr = curr->left;
        else
            curr = curr->right;
    }
    
    if (newNode->customer.id < prev->customer.id)//set @ left
        prev->left = newNode;
    else//set @ right
        prev->right = newNode;
}

//Search for a customer in the Binary search tree by using id
Customer searchCustomer(Node *root, int id){
	Customer customer;
	//initial value for the id
	customer.id = -1; 
	
	Node *curr = root; //curr :the node we looking to find
	Node *prev = NULL; //prev: father of curr
	
	//search for node
    //until founded or raech null
	while (!isEmpty(curr)) 
	{
		
		if(curr->customer.id == id){//node is founded
			customer = curr->customer;
			break;
		}
		
        prev = curr;
        //move to next nodes
        if (id < curr->customer.id)
            curr = curr->left;
        else
            curr = curr->right;
    }
    
    if (isEmpty(curr)) //raech null: not found
	{ 
        cout << "Customer with id " << id << " is not found in the System.";
        deleteText(12,4);
    }
	
    return customer;
}

void display1Flight(FlightReservation flight) {
    cout << "Flight Number: " << flight.number << endl;
    cout << "Destination: " << flight.destination << endl;
}

void displayCustomerFlights(Customer customer) {
	cout << endl;
    cout << "Flights reserved for customer " << customer.name << ":" << endl;
    cout << endl;
    
    for(int i = 0; i < customer.flightCounter; i++) {
        cout << "__________Flight " << (i + 1) << "__________" << endl;
        display1Flight(customer.flights[i]);
    }
}

//Display 1 customer record
void display1Customer(Customer &customer){
	cout << "Name: " << customer.name << endl;
	cout << "ID: " << customer.id << endl; 
	cout << "Age: " << customer.age << endl;
	cout << "Mobile Number: " << customer.mobileNumber << endl;
	displayCustomerFlights(customer);
	cout << endl;
}

//Display all customers records in the system
//Using inorder traversal
void displayAllCustomers(Node *root , int &order){
    if(isEmpty(root))
        return;
    displayAllCustomers(root->left, order);
    
    cout << "__________Customer " << ++order << " information__________" << endl;
    display1Customer(root->customer);
    
    displayAllCustomers(root->right, order);
}

//Delete a customer with a specific id from the system
void deleteCustomer(Node *&root, int id){
	string name;
    Node *curr = root; //curr :the node we looking to delete
    Node *prev = NULL; //prev: father of curr
  
    while (curr != NULL && curr->customer.id != id){//search for node
    //until founded or raech null
    //move to next
        prev = curr; 
        if (id < curr->customer.id) 
            curr = curr->left; 
        else
            curr = curr->right; 
    }
	 
    if (curr == NULL){ //raech null: not found
        cout << "Customer with id " << id << " is not found in the System.";
        deleteText(12,4);
        return; //exit
    }
	
	//if founded curr will be the node we looking to delete
	name = curr->customer.name;
	cout << "Customer " << name << " is deleted successfully!" << endl << endl;
    
    //Node contains 1 or 0 child
    if (curr->left == NULL || curr->right == NULL)
	{ 
		//used to point to child node, and initialize with null
        Node* newCurr = NULL;
        
        if (curr->left == NULL) //to set the pos for newCurr
            newCurr = curr->right; 
        else
            newCurr = curr->left; 
  		
  		// if we will delete the root and may has one child
        if (prev == NULL){
        	root = newCurr;
        	return;
		}
		
        if (prev->left == curr) 
            prev->left = newCurr; //re connect from left
        else
            prev->right = newCurr; //re connect from right
  		
        delete curr;
    } 
    
    //if the node we looking to delete has 2 child, apply the successor 
    //the successor: The smallest value that greater than it
    else{ 
        Node* succParent = NULL; //the successor parent like new prev
        Node* succ; //the successor node like new curr
  
        succ = curr->right; //start from right to search the successor
        
        //search the successor
        while (succ->left != NULL){ 
            succParent = succ; //prev=curr
            succ = succ->left; //move curr to new pos
        } 
        
        //change value with successor
		curr->customer = succ->customer;
		
		//if node we looking to delete isn't the parent for successor
        if (succParent != NULL)
            //connect to right because no nods connected to the left
       		succParent->left = succ->right; 
       		
	    // if node we looking to delete is the parent for successor
		else
			//connect to right because no nods connected to the left
            curr->right = succ->right;
        delete succ;
    }
}

//Display masseage when the system is empty
void emptySystem(){
	cout << "There is no customer in the system!";
	deleteText(11,3);	
}

//Display the Menu list
void displayMenu(){
	cout << " _________________Main Menu_________________" << endl;
	cout << "|1. Enter New Customer                      |" << endl;
	cout << "|2. Update Existing Customer Information    |" << endl;
	cout << "|3. Delete Customer record                  |" << endl;
	cout << "|4. Display All Customer Information        |" << endl;
	cout << "|5. Display All Flight Reservations for     |" << endl;
	cout << "|   specific Customer                       |" << endl;
	cout << "|6. Exit                                    |" << endl;
	cout << "|___________________________________________|" << endl;
}

int main()
{
	//creat the first node and initialize it to null
    Node *root = NULL;
    int choice;
    int order; //the index of customers in the Binary Search Tree
    int id;
	Customer customer;

    do {
        displayMenu();
        choice = inputInt("Your choice");
        cout << endl;

        switch(choice) {
			case 1:
				addCustomer(root);
				cout << endl;
            	break;
            
            case 2:
            	//if the system is empty don't search for a customer
				if(isEmpty(root)){
	   				emptySystem();
	   				continue;
				} 
				
	   			id = inputInt("Customer ID to update");
	   			customer = searchCustomer(root, id);
	   				   			
	   			if(isCorrect(customer.id)){
	   				updateCustomerInfo(customer);
	   			}
	   			break;
            
            case 3:
            	//if the system is empty don't search for a customer
            	if(isEmpty(root)){
	   				emptySystem();
	   				continue;
				} 
				
	   			id = inputInt("Customer ID to delete");
            	deleteCustomer(root, id);
            	break;
            
            case 4: 
            	//if the system is empty don't call display 
            	if(isEmpty(root)){
	   				emptySystem();
	   				continue;
				} 
				
        		order = 0;
        		displayAllCustomers(root, order);
        		deleteText(0, 0);
        		cout << "--------------------------------------" << endl;
        		cout << endl;
            	break;
            	
            case 5:
            	//if the system is empty don't call display
            	if(isEmpty(root)){
	   				emptySystem();
	   				continue;
				}
				
				id = inputInt("Customer ID to display his flights information");
	   			customer = searchCustomer(root, id);
	   			
	   			//check if the searched customer actually exists
	   			//if the id is not found the customer id will be -1
	   			if(isCorrect(customer.id)){
	   				displayCustomerFlights(customer);
		   			cout << "----------------------------" << endl;
		   			cout << endl;
				}
				break;
	   			
                
            case 6:
                cout << "Exiting the system .. Thank you.";
                break;
                
            default://if the choice entered is not in the list
                cout << "Invalid choice ,Please try again.";
                deleteText(11, 3);
        }
        
    } while (choice != 6);
    
    return 0;
}
