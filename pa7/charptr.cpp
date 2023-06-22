//This program should read any string (including spaces) from the user and print it using a character pointer
//The program is setup to use pointer offset notation to get each character of the string

//Number of bugs/errors : 8

// 1. changed the header from stdio to iostream
#include <iostream>
#include <string>

using namespace std;

//2. main must be an integer
int main(void){
    char s[20];
    // 3. changed cPtr from char to char*
    char* cPtr;
    cin>>s;
    cPtr = s;
    // changed the while loop to make it valid.
    while(*cPtr != '\0'){
        // changed the output.
        cout<<*cPtr++;
    }
  cout<<"\n";
  return 0;
}
