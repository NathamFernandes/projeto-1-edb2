#include <stdlib.h>
#include <stdio.h>

#include "book.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    Node *library = initialize();

    library = load_books(argv[1], library);

    if (library == NULL)
    {
        return EXIT_FAILURE;
    }

    main_loop(library);

    // show_books(library);
    // search_by_genre(library, "Informatica");

    return EXIT_SUCCESS;
}
