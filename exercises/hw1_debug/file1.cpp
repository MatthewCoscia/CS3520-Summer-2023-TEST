/* Print the sum of products of odd and even numbers from 1 to 10
*  Print alternate characters from 'A' to 'Z' in the reverse order starting with 'Z'
*  Ouput of the program should look like:
    The value of limit is 10
    The Sum = 4785
    Z X V T R P N L J H F D B
*/

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

// revisions made to code.
// added using namespace std to fix the cout errors.
// intialized integer i and changed the for loop colons from : to ;
// changed the second for loop variable from i to c.
// changed the ** in (i ** 2 == 1) to (i / 2).

#include <iostream>

using namespace std;

int main() {
    int limit = 10, sum = 0, even_product = 1, odd_product = 1;
    char c = 'Z';
    cout << "The value of limit is " << limit << endl;
    for (int i = 0; i <= limit; i = i + 1) {
        if (i % 2 == 0 && i != 0) {
            even_product = even_product * i;
        }
        if (i % 2 == 1) {
            odd_product = odd_product * i;
        }
    }
    sum = even_product + odd_product;
    cout << "The Sum = " << sum;
    cout << "\n";
    while (c >= 'A') {
        cout << c << " ";
        c = c - 2;
    }

    return 0;
}
