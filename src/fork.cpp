#include<iostream>
#include <unistd.h>
#include <ctime>
#include <chrono>
#include <sstream>

// pid < 0, error
// pid == 0, son
// pid > 0, father

std::string timeToStr(std::time_t *t) {
    if (nullptr == t) {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        t = &time;
    }

    std::tm *now = std::localtime(t);

    std::ostringstream s;
    s << now->tm_hour << ':'
      << now->tm_min << ':'
      << now->tm_sec;

    return s.str();
}

int main() {
    auto fathersBirth = std::chrono::system_clock::now();
    std::time_t fathersBirthTime = std::chrono::system_clock::to_time_t(fathersBirth);
    std::cout << "+ fathers birth: " << timeToStr(&fathersBirthTime) << '\n';

    sleep(14);
    std::cout << "father has 14 years\n";

    pid_t fatherPid = fork();

    if (fatherPid < 0) {
        std::cout << "error when creating child 1\n";
        exit(-1);
    } else if (fatherPid == 0) {
        auto son1Birth = std::chrono::system_clock::now();
        std::time_t son1BirthTime = std::chrono::system_clock::to_time_t(son1Birth);
        std::cout << "+ son 1 birth: " << timeToStr(&son1BirthTime) << '\n';

        sleep(12);// son 1 has 12
        std::cout << "father has 26 years\n";

        pid_t son1Pid = fork();

        if (son1Pid < 0) {
            std::cout << "error when creating grandchild 1\n";
            exit(-1);
        } else if (son1Pid == 0) {
            auto gc1Birth = std::chrono::system_clock::now();
            std::time_t gc1BirthTime = std::chrono::system_clock::to_time_t(gc1Birth);
            std::cout << "+ grandchild 1 birth: " << timeToStr(&gc1BirthTime) << '\n';

            sleep(18);   // grandchildren 1 has 18

            auto gc1Death = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = gc1Death - gc1Birth;
            std::time_t end_time = std::chrono::system_clock::to_time_t(gc1Death);

            std::cout << "- grandchild 1 died: " << timeToStr(&end_time)
                      << " --- grandchild 1 lived: " << elapsed_seconds.count() << "s\n";

            exit(0);
        } else {
            sleep(18);  // son 1 has 30

            auto son1Death = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = son1Death - son1Birth;
            std::time_t end_time = std::chrono::system_clock::to_time_t(son1Death);

            std::cout << "- son 1 died: " << timeToStr(&end_time)
                      << " --- son 1 lived: " << elapsed_seconds.count() << "s\n";

            exit(1);
        }
    } else {
        // father
        sleep(2);   // father has 16 years
        std::cout << "father has 16 years\n";

        pid_t son2Pid = fork();

        if (son2Pid < 0) {
            std::cout << "error when creating son 2\n";
            exit(-1);
        } else if (son2Pid == 0) {
            auto son2Birth = std::chrono::system_clock::now();
            std::time_t son2BirthTime = std::chrono::system_clock::to_time_t(son2Birth);
            std::cout << "+ son 2 birth: " << timeToStr(&son2BirthTime) << '\n';


            sleep(14);   // son 2 has 14
            std::cout << "father has 30 years\n";

            pid_t gc2Pid = fork();

            if (gc2Pid < 0) {
                std::cout << "error when creating grandchild 2\n";
                exit(-1);
            } else if (gc2Pid == 0) {
                auto gc2Birth = std::chrono::system_clock::now();
                std::time_t gc2BirthTime = std::chrono::system_clock::to_time_t(gc2Birth);
                std::cout << "+ grandchild 2 birth: " << timeToStr(&gc2BirthTime) << '\n';

                sleep(12);   //grandchildren 2 has 12

                auto gc2Death = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = gc2Death - gc2Birth;
                std::time_t end_time = std::chrono::system_clock::to_time_t(gc2Death);

                std::cout << "- grandchild 2 died: " << timeToStr(&end_time)
                          << " --- grandchild 2 lived: " << elapsed_seconds.count() << "s\n";

                exit(0);
            } else {
                sleep(16);   // son 2 has 30

                auto son2Death = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = son2Death - son2Birth;
                std::time_t end_time = std::chrono::system_clock::to_time_t(son2Death);

                std::cout << "- son 2 died: " << timeToStr(&end_time)
                          << " --- son 2 lived: " << elapsed_seconds.count() << "s\n";

                exit(1);
            }
        } else {
            // father
            sleep(44);   // father has 16 years
            std::cout << "father has 60 years\n";

            auto fatherDeath = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = fatherDeath - fathersBirth;
            std::time_t end_time = std::chrono::system_clock::to_time_t(fatherDeath);

            std::cout << "- father died: " << timeToStr(&end_time)
                      << " --- father lived: " << elapsed_seconds.count() << "s\n";

            exit(1);
        }
    }
}