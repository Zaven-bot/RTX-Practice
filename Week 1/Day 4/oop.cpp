#include <string>
#include <iostream>
#include <vector>
#include <memory>

class Person {
    protected:
        std::string first;
        std::string last;
    public:
        Person(std::string first, std::string last) : first(first), last(last) {};
        virtual void printInfo() const {
            std::cout << "-------------------------------------\n";
            std::cout << "Person Information:\n";
            std::cout << "Name: " << first << " " << last << "\n";
            std::cout << "-------------------------------------\n";
        }
};

class Employee : public Person {
    private:
        std::string department;
    public:
        Employee(std::string first, std::string last, std::string department) : Person(first, last), department(department) {};
        void printInfo() const override {
            std::cout << "-------------------------------------\n";
            std::cout << "Employee Information:\n";
            std::cout << "Name: " << first << " " << last << "\n";
            std::cout << "Department: " << department << "\n";
            std::cout << "-------------------------------------\n";
        }
};

int main() {
    std::vector<std::unique_ptr<Person>> people;
    std::unique_ptr<Person> p0(new Person("Ian", "Unebasami"));
    std::unique_ptr<Employee> p1(new Employee("Ian", "Unebasami", "Raytheon"));
    people.push_back(std::move(p0));
    people.push_back(std::move(p1));
    for (const auto& p : people) {
        p -> printInfo();
    }
    return 0;
}