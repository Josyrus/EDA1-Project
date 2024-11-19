#ifndef STORE_HEADER_H
#define STORE_HEADER_H

/**
 * @file store.h
 * @brief Definiciones de estructuras y funciones para gestionar una tienda.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

 /**
  * @brief Estructura para representar un producto en la tienda.
  */
typedef struct Products {
    int id; /**< Identificador único del producto */
    int codebar; /**< Código de barras del producto */
    float price; /**< Precio del producto */
    int stock; /**< Stock disponible del producto */
    char name[50]; /**< Nombre del producto */
    char tag[30]; /**< Etiqueta del producto */
} Products;

/**
 * @brief Estructura para representar un nodo en la lista enlazada de productos.
 */
typedef struct NodeProduct {
    struct Products* products; /**< Producto almacenado en el nodo */
    struct NodeProduct* next; /**< Puntero al siguiente nodo */
    struct NodeProduct* prev; /**< Puntero al nodo previo */
} NodeProduct;

/**
 * @brief Estructura para representar una tienda.
 */
typedef struct Store {
    NodeProduct* cursor; /**< Puntero al nodo actual en la tienda */
    NodeProduct* first; /**< Puntero al primer nodo en la tienda */
    NodeProduct* last; /**< Puntero al último nodo en la tienda */
    int len; /**< Longitud de la tienda (cantidad de productos) */
    char store_name[30]; /**< Nombre de la tienda */
} Store;

/**
 * @brief Estructura para representar un carrito de compras.
 */
typedef struct Shopping_Cart {
    NodeProduct* top; /**< Puntero al nodo superior de la pila (último elemento añadido) */
    int LenProducts;/**< Cantidad de productos añadidos(Implementación de un carrito) */
    float PriceProducts;/**< Total del precio acomulado en la pila*/
} Shopping_Cart;

/**
 * @brief Imprime el título del programa.
 */
void Print_Title(void);

/**
 * @brief Imprime el menú de opciones de la tienda.
 * @param store_name Nombre de la tienda (String)
 */
void Print_Menu(char* store_name);
/**
 * @brief Crea un nuevo producto.
 * @param p Puntero al producto a crear.
 * @param id Identificador único del producto.
 * @param codebar Código de barras del producto.
 * @param price Precio del producto.
 * @param stock Stock disponible del producto.
 * @param name Nombre del producto.
 * @param tag Etiqueta del producto.
 */
void Create_Node_Products(Products* p, int id, int codebar, float price, int stock, const char* name, const char* tag);

/**
 * @brief Crea un nuevo producto en la tienda.
 * @param nstore Puntero a la tienda donde se agregará el producto.
 * @param codebar Código de barras del producto.
 * @param price Precio del producto.
 * @param stock Stock disponible del producto.
 * @param name Nombre del producto.
 * @param tag Etiqueta del producto.
 */
void Create_Products(Store* nstore, int codebar, float price, int stock, const char* name, const char* tag);

/**
 * @brief Crea un nuevo nodo de producto.
 * @details Esta funcion se cancelara en caso de no poder crear un producto
 * @param id Identificador único del producto.
 * @param codebar Código de barras del producto.
 * @param price Precio del producto.
 * @param stock Stock disponible del producto.
 * @param name Nombre del producto.
 * @param tag Etiqueta del producto.
 * @return Puntero al nuevo nodo creado.
 */
static NodeProduct* New_Node(int id, int codebar, float price, int stock, const char* name, const char* tag);

/*
* @brief Ajusta los ID de la lista
* @param apuntador store
*/
static void Adjust_ID(Store* store);
/**
 * @brief Crea una nueva tienda.
 * @param name Nombre de la tienda.
 * @return Puntero a la tienda creada.
 */
Store* New_Store(const char* name);

/**
 * @brief Destruye una tienda y libera memoria.
 * @param store Puntero a la tienda a destruir.
 * @warning SÓLO debe usarse para salir del programa, además de asegurarse que exista una tienda que borrar
 */
void Destroy_Store(Store** store);

/**
 * @brief Destruye un nodo de producto y libera memoria.
 * @param node Puntero al nodo a destruir.
 * @warning Debe asegurarse que "Product" sea diferente de 'NULL'
 */
void Destroy_Product(NodeProduct** node);

/**
 * @brief Elimina un producto de la tienda y mueve a la derecha el cursor.
 * @warning elimina donde esta ubicado el cursor
 * @param store Puntero a la tienda.
 * @param id Identificador único del producto a eliminar.
 * @warning Debe de asegurarse que el producto exista antes de ejecutar esta función, en dado caso se disparara un 'assert()'
 */
void Remove_Product(Store* store);

/**
 * @brief Imprime el inventario de la tienda.
 * @param store Puntero a la tienda.
 */
void Printf_Inv(Store* store);

/**
 * @brief Crea una nueva pila.
 * @return Puntero a la pila creada.
 */
Shopping_Cart* Create_Stack();

/**
 * @brief Agrega un producto a la pila (carrito de compras).
 * @param stack Puntero a la pila.
 * @param product Puntero al producto a agregar.
 */
void Stack_Push(Shopping_Cart* stack, NodeProduct* product);

/**
 * @brief Quita y devuelve el producto en la cima de la pila.
 * @param stack Puntero a la pila.
 * @return Puntero al producto en la cima de la pila.
 */
NodeProduct* Stack_Pop(Shopping_Cart* stack);

/**
 * @brief Destruye una pila y libera memoria.
 * @param stack Puntero a la pila a destruir.
 */
void Destroy_Stack(Shopping_Cart** stack);

/**
 * @brief Imprime el contenido del carrito de compras.
 * @param cart Puntero al carrito de compras.
 */
void Print_Cart(Shopping_Cart* cart);

/**
 * @brief Calcula el total de los productos en el carrito de compras.
 * @param cart Puntero al carrito de compras.
 * @return Suma total de los productos en el carrito.
 */
float Get_Total_Amount_Cart(Shopping_Cart* cart);
/*
* @brief Devuelve la cantidad de objetos alojados en la pila (Carrito).
* @param cart Puntero al carrito de compras.
* @return Total de los productos
*/
int Get_Total_Cart(Shopping_Cart* cart);
/*
* @brief Mueve el cursor a un ID dado por el usuario
* @param store Puntero de store
* @param key id a buscar en "store"
* @return bool si fue posible mover el cursor
*/
bool Move_Cursor_By_ID(Store* store, int key);
/*
* @brief Elimina parte del inventario del producto
* @param store Puntero de store
* @return NodeProduct como copia de si mismo
* @details en caso de no poder retirar más productos retornara un valor 'NULL'
*/
NodeProduct* Subtract_Product(Store* store);
/*
* @brief Imprime toda la pila usando Stack_Pop()
* @param cart Puntero de "Shopping_Cart"
*/
void Print_ticket(Shopping_Cart* cart);
/*
* @brief Añade productos a un NodeProduct
* @param cart Puntero de NodeProduct a modificar
*/
void Sum_Product(NodeProduct* product);
/*
* @brief Obtiene el nodo donde esta el cursor
* @param cart Puntero de NodeProduct a modificar
*/
NodeProduct* Get_Cursor(Store* store);
/**
 * @author
 * Garcia Guerra Andres Caleb
 *
 */
 /**
  * @date 2024-22-18
  */
#endif
