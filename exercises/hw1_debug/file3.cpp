/*  This program should determine if a number is a prime or composite number 
    The program should ask user for a number 'num'
    If 'num' is 0 or 1, print "num is not prime or composite"
    For any value > 1, print "num is a prime number" or "num is a composite number" depending on the number */

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

// revisions made to code.
// changed #include<iosteam> to #include<iostream>
// added using namespace std.

// Revisions:
// changed the num = 0 or 1 if statement to || instead of &&.
// changed if statement from not factor_found to factor_found for convenience.


#include<iostream>
using namespace std;

int main(){
    int num,i;
    bool factor_found = false;
    cout<<"Enter Number:" << "\n";
    cin>>num;
    if(num == 0 || num == 1) {
        cout<<num<<" is not prime or composite";
        return 0;
    }
    for (i = 2; i<num; i++) {
        if (num % i == 0) {
            factor_found = true;
            break;
        }
    }
    if (factor_found) {
        cout<<"is a composite number\n";
    }
    else {
        cout<<"is a prime number\n";
    }
}
