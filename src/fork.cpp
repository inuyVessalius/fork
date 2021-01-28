#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
#include <ctime>
#include <chrono>

// pid < 0, erro
// pid == 0, filho
// pid > 0, pai


//auto start = std::chrono::system_clock::now();
//// Some computation here
//auto end = std::chrono::system_clock::now();
//
//std::chrono::duration<double> elapsed_seconds = end-start;
//std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//
//std::cout << "died: " << std::ctime(&end_time)
//<< "lived: " << elapsed_seconds.count() << "s\n";

int main() {
    auto fathersBirth = std::chrono::system_clock::now();
    std::time_t fathersBirthTime = std::chrono::system_clock::to_time_t(fathersBirth);
    std::cout << "fathers birth: " << std::ctime(&fathersBirthTime);

    sleep(14);  // father has 14 years
    pid_t fatherPid = fork();

    if (fatherPid < 0) {
        std::cout << "error when creating child 1\n";
        exit(-1);
    } else if (fatherPid == 0) {
        auto son1Birth = std::chrono::system_clock::now();
        std::time_t son1BirthTime = std::chrono::system_clock::to_time_t(son1Birth);
        std::cout << "son 1 birth: " << std::ctime(&son1BirthTime);

        sleep(12);// father has 26 years, son 1 has 12

        pid_t son1Pid = fork();

        if (son1Pid < 0) {
            std::cout << "error when creating grandchild 1\n";
            exit(-1);
        } else if (son1Pid == 0) {
            auto gc1Birth = std::chrono::system_clock::now();
            std::time_t gc1BirthTime = std::chrono::system_clock::to_time_t(gc1Birth);
            std::cout << "grandchild 1 birth: " << std::ctime(&gc1BirthTime);

            sleep(18);   // grandchildren 1 has 18

            auto gc1Death = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = gc1Death - gc1Birth;
            std::time_t end_time = std::chrono::system_clock::to_time_t(gc1Death);

            std::cout << "grandchild 1 died: " << std::ctime(&end_time)
                      << "grandchild 1 lived: " << elapsed_seconds.count() << "s\n";

            exit(0);
        } else {
            sleep(18);   // son 1 has 30

            auto son1Death = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = son1Death - son1Birth;
            std::time_t end_time = std::chrono::system_clock::to_time_t(son1Death);

            std::cout << "son 1 died: " << std::ctime(&end_time)
                      << "son 1 lived: " << elapsed_seconds.count() << "s\n";

            exit(1);
        }
    } else {
        // codigo pai
        sleep(2);   // father has 16 years

        pid_t son2Pid = fork();

        if (son2Pid < 0) {
            std::cout << "error when creating son 2\n";
            exit(-1);
        } else if (son2Pid == 0) {
            auto son2Birth = std::chrono::system_clock::now();
            std::time_t son2BirthTime = std::chrono::system_clock::to_time_t(son2Birth);
            std::cout << "son 2 birth: " << std::ctime(&son2BirthTime);


            sleep(14);   // father has 30 years, son 2 has 14

            pid_t gc2Pid = fork();

            if (gc2Pid < 0) {
                std::cout << "error when creating grandchild 2\n";
                exit(-1);
            } else if (gc2Pid == 0) {
                auto gc2Birth = std::chrono::system_clock::now();
                std::time_t gc2BirthTime = std::chrono::system_clock::to_time_t(gc2Birth);
                std::cout << "grandchild 2 birth: " << std::ctime(&gc2BirthTime);

                sleep(12);   //grandchildren 2 has 12

                auto gc2Death = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = gc2Death - gc2Birth;
                std::time_t end_time = std::chrono::system_clock::to_time_t(gc2Death);

                std::cout << "grandchild 2 died: " << std::ctime(&end_time)
                          << "grandchild 2 lived: " << elapsed_seconds.count() << "s\n";

                exit(0);
            } else {
                sleep(16);   //son 2 has 30

                auto son2Death = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = son2Death - son2Birth;
                std::time_t end_time = std::chrono::system_clock::to_time_t(son2Death);

                std::cout << "grandchild 2 died: " << std::ctime(&end_time)
                          << "grandchild 2 lived: " << elapsed_seconds.count() << "s\n";

                exit(1);
            }

            exit(0);
        } else {
            // codigo pai
            sleep(44);   // father has 16 years

            auto fatherDeath = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = fatherDeath - fathersBirth;
            std::time_t end_time = std::chrono::system_clock::to_time_t(fatherDeath);

            std::cout << "father died: " << std::ctime(&end_time)
                      << "father lived: " << elapsed_seconds.count() << "s\n";

            exit(1);
        }
    }
}