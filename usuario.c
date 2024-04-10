#include "usuario.h"
#include "livro.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionarUsuario(Usuario **cabecaUsuarios) {
  printf("\033[2J\033[H");
  printf("| Adicionar Usuário\n");

  Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));

  if (novoUsuario == NULL) {
    printf("Erro ao alocar memória\n");
    return;
  }

  printf("| Digite o nome do usuario:\n| -> ");
  scanf(" %[^\n]", novoUsuario->nome);
  if (verificar(novoUsuario->nome, 0)) {
    free(novoUsuario);
    return;
  }

  printf("| Digite o contato do usuario:\n| -> ");
  scanf(" %[^\n]", novoUsuario->contato);

  if (verificar(novoUsuario->contato, 1)) {
    free(novoUsuario);
    return;
  }

  Usuario *atual = *cabecaUsuarios;

  while (atual != NULL) {
    if (strcmp(atual->nome, novoUsuario->nome) == 0 ||
        strcmp(atual->contato, novoUsuario->contato) == 0) {
      printf("| Nome ou contato já existente!\n|\n");
      free(novoUsuario);
      return;
    }
    atual = atual->prox;
  }

  novoUsuario->prox = *cabecaUsuarios;
  *cabecaUsuarios = novoUsuario;

  printf("| Usuario adicionado!\n|\n");
}

void removerUsuario(Usuario **cabecaUsuarios) {
  char nome[500];
  printf("\033[2J\033[H");
  printf("| Remover Usuario\n");
  printf("| Digite o nome do usuario que deseja remover:\n| -> ");
  scanf(" %[^\n]", nome);
  if (verificar(nome, 0)) {
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
      printf("| Usuário removido com sucesso.\n|\n");
      return;
    }
    anterior = atual;
    atual = atual->prox;
  }
  printf("| Usuário não encontrado.\n|\n");
}

void listarUsuarios(Usuario *cabecaUsuarios) {
  printf("\033[2J\033[H");
  Usuario *atual = cabecaUsuarios;
  int i = 1;

  if (atual == NULL) {
    printf("|\n| Nenhum usuário cadastrado.\n|\n");
    return;
  }

  while (atual != NULL) {
    printf("| Usuário %d: %s | %s\n", i++, atual->nome, atual->contato);
    atual = atual->prox;
  }
  printf("|\n");
}

void escreverDados(Usuario *cabecaUsuarios, Livro *cabecaLivros) {
  FILE *arquivoUsuarios = fopen("usuarios.txt", "w");
  FILE *arquivoLivros = fopen("livros.txt", "w");

  if (arquivoUsuarios == NULL || arquivoLivros == NULL) {
    printf("| Erro ao abrir os arquivos\n|\n");
    return;
  }

  Usuario *atualUsuario = cabecaUsuarios;
  while (atualUsuario != NULL) {
    if (strcmp(atualUsuario->livrosEmprestados, "|") == 0) {
      fprintf(arquivoUsuarios, "%s\t%s\n|NENHUM\n", atualUsuario->nome,
              atualUsuario->contato);
    } else {
      fprintf(arquivoUsuarios, "%s\t%s\n%s\n", atualUsuario->nome,
              atualUsuario->contato, atualUsuario->livrosEmprestados);
    }
    atualUsuario = atualUsuario->prox;
  }

  Livro *atualLivro = cabecaLivros;
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

void copiarDados(Usuario **cabecaUsuarios, Livro **cabecaLivros) {
  FILE *arquivoUsuarios = fopen("usuarios.txt", "r");
  FILE *arquivoLivros = fopen("livros.txt", "r");

  if (arquivoUsuarios == NULL || arquivoLivros == NULL) {
    printf("| Erro ao abrir os arquivos\n|\n");
    return;
  }

  char tempNome[500];
  char tempContato[500];
  char tempLivrosEmprestados[500];

  while (fscanf(arquivoUsuarios, " %[^\t] \t %[^\n] \n %[^\n]", tempNome,
                tempContato, tempLivrosEmprestados) == 3) {
    Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));
    if (novoUsuario == NULL) {
      printf("Erro ao alocar memória\n");
      return;
    }
    strcpy(novoUsuario->nome, tempNome);
    strcpy(novoUsuario->contato, tempContato);
    strcpy(novoUsuario->livrosEmprestados, tempLivrosEmprestados);
    novoUsuario->prox = *cabecaUsuarios;
    *cabecaUsuarios = novoUsuario;
  }

  char tempTitulo[500];
  char tempAutor[500];
  char tempEditora[500];
  int tempAnoPublicacao;
  int tempCopias;

  while (fscanf(arquivoLivros, "%[^\t] \t %[^\t] \t %[^\t] \t %d \t %d\n",
                tempTitulo, tempAutor, tempEditora, &tempAnoPublicacao,
                &tempCopias) == 5) {
    Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
    if (novoLivro == NULL) {
      printf("Erro ao alocar memória\n");
      return;
    }
    strcpy(novoLivro->titulo, tempTitulo);
    strcpy(novoLivro->autor, tempAutor);
    strcpy(novoLivro->editora, tempEditora);
    novoLivro->anoPublicacao = tempAnoPublicacao;
    novoLivro->copias = tempCopias;
    novoLivro->prox = *cabecaLivros;
    *cabecaLivros = novoLivro;
  }

  fclose(arquivoUsuarios);
  fclose(arquivoLivros);
}

void Sair(Usuario *cabecaUsuarios, Livro *cabecaLivros) {
  ordenarAlfabeticamente(&cabecaUsuarios);
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

  printf("|\n| Saindo...");
  return;
}

int verificar(char *conteudo, int numeroOuLetra) {

  for (int i = 0; conteudo[i] != '\0'; i++) {
    conteudo[i] = toupper(conteudo[i]);
  }
  for (int i = 0; conteudo[i] != '\0'; i++) {
    if (numeroOuLetra == 1) {
      if (!isdigit(conteudo[i]) && conteudo[i] != ' ') {
        printf("| Entrada inválida!\n| Apenas números são permitidos.\n|\n");
        return 1;
      }
    } else if (numeroOuLetra == 0) {
      if (!isalpha(conteudo[i]) && conteudo[i] != ' ') {
        printf("| Entrada inválida!\n| Apenas letras são permitidas.\n|\n");
        return 1;
      }
    }
  }

  return 0;
}
