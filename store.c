#include "store.h"
#include "products.h"
#include "shopping_cart.h"
#include "ui.h"

/**
 * @brief Crea una nueva tienda.
 * @param name Nombre de la tienda.
 * @return Puntero a la tienda creada.
 */
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
/**
 * @brief Destruye una tienda y libera memoria.
 * @param store Puntero a la tienda a destruir.
 * @warning SÓLO debe usarse para salir del programa, además de asegurarse que exista una tienda que borrar
 */
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

/**
 * @brief Elimina un producto de la tienda y mueve a la derecha el cursor.
 * @warning elimina donde esta ubicado el cursor
 * @param store Puntero a la tienda.
 * @param id Identificador único del producto a eliminar.
 * @warning Debe de asegurarse que el producto exista antes de ejecutar esta función, en dado caso se disparara un 'assert()'
 */
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
/*
* @brief Mueve el cursor a un ID dado por el usuario
* @param store Puntero de store
* @param key id a buscar en "store"
* @return bool si fue posible mover el cursor
*/
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
/*
* @brief Elimina parte del inventario del producto
* @param store Puntero de store
* @return NodeProduct como copia de si mismo
* @details en caso de no poder retirar más productos retornara un valor 'NULL'
*/
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
/*
* @brief Obtiene el nodo donde esta el cursor
* @param cart Puntero de NodeProduct a modificar
*/
NodeProduct* Get_Cursor(Store* store)
{
    return(store->cursor);
}

/*
* @brief Añade productos a un NodeProduct
* @param cart Puntero de NodeProduct a modificar
*/
void Sum_Product(NodeProduct* product)
{
    ++product->products->stock;
}