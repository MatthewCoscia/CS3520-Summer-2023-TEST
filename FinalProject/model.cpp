//
// Created by matthewcoscia on 6/26/23.
//

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "model.hpp"
#include "classes.hpp"
#include <ncurses.h>

using namespace std;

const int DAY_WIDTH = 11;
const int TIME_SLOT_WIDTH = 10;
const int USERNAME_WIDTH = 10;


extern User *user;
User *user = new Empty;

std::vector<std::string> splitString(const std::string &input, char delimiter) {
    std::vector<std::string> tokens;
    std::size_t start = 0;
    std::size_t end = input.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(input.substr(start, end - start));
        start = end + 1;
        end = input.find(delimiter, start);
    }

    tokens.push_back(input.substr(start));
    return tokens;
}

void signUp(string username, string password, string role) {
    ofstream file("data.txt", ios::app);
    if (file.is_open()) {
        file << "-" << username << "-" << password << "-" << role << "\n";
    }
    file.close();
}

void signIn(string username, string password) {
    string dataLine = "";
    ifstream file("data.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find(username) != string::npos) {
                dataLine = line;
            }
        }
        vector<string> userData = splitString(dataLine, '-');
        vector<string> signInDataFinal;
        int counter = 0;
        string founduser;
        string foundpass;
        string foundrole;
        for (string s: userData) {
            if (counter == 1) {
                founduser = s;
            }
            if (counter == 2) {
                foundpass = s;
            }
            if (counter == 3) {
                foundrole = s;
            }
            counter++;
        }
        if (username == founduser && password == foundpass) {

            if (foundrole == "CM") {
                user = new ClubMember;
                user->username = founduser;
                user->membership = "CM";
                user->signedIn = true;
            }
            if (foundrole == "CO") {
                user = new ClubOfficer;
                user->username = founduser;
                user->membership = "CO";
                user->signedIn = true;
            }
            if (foundrole == "CC") {
                user = new ClubCoach;
                user->username = founduser;
                user->membership = "CC";
                user->signedIn = true;
            }
        }
    } else {
        cout << "problems opening data file";
    }
}

Reservation makeReservationFromLine(string line) {
    vector<string> userData = splitString(line, ',');
    int counter2 = 0;
    string day;
    string time;
    string court;
    string reservedBy;
    for (string s: userData) {
        if (counter2 == 0) {
            day = s;
        }
        if (counter2 == 1) {
            time = s;
        }
        if (counter2 == 2) {
            court = s;
        }
        if (counter2 == 3) {
            reservedBy = s;
        }
        counter2++;
    }
    return *new Reservation(day, time, court, reservedBy);
}

void printSchedule() {
    ifstream scheduleInput("reservations.csv");
    vector<Reservation> schedule;
    schedule.push_back(*new Reservation("h", "h", "h", "h"));
    schedule.push_back(*new Reservation("Day:", "Time:", "Court:", "Reserver:"));
    string line;
    int counter = 0;
    int headerCounter = 0;
    while (getline(scheduleInput, line)) {
        if (counter != 0) {
            Reservation temp = makeReservationFromLine(line);
            schedule.push_back(temp);
            if (headerCounter == 30) {
                schedule.push_back(*new Reservation("Day:", "Time:", "Court:", "Reserver:"));
                headerCounter = 0;
            }
            headerCounter++;
        }
        counter++;
    }
    scheduleInput.close();
    initscr();
    cbreak();
    noecho();

    int rows, cols;
    getmaxyx(stdscr, rows, cols); // Get terminal dimensions

    WINDOW *win = newwin(rows, cols, 0, 0); // Create a new window

// Enable scrolling for the window
    scrollok(win, true);

// Display the schedule in the scrollable window
    for (const auto &reservation: schedule) {
        std::string line = reservation.day + "    " + reservation.time + "    " + reservation.court + "    " +
                           reservation.reservedBy;
        wprintw(win, "%s\n", line.c_str());
    }

// Refresh the window to display the content
    wrefresh(win);

// Enable keypad input for the window
    keypad(win, true);

// Handle scrolling
    int ch;
    int scrollPos = 0;
    int viewTop = 0;
    int viewBottom = getmaxy(win) - 1;

    while ((ch = wgetch(win)) != 'q') {
        switch (ch) {
            case KEY_UP:
                if (scrollPos > 0) {
                    --scrollPos;
                    wclear(win);
                    for (int i = scrollPos; i < scrollPos + getmaxy(win); ++i) {
                        if (i < schedule.size()) {
                            std::string line =
                                    schedule[i].day + "    " + schedule[i].time + "    " + schedule[i].court + "    " +
                                    schedule[i].reservedBy;
                            wprintw(win, "%s\n", line.c_str());
                        } else {
                            break;
                        }
                    }
                    wrefresh(win);
                }
                break;
            case KEY_DOWN:
                if (scrollPos < schedule.size() - getmaxy(win)) {
                    ++scrollPos;
                    wclear(win);
                    for (int i = scrollPos; i < scrollPos + getmaxy(win); ++i) {
                        if (i < schedule.size()) {
                            std::string line =
                                    schedule[i].day + "    " + schedule[i].time + "    " + schedule[i].court + "    " +
                                    schedule[i].reservedBy;
                            wprintw(win, "%s\n", line.c_str());
                        } else {
                            break;
                        }
                    }
                    wrefresh(win);
                }
                break;
        }
    }
    endwin();
}

int countChar(const std::string &str, char target) {
    int count = 0;
    for (char c: str) {
        if (c == target) {
            count++;
        }
    }
    return count;
}

int reservationCountForDay(string day, string username) {
    ifstream file("reservations.csv");
    string line;
    int counter = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            Reservation temp = makeReservationFromLine(line);
            if (temp.day == day && temp.reservedBy.find(username) != string::npos) {
                counter++;
            }
        }
    }
    return counter;
}

void makeReservation(string username, string day, string time, string court) {
    ifstream file("reservations.csv");
    string line;
    string backupLines = "";
    Reservation final;
    string finalLine;
    int lineCounter = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            backupLines += line + "\n";
            Reservation temp = makeReservationFromLine(line);
            if (temp.time == time && temp.day == day && temp.court == court) {
                finalLine = line;
                final = temp;
            }
            lineCounter++;
        }
        file.close();
    }
    bool somethingDone = false;
    string newRes;
    bool canReserve = true;
    if (reservationCount(username) > 1 && user->getSymbol() == "CM") {
        cout << "You have maxed your reservations for the week. You cannot reserve another slot" << endl;
        canReserve = false;
    }
    if (reservationCountForDay(day, username) > 0) {
        cout << "You have maxed your reservations for that day." << endl;
        canReserve = false;
    }
    if (canReserve) {
        if (final.reservedBy == "OPEN" && !somethingDone) {
            newRes = final.day + "," + final.time + "," + final.court + "," + username;
            size_t pos = backupLines.find(finalLine);
            if (pos != string::npos) {
                backupLines.replace(pos, finalLine.length(), newRes);
            }
            cout << "Reserved!" << endl;
            somethingDone = true;
        }
        if (countChar(final.reservedBy, '&') == 0 && !somethingDone) {
            newRes = final.day + "," + final.time + "," + final.court + "," + final.reservedBy + "&" + username;
            size_t pos = backupLines.find(finalLine);
            if (pos != string::npos) {
                backupLines.replace(pos, finalLine.length(), newRes);
            }
            cout << "Reserved with: " << final.reservedBy << endl;
            somethingDone = true;
        }
        if (countChar(final.reservedBy, '&') > 0 && !somethingDone) {
            cout << "This court cannot be reserved, please check the schedule for a different time" << endl;
            somethingDone = false;
        }
    }
    if (somethingDone) {
        ofstream fileWrite("reservations.csv", ios::trunc);
        if (fileWrite.is_open()) {
            fileWrite.close();
        }
        ofstream fileWrite2("reservations.csv", ios::app);
        if (fileWrite2.is_open()) {
            fileWrite2 << backupLines;
            fileWrite2.close();
        }
    }
}

bool checkIfReservedByUser(string username) {
    ifstream file("reservations.csv");
    string line;
    int counter = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            Reservation temp = makeReservationFromLine(line);
            vector<string> reservers = splitString(temp.reservedBy, '&');
            for (string s: reservers) {
                if (s == username) {
                    return true;
                }
            }
            vector<string> lessonReservers = splitString(temp.reservedBy, '-');
            for (string k : lessonReservers) {
                if (k == username) {
                    return true;
                }
            }
        }
        file.close();
    }
    return false;
}

int reservationCount(string username) {
    ifstream file("reservations.csv");
    string line;
    int counter = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            Reservation temp = makeReservationFromLine(line);
            vector<string> reservers = splitString(temp.reservedBy, '&');
            for (string s: reservers) {
                if (s == username) {
                    counter += 1;
                }
            }
        }
        file.close();
    }
    return counter;
}

void deleteReservation(string username, string day, string time, string court) {
    ifstream file("reservations.csv");
    string line;
    string backupLines = "";
    Reservation final;
    string finalLine;
    int lineCounter = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            backupLines += line + "\n";
            Reservation temp = makeReservationFromLine(line);
            if (temp.time == time && temp.day == day && temp.court == court && checkIfReservedByUser(username)) {
                finalLine = line;
                final = temp;
            }
            lineCounter++;
        }
        file.close();
    }
    bool somethingDone = false;
    string newRes;
    if (countChar(final.reservedBy, '&') == 0) {
        newRes = final.day + "," + final.time + "," + final.court + "," + "OPEN";
        if (username == final.reservedBy) {
            somethingDone = true;
        }
    }
    string otherUser;
    bool checkIfUserExists = false;
    if (countChar(final.reservedBy, '&') > 0) {
        vector<string> users = splitString(final.reservedBy, '&');
        for (string s : users) {
            if (s != username) {
                otherUser = s;
            }
            if (s == username) {
                checkIfUserExists = true;
            }
        }
        newRes = final.day + "," + final.time + "," + final.court + "," + otherUser;
        if (checkIfUserExists) {
            somethingDone = true;
        }
    }
    if (somethingDone) {
        size_t pos = backupLines.find(finalLine);
        if (pos != string::npos) {
            backupLines.replace(pos, finalLine.length(), newRes);
        }
        cout << "Your Reservation for this time has been deleted." << endl;
        ofstream fileWrite("reservations.csv", ios::trunc);
        if (fileWrite.is_open()) {
            fileWrite.close();
        }
        ofstream fileWrite2("reservations.csv", ios::app);
        if (fileWrite2.is_open()) {
            fileWrite2 << backupLines;
            fileWrite2.close();
        }
    }
    if (!somethingDone) {
        cout << "Your reservation could not be deleted." << endl;
    }

}

void checkReservations(string username) {
    ifstream file("reservations.csv");
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            Reservation temp = makeReservationFromLine(line);
            vector<string> reservers = splitString(temp.reservedBy, '&');
            for (string s: reservers) {
                if (s == username) {
                    temp.print();
                }
            }
        }
        file.close();
    }
}

void checkCoachingReservations(string username) {
    ifstream file("reservations.csv");
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            Reservation temp = makeReservationFromLine(line);
            vector<string> lessonReservers = splitString(temp.reservedBy, '-');
            for (string k : lessonReservers) {
                if (k == username) {
                    temp.print();
                }
            }
        }
        file.close();
    }
}

void createLesson(string username, string day, string time, string court) {
    ifstream file("reservations.csv");
    string line;
    string backupLines = "";
    Reservation final;
    string finalLine;
    int lineCounter = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            backupLines += line + "\n";
            Reservation temp = makeReservationFromLine(line);
            if (temp.time == time && temp.day == day && temp.court == court) {
                finalLine = line;
                final = temp;
            }
            lineCounter++;
        }
        file.close();
    }
    bool correctDay = false;
    bool somethingDone = false;
    string newRes;
    if (day == "Monday" || day == "Tuesday") {
        if (final.reservedBy == "OPEN") {
            correctDay = true;
        }
    }
    if (day == "Wednesday" || day == "Thursday" || day == "Friday") {
        correctDay = true;
    }
    vector<string> possibleTimes = {"09:00", "09:30", "10:00", "10:30", "11:00",
                                    "11:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30"};
    if (correctDay) {
        for (string s : possibleTimes) {
            if (final.time == s) {
                somethingDone = true;
            }
        }
    }
    if (user->getSymbol() != "CC") {
        somethingDone = false;
    }

    if (somethingDone) {
        newRes = final.day + "," + final.time + "," + final.court + "," + "LESSON-" + username;
        size_t pos = backupLines.find(finalLine);
        if (pos != string::npos) {
            backupLines.replace(pos, finalLine.length(), newRes);
        }
        cout << "Your lesson has been created." << endl;
        ofstream fileWrite("reservations.csv", ios::trunc);
        if (fileWrite.is_open()) {
            fileWrite.close();
        }
        ofstream fileWrite2("reservations.csv", ios::app);
        if (fileWrite2.is_open()) {
            fileWrite2 << backupLines;
            fileWrite2.close();
        }
    }
    if (!somethingDone) {
        cout << "Your lesson could not be created" << endl;
    }
}

void cancelLesson(string username, string day, string time, string court) {
    ifstream file("reservations.csv");
    string line;
    string backupLines = "";
    Reservation final;
    string finalLine;
    int lineCounter = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            backupLines += line + "\n";
            Reservation temp = makeReservationFromLine(line);
            if (temp.time == time && temp.day == day && temp.court == court && checkIfReservedByUser(username)) {
                finalLine = line;
                final = temp;
            }
            lineCounter++;
        }
        file.close();
    }
    bool somethingDone = false;
    string newRes;
    if (checkIfReservedByUser(username)) {
        somethingDone = true;
    }
    newRes = final.day + "," + final.time + "," + final.court + "," + "OPEN";
    if (somethingDone) {
        size_t pos = backupLines.find(finalLine);
        if (pos != string::npos) {
            backupLines.replace(pos, finalLine.length(), newRes);
        }
        cout << "Your Reservation for this time has been deleted." << endl;
        ofstream fileWrite("reservations.csv", ios::trunc);
        if (fileWrite.is_open()) {
            fileWrite.close();
        }
        ofstream fileWrite2("reservations.csv", ios::app);
        if (fileWrite2.is_open()) {
            fileWrite2 << backupLines;
            fileWrite2.close();
        }
    }
    if (!somethingDone) {
        cout << "Your lesson could not be deleted." << endl;
    }
}
