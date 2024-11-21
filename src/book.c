#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "book.h"

/**
 * @brief Inicializa a árvore de nós, retornando um ponteiro nulo.
 * 
 * Esta função é usada para criar uma árvore binária vazia, ou seja, o ponteiro 
 * para o nó raiz é inicializado como NULL.
 * 
 * @return Ponteiro nulo, representando uma árvore vazia.
 */
Node* initialize()
{
    return NULL; // Retorna NULL indicando que a árvore está vazia.
}

/**
 * @brief Cria um novo nó com as informações de um livro.
 * 
 * Esta função aloca dinamicamente memória para um novo nó e copia os dados 
 * de um livro para o nó recém-criado. O nó é inicializado com ponteiros 
 * filhos (esquerdo e direito) como NULL.
 * 
 * @param book Estrutura do tipo Book que contém as informações do livro.
 * 
 * @return Ponteiro para o novo nó criado.
 */
static Node* create_node(const Book book) 
{
    // Aloca memória para um novo nó.
    Node* new_node = (Node*) malloc(sizeof(Node));

    // Copia as informações do livro para o nó.
    new_node->book.id = book.id;
    strcpy(new_node->book.title, book.title);
    strcpy(new_node->book.author, book.author);
    strcpy(new_node->book.genre, book.genre);
    strcpy(new_node->book.publisher, book.publisher);
    new_node->book.pages = book.pages;
    new_node->book.year = book.year;

    // Inicializa os ponteiros filhos como NULL, já que o nó não tem filhos inicialmente.
    new_node->left = NULL;
    new_node->right = NULL;

    // Retorna o novo nó criado.
    return new_node;
}

/**
 * @brief Exibe as informações de um livro.
 * 
 * Esta função imprime no console os dados do livro (id, título, autor, gênero, 
 * editora, ano e número de páginas).
 * 
 * @param book Estrutura do tipo Book que contém as informações do livro.
 */
static void show_book_info(const Book book)
{
    printf("Id: %d\n", book.id);
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Book Genre: %s\n", book.genre);
    printf("Publisher: %s\n", book.publisher);
    printf("Year: %d\n", book.year);
    printf("Pages: %d\n", book.pages);
    printf("\n");
}

/**
 * @brief Insere um livro na árvore binária.
 * 
 * A função insere um livro na árvore binária, de acordo com seu id. Livros com
 * id maior que o nó atual são inseridos à esquerda, e os com id menor à direita.
 * 
 * @param root Ponteiro duplo para o nó raiz da árvore binária.
 * @param book Livro que será inserido na árvore.
 */
void insert(Node **root, const Book book)
{
    // Se o nó atual for NULL, significa que chegamos em uma posição válida para inserir.
    if ((*root) == NULL) {
        Node* new_node = create_node(book); // Cria um novo nó com os dados do livro.
        *root = new_node; // Define o novo nó como o nó raiz ou como filho do nó anterior.
        return;
    }

    // Se o id do livro for menor que o id do nó atual, insere recursivamente à esquerda.
    if (book.id < (*root)->book.id)
        insert(&(*root)->left, book);

    // Se o id do livro for maior que o id do nó atual, insere recursivamente à direita.
    if (book.id > (*root)->book.id)
        insert(&(*root)->right, book);
}

/**
 * @brief Carrega uma lista de livros a partir de um arquivo e os insere em uma árvore binária.
 * 
 * A função abre o arquivo especificado, lê cada linha e a converte para dados de livros. 
 * Cada livro lido é inserido na árvore binária usando a função `insert`.
 * 
 * @param file_path Caminho para o arquivo contendo os dados dos livros.
 * @param root Ponteiro para o nó raiz da árvore binária onde os livros serão inseridos.
 * 
 * @return A árvore binária com os livros carregados.
 */
Node* load_books(const char* file_path, Node* root)
{
    // Abre o arquivo no modo leitura.
    FILE* input_file = fopen(file_path, "r");

    // Verifica se o arquivo foi aberto corretamente.
    if (!input_file) {
        // Exibe uma mensagem de erro caso o arquivo não possa ser lido.
        fprintf(stderr, "Unable to read file: %s.\n", strerror(errno));
        return NULL; // Retorna NULL em caso de erro ao abrir o arquivo.
    }

    char linha[512]; // Buffer para ler cada linha do arquivo.
    Book book; // Variável para armazenar os dados do livro.

    // Lê cada linha do arquivo até o final.
    while (fgets(linha, sizeof(linha), input_file)) {
        // Tenta analisar os dados da linha e preencher a estrutura Book.
        int success = sscanf(linha, "%u,%99[^,],%99[^,],%49[^,],%49[^,],%u,%u",
                        &book.id, book.title, book.author, book.genre, book.publisher,
                        &book.pages, &book.year);
        
        // Se a linha foi lida com sucesso (7 campos), insere o livro na árvore.
        if (success == 7)
            insert(&root, book);
        //else
        //    fprintf(stderr, "Warning: Invalid format in line: %s", linha); // Aviso em caso de formato inválido.
    }

    // Fecha o arquivo após terminar a leitura.
    fclose(input_file);

    // Retorna a árvore binária com os livros carregados.
    return root;
}

/**
 * @brief Busca e exibe todos os livros de um determinado gênero.
 * 
 * A função percorre a árvore binária recursivamente e exibe as informações dos livros
 * que correspondem ao gênero especificado.
 * 
 * @param root Nó raiz da árvore binária.
 * @param genre Gênero dos livros a serem exibidos.
 */
void search_by_genre(Node *root, const char *genre)
{
    // Se o nó atual não for NULL, continua a busca.
    if (root != NULL) {
        // Se o gênero do livro no nó atual for igual ao gênero buscado, exibe as informações do livro.
        if (strcmp(genre, root->book.genre) == 0)
            show_book_info(root->book);

        // Recursivamente busca à esquerda e à direita da árvore.
        search_by_genre(root->left, genre);
        search_by_genre(root->right, genre);
    }
}

/**
 * @brief Exibe as informações de todos os livros na árvore.
 * 
 * Esta função percorre a árvore binária de forma recursiva e exibe as informações 
 * de todos os livros presentes na árvore.
 * 
 * @param root Nó raiz da árvore binária.
 */
void show_books(Node *root)
{
    // Se o nó atual não for NULL, continua a exibição.
    if (root != NULL) {
        // Exibe as informações do livro no nó atual.
        show_book_info(root->book);
        
        // Recursivamente exibe os livros à esquerda e à direita da árvore.
        show_books(root->left);
        show_books(root->right);
    }
}
