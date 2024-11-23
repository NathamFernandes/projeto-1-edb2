#ifndef BOOK_H
#define BOOK_H

#include <stddef.h>

#define MAX_LEN 50

//== Aliases

typedef size_t hash_t;

//== Structs

// Representaçãp de um livro.
typedef struct
{
    hash_t id;               //! Código único de um livro.
    char title[MAX_LEN];     //! Titulo de um livro.
    char author[MAX_LEN];    //! Autor de um livro.
    char genre[MAX_LEN];     //! Gênero de um livro.
    unsigned year;           //! Ano de publicação do livro.
    char publisher[MAX_LEN]; //! Editora do livro.
    unsigned pages;          //! Quantidade de páginas do livro.
} Book;

// Representaçãp de um nó da árvore.
typedef struct node
{
    Book book;          //! Dado guardado pelo nó da árvore.
    struct node *left;  //! Ponteiro para o filho esquerdo do nó.
    struct node *right; //! Ponteiro para o filho direito do nó.
} Node;

//== Aux functions

hash_t generate_id();

//== Main functions

// Inicializa uma árvore vazia.
Node *initialize();
// Carrega os livros de um arquivo .csv.
Node *load_books(const char *file_path, Node *root);
// Insere um livro na árvore.
void insert(Node **root, const Book book);
// Busca por todos os livros de um determinado gênero.
void search_by_genre(Node *root, const char *genre);
// Lista todos os livros da árvore.
void show_books(Node *root);
// Desaloca toda a árvore binária.
void deallocate(Node *root);

#endif
