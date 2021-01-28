#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

// pid < 0, erro
// pid == 0, filho
// pid > 0, pai



int main() {
    pid_t fatherPid = fork();

    if (fatherPid < 0) {  // erro
        std::cout << "Erro ao criar processo\n";
        return 1;
    } else if (fatherPid == 0) {  // filho 1
        id_t sonPid = fork();

        if (sonPid < 0) {  //erro
            std::cout << "Erro ao criar processo\n";
            return 1;
        } else if (sonPid == 0) {  // neto 1
            //id_t sonPid = fork();
            printf("Essa é a execução do filho(PID=%d), cujo pai tem PID=%d\n", gettid(), getppid());
        } else {    // filho 1
            // end
        }
        printf("Essa é a execução do filho(PID=%d), cujo pai tem PID=%d\n", gettid(), getppid());
    } else {    // pai
        // wait(nullptr);
        id_t son2Pid = fork();

        if (son2Pid < 0) {  // erro
            std::cout << "Erro ao criar processo\n";
            return 1;
        } else if (son2Pid == 0) {  // filho 2
            id_t GC2 = fork();
            if (GC2 < 0) {  //erro
                std::cout << "Erro ao criar processo\n";
                return 1;
            } else if (GC2 == 0) {  // neto 2
                //id_t sonPid = fork();
                printf("Essa é a execução do filho(PID=%d), cujo pai tem PID=%d\n", gettid(), getppid());
            } else {    // filho 2
                // end
            }
            printf("Essa é a execução do filho(PID=%d), cujo pai tem PID=%d\n", gettid(), getppid());
        } else {    // pai
            // end
        }
    }
    return 0;
}