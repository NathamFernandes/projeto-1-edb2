#ifndef BOOK_H
#define BOOK_H

#define MAX_LEN 50

typedef struct {
    unsigned    id;
    char        title[MAX_LEN];
    char        author[MAX_LEN];
    char        genre[MAX_LEN];
    unsigned    year;
    char        publisher[MAX_LEN];
    unsigned    pages;
} Book;

typedef struct node {
    Book book;
    struct node* left;
    struct node* right;
} Node;

typedef struct {
    Node* root;
} BTree;

Node* initialize();
Node* load_books(const char *file_path, Node* root);
void insert(Node** root, const Book book);
void search_by_genre(Node* root, const char *genre);
void show_books(Node* root);
void deallocate(Node* root);

#endif
