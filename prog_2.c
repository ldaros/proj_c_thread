// prog_2.c
//
// Controle a execução de um programa externo. Crie um shell script e configure
// o programa em C para realizar a chamada do mesmo em um processo filho;

#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  // cria um processo filho.
  int pid = fork();

  if (pid == 0) {
    // exibindo o PID do processo filho.
    printf("Processo filho [PID - %d] \n", getpid());

    // syscall para executar um programa externo.
    execlp("./prog_2.sh", "prog_2.sh", NULL);
  }

  else {
    // exibindo o PID do processo pai.
    printf("Processo pai [PID - %d] \n", getpid());
  }

  return 0;
}
