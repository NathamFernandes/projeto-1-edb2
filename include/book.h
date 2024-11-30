#ifndef BOOK_H
#define BOOK_H

#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LEN 50

//== Structs

// Representaçãp de um livro.
typedef struct
{
    unsigned short id;       //! Código único de um livro.
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

// Gera um codigo unico para um livro inserido na árvore.
unsigned short generate_id();
// Cria um novo nó na árvore.
Node *create_node(const Book book);
// Verifica se um nó existe na arvore.
bool exists(Node* root, unsigned id);

//== Main functions

// Inicializa uma árvore vazia.
Node *initialize();
// Carrega os livros de um arquivo .csv.
Node *load_books(const char *file_path, Node *root);
// Insere um livro na árvore.
void insert(Node **root, const Book book);
// Busca por todos os livros de um determinado gênero.
void search_by_genre(Node *root, const char *genre, void (*print)(const Book book));
// Lista todos os livros da árvore.
void show_books(Node *root, void (*print)(const Book));
// Desaloca toda a árvore binária.
void deallocate(Node *root);

#endif
