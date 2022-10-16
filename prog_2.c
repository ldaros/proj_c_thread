#include <stdio.h>

// Controle a execução de um programa externo. Crie um shell script e configure
// o programa em C para realizar a chamada do mesmo em um processo filho;
int main(int argc, char const *argv[]) {
  // cria um processo filho.
  int pid = fork();

  if (pid == 0) {
    printf("Processo filho [PID - %d] \n", getpid());

    // syscall para executar um programa externo.
    execlp("./prog_2.sh", "prog_2.sh", NULL);
  }

  else {
    printf("Processo pai [PID - %d] \n", getpid());
  }

  return 0;
}
