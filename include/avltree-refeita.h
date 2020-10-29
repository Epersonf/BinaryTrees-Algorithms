typedef struct avlnode {
    int valor;
    int height;
    struct avlnode* right;
    struct avlnode* left;
} TAvl;

TAvl* avl_criar_no(int valor) {
    TAvl* node = (TAvl*) malloc(sizeof(TAvl));
    node->valor = valor;
    node->right = NULL;
    node->left = NULL;
    node->height = 1;
    return node;
}

int avl_max(int a, int b) {
    return (a > b) ? a : b;
}

int height(TAvl* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int avl_update_height(TAvl* node) {
    if (node == NULL)
        return 0;
    return 1 + avl_max(height(node->right), height(node->left));
}

int avl_balance(TAvl* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

TAvl* avl_right_rotate(TAvl* z) {
    TAvl* y = z->left;
    TAvl* T3 = y->right;

    y->right = z;
    z->left = T3;

    z->height = avl_update_height(z);
    y->height = avl_update_height(y);

    return y;
}

TAvl* avl_left_rotate(TAvl* z) {
    TAvl* y = z->right;
    TAvl* T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = avl_update_height(z);
    y->height = avl_update_height(y);

    return y;
}

TAvl* avl_inserir_no(TAvl* node, int valor) {

    //criacao do no
    if (node == NULL)
        return avl_criar_no(valor);

    //pesquisa de no
    if (valor < node->valor) {
        node->left = avl_inserir_no(node->left, valor);
    } else if (node->valor < valor) {
        node->right = avl_inserir_no(node->right, valor);
    } else {
        return node;
    }

    //atualizacao de altura
    node->height = avl_update_height(node);

    //balanceamento
    int balance = avl_balance(node);

    //left right case
    if (balance > 1) {
        if (node->left->valor < valor)
            node->left = avl_left_rotate(node->left);
        return avl_right_rotate(node);
    }

    //right left case
    if (balance < -1) {
        if (valor < node->right->valor)
            node->right = avl_right_rotate(node->right);
        return avl_left_rotate(node);
    }

    return node;
}

TAvl* avl_pega_no_mais_a_direita(TAvl* node) {
    TAvl* current = node;

    while(current->right != NULL)
        current = current->right;

    return current;
}

TAvl* avl_pega_no_mais_a_esquerda(TAvl* node) {
    TAvl* current = node;

    while(current->left != NULL)
        current = current->left;

    return current;
}

TAvl* avl_deleta_no(TAvl* node, int valor) {
    //se no nao existe
    if (node == NULL)
        return NULL;

    TAvl* aux;
    if (node->valor < valor) {
        //ir pra direita
        node->right = avl_deleta_no(node->right, valor);
    } else if (valor < node->valor) {
        //ir pra esquerda
        node->left = avl_deleta_no(node->left, valor);
    } else {
        //achou o no pra deletar
        if (node->right == NULL && node->left == NULL) {
            //se no folha
            free(node);
            return NULL;
        } else if (node->right != NULL && node->left != NULL) {
            //se no com duas subarvores
            aux = avl_pega_no_mais_a_direita(node->left);
            node->valor = aux->valor;
            node->left = avl_deleta_no(node->left, aux->valor);
        } else {
            //se no com uma arvore
            aux = (node->right != NULL) ? node->right : node->left;
            free(node);
            node = aux;
        }
    }

    //atualizacao de altura
    node->height = avl_update_height(node);

    //balanceamento
    int balance = avl_balance(node);

    if (balance > 1) {
        if (avl_balance(node->left) < 0)
            node->left = avl_left_rotate(node->left);
        return avl_right_rotate(node);
    }

    if (balance < -1) {
        if (avl_balance(node->right) > 0)
            node->right = avl_right_rotate(node->right);
        return avl_left_rotate(node);
    }

    return node;
}

void avl_free(TAvl* node) {
    if (node == NULL) return;
    avl_free(node->right);
    avl_free(node->left);
    free(node);
}

void _avl_printar(TAvl* node, int height) {
    if (node == NULL) return;

    _avl_printar(node->right, height + 1);

    for (int i = 0; i < height; i++)
        printf(">>>>");
    printf("%d\n", node->valor);

    _avl_printar(node->left, height + 1);
}

void avl_printar(TAvl* node) {
    printf("------------\n");
    printf("------------\n");
    _avl_printar(node, 0);
    printf("------------\n");
    printf("------------\n");
}
