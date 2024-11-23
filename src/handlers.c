#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "handlers.h"

/**
 * @brief Lida com a inserção de um novo livro na biblioteca.
 *
 * @param library O nó raiz da biblioteca.
 */
Node *handle_new_book(Node *library)
{
    Book new_book;
    char keys[6][64] = {
        {"Titulo"},
        {"Autor"},
        {"Genero"},
        {"Publicador"},
        {"Paginas"},
        {"Ano"},
    };

    void *attributes[6] = {
        new_book.title,
        new_book.author,
        new_book.genre,
        new_book.publisher,
        &new_book.pages,
        &new_book.year,
    };

    new_book.id = generate_id();

    for (int i = 0; i < 6; i++)
    {
        printf("%s: ", keys[i]);

        if (i < 4)
            scanf("%63s", (char *)attributes[i]);
        else
            scanf("%d", (int *)attributes[i]);
    }

    if (library == NULL)
    {
        Node *new_node = create_node(new_book);
        library = new_node;
        return library;
    }

    insert(&library, new_book);

    return library;
}

/**
 * @brief Lida com a procura de livros pelo gênero na biblioteca.
 *
 * @param library O nó raiz da biblioteca.
 */
void handle_book_search(Node *library)
{
    char genre[64];
    getchar();

    printf("Genero para pesquisa: ");
    scanf("%63[^\n]", genre);

    search_by_genre(library, genre);
}

/**
 * @brief Lida com a importação de novos livros para a biblioteca.
 *
 * @param library O nó raiz da biblioteca.
 */
Node *handle_books_import(Node *library)
{
    char path[128] = "seeders/";
    char extension[8] = ".csv";
    char file[64];
    getchar();

    printf("Nome do arquivo (apenas) para importacao: ");
    scanf("%63[^\n]", file);

    strcat(path, file);
    strcat(path, extension);

    printf("%s", path);

    library = load_books(path, library);

    return library;
}

/**
 * @brief Lida com a exibição dos livros da biblioteca.
 *
 * @param library O nó raiz da biblioteca.
 */
void handle_books_show(Node *library)
{
    show_books(library);
}