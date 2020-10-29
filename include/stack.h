typedef struct stackstruct {
    int top;
    TAVL** nodeList;
} TStack;

void pop(TStack* tStack) {
    if (tStack->top < 0) return;
    tStack->top--;
}

TStack* create_stack(int max_size) {
    TStack* newStack = (TStack*) malloc(sizeof(TStack));
    newStack->top = -1;
    newStack->nodeList = (TAVL*) malloc(sizeof(TNoAVL) * max_size);
    return newStack;
}

TAVL* add_to_stack(TStack* tStack, TAVL* node) {
    tStack->top++;
    int top = tStack->top;
    tStack->nodeList[top] = node;
    return node;
}

TNoAVL* get_from_stack(TStack* tStack) {
    int top = tStack->top;
    if (top < 0) return NULL;
    TNoAVL* node = tStack->nodeList[top];
    pop(tStack);
    return node;
}
