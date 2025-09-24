#include <fstream> // i/o
#include <memory> // smart ptr
#include <iostream>

class FileWriter {
    public:
        // Initialize connection to file with filename,
        // a reference to a full C++ string object
        FileWriter(const std::string& filename) {
            file.open(filename, std::ios::app);
        }
        
        void write(const std::string& text) {
            file << text << "\n";
        }
        
        // Close connection to file
        ~FileWriter() {
            file.close();
        }
    private:
        std::ofstream file; // ofstream to write, ifstream to read, fstream for both
};

int main() {
    std::string filename;
    std::cout << "Enter filename: ";

    // Assign filename variable the full line of code (before "\n")
    std::getline(std::cin, filename);

    // Initialize FileWriter fw with filename
    FileWriter fw(filename);

    fw.write("You say you got a girl\nHow you want me? How you want me when you got a girl?\nThe feelin' is rckless of knowin' it's selfish\nKnowin' iI'm desperate\nGettin' in all in your love, fallin' all over love, like\nDo it 'til it hurts less\n");

    return 0;
}