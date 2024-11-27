#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <random>


class Printer {
public:
    void print(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << message << "\n";
    }

private:
    std::mutex mutex_;
};


void sortCollection(std::vector<int>& collection, Printer& printer) {
    std::sort(collection.begin(), collection.end());
    printer.print("Сортировка: ""\n");
    for (int i : collection) {
        printer.print(std::to_string(i));
    }
}

int main() {

    Printer printer;


    std::vector<int> collection1(10);
    std::vector<int> collection2(10);
    std::vector<int> collection3(10);


    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    for (int i = 0; i < 10; ++i) {
        collection1[i] = dist(mt);
        collection2[i] = dist(mt);
        collection3[i] = dist(mt);
    }


    std::thread t1([&printer, &collection1]() {
        sortCollection(collection1, printer);
        });
    std::thread t2([&printer, &collection2]() {
        sortCollection(collection2, printer);
        });
    std::thread t3([&printer, &collection3]() {
        sortCollection(collection3, printer);
        });

    t1.join();
    t2.join();
    t3.join();

    return 0;
}