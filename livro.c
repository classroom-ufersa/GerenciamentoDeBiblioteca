#include "livro.h"
#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>

void editarLivro(Livro *livros, int numLivros) {
  char titulo[50];
  printf("\033[2J\033[H");
  printf("Editar Livro\n");
  printf("Digite o título do livro que deseja editar: ");
  scanf("%s", titulo);
  for (int i = 0; i < numLivros; i++) {
    if (strcmp(livros[i].titulo, titulo) == 0) {
      printf("Digite o novo título do livro: ");
      scanf("%s", livros[i].titulo);
      printf("Digite o jogo autor do livro: ");
      scanf("%s", livros[i].autor);
      printf("Digite a nova editora do livro: ");
      scanf("%s", livros[i].editora);
      printf("Digite o novo ano de publicação do livro: ");
      scanf("%d", &livros[i].anoPublicacao);
      return;
    }
  }
  printf("Livro não encontrado.\n");
}

void buscarLivro(Livro *livros, int numLivros) {
  char titulo[50];
  printf("\033[2J\033[H");
  printf("Buscar Livro\n");
  printf("Digite o título do livro que deseja buscar: ");
  scanf("%s", titulo);
  for (int i = 0; i < numLivros; i++) {
    if (strcmp(livros[i].titulo, titulo) == 0) {
      printf("Título: %s\n", livros[i].titulo);
      printf("Autor: %s\n", livros[i].autor);
      printf("Editora: %s\n", livros[i].editora);
      printf("Ano de Publicação: %d\n", livros[i].anoPublicacao);
      return;
    }
  }
}

void emprestarLivro(Usuario *usuarios, Livro *livros, int numLivros) {
  char titulo[50];
  char usuarioNome[50];
  int encontrado = 0;

  printf("\033[2J\033[H");
  printf("Emprestar Livro\n");
  printf("Digite o título do livro que deseja emprestar: ");
  scanf("%s", titulo);

  for (int i = 0; i < numLivros; i++) {
    if (strcmp(livros[i].titulo, titulo) == 0) {
      printf("Digite o nome do usuário para emprestar o livro: ");
      scanf("%s", usuarioNome);

      for (int j = 0; j < numLivros; j++) {
        if (strcmp(usuarios[j].nome, usuarioNome) == 0) {
          strcpy(usuarios[j].livrosEmprestados, titulo);
          printf("Livro emprestado com sucesso para o usuário: %s\n",
                 usuarioNome);
          encontrado = 1;
          break;
        }
      }

      if (!encontrado) {
        printf("Usuário não encontrado.\n");
      }
      return;
    }
  }

  printf("Livro não encontrado.\n");
}

void devolverLivro(Usuario *usuarios, Livro *livros, int numLivros) {
  char titulo[50];
  printf("\033[2J\033[H");
  printf("Devolver Livro\n");
  printf("Digite o livro que deseja devolver: \n");
  scanf("%s", titulo);
  for (int i = 0; i < numLivros; i++) {
    if (strcmp(usuarios[i].livrosEmprestados, titulo) == 0) {
      strcpy(usuarios[i].livrosEmprestados, "");
      printf("Livro devolvido com sucesso!\n");
      return;
    }
  }
  printf("Livro não encontrado ou não está emprestado.\n");
}

void adicionarListaEmOrdemAlfabetica(Usuario *usuarios, int numUsuarios, Livro *livros, int numLivros) {
  int i, j;
  char tempNome[50];

  for (i = 0; i < numUsuarios; i++) {
    for (j = i + 1; j < numUsuarios; j++) {
      if (strcmp(usuarios[i].nome, usuarios[j].nome) > 0) {
        strcpy(tempNome, usuarios[i].nome);
        strcpy(usuarios[i].nome, usuarios[j].nome);
        strcpy(usuarios[j].nome, tempNome);
      }
    }
  }
}