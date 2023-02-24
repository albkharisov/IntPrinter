#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

class IntPrinter {
    std::mutex& m;
    std::condition_variable& cv;
    int print_value;
    int& counter;
    static int max_value;

public:
    IntPrinter(std::condition_variable& cv, std::mutex& m, int& counter) : cv(cv), m(m), counter(counter) {
        std::unique_lock<std::mutex> lock(m);
        print_value = max_value;
        ++max_value;
    }
    void operator()() {
        while(1) {
            std::unique_lock<std::mutex> lock(m);
            cv.wait(lock, [&](){return print_value == counter;});
            std::cout << print_value + 1 << std::endl;
            sleep(1);
            counter = (counter < max_value - 1) ? counter + 1 : 0;
            cv.notify_all();
        }
    }
};

int IntPrinter::max_value;

int main() {
    std::mutex m;
    std::condition_variable cv;
    int counter = 0;

    std::thread t1(IntPrinter(cv, m, counter));
    std::thread t2(IntPrinter(cv, m, counter));
    std::thread t3(IntPrinter(cv, m, counter));

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

