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

TBinaryTree* create_node(int key, TBinaryTree* left, TBinaryTree* right)
{
    TBinaryTree* newNode = (TBinaryTree*) malloc(sizeof(TBinaryTree));
    newNode->key = key;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

TBinaryTree* remove_node(TBinaryTree* node, int key)
{
    if (node == NULL) return NULL;
    if (node->key < key)
    {
        node->right = remove_node(node->right, key);
    }
    else if (key < node->key)
    {
        node->left = remove_node(node->left, key);
    }
    else
    {
        //se igual
        if (node->right == NULL && node->left == NULL)
        {
            free(node);
            return NULL;
        }
        else if (node->right != NULL && node->left != NULL)
        {
            //duas sub-arvores
            TBinaryTree* aux = get_more_left(node->right);
            node->key = aux->key;
            aux->key = key;
            remove_node(node->right, key);
        }
        else
        {
            TBinaryTree* r = (node->right != NULL) ? node->right : node->left;
            free(node);
            return r;
        }
    }
    return node;
}

void delete_tree(TBinaryTree* node)
{
    if (node == NULL) return;
    delete_tree(node->right);
    delete_tree(node->left);
    free(node);
}

void print_tree(TBinaryTree* node, int height)
{
    if (node == NULL) return;
    print_tree(node->right, height + 1);
    for (int i = 0; i < height; i++)
        printf("---");
    printf("%d\n", node->key);
    print_tree(node->left, height + 1);
}
