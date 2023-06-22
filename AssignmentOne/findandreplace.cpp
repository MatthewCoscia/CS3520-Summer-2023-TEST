#include <iostream>
#include <vector>

using namespace std;

int main() {
    string paragraph = "", total_paragraph = "";
    cout << "Please enter your paragraph." << "\n";
    // do while that allows the user to paste in paragraphs.
    do {
        getline(cin, paragraph);
        if (paragraph != "STOPINPUT") {
            total_paragraph += paragraph;
        }
    } while (paragraph != "STOPINPUT");
    cout << "Please enter the word or phrase you want to check for." << "\n";
    paragraph = "";
    string total_phrase = "";
    string backup_phrase = "";
    do {
        getline(cin, paragraph);
        if (paragraph != "STOPINPUT") {
            total_phrase += paragraph;
        }
    } while (paragraph != "STOPINPUT");
    backup_phrase = total_phrase;
    string temp_total_paragraph = total_paragraph;
    int timer = 0;
    vector<int> positions = {};
    vector<int> positions_filtered = {};
    while (timer < 1) {
        try {
            size_t pos = temp_total_paragraph.find(total_phrase);
            int position = pos;
            positions.push_back(position);
            temp_total_paragraph.replace(pos, total_phrase.length(), "IGNORE");
        }
        catch (exception e) {
            timer += 1;
        }
    }
    for (int k: positions) {
        if (k >= 0) {
            positions_filtered.push_back(k);
        }
    }
    cout << "This word/phrase is used " << positions_filtered.size() << " times" << "\n";
    cout << "This word/phrase is located at positions: " << "\n";
    for (int z: positions_filtered) {
        cout << z << ", ";
    }
    cout << "\n" << "Please input the phrase you want to replace the word with." << "\n";
    string new_phrase = "";
    string input = "";
    do {
        getline(cin, input);
        if (input != "STOPINPUT") {
            new_phrase += input;
        }
    } while (input != "STOPINPUT");
    timer = 0;
    string new_paragraph = total_paragraph;
    while (timer < 1) {
        try {
            size_t pos = new_paragraph.find(backup_phrase);
            new_paragraph.replace(pos, backup_phrase.length(), new_phrase);
        }
        catch (exception e) {
            timer += 1;
        }
    }
    cout << "\n" << new_paragraph;
    return 0;
}

