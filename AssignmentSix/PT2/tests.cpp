#include "Repository.h"
#include <iostream>
#include <string>

// User-defined types
class Course {
private:
    std::string title;
    std::string semester;

public:
    Course(const std::string& title, const std::string& semester) : title(title), semester(semester) {}

    bool operator==(const Course& other) const {
        return title == other.title && semester == other.semester;
    }
};

class Book {
private:
    std::string title;
    std::string author;

public:
    Book(const std::string& title, const std::string& author) : title(title), author(author) {}

    bool operator==(const Book& other) const {
        return title == other.title && author == other.author;
    }
};

int main() {
    // Create Repository for strings
    Repository<std::string> stringRepo;
    stringRepo.addOrUpdate("Item 1");
    stringRepo.addOrUpdate("Item 2");
    stringRepo.addOrUpdate("Item 3");
    stringRepo.addOrUpdate("Item 2");  // Update existing item
    std::cout << "String Repository:\n" << stringRepo << std::endl;

    // Create Repository for integers
    Repository<int> intRepo;
    intRepo.addOrUpdate(10);
    intRepo.addOrUpdate(20);
    intRepo.addOrUpdate(30);
    intRepo.addOrUpdate(40);
    intRepo.remove(20);
    std::cout << "Int Repository:\n" << intRepo << std::endl;

    // Create Repository for courses
    Repository<Course> courseRepo;
    Course course1("Course 1", "Semester 1");
    Course course2("Course 2", "Semester 2");
    courseRepo.addOrUpdate(course1);
    courseRepo.addOrUpdate(course2);
    courseRepo.remove(course1);
    std::cout << "Course Repository:\n" << courseRepo << std::endl;

    // Create Repository for books
    Repository<Book> bookRepo;
    Book book1("Book 1", "Author 1");
    Book book2("Book 2", "Author 2");
    bookRepo.addOrUpdate(book1);
    bookRepo.addOrUpdate(book2);
    bookRepo.remove(book2);
    std::cout << "Book Repository:\n" << bookRepo << std::endl;

    return 0;
}

