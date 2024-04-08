#include "livro.h"
#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void editarLivro(Livro *cabecaLivros) {
  char titulo[500];
  printf("\033[2J\033[H");
  printf("Editar Livro\n");
  printf("Digite o título do livro que deseja editar: ");
  scanf(" %[^\n]", titulo);

  Livro *atual = cabecaLivros;
  while (atual != NULL) {
    if (strcmp(atual->titulo, titulo) == 0) {
      printf("Digite o novo título do livro: ");
      scanf(" %[^\n]", atual->titulo);
      printf("Digite o novo autor do livro: ");
      scanf(" %[^\n]", atual->autor);
      printf("Digite a nova editora do livro: ");
      scanf(" %[^\n]", atual->editora);
      printf("Digite o novo ano de publicação do livro: ");
      scanf("%d", &atual->anoPublicacao);
      printf("Digite o novo número de cópias do livro: ");
      scanf("%d", &atual->copias);
      return;
    }
    atual = atual->prox;
  }
  printf("Livro não encontrado.\n");
}

void buscarLivro() {
  char titulo[500];
  printf("\033[2J\033[H");
  printf("Buscar Livro\n");
  printf("Digite o título do livro que deseja buscar: ");
  scanf(" %[^\n]", titulo);

  FILE *arquivo;
  arquivo = fopen("livros.txt", "r");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  Livro livroAtual;
  while (fscanf(arquivo, "%[^\t] \t %[^\t] \t %[^\t] \t %d \t %d\n",
                livroAtual.titulo, livroAtual.autor, livroAtual.editora,
                &livroAtual.anoPublicacao, &livroAtual.copias) == 5) {
    if (strcmp(livroAtual.titulo, titulo) == 0) {
      printf("\nTítulo: %s\n", livroAtual.titulo);
      printf("Autor: %s\n", livroAtual.autor);
      printf("Editora: %s\n", livroAtual.editora);
      printf("Ano de Publicação: %d\n", livroAtual.anoPublicacao);
      printf("Quantidade de cópias disponíveis: %d\n\n", livroAtual.copias);
      fclose(arquivo);
      return;
    }
  }
  fclose(arquivo);
  printf("Livro não encontrado.\n");
}

void emprestarLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros) {
  char titulo[500];
  char usuarioNome[500];

  printf("\033[2J\033[H");
  printf("Emprestar Livro\nDigite o nome do seu usuário:\n");
  scanf(" %[^\n]", usuarioNome);

  Usuario *usuarioAtual = cabecaUsuarios;
  while (usuarioAtual != NULL) {
    if (strcmp(usuarioAtual->nome, usuarioNome) == 0) {
      printf("Digite o título do livro que deseja pegar emprestado: ");
      scanf(" %[^\n]", titulo);

      Livro *livroAtual = *cabecaLivros;
      while (livroAtual != NULL) {
        if (strcmp(livroAtual->titulo, titulo) == 0 &&
            livroAtual->copias != 0) {
          if (strcmp(usuarioAtual->livrosEmprestados, "|Nenhum") == 0) {
            strcpy(usuarioAtual->livrosEmprestados, "");
          }
          char detalhesLivro[2000];
          sprintf(detalhesLivro, "|%s\t%s\t%s\t%d ", livroAtual->titulo,
                  livroAtual->autor, livroAtual->editora,
                  livroAtual->anoPublicacao);
          strcat(usuarioAtual->livrosEmprestados, detalhesLivro);
          printf("Livro emprestado com sucesso\n\n");
          livroAtual->copias--;
          return;
        }
        livroAtual = livroAtual->prox;
      }
      printf("Livro não encontrado ou não disponível.\n\n");
      return;
    }
    usuarioAtual = usuarioAtual->prox;
  }
  printf("Usuário não encontrado.\n\n");
}

void devolverLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros) {
  char titulo[500];
  char nome[500];

  printf("\033[2J\033[H");
  printf("Devolver Livro\n");
  printf("Digite o seu usuário: ");
  scanf(" %[^\n]", nome);
  printf("Digite o título do livro que deseja devolver: ");
  scanf(" %[^\n]", titulo);

  Usuario *usuarioAtual = cabecaUsuarios;
  while (usuarioAtual != NULL) {
    if (strcmp(usuarioAtual->nome, nome) == 0) {
      char *livrosEmprestados = usuarioAtual->livrosEmprestados;
      char *livroEmprestado = strtok(livrosEmprestados, "|");
      while (livroEmprestado != NULL) {
        char tempTitulo[500];
        sscanf(livroEmprestado, "%[^'\t']", tempTitulo);
        if (strcmp(tempTitulo, titulo) == 0) {
          strcpy(livroEmprestado, "");
          Livro *livroAtual = *cabecaLivros;
          while (livroAtual != NULL) {
            if (strcmp(livroAtual->titulo, titulo) == 0) {
              livroAtual->copias++;
              printf("Livro \"%s\" devolvido com sucesso!\n\n", titulo);
              return;
            }
            livroAtual = livroAtual->prox;
          }
          printf("Livro não encontrado.\n\n");
          return;
        }
        livroEmprestado = strtok(NULL, "|");
      }
      return;
    }
    usuarioAtual = usuarioAtual->prox;
  }
  printf("Usuário \"%s\" não encontrado.\n\n", nome);
}

void ordenarAlfabeticamente(Usuario **cabecaUsuarios) {
  if (*cabecaUsuarios == NULL || (*cabecaUsuarios)->prox == NULL) {
    return;
  }

  Usuario *atual, *proximo;
  int trocado;
  char tempString[500];

  do {
    trocado = 0;
    atual = *cabecaUsuarios;

    while (atual->prox != NULL) {
      proximo = atual->prox;

      if (strcmp(atual->nome, proximo->nome) > 0) {
        strcpy(tempString, atual->nome);
        strcpy(atual->nome, proximo->nome);
        strcpy(proximo->nome, tempString);

        strcpy(tempString, atual->contato);
        strcpy(atual->contato, proximo->contato);
        strcpy(proximo->contato, tempString);

        strcpy(tempString, atual->livrosEmprestados);
        strcpy(atual->livrosEmprestados, proximo->livrosEmprestados);
        strcpy(proximo->livrosEmprestados, tempString);

        trocado = 1;
      }

      atual = atual->prox;
    }
  } while (trocado);
}
