// Utilizando named pipes crie um processo (writer) que envie o valor numérico
// para o processo de outro programa (reader). No programa cliente verifique se
// o valor enviado é um número perfeito;

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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

  // cria um fifo
  mkfifo(path, 0666);

  // buffer de escrita
  char buffer[30];

  while (1) {
    // abre o fifo para escrita
    fd = open(path, O_WRONLY);

    // recebe um valor do usuário
    printf("Digite um valor: ");
    scanf("%s", buffer);

    // escreve o valor no fifo
    write(fd, buffer, strlen(buffer) + 1);

    // fecha o fifo
    close(fd);
  }

  return 0;
}
