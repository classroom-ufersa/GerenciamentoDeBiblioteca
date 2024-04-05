#include "usuario.h"
#include "livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionarUsuario(Usuario **cabecaUsuarios) {
  printf("\033[2J\033[H");
  printf("Adicionar Usuário\n");

  Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));

  if (novoUsuario == NULL) {
    printf("Erro ao alocar memória para novo usuário\n");
    return;
  }

  printf("Digite o nome do usuário: ");
  scanf(" %[^\n]", novoUsuario->nome);
  getchar();

  printf("Digite o contato do usuário: ");
  scanf("%d", &novoUsuario->contato);

  novoUsuario->prox = *cabecaUsuarios;
  *cabecaUsuarios = novoUsuario;

  printf("Usuário adicionado!\n\n");
}

void removerUsuario(Usuario **cabecaUsuarios) {
  char nome[50];
  printf("\033[2J\033[H");
  printf("Remover Usuário\n");
  printf("Digite o nome do usuário que deseja remover: ");
  scanf(" %[^\n]", nome);

  Usuario *atual = *cabecaUsuarios;
  Usuario *anterior = NULL;

  while (atual != NULL) {
    if (strcmp(atual->nome, nome) == 0) {
      if (anterior != NULL) {
        anterior->prox = atual->prox;
      } else {
        *cabecaUsuarios = atual->prox;
      }
      free(atual);
      printf("Usuário removido com sucesso.\n");
      return;
    }
    anterior = atual;
    atual = atual->prox;
  }
  printf("Usuário não encontrado.\n");
}

void listarUsuarios(Usuario *cabecaUsuarios) {
  printf("\033[2J\033[H");
  Usuario *atual = cabecaUsuarios;
  int i = 1;

  while (atual != NULL) {
    printf("Usuário %d: %s, %d\n", i++, atual->nome, atual->contato);
    atual = atual->prox;
  }
  printf("\n");
}

void escreverDados(Usuario *cabecaUsuarios, Livro *cabecaLivros) {
  FILE *arquivoUsuarios = fopen("usuarios.txt", "w");
  FILE *arquivoLivros = fopen("livros.txt", "w");

  if (arquivoUsuarios == NULL || arquivoLivros == NULL) {
    printf("Erro ao abrir os arquivos\n");
    return;
  }

  Usuario *atualUsuario = cabecaUsuarios;
  while (atualUsuario != NULL) {
    if (strcmp(atualUsuario->livrosEmprestados, "") == 0) {
      fprintf(arquivoUsuarios, "%s\t%d\nNenhum\n", atualUsuario->nome,
              atualUsuario->contato);
    } else {
      fprintf(arquivoUsuarios, "%s\t%d\n%s\n", atualUsuario->nome,
              atualUsuario->contato, atualUsuario->livrosEmprestados);
    }
    atualUsuario = atualUsuario->prox;
  }

  Livro *atualLivro = cabecaLivros;
  while (atualLivro != NULL) {
    fprintf(arquivoLivros, "%s\t%s\t%s\t%d\n", atualLivro->titulo,
            atualLivro->autor, atualLivro->editora, atualLivro->anoPublicacao);
    atualLivro = atualLivro->prox;
  }

  fclose(arquivoUsuarios);
  fclose(arquivoLivros);
}

void copiarDados(Usuario **cabecaUsuarios, Livro **cabecaLivros) {
  FILE *arquivoUsuarios = fopen("usuarios.txt", "r");
  FILE *arquivoLivros = fopen("livros.txt", "r");

  if (arquivoUsuarios == NULL || arquivoLivros == NULL) {
    printf("Erro ao abrir os arquivos\n");
    return;
  }

  char tempNome[50];
  int tempContato;
  char tempLivrosEmprestados[100];

  while (fscanf(arquivoUsuarios, " %[^\t] \t %d \n %[^\n]", tempNome,
                &tempContato, tempLivrosEmprestados) == 3) {
    Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));
    if (novoUsuario == NULL) {
      printf("Erro ao alocar memória para novo usuário\n");
      return;
    }
    strcpy(novoUsuario->nome, tempNome);
    novoUsuario->contato = tempContato;
    strcpy(novoUsuario->livrosEmprestados, tempLivrosEmprestados);
    novoUsuario->prox = *cabecaUsuarios;
    *cabecaUsuarios = novoUsuario;
  }

  char tempTitulo[50];
  char tempAutor[50];
  char tempEditora[50];
  int tempAnoPublicacao;

  while (fscanf(arquivoLivros, "%[^\t] \t %[^\t] \t %[^\t] \t %d\n",
                  tempTitulo, tempAutor, tempEditora, &tempAnoPublicacao) == 4) {
      Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
      if (novoLivro == NULL) {
        printf("Erro ao alocar memória\n");
        return;
      }
      strcpy(novoLivro->titulo, tempTitulo);
      strcpy(novoLivro->autor, tempAutor);
      strcpy(novoLivro->editora, tempEditora);
      novoLivro->anoPublicacao = tempAnoPublicacao;
      novoLivro->prox = *cabecaLivros;
      *cabecaLivros = novoLivro;
  }
}

void Sair(Usuario *cabecaUsuarios, Livro *cabecaLivros) {
  adicionarListaEmOrdemAlfabetica(&cabecaUsuarios);
  escreverDados(cabecaUsuarios, cabecaLivros);
  Usuario *atualUsuario = cabecaUsuarios;

  while (atualUsuario != NULL) {
    Usuario *temp = atualUsuario;
    atualUsuario = atualUsuario->prox;
    free(temp);
  }

  Livro *atualLivro = cabecaLivros;
  while (atualLivro != NULL) {
    Livro *temp = atualLivro;
    atualLivro = atualLivro->prox;
    free(temp);
  }

  printf("\nSaindo...");
  return;
}
