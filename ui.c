#include "store.h"
#include "products.h"
#include "shopping_cart.h"
#include "ui.h"

/**
 * @brief Imprime el título del programa.
 */
void Print_Title(void) {
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

/**
 * @brief Imprime el menú de opciones de la tienda.
 * @param store_name Nombre de la tienda (String)
 */
void Print_Menu(char* store_name)
{
    printf("\n=====| %s |=====\n(1) Ver Inventario\n(2) Añadir Producto\n(3) Remover Producto\n(4) Sumar Productos al Inventario\n(5) Restar Productos al Inventario\n(6) Añadir Producto al Carrito\n(7) Comprar Productos del Carrito\n(8) Devolver Productos del Carrito\n(9) Salir\n===============\n", store_name);
}
/**
 * @brief Imprime el inventario de la tienda.
 * @param store Puntero a la tienda.
 */

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
/**
 * @brief Imprime el contenido del carrito de compras.
 * @param cart Puntero al carrito de compras.
 */



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


/*
* @brief Imprime toda la pila usando Stack_Pop()
* @param cart Puntero de "Shopping_Cart"
*/
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
