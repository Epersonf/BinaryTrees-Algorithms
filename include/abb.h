typedef struct binaryTree
{
    int key;
    struct binaryTree* left;
    struct binaryTree* right;
} TBinaryTree;

TBinaryTree* get_more_right(TBinaryTree* node)
{
    if (node == NULL) return node;
    if (node->right == NULL) return node;
    return get_more_right(node->right);
}

TBinaryTree* get_more_left(TBinaryTree* node)
{
    if (node == NULL) return NULL;
    if (node->left == NULL) return node;
    return get_more_left(node->left);
}

TBinaryTree* create_node(int key)
{
    TBinaryTree* newNode = (TBinaryTree*) malloc(sizeof(TBinaryTree));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TBinaryTree* remove_node(TBinaryTree* node, int key)
{
    if (node == NULL) return NULL;
    TBinaryTree* aux;
    if (node->key < key)
        node->right = remove_node(node->right, key);
    else if (key < node->key)
        node->left = remove_node(node->left, key);
    else
    {
        //se igual
        if (node->right == NULL && node->left == NULL)
        {
            //no folha
            free(node);
            return NULL;
        }
        else if (node->right != NULL && node->left != NULL)
        {
            //duas sub-arvores
            aux = get_more_left(node->right);
            node->key = aux->key;
            aux->key = key;
            node->right = remove_node(node->right, key);
        }
        else
        {
            //no com 1 subarvore
            aux = (node->right != NULL) ? node->right : node->left;
            free(node);
            return aux;
        }
    }
    return node;
}

TBinaryTree* add_node(TBinaryTree* node, int key) {
    if (node == NULL)
        return create_node(key);
    else if (key < node->key)
        node->left = add_node(node->left, key);
    else if (node->key < key)
        node->right = add_node(node->right, key);
    return node;
}

void free_tree(TBinaryTree* node)
{
    if (node == NULL) return;
    free_tree(node->right);
    free_tree(node->left);
    free(node);
}

void print_tree(TBinaryTree* node, int avl_height)
{
    if (node == NULL) return;
    print_tree(node->right, avl_height + 1);
    for (int i = 0; i < avl_height; i++)
        printf("---");
    printf("%d\n", node->key);
    print_tree(node->left, avl_height + 1);
}
