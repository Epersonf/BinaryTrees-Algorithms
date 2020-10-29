typedef struct node {
    int valor;
    struct node* left;
    struct node* right;
} TNode;

TNode* pega_no_mais_a_esquerda(TNode* node) {
    if (node == NULL) return NULL;
    if (node->left == NULL) return node;
    return pega_no_mais_a_esquerda(node->left);
}

TNode* pega_no_mais_a_direita(TNode* node) {
    if (node == NULL) return NULL;
    if (node->right == NULL) return node;
    return pega_no_mais_a_direita(node->right);
}

TNode* cria_no(int valor) {
    TNode* novoNo = (TNode*) malloc(sizeof(TNode));
    novoNo->valor = valor;
    novoNo->right = NULL;
    novoNo->left = NULL;
    return novoNo;
}

TNode* _cria_arvore_de_lista(int lista[], int comeco, int fim) {
    if (fim - comeco <= 1) return NULL;

    int meio = (comeco + fim)/2;

    TNode* newNode = cria_no(lista[meio]);

    newNode->left = _cria_arvore_de_lista(lista, comeco, meio);

    newNode->right = _cria_arvore_de_lista(lista, meio, fim);

    return newNode;
}

TNode* cria_arvore_de_lista(int lista[], int tamanho) {
    return _cria_arvore_de_lista(lista, -1, tamanho);
}

TNode* busca_em_arvore(TNode* node, int valor) {
    if (node == NULL) return NULL;
    if (valor < node->valor) {
        return busca_em_arvore(node->left, valor);
    } else if (node->valor < valor) {
        return busca_em_arvore(node->right, valor);
    }
    return node;
}

TNode* deletar_no_especifico(TNode* node, int valor) {
    if (node == NULL) return NULL;

    if (valor < node->valor) {
        node->left = deletar_no_especifico(node->left, valor);
    } else if (node->valor < valor) {
        node->right = deletar_no_especifico(node->right, valor);
    } else {
        //se for o no a ser deletado
        if (node->right == NULL && node->left == NULL) {
            //caso no folha
            free(node);
            return NULL;
        } else if (node->right != NULL && node->left != NULL) {
            //caso duas subarvores
            TNode* aux = pega_no_mais_a_direita(node->left);
            node->valor = aux->valor;
            node->left = deletar_no_especifico(node->left, node->valor);
        } else {
            //caso uma subarvore
            TNode* aux = (node->right != NULL) ? node->right : node->left;
            free(node);
            return aux;
        }
    }

    return node;
}

void free_arvore(TNode* node) {
    if (node == NULL) return;
    free_arvore(node->right);
    free_arvore(node->left);
    free(node);
}

void printa_no(TNode* node, int height) {
    if (node == NULL) return;

    printa_no(node->right, height + 1);

    for (int i = 0; i < height; i++)
        printf("--");
    printf("%d\n", node->valor);

    printa_no(node->left, height + 1);
}
