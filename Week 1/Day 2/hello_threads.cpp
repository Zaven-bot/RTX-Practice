#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <mutex>

class BestPrinter {
    std::mutex num_lock;
    std::mutex word_lock;
    std::ofstream file;
    int sum = 0;

public:
    void printWiseStuff(const std::string& filename, const std::string& wise_words) {
        std::lock_guard<std::mutex> guard(word_lock);
        file.open(filename, std::ios::app);
        file << wise_words << "\n";
        file.close();
    }

    void incrWiseStuff(const std::string& filename, const int& num) {
        std::lock_guard<std::mutex> guard(num_lock);
        file.open(filename, std::ios::app);
        sum = sum + num;
        file << sum << "\n";
        file.close();
    }
};

int main() {

    BestPrinter printer;
    std::vector<std::string> files;
    std::vector<std::thread> gru;

    std::string filename;
    std::string input;

    for (int i = 0; i < 2; i++) {
        std::cout << "Filename: ";
        std::getline(std::cin, filename);
        files.emplace_back(filename);
        if (i == 0) {
            std::cout << "Wisdom?: ";
        } else {
            std::cout << "Wise number?: ";
        }
        std::getline(std::cin, input);


        // threads request the function, and then its arguments
        // if you give arguments at same time, it will automatically call
        // and try to pass its return value (void)
        if (i == 0) {
            for (int i = 0; i < 125; i++) {
                gru.emplace_back(&BestPrinter::printWiseStuff, &printer, filename, input);
            }
        } else {
            for (int i = 0; i < 35; i++) {
                gru.emplace_back(&BestPrinter::incrWiseStuff, &printer, filename, std::stoi(input));
            }
        }
    }


    for (auto& minion : gru) {
        minion.join(); // wait for all threads to finish
    }

    return 0;
}