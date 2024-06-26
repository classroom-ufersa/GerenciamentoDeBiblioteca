## Gerenciamento de Biblioteca

## Sumário

- Sobre nooso projeto
- Requisitos
- Arquitetura
- Desenvolvedores

## Sobre nosso projeto
Este é um projeto de gerenciamento de biblioteca em C. Nossa biblioteca virtual é chamada de "Bytes de Livros", O mesmo foi desenvolvido com o objetivo de proporcionar uma maneira eficiente e organizada de administrar uma biblioteca fictícia. Utilizamos duas TADs distintas para representar os livros e os usuários da biblioteca, além de criar um módulo para funções gerais. Este projeto foi feito para inovar em escolas ou instituições de ensino que costumam usar caderno e caneta para anotar os livros emprestados, assim como era em nossa antiga escola que cursamos o ensino médio.

## Requisitos do projeto
O projeto tem os seguintes requisitos:

1. Adicionar livros à biblioteca.
2. Remover livros da biblioteca.
3. Emprestar livro.
4. Devolver livro.
5. Editar informações de livros existentes na biblioteca.
6. Buscar livro.
7. Visualizar todos os usuários.
8. Sair.

## Arquitetura
### Estrutura
#### Usuários
```c
typedef struct usuario {
  char nome[300];
  char contato[300];
  char livrosEmprestados[300];
  Livro *livros;
  struct usuario *prox;
} Usuario;
```

#### Livros
```c
typedef struct livro {
  char titulo[300];
  char autor[300];
  char editora[300];
  int anoPublicacao;
  int copias;
  struct livro *prox;
} Livro;
```
São as duas estruturas presente no nosso código
### Módulos
#### Usuários
```c
void adicionarUsuario(Usuario **cabecaUsuarios);

void removerUsuario(Usuario **cabecaUsuarios);

void listarUsuarios(Usuario *cabecaUsuarios);

void escreverDados(Usuario *cabecaUsuarios, struct livro *cabecaLivros);

void copiarDados(Usuario **cabecaUsuarios, struct livro **cabecaLivros);

int verificar(char *conteudo, int numeroOuLetra);

void Sair(Usuario *cabecaUsuarios, struct livro *cabecaLivros);
```
#### Livros
```c
void editarLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros);

void buscarLivro(Livro **cabecaLivros);

void emprestarLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros);

void devolverLivro(Usuario *cabecaUsuarios, Livro **cabecaLivros);

void ordenarAlfabeticamente(Usuario **cabecaUsuarios);
```
São dois módulos diferentes com funções diferentes, algumas trabalhando com verificação, ordenação etc...
# Este projeto foi desenvolvido por
- Carlos Henrique Duarte Abrantes
- Luís Otávio Martins Abrantes
