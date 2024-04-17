#include "usuario.h"
#include "livro.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionarUsuario(Usuario **cabecaUsuarios) {
  printf("\033[2J\033[H");
  printf("| Adicionar Usuario\n");

  Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));

  if (novoUsuario == NULL) {
    printf("Erro ao alocar memoria\n");
    return;
  }

  printf("| Digite o nome do usuario:\n| -> ");
  scanf(" %[^\n]", novoUsuario->nome);
  if (verificar(novoUsuario->nome, 0) == 0) {
    free(novoUsuario);
    return;
  }

  printf("| Digite o contato do usuario:\n| -> ");
  scanf(" %[^\n]", novoUsuario->contato);

  if (verificar(novoUsuario->contato, 1) == 0) {
    free(novoUsuario);
    return;
  }

  Usuario *atual = *cabecaUsuarios;

  while (atual != NULL) {
    if (strcmp(atual->nome, novoUsuario->nome) == 0 ||
        strcmp(atual->contato, novoUsuario->contato) == 0) {
      printf("| Nome ou contato ja existente!\n|\n");
      free(novoUsuario);
      return;
    }
    atual = atual->prox;
  }

  novoUsuario->livros = NULL;
  novoUsuario->prox = NULL;

  if (*cabecaUsuarios == NULL) {
    *cabecaUsuarios = novoUsuario;
  } else {
    Usuario *atual = *cabecaUsuarios;
    while (atual->prox != NULL) {
      atual = atual->prox;
    }
    atual->prox = novoUsuario;
  }

  printf("| Usuario adicionado!\n|\n");
}

void removerUsuario(Usuario **cabecaUsuarios) {
  char nome[100];
  printf("\033[2J\033[H");
  printf("| Remover Usuario\n");
  printf("| Digite o nome do usuario que deseja remover:\n| -> ");
  scanf(" %[^\n]", nome);
  if (verificar(nome, 0) == 0) {
    return;
  }

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
      printf("| Usuario removido com sucesso.\n|\n");
      return;
    }
    anterior = atual;
    atual = atual->prox;
  }
  printf("| Usuario não encontrado.\n|\n");
}

void listarUsuarios(Usuario *cabecaUsuarios) {
  printf("\033[2J\033[H");
  Usuario *atual = cabecaUsuarios;

  if (atual == NULL) {
    printf("|\n| Nenhum usuario cadastrado.\n|\n");
    return;
  }

  ordenarAlfabeticamente(&cabecaUsuarios);

  while (atual != NULL) {
    printf("| Usuário: %s | Contato: %s\n", atual->nome, atual->contato);
    atual = atual->prox;
  }
  printf("|\n");
}

void escreverDados(Usuario *cabecaUsuarios) {
  FILE *arquivoUsuarios = fopen("usuarios.txt", "w");
  FILE *arquivoLivros = fopen("livros.txt", "w");

  if (arquivoUsuarios == NULL || arquivoLivros == NULL) {
    printf("| Erro ao abrir os arquivos\n|\n");
    return;
  }

  Usuario *atualUsuario = cabecaUsuarios;

  while (atualUsuario != NULL) {
    if (strcmp(atualUsuario->livrosEmprestados, "") == 0) {
      fprintf(arquivoUsuarios, "%s\t%s\n|NENHUM\n", atualUsuario->nome,
              atualUsuario->contato);
    } else {
      fprintf(arquivoUsuarios, "%s\t%s\n%s\n", atualUsuario->nome,
              atualUsuario->contato, atualUsuario->livrosEmprestados);
    }
    atualUsuario = atualUsuario->prox;
  }

  Livro *atualLivro = cabecaUsuarios->livros;

  while (atualLivro != NULL) {
    if (atualLivro->copias != 0) {
      fprintf(arquivoLivros, "%s\t%s\t%s\t%d\t%d\n", atualLivro->titulo,
              atualLivro->autor, atualLivro->editora, atualLivro->anoPublicacao,
              atualLivro->copias);
    }
    atualLivro = atualLivro->prox;
  }

  fclose(arquivoUsuarios);
  fclose(arquivoLivros);
}

void copiarDados(Usuario **cabecaUsuarios) {
  FILE *arquivoUsuarios = fopen("usuarios.txt", "r");
  FILE *arquivoLivros = fopen("livros.txt", "r");

  if (arquivoUsuarios == NULL || arquivoLivros == NULL) {
    printf("| Erro ao abrir os arquivos\n|\n");
    return;
  }

  char tempNome[300];
  char tempContato[300];
  char tempLivrosEmprestados[300];

  while (fscanf(arquivoUsuarios, " %[^\t] \t %[^\n] \n %[^\n]", tempNome,
                tempContato, tempLivrosEmprestados) == 3) {
    Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));
    if (novoUsuario == NULL) {
      printf("Erro ao alocar memoria\n");
      return;
    }
    strcpy(novoUsuario->nome, tempNome);
    strcpy(novoUsuario->contato, tempContato);
    strcpy(novoUsuario->livrosEmprestados, tempLivrosEmprestados);
    novoUsuario->prox = *cabecaUsuarios;
    *cabecaUsuarios = novoUsuario;
  }

  char tempTitulo[300];
  char tempAutor[300];
  char tempEditora[300];
  int tempAnoPublicacao;
  int tempCopias;

  while (fscanf(arquivoLivros, "%[^\t] \t %[^\t] \t %[^\t] \t %d \t %d\n",
                tempTitulo, tempAutor, tempEditora, &tempAnoPublicacao,
                &tempCopias) == 5) {
    Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
    if (novoLivro == NULL) {
      printf("Erro ao alocar memoria\n");
      return;
    }
    strcpy(novoLivro->titulo, tempTitulo);
    strcpy(novoLivro->autor, tempAutor);
    strcpy(novoLivro->editora, tempEditora);
    novoLivro->anoPublicacao = tempAnoPublicacao;
    novoLivro->copias = tempCopias;
    novoLivro->prox = (*cabecaUsuarios)->livros;
    (*cabecaUsuarios)->livros = novoLivro;
  }

  fclose(arquivoUsuarios);
  fclose(arquivoLivros);
}

void Sair(Usuario *cabecaUsuarios) {
  ordenarAlfabeticamente(&cabecaUsuarios);
  escreverDados(cabecaUsuarios);
  Usuario *atualUsuario = cabecaUsuarios;

  while (atualUsuario != NULL) {
    Usuario *temp = atualUsuario;
    atualUsuario = atualUsuario->prox;
    free(temp);
  }

  Livro *atualLivro = (*cabecaUsuarios).livros;

  while (atualLivro != NULL) {
    Livro *temp = atualLivro;
    atualLivro = atualLivro->prox;
    free(temp);
  }

  printf("|\n| Saindo...");
  return;
}

int verificar(char *conteudo, int numeroOuLetra) {
  for (int i = 0; conteudo[i] != '\0'; i++) {
    conteudo[i] = toupper(conteudo[i]);
  }
  for (int i = 0; conteudo[i] != '\0'; i++) {
    if (numeroOuLetra == 1) {
      if (!isdigit(conteudo[i])) {
        printf("| Entrada invalida!\n| Apenas numeros sao permitidos.\n|\n");
        return 0;
      }
    } else if (numeroOuLetra == 0) {
      if (!isalpha(conteudo[i]) && conteudo[i] != ' ') {
        printf("| Entrada invalida!\n| Apenas letras sao permitidas.\n|\n");
        return 0;
      }
    }
  }
  return 1;
}

int conferirCaractere(char *conteudo) {
  if (strlen(conteudo) == 1) {
    return 1;
  }
  printf("\033[2J\033[H");
  printf("| Entrada invalida!\n| Apenas um caractere e permitido.\n|\n");
  return 0;
}
