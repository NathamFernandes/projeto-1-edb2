#include "handlers.h"

/**
 * @brief Lida com a inserção de um novo livro na biblioteca.
 *
 * @param library O nó raiz da biblioteca.
 */
void handle_new_book(Node *library)
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

    insert(&library, new_book);
}

void handle_book_search(Node *library)
{
}

void handle_books_import(Node *library)
{
}

void handle_books_show(Node *library)
{
    show_books(library);
}

void handle_library_delete(Node *library)
{
}