#include "usuario.h"
#include "livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionarUsuario(Usuario *usuarios, int *numUsuarios) {
  printf("\033[2J\033[H");
  printf("Adicionar Usuário\n");
  printf("Digite o nome do usuário: ");
  scanf("%s", usuarios[*numUsuarios].nome);
  printf("Digite o contato do usuário: ");
  scanf("%d", &usuarios[*numUsuarios].contato);
  (*numUsuarios)++;
  printf("Usuário adicionado!\n\n");
}

void removerUsuario(Usuario *usuarios, int *numUsuarios) {
  char nome[50];
  printf("\033[2J\033[H");
  printf("Remover Usuário\n");
  printf("Digite o nome do usuário que deseja remover: ");
  scanf("%s", nome);
  for (int i = 0; i < *numUsuarios; i++) {
    if (strcmp(usuarios[i].nome, nome) == 0) {
      strcpy(usuarios[i].nome, "");
      numUsuarios--;
    }
  }
}

void copiarDados(Usuario *usuarios, int *numUsuarios, Livro *livros,
                 int *numLivros) {
  const char *dadosUsuarios = "usuarios.txt";
  const char *dadosLivros = "livros.txt";

  FILE *Usuarios = fopen(dadosUsuarios, "r");
  FILE *Livros = fopen(dadosLivros, "r");

  if (Usuarios == NULL || Livros == NULL) {
    printf("Erro ao abrir os arquivos\n");
    return;
  }

  *numUsuarios = 0;
  *numLivros = 0;

  while (*numUsuarios < 100 &&
         fscanf(Usuarios, "%s - %d - %s", usuarios[*numUsuarios].nome,
                &usuarios[*numUsuarios].contato,
                usuarios[*numUsuarios].livrosEmprestados) == 3) {
    (*numUsuarios)++;
  }

  while (*numLivros < 100 &&
         fscanf(Livros, "%s - %s - %s - %d\n", livros[*numLivros].titulo,
                livros[*numLivros].autor, livros[*numLivros].editora,
                &livros[*numLivros].anoPublicacao) == 4) {
    (*numLivros)++;
  }

  fclose(Usuarios);
  fclose(Livros);
}

void escreverDados(Usuario *usuarios, int *numUsuarios, Livro *livros,
                   int *numLivros) {
  const char *dadosUsuarios = "usuarios.txt";
  const char *dadosLivros = "livros.txt";

  FILE *Usuarios = fopen(dadosUsuarios, "w");
  FILE *Livros = fopen(dadosLivros, "w");

  if (Usuarios == NULL || Livros == NULL) {
    printf("Erro");
    return;
  }

  for (int i = 0; i < *numUsuarios; i++) {
    if (strcmp(usuarios[i].livrosEmprestados, "") == 0) {
      fprintf(Usuarios, "%s - %d - Nenhum\n", usuarios[i].nome,
              usuarios[i].contato);
    } else if (strcmp(usuarios[i].nome, "") == 0) {

    } else {
      fprintf(Usuarios, "%s - %d - %s\n", usuarios[i].nome, usuarios[i].contato,
              usuarios[i].livrosEmprestados);
    }
  }

  for (int i = 0; i < *numLivros; i++) {
    fprintf(Livros, "%s - %s - %s - %d\n", livros[i].titulo, livros[i].autor,
            livros[i].editora, livros[i].anoPublicacao);
  }

  fclose(Usuarios);
  fclose(Livros);
}

void Sair(Usuario *usuarios, int *numUsuarios, Livro *livros, int *numLivros) {
  adicionarListaEmOrdemAlfabetica(usuarios, *numUsuarios, livros, *numLivros);
  escreverDados(usuarios, numUsuarios, livros, numLivros);
  printf("Saindo...");
  return;
}
