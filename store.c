#include"store.h"

static NodeProduct* New_Node(int id, int codebar, float price, int stock, const char* name, const char* tag)
{
    NodeProduct* n = (NodeProduct*)malloc(sizeof(NodeProduct));
    if (n) {
        n->next = n->prev = NULL;
        n->products = (Products*)malloc(sizeof(Products));
        if (n->products) {
            Create_Node_Products(n->products, id, codebar, price, stock, name, tag);
        }
        else {
            free(n);
            n = NULL;
        }
    }
    return n;
}

void Create_Node_Products(Products* p, int id, int codebar, float price, int stock, const char* name, const char* tag)
{
    p->id = id;
    p->codebar = codebar;
    p->price = price;
    p->stock = stock;
    strcpy(p->name, name);
    strcpy(p->tag, tag);
}

void Create_Products(Store* nstore, int codebar, float price, int stock, const char* name, const char* tag) {
    NodeProduct* n = New_Node(nstore->len, codebar, price, stock, name, tag);
    if (!n)
    {
        fprintf(stderr, "Memoria insuficiente");
        return;
    }
    if (nstore->len == 0) {
        nstore->first = nstore->last = n;
    }
    else {
        nstore->last->next = n;
        n->prev = nstore->last;
        nstore->last = n;
    }
    nstore->len++;
}

Store* New_Store(const char* name)
{
    Store* s = (Store*)malloc(sizeof(Store));
    if (s)
    {
        s->cursor = s->first = s->last = NULL;
        s->len = 0;
        strcpy(s->store_name, name);
    }
    return s;
}

void Destroy_Store(Store** store) {
    assert(store);
    NodeProduct* current = (*store)->first;
    NodeProduct* next_node;
    while (current != NULL) {
        next_node = current->next;
        Destroy_Product(&current);
        current = next_node;
    }
    free(*store);
    *store = NULL;
}

void Destroy_Product(NodeProduct** node) {
    assert(node);
    free((*node)->products);
    free(*node);
    *node = NULL;
}

void Remove_Product(Store* store) {
    assert(store->cursor);
    if (store->cursor == store->first)
    {

        store->first = store->cursor->next;
        if (store->first != NULL) {
            store->first->prev = NULL;
        }
    }
    else if (store->cursor == store->last)
    {
        store->last = store->cursor->prev;
        store->last->next = NULL;
    }
    else
    {
        store->cursor->prev->next = store->cursor->next;
        store->cursor->next->prev = store->cursor->prev;
    }
    Adjust_ID(store);
    free(store->cursor->products);
    free(store->cursor);
    store->len--;
    fprintf(stdout, "Producto eliminado del inventario.\n");
}
static void Adjust_ID(Store* store)
{
    NodeProduct* n = store->cursor;
    while (n != NULL)
    {
        n->products->id--;
        n = n->next;
    }
}
void Print_Title() {
    printf("\033[38;5;82m\n               _     _\n              | |   (_)\n  ___ __ _ ___| |__  _  ___ _ __ \n / __/ _` / __| '_ \\| |/ _ \\ '__|\n |(_| (_| \\__ \\ | | | |  __/ | \n \\___\\__,_|___/_| |_|_|\\___|_|  \033[0m");
    /*" Imprime lo siguiente:
               _     _
              | |   (_)
  ___ __ _ ___| |__  _  ___ _ __
 / __/ _` / __| '_ \| |/ _ \ '__|
| (_| (_| \__ \ | | | |  __/ |
 \___\__,_|___/_| |_|_|\___|_|

     "*/
}

void Print_Menu(char* store_name)
{
    printf("\n=====| %s |=====\n(1) Ver Inventario\n(2) Añadir Producto\n(3) Remover Producto\n(4) Sumar Productos al Inventario\n(5) Restar Productos al Inventario\n(6) Añadir Producto al Carrito\n(7) Comprar Productos del Carrito\n(8) Devolver Productos del Carrito\n(9) Salir\n===============\n", store_name);
}

void Printf_Inv(Store* store)
{
    NodeProduct* s = store->first;
    printf("\n|  id   |codebar|  name  |  price | stock  |    tag    |\n");
    while (s != NULL)
    {
        printf("| %05d |%07d| %s | $%.2f |   %02d   | %s |\n", s->products->id, s->products->codebar, s->products->name, s->products->price, s->products->stock, s->products->tag);
        s = s->next;
    }
}

Shopping_Cart* Create_Stack() {
    Shopping_Cart* stack = (Shopping_Cart*)malloc(sizeof(Shopping_Cart));
    if (stack) {
        stack->top = NULL;
        stack->LenProducts = 0;
        stack->PriceProducts = 0;
    }
    return stack;
}

void Stack_Push(Shopping_Cart* stack, NodeProduct* product) {
    ++stack->LenProducts;
    stack->top = (NodeProduct*)realloc(stack->top, stack->LenProducts * sizeof(NodeProduct));
    stack->top[stack->LenProducts - 1] = *product;
    stack->PriceProducts += product->products->price;
}

NodeProduct* Stack_Pop(Shopping_Cart* stack) {
    assert(stack->top);
    --stack->LenProducts;
    return &stack->top[stack->LenProducts];
}

void Destroy_Stack(Shopping_Cart** stack) {
    assert(stack);
    while ((*stack)->LenProducts != 0)
    {
        Stack_Pop(*stack);
    }
    free(*stack);
    *stack = NULL;
}

void Print_Cart(Shopping_Cart* cart) {
    int len = Get_Total_Cart(cart);
    if (len > 0) {
        printf("\n(%d) Total en el carrito: $%.2f\n", Get_Total_Cart(cart), Get_Total_Amount_Cart(cart));
    }
    else {
        printf("El carrito está vacío.\n");
        return;
    }
}

float Get_Total_Amount_Cart(Shopping_Cart* cart) {
    return cart->PriceProducts;
}

int Get_Total_Cart(Shopping_Cart* cart)
{
    return cart->LenProducts;
}
bool Move_Cursor_By_ID(Store* store, int key)
{
    for (NodeProduct* n = store->first; n != NULL; n = n->next)
    {
        if (n->products->id == key)
        {
            store->cursor = n;
            return true;
        }
    }
    return false;
}
NodeProduct* Subtract_Product(Store* store)
{
    assert(store->cursor);
    if (store->cursor->products->stock > 0) {
        --store->cursor->products->stock;
        return (Get_Cursor(store));
    }
    else
    {
        return NULL;
    }
}

void Print_ticket(Shopping_Cart* cart)
{
    int total = Get_Total_Amount_Cart(cart);
    printf("|id|\t\t|Product Name|\t\t|Price|\n");
    while (Get_Total_Cart(cart) > 0)
    {
        NodeProduct* tmp = Stack_Pop(cart);
        printf("|%d|\t\t|%s|\t\t|%f|", tmp->products->id, tmp->products->name, tmp->products->price);
    }printf("\t\t\t\t|Total| %d", total);
}

NodeProduct* Get_Cursor(Store* store)
{
    return(store->cursor);
}
void Sum_Product(NodeProduct* product)
{
    ++product->products->stock;
}