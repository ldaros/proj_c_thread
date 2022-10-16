// prog_3.c
//
// Utilizando pipes crie um programa que envie um valor numérico para o processo
// filho. Ao receber o valor, o processo filho deverá calcular o fatorial do
// mesmo e exibir o valor;

#include <stdio.h>
#include <unistd.h>

// função factorial
int factorial(int n) {
  if (n == 0) {
    return 1;
  }

  return n * factorial(n - 1);
}

int main(int argc, char const *argv[]) {
  // file descriptors
  int fd[2];

  // cria um pipe
  pipe(fd);

  // cria um processo filho
  int pid = fork();

  if (pid == 0) {
    // fecha o lado de escrita do pipe
    close(fd[1]);

    // lê o valor do pipe
    int n;
    read(fd[0], &n, sizeof(n));

    // fecha o lado de leitura do pipe
    close(fd[0]);

    // calcula o fatorial do valor lido
    int f = factorial(n);

    // exibe o valor
    printf("Fatorial de %d: %d \n", n, f);
  }

  else {
    // fecha o lado de leitura do pipe
    close(fd[0]);

    // escreve o valor no pipe
    int n = 5;
    write(fd[1], &n, sizeof(n));

    // fecha o lado de escrita do pipe
    close(fd[1]);
  }

  return 0;
}
