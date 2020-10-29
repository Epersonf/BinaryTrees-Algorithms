//Exercicio 1 - Segunda lista de exercicios
int is_equal(TNoAVL* node1, TNoAVL* node2) {
    if (node1 == NULL && node2 == NULL) return true;
    if (node1 == NULL || node2 == NULL) return false;
    if (node1->key != node2->key) return false;
    return is_equal(node1->right, node2->right) && is_equal(node1->left, node2->left);
}

//Exercicio 2 - Segunda lista de exercicios
TNoAVL* clone(TNoAVL * node) {
    if (node == NULL) return NULL;
    TNoAVL* newNode = avl_create_node(node->key);
    newNode->right = clone(node->right);
    newNode->left = clone(node->left);
    return newNode;
}

//Exercicio 3 - Segunda lista de exercicios
int is_complete(TNoAvl* node) {
    if (node == NULL) return 1;
    if ((node->left == NULL || node->right == NULL) && node->height > 2)
        return 0;
    return is_complete(node->right) && is_complete(node->left);
}

//Exercicio 4 - Segunda lista de exercicios


//Exercicio 5 - Segunda lista de exercicios

TNoAVL* simetric_search(TNoAVL* node, int key) {
    TNoAVL* current = node;
    TStack* tStack = create_stack(100);
    while (current != NULL) {
        if (current->key == key)
            return current;
        if (current->right != NULL)
            add_to_stack(tStack, current->right);
        current = current->left;
        if (current == NULL)
            current = get_from_stack(tStack);
    }
    return NULL;
}

TNoAVL* post_order_search(TNoAVL* node, int key) {
    TNoAVL* current = node;
    TStack* tStack = create_stack(100);
    while (current != NULL) {

    }
}
