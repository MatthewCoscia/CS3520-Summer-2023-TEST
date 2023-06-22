#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Employee {
private:
    string name;
    string email;
    string designation;
    int groupId;

public:
    Employee(string name, string email, string designation, int groupId)
            : name(name), email(email), designation(designation), groupId(groupId) {}

    friend ostream& operator<<(ostream& os, const Employee& employee) {
        os << "Name: " << employee.name << ", Email: " << employee.email << ", Designation: " << employee.designation;
        return os;
    }

    friend istream& operator>>(istream& is, Employee& employee) {
        cout << "Enter Name: ";
        is >> employee.name;
        cout << "Enter Email: ";
        is >> employee.email;
        cout << "Enter Designation: ";
        is >> employee.designation;
        return is;
    }

    int getGroupId() const {
        return groupId;
    }
};

class Group {
private:
    string name;
    int groupNumber;
    string focusArea;
    vector<Employee> employees;

public:
    Group(string name, int groupNumber, string focusArea)
            : name(name), groupNumber(groupNumber), focusArea(focusArea) {}

    void addEmployee(const Employee& employee) {
        employees.push_back(employee);
    }

    void removeEmployee(int index) {
        employees.erase(employees.begin() + index);
    }

    void mergeWithGroup(const Group& otherGroup) {
        employees.insert(employees.end(), otherGroup.employees.begin(), otherGroup.employees.end());
    }

    friend Group operator+(const Group& group1, const Group& group2) {
        Group mergedGroup = group1;
        mergedGroup.employees.insert(mergedGroup.employees.end(), group2.employees.begin(), group2.employees.end());
        return mergedGroup;
    }

    friend ostream& operator<<(ostream& os, const Group& group) {
        os << "Group Name: " << group.name << ", Group Number: " << group.groupNumber << ", Focus Area: " << group.focusArea << endl;
        os << "Employees: " << endl;
        for (const auto& employee : group.employees) {
            os << employee << endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Group& group) {
        cout << "Enter Group Name: ";
        is >> group.name;
        cout << "Enter Group Number: ";
        is >> group.groupNumber;
        cout << "Enter Focus Area: ";
        is >> group.focusArea;
        return is;
    }

    int getGroupNumber() const {
        return groupNumber;
    }

    void removeXEmployees(int x) {
        while (x > 0 && !employees.empty()) {
            employees.pop_back();
            x--;
        }
    }
};

int main() {
    // Create Group 1
    Group group1("Group 1", 1, "Focus Area 1");
    Employee employee1("John Doe", "john.doe@example.com", "Manager", 1);
    Employee employee2("Jane Smith", "jane.smith@example.com", "Developer", 1);
    group1.addEmployee(employee1);
    group1.addEmployee(employee2);

    // Create Group 2
    Group group2("Group 2", 2, "Focus Area 2");
    Employee employee3("Michael Johnson", "michael.johnson@example.com", "Designer", 2);
    Employee employee4("Emily Brown", "emily.brown@example.com", "QA Engineer", 2);
    group2.addEmployee(employee3);
    group2.addEmployee(employee4);

    // Print initial groups
    cout << "Initial Groups:" << endl;
    cout << "----------------" << endl;
    cout << "Group 1:" << endl;
    cout << group1 << endl;
    cout << "Group 2:" << endl;
    cout << group2 << endl;

    // Scenario 1: Group 1 loses X employees
    int x = 1; // Number of employees to be removed
    group1.removeXEmployees(x);
    cout << "Scenario 1: Group 1 loses " << x << " employee(s):" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Group 1 after removal:" << endl;
    cout << group1 << endl;

    // Scenario 2: Groups 1 and 2 are merged
    Group mergedGroup = group1 + group2;
    cout << "Scenario 2: Group 1 and Group 2 are merged:" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Merged Group:" << endl;
    cout << mergedGroup << endl;

    return 0;
}