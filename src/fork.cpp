#include<iostream>
#include <unistd.h>
#include <ctime>
#include <chrono>
#include <sstream>

// pid < 0, error
// pid == 0, son
// pid > 0, father

void lastNode(const std::string &nodeName, int nodeTTL);

void
intermediateNode(const std::string &nodeName, const std::string &childName, int childBirthTime,
                 int childTTL, int nodeTTL,
                 std::chrono::time_point<std::chrono::high_resolution_clock> parentBirth);

void
firstNode(const std::string &parentNode, const std::string &nodeName, const std::string &childName,
          int childBirthTime, int childTTL, int parentTTL, int nodeTTL,
          std::chrono::time_point<std::chrono::high_resolution_clock> parentBirth);

void fathersAge(std::chrono::time_point<std::chrono::high_resolution_clock> birth);

std::string timeToStr(std::chrono::time_point<std::chrono::high_resolution_clock> time);

void
kill(const std::string &nodeName, std::chrono::time_point<std::chrono::high_resolution_clock> birth);

int main() {
    std::chrono::time_point<std::chrono::high_resolution_clock> fathersBirth = std::chrono::system_clock::now();
    std::cout << "+ fathers birth: " << timeToStr(fathersBirth) << '\n';

    sleep(14);
    fathersAge(fathersBirth); // 14

    pid_t pid = fork();

    if (pid < 0) {
        std::cout << "error when creating " << "child 1" << "\n";
        exit(-1);
    } else if (pid == 0) {
        intermediateNode("child 1", "grandchild 1", 12, 18, 18, fathersBirth);
        exit(0);
    } else {
        sleep(2);
        fathersAge(fathersBirth); // 16

        firstNode("father", "child 2", "grandchild 2", 14, 12, 44, 16, fathersBirth);
        exit(1);
    }
}

std::string timeToStr(std::chrono::time_point<std::chrono::high_resolution_clock> time) {
    std::time_t t = std::chrono::system_clock::to_time_t(time);

    std::tm *now = std::localtime(&t);

    std::ostringstream s;
    s << now->tm_hour << ':'
      << now->tm_min << ':'
      << now->tm_sec;

    return s.str();
}

void fathersAge(std::chrono::time_point<std::chrono::high_resolution_clock> birth) {
    std::chrono::time_point<std::chrono::high_resolution_clock> death = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = death - birth;

    std::cout << "father has " << int(elapsed_seconds.count()) << " years\n";
}

void firstNode(const std::string &parentNode, const std::string &nodeName, const std::string &childName,
               const int childBirthTime, const int childTTL, const int parentTTL, const int nodeTTL,
               std::chrono::time_point<std::chrono::high_resolution_clock> parentBirth) {
    pid_t pid = fork();

    if (pid < 0) {
        std::cout << "error when creating " << nodeName << "\n";
        exit(-1);
    } else if (pid == 0) {
        intermediateNode(nodeName, childName, childBirthTime, childTTL, nodeTTL, parentBirth);
        exit(0);
    } else {
        // father
        sleep(parentTTL);
        fathersAge(parentBirth);  // 60 years
        kill(parentNode, parentBirth);
        exit(1);
    }
}

void intermediateNode(const std::string &nodeName, const std::string &childName, const int childBirthTime,
                      const int childTTL, const int nodeTTL,
                      std::chrono::time_point<std::chrono::high_resolution_clock> parentBirth) {

    std::chrono::time_point<std::chrono::high_resolution_clock> birth = std::chrono::system_clock::now();
    std::cout << "+ " << nodeName << " birth: " << timeToStr(birth) << '\n';

    sleep(childBirthTime);
    fathersAge(parentBirth); // 26

    pid_t pid = fork();

    if (pid < 0) {
        std::cout << "error when creating " << childName << "\n";
        exit(-1);
    } else if (pid == 0) {
        lastNode(childName, childTTL);
        exit(0);
    } else {
        sleep(nodeTTL);
        kill(nodeName, birth);
        exit(1);
    }
}

void kill(const std::string &nodeName, const std::chrono::time_point<std::chrono::high_resolution_clock> birth) {
    std::chrono::time_point<std::chrono::high_resolution_clock> death = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = death - birth;

    std::cout << "- " << nodeName << " died: " << timeToStr(death)
              << " --- " << nodeName << " was born: " << timeToStr(birth)
              << " --- " << nodeName << " lived: " << int(elapsed_seconds.count()) << "s\n";
}

void lastNode(const std::string &nodeName, const int nodeTTL) {
    std::chrono::time_point<std::chrono::high_resolution_clock> birth = std::chrono::system_clock::now();
    std::cout << "+ " << nodeName << " birth: " << timeToStr(birth) << '\n';

    sleep(nodeTTL);
    kill(nodeName, birth);
}