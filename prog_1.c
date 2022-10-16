// prog_1.c
//
// Gere um processo pai e filho e exibam os respectivos PIDs.

#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  // fork é uma chamada de sistema que cria um processo filho.
  int pid = fork();

  // o codigo abaixo é executado por ambos os processos.

  // se pid == 0, então estamos no processo filho.
  if (pid == 0) {
    printf("Processo filho [PID - %d] \n", getpid());
  }

  // se não estamos no processo pai.
  else {
    printf("Processo pai [PID - %d] \n", getpid());
  }

  return 0;
}
