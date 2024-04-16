#include "livro.h"
#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void emprestarLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros) {
  char titulo[100];
  char usuarioNome[100];

  printf("\033[2J\033[H");
  printf("| Emprestar Livro\n| Digite o nome do seu usuario:\n| -> ");
  scanf(" %[^\n]", usuarioNome);

  if (verificar(usuarioNome, 0) == 0) {
    return;
  }

  Usuario *usuarioAtual = cabecaUsuarios;
  while (usuarioAtual != NULL) {
    if (strcmp(usuarioAtual->nome, usuarioNome) == 0) {
      printf("| Digite o titulo do livro que deseja pegar emprestado:\n| -> ");
      scanf(" %[^\n]", titulo);

      if (verificar(titulo, 0) == 0) {
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
  return;
}

void devolverLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros) {
  char titulo[100];
  char nome[100];

  printf("\033[2J\033[H");
  printf("| Devolver Livro\n");

  printf("| Digite o seu usuario:\n| -> ");
  scanf(" %[^\n]", nome);
  if (verificar(nome, 0) == 0) {
    return;
  }

  printf("| Digite o titulo do livro que deseja devolver:\n| -> ");
  scanf(" %[^\n]", titulo);
  if (verificar(titulo, 0) == 0) {
    return;
  }

  Usuario *usuarioAtual = cabecaUsuarios;
  while (usuarioAtual != NULL) {
    if (strcmp(usuarioAtual->nome, nome) == 0) {
      char *livrosEmprestados = usuarioAtual->livrosEmprestados;
      char *livroEmprestado = strtok(livrosEmprestados, "|");

      while (livroEmprestado != NULL) {
        char tempTitulo[100];
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
      printf("\033[2J\033[H");
      printf("| Livro nao encontrado.\n|\n");
      return;
    }
    usuarioAtual = usuarioAtual->prox;
  }

  printf("\033[2J\033[H");
  printf("| Usuario nao encontrado.\n|\n");
}

void editarLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros) {
  char titulo[100];
  printf("\033[2J\033[H");
  printf("| Editar Livro\n|\n");
  printf("| Digite o titulo do livro que deseja editar:\n| -> ");
  scanf(" %[^\n]", titulo);

  if (verificar(titulo, 0) == 0) {
    return;
  }

  Livro *atual = *cabecaLivros;

  while (atual != NULL) {
    if (strcmp(atual->titulo, titulo) == 0 && atual->copias != 0) {
      char opcao;
      printf("|\n| Livro encontrado!\n");

      printf("|\n| Deseja editar o titulo? [S/N]\n| -> ");
      scanf("%s", &opcao);
      if (verificar(&opcao, 0) == 0) {
        return;
      }
      if (opcao == 'S') {
        char tempTitulo[100];
        printf("|\n| Digite o novo titulo do livro: ");
        scanf(" %[^\n]", tempTitulo);
        if (verificar(tempTitulo, 0) == 0) {
          return;
        }
        strcpy(atual->titulo, tempTitulo);
      }

      printf("|\n| Deseja editar o autor? [S/N]\n| -> ");
      scanf("%s", &opcao);
      if (verificar(&opcao, 0) == 0) {
        return;
      }
      if (opcao == 'S') {
        char tempAutor[100];
        printf("|\n| Digite o novo autor do livro: ");
        scanf(" %[^\n]", tempAutor);
        if (verificar(tempAutor, 0) == 0) {
          return;
        }
        strcpy(atual->autor, tempAutor);
      }

      printf("|\n| Deseja editar a editora? [S/N]\n| -> ");
      scanf("%s", &opcao);
      if (verificar(&opcao, 0) == 0) {
        return;
      }
      if (opcao == 'S') {
        char tempEditora[100];
        printf("|\n| Digite a nova editora do livro: ");
        scanf(" %[^\n]", tempEditora);
        if (verificar(tempEditora, 0) == 0) {
          return;
        }
        strcpy(atual->editora, tempEditora);
      }

      printf("|\n| Deseja editar o ano de publicacao? [S/N]\n| -> ");
      scanf("%s", &opcao);
      if (verificar(&opcao, 0) == 0) {
        return;
      }
      if (opcao == 'S') {
        char tempAno[20];
        printf("|\n| Digite o novo ano de publicacao do livro: ");
        scanf("%s", tempAno);
        if (verificar(tempAno, 1) == 0) {
          return;
        }
        atual->anoPublicacao = atoi(tempAno);
      }

      printf("|\n| Deseja editar o numero de cópias? [S/N]\n| -> ");
      scanf("%s", &opcao);
      if (verificar(&opcao, 0) == 0) {
        return;
      }
      if (opcao == 'S') {
        char tempCopias[100];
        printf("|\n| Digite o novo numero de cópias do livro: ");
        scanf("%s", tempCopias);
        if (verificar(tempCopias, 1) == 0) {
          return;
        }
        atual->copias = atoi(tempCopias);
      }
      return;
    }
    atual = atual->prox;
  }
  printf("| Livro não encontrado ou indisponivel.\n|\n");
}

void buscarLivro(Livro **cabecaLivros) {
  char titulo[100];
  printf("\033[2J\033[H");
  printf("| Buscar Livro\n");
  printf("| Digite o título do livro que deseja buscar:\n| -> ");
  scanf(" %[^\n]", titulo);

  if (verificar(titulo, 0) == 0) {
    return;
  }

  Livro *livroAtual = *cabecaLivros;

  while (livroAtual != NULL) {
    if (strcmp(livroAtual->titulo, titulo) == 0) {
      printf("\n| Titulo: %s\n", livroAtual->titulo);
      printf("| Autor: %s\n", livroAtual->autor);
      printf("| Editora: %s\n", livroAtual->editora);
      printf("| Ano de Publicacao: %d\n", livroAtual->anoPublicacao);
      printf("| Quantidade de copias disponiveis: %d\n|\n", livroAtual->copias);
      return;
    }
    livroAtual = livroAtual->prox;
  }

  printf("| Livro nao encontrado.\n|\n");
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
