#ifndef USUARIO_H
#define USUARIO_H

typedef struct livro Livro;

typedef struct usuario {
  char nome[300];
  char contato[300];
  char livrosEmprestados[300];
  Livro *livros;
  struct usuario *prox;
} Usuario;

void adicionarUsuario(Usuario **cabecaUsuarios);
void removerUsuario(Usuario **cabecaUsuarios);
void listarUsuarios(Usuario *cabecaUsuarios);
void escreverDados(Usuario *cabecaUsuarios);
void copiarDados(Usuario **cabecaUsuarios);
int verificar(char *conteudo, int numeroOuLetra);
void Sair(Usuario *cabecaUsuarios);
int conferirCaractere(char *conteudo);

#endif
