#ifndef USUARIO_H
#define USUARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro Livro;

typedef struct usuario Usuario;

struct usuario {
  char nome[50];
  int contato;
  char livrosEmprestados[50];
};

void adicionarUsuario(Usuario *usuarios, int *numUsuarios);

void removerUsuario(Usuario *usuarios, int *numUsuarios);

void listarUsuarios(Usuario *usuarios, int *numUsuarios);

void escreverDados(Usuario *usuarios, int *numUsuarios, Livro *livros,
                   int *numLivros);

void copiarDados(Usuario *usuarios, int *numUsuarios, Livro *livros,
                 int *numLivros);

void Sair(Usuario *usuarios, int *numUsuarios, Livro *livros, int *numLivros);

#endif
