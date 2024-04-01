#include "livro.h"
#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  Usuario usuarios[100];
  Livro livros[100];
  int numUsuarios = 0;
  int numLivros = 0;
  int emprestado;
  int opcao;

  copiarDados(usuarios, &numUsuarios, livros, &numLivros);

  while (1) {
    printf("Seja bem vindo a biblioteca\n");
    printf("Escolha a ação que deseja realizar:\n");
    printf("1 - Adicionar usuário\n");
    printf("2 - Remover usuário\n");
    printf("3 - Emprestar livro\n");
    printf("4 - Devolver livro\n");
    printf("5 - Editar informações do livro\n");
    printf("6 - Buscar Livro por nome\n");
    printf("7 - Listar usuários e livros emprestados\n");
    printf("8 - Sair\n");
    scanf("%d", &opcao);
    switch (opcao) {
    case 1:
      adicionarUsuario(usuarios, &numUsuarios); // Funcionando
      break;
    case 2:
      removerUsuario(usuarios, &numUsuarios); // Funcionando
      break;
    case 3:
      // emprestarLivro(usuarios, livros, numLivros);
      break;
    case 4:
      // devolverLivro(usuarios, livros, numLivros);
      break;
    case 5:
      // editarLivro(Livro *livros, int numLivros, Livros);
      break;
    case 6:
      // buscarLivro(Livro *livros, int numLivros, Livros);
      break;
    case 7:
      // listarUsuarios(Livro *livros, int numLivros, Livros);
      break;
    case 8:
      Sair(usuarios, &numUsuarios, livros, &numLivros);
      return 0;
      break;
    default:
      printf("Opção inválida\n");
    }
  }
  return 0;
}