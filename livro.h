#ifndef LIVRO_H
#define LIVRO_H

typedef struct usuario Usuario;

typedef struct livro {
  char titulo[300];
  char autor[300];
  char editora[300];
  int anoPublicacao;
  int copias;
  struct livro *prox;
} Livro;

void editarLivro(Usuario *cabecaUsuarios);
void buscarLivro(Usuario *cabecaUsuarios);
void emprestarLivro(Usuario *cabecaUsuarios);
void devolverLivro(Usuario *cabecaUsuarios);
void ordenarAlfabeticamente(Usuario **cabecaUsuarios);

#endif
