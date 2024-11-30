#include <stdlib.h>
#include <stdio.h>

#include "book.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Usage: library <file.csv>\n");
        return EXIT_FAILURE;
    }

    Node *library = initialize();
    library = load_books(argv[1], library);

    if (library == NULL)
        return EXIT_FAILURE;

    main_loop(library);

    return EXIT_SUCCESS;
}
