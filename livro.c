#include "livro.h"
#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void editarLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros) {
  char titulo[500];
  printf("\033[2J\033[H");
  printf("| Editar Livro\n");
  printf("| Digite o titulo do livro que deseja editar:\n| -> ");
  scanf(" %[^\n]", titulo);
  if (verificar(titulo, 0)) {
    return;
  }

  Livro *atual = *cabecaLivros;

  while (atual != NULL) {
    if (strcmp(atual->titulo, titulo) == 0) {
      printf("Digite o novo titulo do livro: ");
      scanf(" %[^\n]", atual->titulo);
      if (verificar(atual->titulo, 0)) {
        return;
      }
      printf("Digite o novo autor do livro: ");
      scanf(" %[^\n]", atual->autor);
      if (verificar(atual->autor, 0)) {
        return;
      }
      printf("Digite a nova editora do livro: ");
      scanf(" %[^\n]", atual->editora);
      if (verificar(atual->editora, 0)) {
        return;
      }
      printf("Digite o novo ano de publicacao do livro: ");
      scanf("%d", &atual->anoPublicacao);
      if (verificar(atual->editora, 0)) {
        return;
      }
      printf("Digite o novo numero de cópias do livro: ");
      scanf("%d", &atual->copias);
      if (verificar(atual->editora, 0)) {
        return;
      }
      return;
    }
    atual = atual->prox;
  }
  printf("| Livro não encontrado.\n|\n");
}

void buscarLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros) {
  char titulo[500];
  printf("\033[2J\033[H");
  printf("| Buscar Livro\n");
  printf("| Digite o título do livro que deseja buscar:\n| -> ");
  scanf(" %[^\n]", titulo);

  if (verificar(titulo, 0)) {
    return;
  }

  FILE *arquivo;
  arquivo = fopen("livros.txt", "r");

  if (arquivo == NULL) {
    printf("| Erro ao abrir o arquivo.\n|\n");
    return;
  }

  Livro livroAtual;
  while (fscanf(arquivo, "%[^\t] \t %[^\t] \t %[^\t] \t %d \t %d\n",
                livroAtual.titulo, livroAtual.autor, livroAtual.editora,
                &livroAtual.anoPublicacao, &livroAtual.copias) == 5) {
    if (strcmp(livroAtual.titulo, titulo) == 0) {
      printf("\n| Titulo: %s\n", livroAtual.titulo);
      printf("| Autor: %s\n", livroAtual.autor);
      printf("| Editora: %s\n", livroAtual.editora);
      printf("| Ano de Publicacao: %d\n", livroAtual.anoPublicacao);
      printf("| Quantidade de copias disponiveis: %d\n|\n", livroAtual.copias);
      fclose(arquivo);
      return;
    }
  }
  fclose(arquivo);
  printf("Livro nao encontrado.\n");
}

void emprestarLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros) {
  char titulo[500];
  char usuarioNome[500];

  printf("\033[2J\033[H");
  printf("| Emprestar Livro\n| Digite o nome do seu usuario:\n| -> ");
  scanf(" %[^\n]", usuarioNome);

  if (verificar(usuarioNome, 0)) {
    return;
  }

  Usuario *usuarioAtual = cabecaUsuarios;
  while (usuarioAtual != NULL) {
    if (strcmp(usuarioAtual->nome, usuarioNome) == 0) {
      printf("| Digite o titulo do livro que deseja pegar emprestado:\n| -> ");
      scanf(" %[^\n]", titulo);

      if (verificar(titulo, 0)) {
        return;
      }

      Livro *livroAtual = *cabecaLivros;
      while (livroAtual != NULL) {
        if (strcmp(livroAtual->titulo, titulo) == 0 &&
            livroAtual->copias != 0) {
          if (strcmp(usuarioAtual->livrosEmprestados, "|NENHUM") == 0) {
            strcpy(usuarioAtual->livrosEmprestados, "");
          }
          char detalhesLivro[500];
          sprintf(detalhesLivro, "|%s\t%s\t%s\t%d", livroAtual->titulo,
                  livroAtual->autor, livroAtual->editora,
                  livroAtual->anoPublicacao);
          strcat(usuarioAtual->livrosEmprestados, detalhesLivro);
          printf("| Livro emprestado com sucesso\n|\n");
          livroAtual->copias--;
          return;
        }
        livroAtual = livroAtual->prox;
      }
      printf("| Livro nao encontrado ou nao disponivel.\n|\n");
      return;
    }
    usuarioAtual = usuarioAtual->prox;
  }
  printf("| Usuário nao encontrado.\n|\n");
}

void devolverLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros) {
  char titulo[500];
  char nome[500];

  printf("\033[2J\033[H");
  printf("| Devolver Livro\n");
  printf("| Digite o seu usuario:\n| -> ");
  scanf(" %[^\n]", nome);
  if (verificar(nome, 0)) {
    return;
  }
  printf("| Digite o titulo do livro que deseja devolver:\n| ->");
  scanf(" %[^\n]", titulo);
  if (verificar(titulo, 0)) {
    return;
  }

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
              printf("| Livro \"%s\" devolvido com sucesso!\n|\n", titulo);
              return;
            }
            livroAtual = livroAtual->prox;
          }
          printf("\033[2J\033[H");
          return;
        }
        livroEmprestado = strtok(NULL, "|");
      }
      return;
    }
    usuarioAtual = usuarioAtual->prox;
  }
  printf("\033[2J\033[H");
  printf("| Usuario \"%s\" nao encontrado.\n|\n", nome);
}

void ordenarAlfabeticamente(Usuario **cabecaUsuarios) {
  if (*cabecaUsuarios == NULL || (*cabecaUsuarios)->prox == NULL) {
    return;
  }

  Usuario *atual, *proximo;
  int trocado;
  char stringTemporaria[500];

  do {
    trocado = 0;
    atual = *cabecaUsuarios;

    while (atual->prox != NULL) {
      proximo = atual->prox;

      if (strcmp(atual->nome, proximo->nome) > 0) {
        strcpy(stringTemporaria, atual->nome);
        strcpy(atual->nome, proximo->nome);
        strcpy(proximo->nome, stringTemporaria);

        strcpy(stringTemporaria, atual->contato);
        strcpy(atual->contato, proximo->contato);
        strcpy(proximo->contato, stringTemporaria);

        strcpy(stringTemporaria, atual->livrosEmprestados);
        strcpy(atual->livrosEmprestados, proximo->livrosEmprestados);
        strcpy(proximo->livrosEmprestados, stringTemporaria);

        trocado = 1;
      }

      atual = atual->prox;
    }
  } while (trocado);
}
