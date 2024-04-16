#ifndef USUARIO_H
#define USUARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct livro;

typedef struct usuario {
  char nome[200];
  char contato[200];
  char livrosEmprestados[200];
  struct usuario *prox;
} Usuario;

void adicionarUsuario(Usuario **cabecaUsuarios);

void removerUsuario(Usuario **cabecaUsuarios);

void listarUsuarios(Usuario *cabecaUsuarios);

void escreverDados(Usuario *cabecaUsuarios, struct livro *cabecaLivros);

void copiarDados(Usuario **cabecaUsuarios, struct livro **cabecaLivros);

int verificar(char *conteudo, int numeroOuLetra);

void Sair(Usuario *cabecaUsuarios, struct livro *cabecaLivros);

int conferirCaractere(char *conteudo);

#endif
