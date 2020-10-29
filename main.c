#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "abb-refeito.h"
#include "avltree-refeita.h"
//#include "avltree.h"
//#include "abb.h"
#include "stack.h"
//#include "exercises-two.h"
#define len(a) sizeof(a)/sizeof(a[0])

int eh_simetrica(TAvl* node) {

    TAvl* currentLeft = node->left;
    TAvl* currentRight = node->right;

    if (currentLeft->valor == NULL && currentRight->valor == NULL)
        return 1;

    TStack* stack = create_stack(100);

    while(true) {
        if (currentLeft == NULL && currentRight == NULL) {
            //pega da pilha
            currentRight = get_from_stack(stack);
            currentLeft = get_from_stack(stack);
            if (currentLeft == NULL && currentRight == NULL)
                return 1;
            else if (currentLeft == NULL || currentRight == NULL)
                return 0;
            continue;
        } else if (currentLeft != NULL && currentRight != NULL) {
            //continua verificar
            continue;
        } else {
            return 0;
        }

        if (currentLeft->valor != currentRight->valor)
            return 0;

        add_to_stack(stack, currentLeft->right);
        add_to_stack(stack, currentRight->left);

        currentLeft = currentLeft->left;
        currentRight = currentLeft->right;
    }
    return 1;
}

int main()
{
    TAvl* node = avl_criar_no(5);

    node = avl_inserir_no(node, 6);
    node = avl_inserir_no(node, 7);
    node = avl_inserir_no(node, 3);
    node = avl_inserir_no(node, 8);
    node = avl_inserir_no(node, 9);
    node = avl_inserir_no(node, 2);
    node = avl_inserir_no(node, 12);
    node = avl_inserir_no(node, 15);

    avl_printar(node);

    printf("%d", is_complete(node));

    return 0;
}
