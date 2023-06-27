#include <iostream>
#include "classes.hpp"
#include "model.hpp"

using namespace std;

int main() {
    cout << "Welcome to the City of Newton Pickeball Court!" << endl;
    string command;
    string username;
    string password;
    string role;
    while (!user->signedIn) {
        cout << "Would you like to sign in (sign-in) or sign up (sign-up)?" << endl;
        cin >> command;
        if (command == "sign-in") {
            cout << "please sign in:" << endl;
            cout << "Enter Username: " << endl;
            cin >> username;
            cout << "Enter Password:" << endl;
            cin >> password;
            signIn(username, password);
        }
        if (command == "sign-up") {
            cout << "Enter the username you want to sign up with" << endl;
            cin >> username;
            cout << "Enter the password you'd like to have" << endl;
            cin >> password;
            cout << "Are you a coach (CC), a member (CM), or a officer (CO)?" << endl;
            cin >> role;
            signUp(username, password, role);
            signIn(username, password);
        }
    }
    if (user->getSymbol() == "CM") {
        char ranking;
        cout << "What is current your Rating? (A, B, or C)" << endl;
        cin >> ranking;
        user->setSkillLevel(ranking);
    }
    cout << "Welcome!" << endl;
    cout << "The day is Sunday, so the schedule for the next week is open now." << endl;
    cout << "'schedule': to view the upcoming schedule for each court this week (Press Q to exit)" << endl;
    cout << "'check-reservations': to view the days when you are registered for." << endl;
    cout << "'make-reservation': will let you make a reservation for a court." << endl;
    cout << "'delete-reservation': will allow you to delete a reservation you have made." << endl;
    cout << "'make-lesson': is only available for coaches, and will allow you to create a lesson reservation" << endl;
    cout << "'delete-lesson': is only available for coaches, and will allow you to delete a lesson reservation" << endl;
    cout << "'check-coaching-reservations': is only available for coaches, and will allow you to check your current lessons." << endl;
    cout << "Type exit to quit" << endl;
    cin >> command;
    while (command != "exit") {
        if (command == "schedule") {
            printSchedule();
        }
        if (command == "check-reservations") {
            checkReservations(username);
        }
        if (command == "make-reservation") {
            cout << "What day? (Monday-Sunday)" << endl;
            string day;
            cin >> day;
            cout << "What time? (06:00 to 23:30)" << endl;
            string time;
            cin >> time;
            cout << "What Court? (Court-1, Court-2, or Court-3)" << endl;
            string court;
            cin >> court;
            makeReservation(username, day, time, court);
        }
        if (command == "delete-reservation") {
            cout << "What day? (Monday-Sunday)" << endl;
            string day;
            cin >> day;
            cout << "What time? (06:00 to 23:30)" << endl;
            string time;
            cin >> time;
            cout << "What Court? (Court-1, Court-2, or Court-3)" << endl;
            string court;
            cin >> court;
            deleteReservation(username, day, time, court);
        }
        if (command == "check-coaching-reservations") {
            if (user->getSymbol() == "CC") {
                checkCoachingReservations(username);
            } else {
                cout << "You are not a coach, and cannot make a lesson" << endl;
            }
        }
        if (command == "make-lesson") {
            if (user->getSymbol() == "CC") {
                cout << "What day? (Monday-Sunday)" << endl;
                string day;
                cin >> day;
                cout << "What time? (06:00 to 23:30)" << endl;
                string time;
                cin >> time;
                cout << "What Court? (Court-1, Court-2, or Court-3)" << endl;
                string court;
                cin >> court;
                createLesson(username, day, time, court);
            } else {
                cout << "You are not a coach, and cannot make a lesson" << endl;
            }
        }
        if (command == "delete-lesson") {
            if (user->getSymbol() == "CC") {
                cout << "What day? (Monday-Sunday)" << endl;
                string day;
                cin >> day;
                cout << "What time? (06:00 to 23:30)" << endl;
                string time;
                cin >> time;
                cout << "What Court? (Court-1, Court-2, or Court-3)" << endl;
                string court;
                cin >> court;
                cancelLesson(username, day, time, court);
            } else {
                cout << "You are not a coach, and cannot make a lesson" << endl;
            }
        }
        cout << "\n";
        cout << "'schedule': to view the upcoming schedule for each court this week (Press Q to exit)" << endl;
        cout << "'check-reservations': to view the days when you are registered for." << endl;
        cout << "'make-reservation': will let you make a reservation for a court." << endl;
        cout << "'delete-reservation': will allow you to delete a reservation you have made." << endl;
        cout << "'make-lesson': is only available for coaches, and will allow you to create a lesson reservation" << endl;
        cout << "'delete-lesson': is only available for coaches, and will allow you to delete a lesson reservation" << endl;
        cout << "'check-coaching-reservations': is only available for coaches, and will allow you to check your current lessons." << endl;
        cout << "Type exit to quit" << endl;
        cin >> command;
    }


    return 0;
}
