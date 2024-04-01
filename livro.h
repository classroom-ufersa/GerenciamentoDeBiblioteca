#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro Livro;

typedef struct usuario Usuario;

struct livro {
  char titulo[50];
  char autor[50];
  char editora[50];
  int anoPublicacao;
};

void editarLivro(Livro *livros, int numLivros);

void buscarLivro(Livro *livros, int numLivros);

void emprestarLivro(Usuario *usuarios, Livro *livros, int numLivros);

void devolverLivro(Usuario *usuarios, Livro *livros, int numLivros);

void adicionarListaEmOrdemAlfabetica(Usuario *usuarios, int numUsuarios, Livro *livros, int numLivros);

#endif