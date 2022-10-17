// Utilizando named pipes crie um processo (writer) que envie o valor numérico
// para o processo de outro programa (reader). No programa cliente verifique se
// o valor enviado é um número perfeito;

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>c  

// função que verifica se um número é perfeito
int is_perfect(int n) {
  int sum = 0;

  for (int i = 1; i < n; i++) {
    if (n % i == 0) {
      sum += i;
    }
  }

  return sum == n;
}

int main(int argc, char const *argv[]) {
  // file descriptor
  int fd;

  // caminho do fifo
  char *path = "/tmp/fifo";

  // cria o fifo
  mkfifo(path, 0666);

  // buffer de leitura
  char buffer[30];

  while (1) {
    // abre o fifo para leitura
    fd = open(path, O_RDONLY);

    // lê o valor do fifo
    read(fd, buffer, sizeof(buffer));

    // fecha o fifo
    close(fd);

    // converte o valor lido para inteiro
    int n = atoi(buffer);

    // verifica se o valor é perfeito
    if (is_perfect(n)) {
      printf("\n %d é um número perfeito \n", n);
    } else {
      printf("\n %d não é um número perfeito \n", n);
    }
  }

  return 0;
}
