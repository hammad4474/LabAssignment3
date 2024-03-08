// Including necessary libraries
#include <iostream> 
using namespace std; 

// Maximum number of elements in the hash table
const int MAX = 100; 

// Class representing a Node in the hash table
class Node { 
	// Attributes of the Node
	string identifier, scope, type; 
	int lineNo; 
	Node* next; 

public: 
	// Constructors
	Node() { 
		next = NULL; 
	} 

	Node(string key, string value, string type, int lineNo) { 
		this->identifier = key; 
		this->scope = value; 
		this->type = type; 
		this->lineNo = lineNo; 
		next = NULL; 
	} 

	// Function to print Node details
	void print() { 
		cout << "Identifier's Name:" << identifier 
			<< "\nType:" << type 
			<< "\nScope: " << scope 
			<< "\nLine Number: " << lineNo << endl; 
	} 

	// SymbolTable class is declared as a friend to access Node's private members
	friend class SymbolTable; 
}; 

// Class representing the Symbol Table
class SymbolTable { 
	// Array of pointers to Nodes
	Node* head[MAX]; 

public: 
	// Constructor to initialize head pointers
	SymbolTable() { 
		for (int i = 0; i < MAX; i++) 
			head[i] = NULL; 
	} 

	// Hash function to generate hash value for an identifier
	int hashf(string id); 

	// Function to insert an identifier into the Symbol Table
	bool insert(string id, string scope, string Type, int lineno); 

	// Function to find an identifier in the Symbol Table
	string find(string id); 

	// Function to delete an identifier from the Symbol Table
	bool deleteRecord(string id); 

	// Function to modify an identifier's attributes in the Symbol Table
	bool modify(string id, string scope, string Type, int lineno); 
}; 

// Function to modify an identifier's attributes in the Symbol Table
bool SymbolTable::modify(string id, string s, string t, int l) { 
	int index = hashf(id); 
	Node* start = head[index]; 

	if (start == NULL) 
		return false; 

	while (start != NULL) { 
		if (start->identifier == id) { 
			start->scope = s; 
			start->type = t; 
			start->lineNo = l; 
			return true; 
		} 
		start = start->next; 
	} 

	return false; 
} 

// Function to delete an identifier from the Symbol Table
bool SymbolTable::deleteRecord(string id) { 
	int index = hashf(id); 
	Node* tmp = head[index]; 
	Node* par = head[index]; 

	// No identifier is present at that index
	if (tmp == NULL) { 
		return false; 
	} 

	// Only one identifier is present
	if (tmp->identifier == id && tmp->next == NULL) { 
		tmp->next = NULL; 
		delete tmp; 
		return true; 
	} 

	while (tmp->identifier != id && tmp->next != NULL) { 
		par = tmp; 
		tmp = tmp->next; 
	} 
	if (tmp->identifier == id && tmp->next != NULL) { 
		par->next = tmp->next; 
		tmp->next = NULL; 
		delete tmp; 
		return true; 
	} 

	// Delete at the end
	else { 
		par->next = NULL; 
		tmp->next = NULL; 
		delete tmp; 
		return true; 
	} 
	return false; 
} 

// Function to find an identifier in the Symbol Table
string SymbolTable::find(string id) { 
	int index = hashf(id); 
	Node* start = head[index]; 

	if (start == NULL) 
		return "-1"; 

	while (start != NULL) { 

		if (start->identifier == id) { 
			start->print(); 
			return start->scope; 
		} 

		start = start->next; 
	} 

	return "-1"; // Not found 
} 

// Function to insert an identifier into the Symbol Table
bool SymbolTable::insert(string id, string scope, string Type, int lineno) { 
	int index = hashf(id); 
	Node* p = new Node(id, scope, Type, lineno); 

	if (head[index] == NULL) { 
		head[index] = p; 
		cout << "\n" << id << " inserted"; 
		return true; 
	} 

	else { 
		Node* start = head[index]; 
		while (start->next != NULL) 
			start = start->next; 

		start->next = p; 
		cout << "\n" << id << " inserted"; 
		return true; 
	} 

	return false; 
} 

// Hash function to generate hash value for an identifier
int SymbolTable::hashf(string id) { 
	int asciiSum = 0; 

	for (int i = 0; i < id.length(); i++) { 
		asciiSum = asciiSum + id[i]; 
	} 

	return (asciiSum % 100); 
} 

// Driver code 
int main() { 
	// Creating an instance of SymbolTable
	SymbolTable st; 
	string check; 

	// Output heading
	cout << "** SYMBOL_TABLE **\n"; 

	// Insert 'if' into Symbol Table
	if (st.insert("if", "local", "keyword", 4)) 
		cout << " -successfully"; 
	else
		cout << "\nFailed to insert.\n"; 

	// Insert 'number' into Symbol Table
	if (st.insert("number", "global", "variable", 2)) 
		cout << " -successfully\n\n"; 
	else
		cout << "\nFailed to insert\n"; 

	// Find 'if' in Symbol Table
	check = st.find("if"); 
	if (check != "-1") 
		cout << "Identifier Is present\n"; 
	else
		cout << "\nIdentifier Not Present\n"; 

	// Delete 'if' from Symbol Table
	if (st.deleteRecord("if")) 
		cout << "if Identifier is deleted\n"; 
	else
		cout << "\nFailed to delete\n"; 

	// Modify 'number' in Symbol Table
	if (st.modify("number", "global", "variable", 3)) 
		cout << "\nNumber Identifier updated\n"; 

	// Find and print 'number' in Symbol Table
	check = st.find("number"); 
	if (check != "-1") 
		cout << "Identifier Is present\n"; 
	else
		cout << "\nIdentifier Not Present"; 

	return 0; 
}