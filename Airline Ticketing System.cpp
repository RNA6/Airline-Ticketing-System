#include<iostream>
#include <string>
#include <sstream>
//to use function sleep for(seconds(int))
#include <thread>
#include <chrono>
#define maxFlights 10
using namespace std;
using namespace this_thread;
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
			// if this node does not contain 
	        prev = curr;
	        if (id < curr->customer.id)
	            curr = curr->left;
	        else
	            curr = curr->right;
	    }
	}
		
    return false;
}

//check if the number(id or age) is within the acceptable range
bool isCorrect(int number){
	if(number <= 0)
		return false;
	else
		return true;
}
// Function to check if a flight already exists in the customer's list

bool FlightExist(FlightReservation flight, Customer &customer){
    for (int i = 0; i < customer.flightCounter; i++) {
    	
        if (customer.flights[i].number == flight.number) {
        	if(customer.flights[i].destination == flight.destination)
            	return true; // Flight already exists for the customer
		// Flight already exists for the customer
        }
        
    }
    return false; // Flight does not exist
	// Flight does not exist
}

//input integer number, such as ID, using exception handling
int inputInt(string info){
	string input;
	int number;
	
	do{
			cout << "Enter " << info << ": ";
			getline(cin, input);
			
			stringstream(input) >> number;
						
			if(isCorrect(number)){
				return number;
			}
	
			cout << "Invalid input try again!" << endl;
			cout << "------------------------";
			
			//erase the last 3 lines from screen before asking the user to enter int again
			deleteText(2, 3);
			
	}while(true);
}

//input ID and check for duplication, until the id is unique
int inputID(Node *root){
	int id;
	do
	{
		id = inputInt("customer ID");	
	}while(IDExist(root, id));
	
	return id;
}
//input string of characters and check if it is containing digit , or empty input
string inputString(string info){
	string input;
	do{
		cout << "Enter " << info << " : ";
		getline(cin, input);
		
		for(int i = 0; i < input.length(); i++){
			if(!isalpha(input.at(i)) && input.at(i) != ' '){
				input.clear();
				break;
			}
		}
		
		if(!input.empty()){
			break;
		}
		
		cout << "Invalid " << info << ". Try again!";
		deleteText(1,3);
		
	}while(true);
	
	return input;
}

void inputName(Customer &customer, string info){
        customer.name = inputString(info + " Name");
}

void inputAge(Customer &customer, string info){
	customer.age = inputInt(info + " Age");
}
//input string that represent mobile number and check if it is all digits
void inputMobileNumber(Customer &customer, string info){
	string input;
	do{
		cout << "Enter " << info << " Mobile Number: ";
		getline(cin, input);
		
		for(int i = 0; i < input.length(); i++){
			if(!isdigit(input.at(i))){
				input.clear();
				break;
			}
		}
		
		if(!input.empty()){
			break;
		}
		cout << "Invalid Mobile Number. Try again!";
		deleteText(1,3);
		
	}while(true);
    
    customer.mobileNumber= input;
}
// used to update the name of a specific customer
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
// Function to add a single flight to the customer's list
void add1Flight(Customer &customer){
	
    if (customer.flightCounter == maxFlights) {
        cout << "Cannot add more flights. Maximum limit reached.";
	    // Check if the max flights limit is reached
        return;
    }
    
    FlightReservation newFlight;
	do{
		cout << "_________Flight " << customer.flightCounter + 1 << " information_________" << endl;
		newFlight.number = inputInt("flight number");
		// Input flight number
		newFlight.destination = inputString("Flight destination");
	    // Input flight destination
	    if(!FlightExist(newFlight, customer))
		    // Check if the flight does not already exist
	    	break;
	    	
	    cout << "Flight already exists for the customer!";
		// Print message if flight is duplicate
		deleteText(3, 3);
		// Clear redundant messages from the screen
	    
	}while(FlightExist(newFlight, customer));
    

    customer.flights[customer.flightCounter] = newFlight;
	// Add the flight to the customer's list
    customer.flightCounter++;
	// Increment the flight counter

    cout << "Flight " << customer.flightCounter << " is added successfully." << endl;
	// Confirm addition
    cout << "--------------------------------------" << endl;
}

bool addMore(){
	int choice;
	do{
			cout << "Do you want to add another flight?" << endl;
			choice = inputInt("1 for yes, 2 for no");
			
			if(choice != 1 && choice != 2){
				cout << "Invalid input try again!" << endl;
				cout << "------------------------" << endl;
				
				deleteText(4,3);
				continue;
			}
			
			deleteText(2,0);
			
			if(choice == 1)
				return true;
			else{
				deleteText(0,0);
				return false;
			}
				
							
		}while(true);
}

void addExtraFlights(Customer &customer){
	
	int flightCounter;
	do{
		cout << endl;
		
		if(!addMore())
			break;
			
		flightCounter = customer.flightCounter;
		add1Flight(customer);
		
		if(flightCounter + 1 > maxFlights){
			deleteText(2,3);
			break;
		}		
	}while(true);
}
// A list displaying options for updating information about a specific customer who can be accessed by the ID
void updateCustomerInfo(Customer &customer){
	int choice ; 
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
				if(flightCounter + 1 > maxFlights){
					deleteText(9,3);
				}
				else{
					cout << endl;
				}
				continue;	
			
			case 5 :
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
void addCustomer(Node *&root){
    Node *newNode = getNewNode(root);
    
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
	customer.id = -1; 
	
	Node *curr = root;
	Node *prev = NULL;
	
	while (!isEmpty(curr)) 
	{
		if(curr->customer.id == id){
			customer = curr->customer;
			break;
		}
		
        prev = curr;
        if (id < curr->customer.id)
            curr = curr->left;
        else
            curr = curr->right;
    }
    
    if (isEmpty(curr)) //raech null: not found
	{ 
        cout << "Customer with id " << id << " is not found in the System.";
        deleteText(11,4);
    }
	
    return customer;
}
// Function to display details of a single flight
void display1Flight(FlightReservation flight) {
    cout << "Flight Number: " << flight.number << endl;
	// Print the flight number
    cout << "Destination: " << flight.destination << endl;
	// Print the flight destination
}
// Function to display all flights reserved for a customer
void displayCustomerFlights(Customer customer) {
	cout << endl;
    cout << "Flights reserved for customer " << customer.name << ":" << endl;
	// Print customer's name
    cout << endl;
    
    for(int i = 0; i < customer.flightCounter; i++) {
        cout << "__________Flight " << (i + 1) << "__________" << endl;
        display1Flight(customer.flights[i]);
	    // Call the function to display individual flight details
    }
}

//display 1 customer record
void display1Customer(Customer &customer){
	cout << "Name: " << customer.name << endl;
	cout << "ID: " << customer.id << endl; 
	cout << "Age: " << customer.age << endl;
	cout << "Mobile Number: " << customer.mobileNumber << endl;
	displayCustomerFlights(customer);
	cout << endl;
}

void displayAllCustomers(Node *root , int &order){
    if(isEmpty(root))
        return;
    displayAllCustomers(root->left, order);
    
    cout << "__________Customer " << order++ << " information__________" << endl;
    display1Customer(root->customer);
    
    displayAllCustomers(root->right, order);
}

void deleteCustomer(Node *&root, int id){
	string name;
    Node *curr = root; //curr :the node we looking to delete
    Node *prev = NULL; //prev: father of curr
  
    while (curr != NULL && curr->customer.id != id){
        prev = curr; 
        if (id < curr->customer.id) 
            curr = curr->left; 
        else
            curr = curr->right; 
    }
	 
    if (curr == NULL){ 
        cout << "Customer with id " << id << " is not found in the System.";
        deleteText(12,4);
        return;
    }
	
	name = curr->customer.name;
	cout << "Customer " << name << " is deleted successfully!" << endl << endl;
    
    if (curr->left == NULL || curr->right == NULL)
	{ 
        Node* newCurr = NULL;
       
        if (curr->left == NULL) 
            newCurr = curr->right; 
        else
            newCurr = curr->left; 
  
        if (prev == NULL){
        	root = newCurr;
        	return;
		}
		
        if (prev->left == curr) 
            prev->left = newCurr;
        else
            prev->right = newCurr;
  		
        delete curr;
    } 
    
    else{ 
        Node* succParent = NULL; 
        Node* succ;
  
        succ = curr->right;
        
        while (succ->left != NULL){ 
            succParent = succ;
            succ = succ->left;
        } 
        
		curr->customer = succ->customer;
		
        if (succParent != NULL)
            succParent->left = succ->right; 
        else
            curr->right = succ->right;
            
        delete succ;
    }
}

void emptySystem(){
	cout << "There is no customer in the system!";
	deleteText(11,3);	
}

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
    Node *root = NULL;
    int choice;
    int order;
    int id ;
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
            	if(isEmpty(root)){
	   				emptySystem();
	   				continue;
				} 
				
	   			id = inputInt("Customer ID to delete");
            	deleteCustomer(root, id);
            	break;
            
            case 4: 
            	if(isEmpty(root)){
	   				emptySystem();
	   				continue;
				} 
				
        		order = 1;
        		displayAllCustomers(root, order);
        		deleteText(0, 0);
        		cout << "--------------------------------------" << endl;
        		cout << endl;
            	break;
            	
            case 5:
            	if(isEmpty(root)){
	   				emptySystem();
	   				continue;
				}
				
				id = inputInt("Customer ID to display his flights information");
	   			customer = searchCustomer(root, id);
	   			
	   			if(isCorrect(customer.id)){
	   				displayCustomerFlights(customer);
		   			cout << "----------------------------" << endl;
		   			cout << endl;
				}
				break;
	   			
                
            case 6:
                cout << "Exiting the system .. Thank you.";
                break;
                
            default:
                cout << "Invalid choice ,Please try again.";
                deleteText(11, 3);
        }
        
    } while (choice != 6);
    
    return 0;
}
