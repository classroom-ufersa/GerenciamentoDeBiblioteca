#ifndef LIVRO_H
#define LIVRO_H

#include "usuario.h"

typedef struct livro {
  char titulo[200];
  char autor[200];
  char editora[200];
  int anoPublicacao;
  int copias;
  struct livro *prox;
} Livro;


void editarLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros);

void buscarLivro(Livro **cabecaLivros);

void emprestarLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros);

void devolverLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros);

void ordenarAlfabeticamente(Usuario **cabecaUsuarios);

#endif
