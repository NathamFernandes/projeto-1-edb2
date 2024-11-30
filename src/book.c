#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "book.h"

/**
 * @brief Verifica se um ID existe na árvore binária de busca.
 *
 * Esta função realiza uma busca recursiva para verificar se o ID especificado 
 * está presente em qualquer nó da árvore binária de busca.
 *
 * @param root Ponteiro para o nó raiz da árvore binária de busca.
 * @param id O ID a ser procurado na árvore.
 * @return true Se o ID for encontrado na árvore.
 * @return false Se o ID não for encontrado na árvore.
 */
bool exists(Node* root, unsigned id)
{
    // Caso base: se a árvore está vazia, o ID não existe.
    if (root == NULL)
        return false;

    if (root->book.id == id)
        return true;
    else if (id < root->book.id)
        return exists(root->left, id);
    else
        return exists(root->right, id);
}

/**
 * @brief Gera um ID único entre 100 e 1000.
 *
 * Esta função gera um ID aleatório no intervalo [100, 1000] e verifica se esse ID
 * já existe na árvore binária de busca. Se o ID já existir, a função tenta gerar
 * um novo ID de forma recursiva. A função continua até gerar um ID único.
 *
 * @param root Ponteiro para o nó raiz da árvore binária de busca onde a busca será realizada.
 * @return O novo ID gerado, garantido como único na árvore.
 * 
 * @note A função utiliza a função `exists` para verificar se o ID gerado já existe na árvore.
 *       A função de geração de números aleatórios é inicializada com a semente do tempo usando `srand(time(NULL))`.
 */
unsigned short generate_id(Node* root)
{
    int min = 100;  ///< Valor mínimo do intervalo de geração de IDs.
    int max = 1000; ///< Valor máximo do intervalo de geração de IDs.

    srand(time(NULL));  ///< Inicializa o gerador de números aleatórios com a semente do tempo.

    // Gera um ID aleatório no intervalo [100, 1000).
    int new_id = rand() % (max - min) + min;

    // Verifica se o ID já existe na árvore, e se existir, tenta gerar um novo ID.
    if (exists(root, new_id)) 
        return generate_id(root);  ///< Chamada recursiva para tentar gerar um ID único.

    return new_id;  ///< Retorna o ID gerado que é único na árvore.
}

/**
 * @brief Inicializa a árvore de nós, retornando um ponteiro nulo.
 *
 * Esta função é usada para criar uma árvore binária vazia, ou seja, o ponteiro
 * para o nó raiz é inicializado como NULL.
 *
 * @return Ponteiro nulo, representando uma árvore vazia.
 */
Node *initialize()
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
Node *create_node(const Book book)
{
    // Aloca memória para um novo nó.
    Node *new_node = (Node *)malloc(sizeof(Node));

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
    if ((*root) == NULL)
    {
        Node *new_node = create_node(book); // Cria um novo nó com os dados do livro.
        *root = new_node;                   // Define o novo nó como o nó raiz ou como filho do nó anterior.
        return;
    }

    // Se o id do livro for menor que o id do nó atual, insere recursivamente à esquerda.
    if (book.id < (*root)->book.id)
        insert(&(*root)->left, book);
    // Se o id do livro for maior que o id do nó atual, insere recursivamente à direita.
    else if (book.id > (*root)->book.id)
        insert(&(*root)->right, book);
    else
        fprintf(stderr, "Este livro ja foi inserido na biblioteca.\n");
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
Node *load_books(const char *file_path, Node *root)
{
    // Abre o arquivo no modo leitura.
    FILE *input_file = fopen(file_path, "r");

    // Verifica se o arquivo foi aberto corretamente.
    if (!input_file)
    {
        // Exibe uma mensagem de erro caso o arquivo não possa ser lido.
        fprintf(stderr, "Unable to read file \"%s\": %s.\n", file_path, strerror(errno));
        return NULL; // Retorna NULL em caso de erro ao abrir o arquivo.
    }

    char linha[512]; // Buffer para ler cada linha do arquivo.
    Book book;       // Variável para armazenar os dados do livro.

    // Lê cada linha do arquivo até o final.
    while (fgets(linha, sizeof(linha), input_file))
    {
        //book.id = generate_id();
        // Tenta analisar os dados da linha e preencher a estrutura Book.
        int success = sscanf(linha, "%hu,%99[^,],%99[^,],%49[^,],%u,%49[^,],%u",
                             &book.id, book.title, book.author, book.genre, &book.year,
                             book.publisher, &book.pages);

        // Se a linha foi lida com sucesso (7 campos), insere o livro na árvore.
        if (success == 7)
            insert(&root, book);
    }

    // Fecha o arquivo após terminar a leitura.
    fclose(input_file);

    // Retorna a árvore binária com os livros carregados.
    return root;
}

/**
 * @brief Converte uma string para minúsculas.
 *
 * Esta função recebe uma string como entrada e retorna uma nova string onde todos
 * os caracteres alfabéticos foram convertidos para minúsculas. A string original
 * não é modificada. A memória para a nova string é alocada dinamicamente e deve
 * ser liberada pelo usuário após o uso.
 *
 * @param str A string de entrada que será convertida para minúsculas.
 * @return Uma nova string com todos os caracteres em minúsculas. Retorna NULL se
 *         ocorrer um erro de alocação de memória.
 */
static char* strlower(const char* str) 
{
    // Aloca memória suficiente para a nova string, incluindo o caractere nulo '\0'
    char* s = malloc(strlen(str) + 1);

    // Verifica se a alocação foi bem-sucedida
    if (s == NULL)
        return NULL;

    // Converte cada caractere para minúsculo
    for (size_t i = 0; i < strlen(str); ++i)
        s[i] = tolower(str[i]);

    // Retorna a nova string com todos os caracteres em minúsculas
    return s;
}

/**
 * @brief Busca livros por gênero em uma árvore binária e exibe os encontrados.
 * 
 * Esta função percorre recursivamente uma árvore binária, buscando livros cujo gênero 
 * seja igual ao gênero fornecido como parâmetro. Quando um livro com o gênero correspondente 
 * é encontrado, a função indicada no parâmetro `print` é chamada para exibir as informações 
 * do livro. A travessia da árvore é feita em pré-ordem (processando o nó atual antes dos filhos).
 * 
 * @param root Ponteiro para o nó raiz da árvore binária.
 * @param genre O gênero do livro a ser buscado na árvore. A busca é feita de forma case-insensitive.
 * @param print Função que será chamada para imprimir as informações do livro encontrado. 
 *
 */
void search_by_genre(Node *root, const char *genre, void (*print)(const Book book))
{
    // Se o nó atual não for NULL, continua a busca.
    if (root != NULL)
    {
        // Converte o gênero do livro e o gênero de busca para minúsculas.
        char *aux_book_genre = strlower(root->book.genre);
        char *aux_genre = strlower(genre);

        // Se o gênero do livro no nó atual for igual ao gênero buscado, exibe as informações do livro.
        if (strcmp(aux_genre, aux_book_genre) == 0)
            print(root->book);

        // Libera a memória alocada para as versões minúsculas das strings.
        free(aux_book_genre);
        free(aux_genre);

        // Recursivamente busca à esquerda e à direita da árvore.
        search_by_genre(root->left, genre, print);
        search_by_genre(root->right, genre, print);
    }
}

/**
 * @brief Exibe os livros de uma árvore binária de forma recursiva.
 * 
 * Esta função percorre recursivamente uma árvore binária, exibindo as informações 
 * de cada livro armazenado em cada nó. Para cada nó, a função indicada no parâmetro 
 * `print` será chamada para exibir os dados do livro. A travessia da árvore segue a 
 * ordem pré-ordem, ou seja, o nó atual é processado antes de seus filhos esquerdo e direito.
 * 
 * @param root Ponteiro para o nó raiz da árvore binária.
 * @param print Função que será usada para imprimir as informações do livro armazenado 
 *              no nó.
 * 
 */
void show_books(Node *root, void (*print)(const Book book))
{
    // Se o nó atual não for NULL, continua a exibição.
    if (root != NULL)
    {
        // Exibe as informações do livro no nó atual.
        print(root->book);

        // Recursivamente exibe os livros à esquerda e à direita da árvore.
        show_books(root->left, print);
        show_books(root->right, print);
    }
}

/**
 * @brief Libera a memória de uma árvore binária.
 *
 * Esta função recursivamente percorre a árvore binária, de baixo para cima, e libera a memória de cada nó.
 * O processo de desalocação é feito em pós-ordem, ou seja, os filhos de cada nó são desalocados antes do próprio nó.
 *
 * @param root Ponteiro para o nó raiz da árvore a ser desalocada.
 */
void deallocate(Node *root)
{
    // Caso base: se o nó atual for NULL, não há nada a fazer
    if (root == NULL)
        return;

    // Desaloca recursivamente o nó à esquerda da árvore
    deallocate(root->left);
    // Desaloca recursivamente o nó à direita da árvore
    deallocate(root->right);
}
