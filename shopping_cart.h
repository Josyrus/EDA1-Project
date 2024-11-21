#ifndef SHOPING_CART_HEADER_H
#define SHOPING_CART_HEADER_H


/**
 * @brief Estructura para representar un carrito de compras.
 */
typedef struct Shopping_Cart {
    NodeProduct* top; /**< Puntero al nodo superior de la pila (último elemento añadido) */
    int LenProducts;/**< Cantidad de productos añadidos(Implementación de un carrito) */
    float PriceProducts;/**< Total del precio acomulado en la pila*/
} Shopping_Cart;

Shopping_Cart* Create_Stack();
void Stack_Push(Shopping_Cart* stack, NodeProduct* product);
NodeProduct* Stack_Pop(Shopping_Cart* stack);
void Destroy_Stack(Shopping_Cart** stack);
float Get_Total_Amount_Cart(Shopping_Cart* cart);
int Get_Total_Cart(Shopping_Cart* cart);

#endif

/**
 * @author
 * García Guerra Andrés Caleb
 * Carpizo Garduño Andrés 
 * Carro López Juan
 * Hernandez García Ivette Jaide
 * Fernández Chávez Luis Armando
 * @date 2024-22-18
 */