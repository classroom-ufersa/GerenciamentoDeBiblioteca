#include "livro.h"
#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  Usuario *cabecaUsuarios = NULL;
  Livro *cabecaLivros = NULL;
  int opcao;

  copiarDados(&cabecaUsuarios, &cabecaLivros);

  while (1) {
    printf("Seja bem vindo a biblioteca\n");
    printf("Escolha a ação que deseja realizar:\n");
    printf("1 - Adicionar usuário\n");
    printf("2 - Remover usuário\n");
    printf("3 - Emprestar livro\n");
    printf("4 - Devolver livro\n");
    printf("5 - Editar informações do livro\n");
    printf("6 - Buscar Livro por nome\n");
    printf("7 - Listar usuários\n");
    printf("8 - Sair\n");
   // printf("9 - Adicionar livro"); Desenvolvendo
    scanf("%d", &opcao);
    switch (opcao) {
    case 1:
      adicionarUsuario(&cabecaUsuarios); // Funcionando
      break;
    case 2:
      removerUsuario(&cabecaUsuarios); // Funcionando
      break;
    case 3:
      emprestarLivro(cabecaUsuarios, cabecaLivros); // Funcionando parcialmente
      break;
    case 4:
      devolverLivro(cabecaUsuarios, cabecaLivros); // Funcionando parcialmente 
      break;
    case 5:
      editarLivro(cabecaLivros); // Funcionando
      break;
    case 6:
      buscarLivro(cabecaLivros); // Funcionando
      break;
    case 7:
      listarUsuarios(cabecaUsuarios); // Funcionando
      break;
    case 8:
      Sair(cabecaUsuarios, cabecaLivros); // Funcionando
      return 0;
      break;
    // case 9:
      // adicionarLivro(Livro **cabecaLivros); // Desenvolvendo (por que essa função?)
    default:
      printf("Opção inválida, tente novamente.\n\n");
    }
  }
  return 0;
}
