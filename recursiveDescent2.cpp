#include <iostream> // Including the standard input/output stream library
#include <stdlib.h> // Including standard library functions
#include<conio.h> // Including console I/O functions
using namespace std; // Using standard namespace

// Grammar rules
/*
E->TE'
E'->+TE'|-TE'|null
T-> FT'
T'->*FT'|/FT'|null
F-> id|num|(E)
*/

int count = 0; // Counter to track the current position in the input expression
void E(); // Function prototype for non-terminal E
void Ed(); // Function prototype for non-terminal E'
void T(); // Function prototype for non-terminal T
void Td(); // Function prototype for non-terminal T'
void F(); // Function prototype for non-terminal F

string expr; // Input expression

int main() {
  cin >> expr; // Taking input expression from user
  int l = expr.length(); // Storing length of input expression
  expr += "$"; // Appending "$" to indicate end of input
  E(); // Starting the parsing process from non-terminal E
  if (l == count) // If entire input expression is consumed by the parser
  {
    cout << "Accepted" << endl; // Print "Accepted"
    getchar(); // Wait for user input
  } else
    cout << "Rejected" << endl; // If not, print "Rejected"
  getchar(); // Wait for user input
}

void E() {
  cout << "E->TE'" << endl; // Print production rule being applied
  getchar(); // Wait for user input
  T(); // Apply production for non-terminal T
  Ed(); // Apply production for non-terminal E'
}

void Ed() {
  if (expr[count] == '+') { // If next character is '+'
    count++; // Move to the next character
    cout << "E'->+TE'" << endl; // Print production rule being applied
    getchar(); // Wait for user input
    T(); // Apply production for non-terminal T
    Ed(); // Apply production for non-terminal E'
  }

  else if (expr[count] == '-') { // If next character is '-'
    count++; // Move to the next character
    cout << "E'->-TE'" << endl; // Print production rule being applied
    getchar(); // Wait for user input
    T(); // Apply production for non-terminal T
    Ed(); // Apply production for non-terminal E'
  }

  else {
    cout << "E'->null" << endl; // Print production rule being applied when E' is null
    getchar(); // Wait for user input
  }
}

void T() {
  cout << "T->FT'" << endl; // Print production rule being applied
  getchar(); // Wait for user input
  F(); // Apply production for non-terminal F
  Td(); // Apply production for non-terminal T'
}

void Td() {
  if (expr[count] == '') { // If next character is ''
    count++; // Move to the next character
    cout << "T'->*FT'" << endl; // Print production rule being applied
    getchar(); // Wait for user input
    F(); // Apply production for non-terminal F
    Td(); // Apply production for non-terminal T'
  }

  else if (expr[count] == '/') { // If next character is '/'
    count++; // Move to the next character
    cout << "T'->/FT'" << endl; // Print production rule being applied
    getchar(); // Wait for user input
    F(); // Apply production for non-terminal F
    Td(); // Apply production for non-terminal T'
  }

  else {
    cout << "T'->null" << endl; // Print production rule being applied when T' is null
    getchar(); // Wait for user input
  }
}

void F() {
  if (isalpha(expr[count])) { // If next character is alphabet
    count++; // Move to the next character
    cout << "F->id" << endl; // Print production rule being applied for identifier
    getchar(); // Wait for user input
  } else if (isdigit(expr[count])) { // If next character is digit
    count++; // Move to the next character
    cout << "F->digit" << endl; // Print production rule being applied for digit
    getchar(); // Wait for user input
  } else if (expr[count] == '(') { // If next character is '('
    count++; // Move to the next character
    cout << "F->(E)" << endl; // Print production rule being applied
    getchar(); // Wait for user input
    E(); // Apply production for non-terminal E
    if (expr[count] != ')') { // If next character is not ')'
      cout << "Rejected" << endl; // Print "Rejected"
      getchar(); // Wait for user input
      exit(0); // Exit the program
    }
    count++; // Move to the next character
  } else {
    cout << "Rejected" << endl; // Print "Rejected"
    getchar(); // Wait for user input
    exit(0); // Exit the program
  }
}