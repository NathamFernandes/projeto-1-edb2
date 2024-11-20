#include "menu.h"

void main_loop(Node *library)
{
    int option;

    while (1)
    {
        option = render_first_menu();

        if (option == 0)
            return;

        if (option < 0 || option > 5)
        {
            printf("\nOpcao invalida!\n");
            continue;
        }

        switch (option)
        {
        case 1:
            handle_new_book(library);
            break;
        case 2:
            handle_book_search(library);
            break;
        case 3:
            handle_books_import(library);
            break;
        case 4:
            handle_books_show(library);
            break;
        case 5:
            handle_library_delete(library);
            break;
        }
    }
}

int render_first_menu()
{
    int option;

    printf("\n0 - Encerrar programa\n1 - Inserir um novo livro\n2 - Buscar livro por genero\n3 - Carregar livros por CSV\n4 - Exibir livros\n5 - Fechar biblioteca\n\nOpcao: ");

    scanf("%d", &option);

    return option;
}