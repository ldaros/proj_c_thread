// Crie um programa em C que implemente duas threads (writer/reader) que se
// comuniquem através de pipes. O valor enviado pelo primeiro thread deverá
// estar no intervalo de 1 a 12. A thread que receber esse valor (reader) deverá
// exibir uma mensagem dizendo a que mês do ano esse valor se refere;

// COMPILAR COM A FLAG -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// array de meses
char *months[] = {"Janeiro",  "Fevereiro", "Março",    "Abril",
                  "Maio",     "Junho",     "Julho",    "Agosto",
                  "Setembro", "Outubro",   "Novembro", "Dezembro"};

void *writer(void *arg) {
  // file descriptor, passado como argumento
  int fd = *((int *)arg);

  // buffer de escrita
  char buffer[30];

  while (1) {
    // lê o valor do usuário
    scanf("%s", buffer);

    // escreve o valor no pipe
    write(fd, buffer, sizeof(buffer));

    // sai do loop
    if (buffer[0] == '0') break;
  }

  // fecha o pipe e termina a thread
  close(fd);
  return NULL;
}

void *reader(void *arg) {
  // file descriptor, passado como argumento
  int fd = *((int *)arg);

  // buffer de leitura
  char buffer[30];

  while (1) {
    // lê o valor do pipe
    read(fd, buffer, sizeof(buffer));

    // converte para inteiro
    int n = atoi(buffer);

    // sai do loop
    if (n == 0) break;

    // verifica se o valor está no intervalo
    if (n > 0 && n < 13) {
      // exibe o mês
      printf("\n %s \n", months[n - 1]);
    } else {
      printf("\n Número inválido \n");
    }
  }

  // fecha o pipe e termina a thread
  close(fd);
  return NULL;
}

int main(int argc, char const *argv[]) {
  // criando os pipes
  int fd[2];
  pipe(fd);

  // criando os threads
  pthread_t writer_thread, reader_thread;

  // inicializando os threads
  pthread_create(&reader_thread, NULL, reader, &fd[0]);
  pthread_create(&writer_thread, NULL, writer, &fd[1]);

  // espera os threads terminarem
  pthread_join(writer_thread, NULL);
  pthread_join(reader_thread, NULL);

  return 0;
}
