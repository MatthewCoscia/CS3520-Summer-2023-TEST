// Automatic dialing machine
// Delivers a sales message
/* Needs to print all possible combinations of areacode and exchangecode with the last 4 digits
Example : If areacode = 617, exchange = 424
Output : 
"I am calling to tell you to buy a subscription to Dogs Monthly Magazine!"
617-424-0001
617-424-0002
617-424-0003
...
617-424-9998
617-424-9999
*/

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

// revisions made to code.
// added using namespace std and deleted the std:: from the couts and cins for clarity.
// fixed the for loops by changing : to ;
// changed the while loop for digit3 to a for loop.
// fixed the digit1 and digit2 loops by adding the proper variables.
// (changed digit2 to digit1 and digit3 to digit2.
// moved the calls completed cout statement and the return statement into the main.
// removed extra parenthesis and brackets.
// moved the calling cout to above the for loop.
// changed the for loops to work the same and also added a loop for digit4.

#include<iostream>

using namespace std;

int main() {
    int digit1, digit2, digit3, digit4;
    int areaCode, exchange;
    cout << "Hello, I am a telemarketing calling making program.\n";
    cout << "Enter a three-digit area code" << "\n";
    cin >> exchange;
    cout << "Enter a three-digit exchange to call" << "\n";
    cin >> areaCode;
    cout << "I am calling to tell you to buy a subscription to Dogs Monthly!\n";
    for (digit1 = 0; digit1 <= 9; ++digit1) {
        for (digit2 = 0; digit2 <= 9; ++digit2) {
            for (digit3 = 0; digit3 <= 9; ++digit3) {
                for (digit4 = 0; digit4 <= 9; ++digit4) {
                    cout << "Dialing (" << areaCode << ") " << exchange << " - ";
                    cout << digit1 << digit2 << digit3 << digit4 << endl;
                }
            }
        }
    }
    cout << "\nCalls completed"<< endl;
    return 0;

}
