#include "livro.h"
#include "usuario.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  Usuario *cabecaUsuarios = NULL;
  char opcao[10];

  copiarDados(&cabecaUsuarios);

  while (1) {
    printf("| -=-=-=-=- Biblioteca Bytes -=-=-=-=-\n"
           "|\n"
           "| Escolha a acao que deseja realizar:\n"
           "| [1] - Adicionar usuario\n"
           "| [2] - Remover usuario\n"
           "| [3] - Emprestar livro\n"
           "| [4] - Devolver livro\n"
           "| [5] - Editar informacoes do livro\n"
           "| [6] - Buscar livro\n"
           "| [7] - Listar usuarios\n"
           "| [8] - Sair\n| -> ");
    scanf("%s", opcao);

    if (verificar(opcao, 1) && conferirCaractere(opcao)) {
      switch (opcao[0]) {
      case '1':
        adicionarUsuario(&cabecaUsuarios);
        break;
      case '2':
        removerUsuario(&cabecaUsuarios);
        break;
      case '3':
        emprestarLivro(cabecaUsuarios);
        break;
      case '4':
        devolverLivro(cabecaUsuarios);
        break;
      case '5':
        editarLivro(cabecaUsuarios);
        break;
      case '6':
        buscarLivro(cabecaUsuarios);
        break;
      case '7':
        listarUsuarios(cabecaUsuarios);
        break;
      case '8':
        Sair(cabecaUsuarios);
        return 0;
      default:
        printf("\033[2J\033[H");
        printf("| Opcao invalida, tente novamente.\n|\n");
      }
    } else {
      printf("\033[2J\033[H");
      printf("| Opcao invalida, tente novamente.\n|\n");
    }
  }
  return 0;
}
