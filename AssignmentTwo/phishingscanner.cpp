#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

class phishing_word {
public:
    string word;
    int value;
};

phishing_word populate_word(phishing_word p, string word, int value) {
    p.value = value;
    p.word = word;
    return p;
}

vector<string> get_words(string str) {
    vector<string> final;
    istringstream ss(str);
    string word;
    while (ss >> word) {
        final.push_back(word);
    }
    return final;
}

bool case_insensitive_comparison(string s1, string s2) {
    int i = 0;
    int len = s1.size();
    while (i < len) {
        if (ispunct(s1[i])) {
            s1.erase(i--, 1);
            len = s1.size();
        }
        i++;
    }
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if (s1.compare(s2) == 0) {
        return true;
    }
    else {
        return false;
    }
}

int PhishingScanner() {
    fstream file;
    phishing_word p;
    string page;
    string words[30] = {"Urgent", "Action", "Hey", "Money", "Opportunity",
                        "Password", "Username", "Necessary", "Limited", "Dropbox",
                        "Time", "Cryptocurrency", "Verification", "Invoice", "Help",
                        "Required", "Vulnerability", "Vulnerable", "Suspicious", "Activity",
                        "Locked", "Account", "Install", "Expire", "Unlock",
                        "Click", "Support", "Label", "Invoice", "Post"};
    int word_values[30] = {2, 2, -1, 1, 2,
                           3, 1, 2, 2, 1,
                           1, 1, 3, 3, 3,
                           2, 3, 3, 3, 1,
                           2, 2, 3, 3, 3,
                           1, 1, 3, 3, 3};
    vector<phishing_word> list_of_phishing_words;
    for (int i = 0; i < 30; ++i) {
        phishing_word p;
        list_of_phishing_words.push_back(populate_word(p, words[i], word_values[i]));
    }
    file.open("email.txt", ios::in);
    if (file.is_open()) {
        string temp;
        int counter = 0;
        while(getline(file, temp)) {
            if (counter != 0) {
                page += "\n" + temp;
            }
            else {
                page += temp;
            }
            counter += 1;
        }
    }
    int phishing_value = 0;
    cout << "\n";
    cout << page << "\n";
    vector<string> email_words = get_words(page);
    cout << "Word : Point Value" << "\n";
    for (int i = 0; i < email_words.size(); ++i) {
        for (int k = 0; k < list_of_phishing_words.size(); ++k) {
            if (case_insensitive_comparison(email_words[i], list_of_phishing_words[k].word)) {
                cout << list_of_phishing_words[k].word << ": " << list_of_phishing_words[k].value << "\n";
                phishing_value += list_of_phishing_words[k].value;
            }
        }
    }
    cout << "The final value of this email is: " << phishing_value << "\n";
}

