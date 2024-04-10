#ifndef LIVRO_H
#define LIVRO_H

#include "usuario.h"

typedef struct livro {
  char titulo[500];
  char autor[500];
  char editora[500];
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
