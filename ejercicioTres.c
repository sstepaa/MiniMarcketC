/*Escriba un programa que permita registrar las ventas y productos que se venden en un pequeño supermercado de barrio.
De los productos se guarda la siguiente información
1-Id producto
2-Nombre del producto
3-Precio
4-Contenido neto / cant

Crear un programa que calcule el valor que debe pagar el cliente, en base a los productos que desea llevar, así como el producto más vendido
-Al comenzar el dia el dueño de la tienda, carga los nuevos productos que tiene para vender
-El dueño del local va a atender a 10 clientes en el dia o hasta que el nuevo de cliente sea igual a 0(cero).
-Cada cliente puede llevar la cantidad de productos que desee siempre que sea mayor a cero y menor a 100.
-Se debe calcular y mostrar el precio total(cantidad x precio) de cada producto elegido, pueden hacerlo creando otra lista que guarde solo los precios totales segun el producto.
-Mostrar una lista de todos los productos disponibles. Para esto se puede usar la lista creada anterioramente o usando su imaginacion.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct listaProducto
{
    int idProducto;
    char nombreProducto[15];
    float precio;
    int cantidad;

    struct listaProducto *siguiente;
} nodo;

typedef struct venta
{
    char nombreCliente[15];
    int idCliente;
    int idProductoCliente;
    int cantidad;
    float precioVenta;

    struct venta *siguiente;

}venta;

typedef struct ventaProducto
    {
        int idProducto;
        float precioProducto;
        int cantidadProducto;

        struct ventaProducto *siguiente;
    }nodoTotal;


//Bloque de funciones
void cargarProducto(nodo *aux, int *contador);
void mostrarProd(nodo *aux);

void cargarVenta(nodo *auxProducto, venta *auxVenta, int *contador);
void mostrarVentas(venta *auxVenta);

void serchVentas(nodoTotal *auxTotal, venta *auxVenta);
void mostrarEstadisticasVentas(nodoTotal *auxTotal);
//Bloque de funciones

int main()
    {
        int contadorIdProducto = 0,contadorIdCliente = 0;
        int numMenu;
        //int contadorTotalVentas = 0, sumadorTotalVentas = 0;
        //Creo mi ountero cabeza de lista
        nodo* cabezaListaProd;
        venta* cabezaListaVenta;
        nodoTotal* cabezaListaTotal;
        //Resevervo memoria para mi puntero
        cabezaListaProd = (nodo*)malloc(sizeof(nodo));
        cabezaListaVenta = (venta*)malloc(sizeof(venta));
        cabezaListaTotal = (nodoTotal*)malloc(sizeof(nodoTotal));

        //Apuntos todos mis punteros a NULL
        cabezaListaProd->siguiente = NULL;
        cabezaListaVenta->siguiente = NULL;
        cabezaListaTotal->siguiente = NULL;

        //Carga de los productos
        /*printf("Carga de producto\n");
        cargarProducto(cabezaListaProd, &contadorIdProducto);
        mostrarProd(cabezaListaProd);*/

        //Carga de los clientes
        /*cargarVenta(cabezaListaProd, cabezaListaVenta, &contadorIdCliente);
        mostrarVentas(cabezaListaVenta);*/
        //Armar un menu
        do
            {
                printf("\nMenu\n1 - Cargar nuevos productos(solo proveedor)\n2 - Mostrar lista de productos\n3 - Ingresar clientes\n4 - Mostrar lista de clientes\n5 - Ver estadisticas de compras\n0 - Salir\nPor favor elija una opcion:\t ");
                scanf("%d", &numMenu);

                switch (numMenu)
                {
                case 1:
                    cargarProducto(cabezaListaProd, &contadorIdProducto);
                    break;
                case 2:
                    mostrarProd(cabezaListaProd);
                    break;
                case 3:
                    cargarVenta(cabezaListaProd, cabezaListaVenta, &contadorIdCliente);
                    break;
                case 4:
                    mostrarVentas(cabezaListaVenta);
                    break;
                case 5:
                    serchVentas(cabezaListaTotal, cabezaListaVenta);
                    mostrarEstadisticasVentas(cabezaListaTotal);
                    break;
                case 0:
                        printf("Saliendo del programa...\n");
                        break;
                default:
                    printf("Opcion no valida. Intente nuevamente\t");
                    break;
                }
            }while(numMenu != 0);

        return 0;
    }

void cargarProducto(nodo *aux, int* contador)
    {
        printf("Ingrese el nombre del producto\t");
        scanf("%s", aux->nombreProducto);
        //Caso base
        if(strcmp(aux->nombreProducto, "FIN") == 0)
            {
                aux->siguiente = NULL;
                return;
            }
        //Caso general
        printf("Ingrese el precio del producto\t");
        scanf("%f", &aux->precio);

        printf("Ingrese la cantidad que tiene en stock\t");
        scanf("%d",&aux->cantidad);

        (*contador)++;
        aux->idProducto = *contador;

        //Reservo memoria para el puntero siguiente
        aux->siguiente = (nodo*)malloc(sizeof(nodo));
        //Llamo a la funcion recursivamente
        cargarProducto(aux->siguiente, contador);

        
    }
void mostrarProd(nodo* aux)
    {
        //Caso base
        if(aux->siguiente == NULL)
            {
                return;
            }
        //Caso general
        printf("Numero identificado [%d]\t Nombre del producto [%s]\t Precio [$%.2f]\t Cantidad disponible [%d]\n", aux->idProducto, aux->nombreProducto, aux->precio,aux->cantidad);

        //Avanzar con el aux->sig en la funcion de manera recursiva
        mostrarProd(aux->siguiente);
        
    }

void cargarVenta(nodo *auxProducto, venta *auxVenta, int *contador)
    {
        printf("Ingrese el nombre del cliente\t");
        scanf("%s", auxVenta->nombreCliente);

        //Caso baso
        if(strcmp(auxVenta->nombreCliente, "FIN") == 0)
            {
                auxVenta->siguiente = NULL;
                return;
            }
        //Caso general
        //Necesito en el caso de cargar mi nueva lista recorrer mi lista anterior y buscar si los datos existen o no.  
        printf("Ingrese el ID del producto\t");
        scanf("%d", &auxVenta->idProductoCliente);


        //Creo un puntero que apunte hacia la cabeza de la cabeza de la lista de PRODUCTO, para que se pueda mover sin que yo pierda mi CABEZA DE LISTA
        nodo *productoActual = auxProducto;//Importantisimo!!

        //El siguiente bucle va a a ser el encargado de verificar si ID producto coincide con ID producto del cliente, si no lo encuentra va a pasar al siguiente nodo hasta llegar al final( nodo -> NULL).
        while (productoActual != NULL && productoActual->idProducto != auxVenta->idProductoCliente)
        {
            productoActual = productoActual->siguiente;
        }
        if(productoActual == NULL)
            {
                printf("Producto no encontrado, intente nuevamente\n");
                cargarVenta(auxProducto, auxVenta, contador);//Revisar si paso -sig
                return;
            }

        //Si el ID del producto lo encuentra entonces ejecuta todo lo que viene a continuacion
        printf("Ingrese la cantidad que desea comprar\t");
        scanf("%d",&auxVenta->cantidad);

        //Verificacion de la cantidad solicitada con la de la lista PRODUCTO
        if(productoActual->cantidad < auxVenta->cantidad)
            {
                printf("No hay tanta cantidad en stock, reingrese una nueva cifra\t");
                cargarVenta(auxProducto, auxVenta, contador);
                return;

            }
            productoActual->cantidad -= auxVenta->cantidad; //Se va restando la cantidad que tiene el nodo actual que tenemos la cantidad solicitada por el cliente.

            auxVenta->precioVenta = productoActual->precio;

            (*contador)++;
            auxVenta->idCliente = *contador; 

            //Se reserva memoria para el proximo nodo de nuestra lista cliente
            auxVenta->siguiente = (venta*)malloc(sizeof(venta));
            //Se vuelve a llamar a la funcion para que evalue el caso base, pero con el nuevo nodo creado
            cargarVenta(auxProducto, auxVenta->siguiente, contador);
           

    }

void mostrarVentas(venta *auxVenta)
    {
        //Caso base
        if(auxVenta->siguiente == NULL)
            {
                return;
            }
        //Caso general
        printf("Nombre del cliente [%s]\t ID del cliente [%d]\t ID producto [%d]\t Cantidad solicitada [%d]\n", auxVenta->nombreCliente, auxVenta->idCliente, auxVenta->idProductoCliente,auxVenta->cantidad);

        //Avanzo con la recursividad
        mostrarVentas(auxVenta->siguiente);

    }

void serchVentas(nodoTotal *auxTotal, venta *auxVenta)
    {
        //Necesito recorrer mi lista de clientes ¿Para que?, por cada nodo que se encuentra con el mismo Id se va a extraer el precio y unidades.
        //Lo voy a recorrer con recursividad
        if(auxVenta == NULL)//Recorre la lista de los clientes
            {
                return;
            }

        //Caso general
        
        //Necesito evaluar si el nodo de los clientes y el nodo nuevo tienen el mismo ID de producto para no hacer dos nodos con dos mismos ID
        nodoTotal *nuevoNodo = auxTotal;

        while (nuevoNodo != NULL)//Recorro mi lista de estadisticas de productos
        {
            if(nuevoNodo->idProducto == auxVenta->idProductoCliente)//Si mi Id de mi nuevo nodo es el mismo que el nodo de cliente actual, necesito guardar los datos en el mismo lugar / ACA HAY UN ERROR!!
                {
                    //Encontramos los nodos y acumulamos en el mismo NODO
                    nuevoNodo->cantidadProducto += auxVenta->cantidad;
                    nuevoNodo->precioProducto += auxVenta->precioVenta;

                    //Llamamos recursivamente a la funcion para que evalue el nuevo nodo
                    serchVentas(auxTotal, auxVenta->siguiente);
                    return;
                }
            //Si no sucede esto, quiero que el nuevo nodo camine al siguiente nodo y se evalue para todos los nodos existentes, si no encuentra similud que salga del bucle
            nuevoNodo = nuevoNodo->siguiente;
        }

        //SI NO EXISTE UN NODO CON EL MISMO ID, NECESITAMOS CREAR UNO NUEVO.
        

        nodoTotal *noditoNuevo = (nodoTotal*)malloc(sizeof(nodoTotal));
        noditoNuevo->idProducto = auxVenta->idProductoCliente;
        noditoNuevo->cantidadProducto = auxVenta->cantidad;
        noditoNuevo->precioProducto = auxVenta->precioVenta;
        noditoNuevo->siguiente = NULL;

        nuevoNodo = auxTotal;

        while (nuevoNodo->siguiente != NULL)
        {
            nuevoNodo = nuevoNodo->siguiente;
        }


        nuevoNodo->siguiente = noditoNuevo; //Se crea el enlace del nodoNuevo al noditoNuevo.
        
        
        //Necesito llamar recursivamente a mi funcion, para que evalue el nodo siguiente de la lista de los clientes
        serchVentas(auxTotal, auxVenta->siguiente);

    }

void mostrarEstadisticasVentas(nodoTotal *auxTotal)
    {
        //Recursividad
        //caso base
        if (auxTotal->siguiente == NULL)
        {
            return;
        }
        //Caso general
        printf("ID PRODUCTO [%d]\t Cantidad total comprada [%d]\t Precio total [%.2f]\n", auxTotal->idProducto, auxTotal->cantidadProducto, auxTotal->precioProducto);

        //Mover el puntero al sigueinte elemente
        mostrarEstadisticasVentas(auxTotal->siguiente);
        

    }

