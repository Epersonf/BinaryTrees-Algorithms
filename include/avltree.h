#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} TNoAVL;

TNoAVL* avl_get_more_left(TNoAVL* node) {
    if (node == NULL) return NULL;
    if (node->left == NULL) return node;
    return avl_get_more_left(node->left);
}

TNoAVL* avl_get_more_right(TNoAVL* node) {
    if (node == NULL) return NULL;
    if (node->right == NULL) return node;
    return avl_get_more_right(node->right);
}

// A utility function to get the height of the tree
int avl_height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* avl_create_node(int key)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

int avl_get_height(TNoAVL* node) {
    return max(avl_height(node->left), avl_height(node->right))+1;
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *avl_right_rotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = avl_get_height(y);
    x->height = avl_get_height(x);

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *avl_left_rotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = avl_get_height(x);
    y->height = avl_get_height(y);

    // Return new root
    return y;
}

// Get Balance factor of node N
int avl_get_balance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return avl_height(N->left) - avl_height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
TNoAVL* avl_insert_node(struct Node* node, int key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(avl_create_node(key));

    if (key < node->key)
        node->left  = avl_insert_node(node->left, key);
    else if (key > node->key)
        node->right = avl_insert_node(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = avl_get_height(node);

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = avl_get_balance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return avl_right_rotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return avl_left_rotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  avl_left_rotate(node->left);
        return avl_right_rotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = avl_right_rotate(node->right);
        return avl_left_rotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

TNoAVL* avl_remove_node(TNoAVL* node, int key) {
    if (node == NULL) return NULL;
    TNoAVL* aux;
    TNoAVL* toReturn = node;
    if (node->right != NULL && node->right->key < key) {
        node->right = avl_remove_node(node->right, key);
    } else if (node->left != NULL && key < node->left->key) {
        node->left = avl_remove_node(node->left, key);
    } else {
        if (node->right == NULL && node->left == NULL) {
            //no folha
            free(node);
            toReturn = NULL;
        } else if (node->right != NULL && node->left != NULL) {
            //duas subarvores
            aux = avl_get_more_right(node->left);
            node->key = aux->key;
            aux->key = key;
            avl_remove_node(node->left, key);
        } else {
            //uma subarvore
            toReturn = (node->right != NULL) ? node->right : node->left;
            free(node);
        }
    }
    return toReturn;
}

void avl_free(TNoAVL* node) {
    if (node == NULL) return;
    avl_free(node->left);
    avl_free(node->right);
    free(node);
}

void avl_print(TNoAVL* no, int avl_height) {
	if (no == NULL) return;
	avl_print(no->right, avl_height + 1);
	for (int i = 0; i < avl_height; i++)
		printf("---");
	printf("%d\n", no->key);
	avl_print(no->left, avl_height + 1);
}
