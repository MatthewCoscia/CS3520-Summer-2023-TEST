
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    vector<char> consonants = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
    int vowel_count = 0, consonent_count = 0, punctuation_count = 0, double_vowel_count = 0, word_count = 0, multiple_vowels = 0;
    string singlequote = "'";
    char singlequote_char = singlequote[0];
    vector<char> punctuation_list = {'!', '.', ',', ';', singlequote_char, '?', '$'};
    string paragraph = "", total_paragraph = "";
    cout << "Please enter your paragraph." << "\n";
    // do while that allows the user to paste in paragraphs.
    do {
        getline(cin, paragraph);
        if (paragraph != "STOPINPUT") {
            total_paragraph += paragraph;
        }
    } while (paragraph != "STOPINPUT");
    for (int i = 0; i < total_paragraph.length(); ++i) {
        char previous_char = ' ';
        if (i > 0) {
            previous_char = total_paragraph[i - 1];
        }
        char tempChar = total_paragraph[i];
        if (tempChar == ' ' && previous_char != ' ') {
            word_count += 1;
        }
        for (char vowel : vowels) {
            if (tempChar == vowel) {
                vowel_count += 1;
                multiple_vowels += 1;
                break;
            }
        }
        for (char consonant : consonants) {
            if (tempChar == consonant) {
                consonent_count += 1;
                break;
            }
        }
        for (char punctuation : punctuation_list) {
            if (tempChar == punctuation) {
                punctuation_count += 1;
                break;
            }
        }
    }
    for (int k = 0; k < total_paragraph.length(); ++k) {
        char tempChar = total_paragraph[k];
        if (tempChar == ' ') {
            if (multiple_vowels > 1) {
                double_vowel_count += 1;
            }
            multiple_vowels = 0;
        }
        for (char vowel : vowels) {
            if (tempChar == vowel) {
                multiple_vowels += 1;
            }
        }
    }

    cout << "\n" << "Your paragraph is:" << "\n" << total_paragraph << "\n";
    cout << "the total number of: " << "\n";
    cout << "Words: " << word_count + 1 << "\n";
    cout << "Vowels: " << vowel_count << "\n";
    cout << "Consonants: " << consonent_count << "\n";
    cout << "Punctuation Characters: " << punctuation_count << "\n";
    cout << "Words with more than one vowel: " << double_vowel_count << "\n";
    cout << "Enter the length of the words you want to filter." << "\n";
    int word_length = 0;
    cin >> word_length;
    int current_word_length = 0;
    int words_greater_then_word_length = 0;
    for (int i = 0; i < total_paragraph.length(); ++i) {
        char tempChar = total_paragraph[i];
        if (tempChar != ' ') {
            bool isPunctuation = false;
            for (char punctuation: punctuation_list) {
                if (tempChar == punctuation) {
                    isPunctuation = true;
                }
            }
            if (!isPunctuation) {
                current_word_length += 1;
            }
        }
        if (tempChar == ' ') {
            if (current_word_length > word_length) {
                words_greater_then_word_length += 1;
            }
            current_word_length = 0;
        }
        if (i == total_paragraph.length() - 1 && tempChar != ' ') {
            if (current_word_length > word_count) {
                words_greater_then_word_length += 1;
            }
        }
    }
    cout << "There are " << words_greater_then_word_length << " Words greater than " << word_length << "\n";
    int random_length = 6 + (rand() % 10);
    current_word_length = 0;
    int words_less_then_random = 0;
    for (int i = 0; i < total_paragraph.length(); ++i) {
        char tempChar = total_paragraph[i];
        if (tempChar != ' ') {
            current_word_length += 1;
        }
        if (tempChar == ' ') {
            if (current_word_length < random_length) {
                words_less_then_random += 1;
            }
            current_word_length = 0;
        }
        if (i == total_paragraph.length() - 1 && tempChar != ' ') {
            if (current_word_length < random_length) {
                words_less_then_random += 1;
            }
        }
    }
    cout << "There are " << words_less_then_random << " words less than the random number " << random_length << "\n";

}

