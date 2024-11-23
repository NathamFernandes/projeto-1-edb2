#ifndef HANDLERS_H
#define HANDLERS_H

#include "book.h"
#include "stdio.h"

void handle_new_book(Node *library);
void handle_book_search(Node *library);
void handle_books_import(Node *library);
void handle_books_show(Node *library);
void handle_library_delete(Node *library);

#endif