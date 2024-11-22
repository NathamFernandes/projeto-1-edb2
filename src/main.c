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

   // show_books(library);

    //main_loop(library);

    deallocate(library);

    return EXIT_SUCCESS;
}
