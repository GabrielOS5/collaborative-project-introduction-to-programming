/*
	@version: 1.0
	@since: 2023-05-05
	@copyright: Todos los derechos reservados
	@author: Jose Gabriel Osorio Salgado <josegabriel.osorio5@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Declaracion de estructura
typedef struct {
	int id;
    char nombre[50];
    char apellido_paterno[50];
    char apellido_materno[50];
    char curp[20];
    char direccion[50];
    char telefono[14];
    char email[50];
} Empleado;

// Declaracion de funciones
void mensaje_error(void);
bool validar_eliminacion(void);
void registro_no_disponible(void);
Empleado registrar_empleado(int id, char mensaje[]);
void buscar_empleado(Empleado empleados[], int size_array);
void eliminar_empleado(Empleado empleados[], int size_array);
void consultar_empleados(Empleado empleados[], int size_array);
void informacion_a_detalle(Empleado empleados[], int posicion);
void actualizar_empleado(Empleado empleados[], int size_array);

// Declaracion de variables globales
int contador = 0;
Empleado empleados[100];

/*
	Metodo principal que ejecutara todas las funciones
*/
int main(void) {
	// Inicializacion de variables
	int opcion;
	int id_pk = 1;
	Empleado empleado;
	bool bandera = true;
	
	// Insercion de datos para test de prueba
	empleados[contador].id = 1;
	strcpy(empleados[contador].nombre , "Jose Gabriel");
    strcpy(empleados[contador].apellido_paterno , "Osorio");
    strcpy(empleados[contador].apellido_materno , "Salgado");
    strcpy(empleados[contador].curp , "XXXX000000XXXXXXXX");
    strcpy(empleados[contador].direccion , "Calle Buenavista Mz. 9 Lt. 10, Naucalpan, Edo. Mex");
    strcpy(empleados[contador].telefono , "5500000000");
    strcpy(empleados[contador].email , "josegabriel.osorio5@gmail.com");
    
	// Desarrollo de la logica de negocio
	printf("----------------------------------------\n");
	printf("         Personal electronico\n"         );
	printf("            FCA S.A de C.V\n"            );
	printf("----------------------------------------\n");
	printf(" ¡Bienvenido al Portal FCA!             \n");
	printf("----------------------------------------\n");
	
	do {
		printf(" 1. Registrar empleado\n");
		printf(" 2. Buscar empleado por nombre\n");
		printf(" 3. Actualizar datos del empleado\n");
		printf(" 4. Eliminar registros\n");
		printf(" 5. Salir\n");
		printf("----------------------------------------\n");
		
		if(scanf("%d", &opcion) == 1) {
			
			switch(opcion) {
				case 1:
					empleado = registrar_empleado(id_pk + 1, "registrado");
					id_pk++;
					contador++;
					empleados[contador] = empleado;
					break;
				case 2:
					buscar_empleado(empleados, contador + 1);
					break;
				case 3:
					actualizar_empleado(empleados, contador + 1);
					break;
				case 4:
					eliminar_empleado(empleados, contador + 1);
					break;
				case 5:
					bandera = false;
					printf("----------------------------------------\n");
					printf(" ¡Hasta luego, vuelva pronto!\n"         );
					printf("        Cerrando sesion\n"         );
					printf("----------------------------------------\n");
					break;
				default:
					printf("----------------------------------------\n");
					printf(" Ingrese una opcion disponible.\n"         );
					printf("----------------------------------------\n");
					break;
			}
			
		} else {
			mensaje_error();
		}
		
	} while(bandera);
	
	return 0;
}

/*
	Metodo que imprime toda la informacion del empleado
	@empleados: Array de tipo empleado donde estan todos los empleados registrados
	@posicion: Numero para obtener la informacion del elemento del array
*/
void informacion_a_detalle(Empleado empleados[], int posicion) {
	printf("---------------------------------------------------\n");
	printf(" ID: %d\n", empleados[posicion].id);
	printf(" Nombre: %s\n", empleados[posicion].nombre);
	printf(" Apellido Paterno: %s\n", empleados[posicion].apellido_paterno);
	printf(" Apellido Materno: %s\n", empleados[posicion].apellido_materno);
	printf(" CURP: %s\n", empleados[posicion].curp);
	printf(" Direccion: %s\n", empleados[posicion].direccion);
	printf(" Tel%sfono: %s\n", "\x82",empleados[posicion].telefono);
	printf(" Email: %s\n", empleados[posicion].email);
	printf("---------------------------------------------------\n");
}

/*
	Metodo que busca un empleado mediante su nombre, en caso de existir podra
	visualizar su informacion a detalle
	@empleados: Array de tipo empleado donde estan todos los empleados registrados
	@size_array: Numero de la cantidad total de empleados registrados
*/
void buscar_empleado(Empleado empleados[], int size_array) {
	printf("---------------------------------------------------\n");
	getchar();
	int i;
	int id;
	int ids[50];
	char nombre[30];
	Empleado empleado;
	int sumatoria = 0;
	bool empleado_encontrado = false;
	bool mostrar_informacion = false;
	
	printf(" Ingrese el nombre del empleado: ");
	fgets(nombre, 30, stdin);
	nombre[strcspn(nombre, "\n")] = 0;
	printf(" ID - Nombre completo\n");
	for(i = 0; i < size_array; i++) {
		if(strstr(empleados[i].nombre, nombre)) {
			empleado_encontrado = true;
			ids[sumatoria] = empleados[i].id;
			sumatoria++;
			printf(" %d  - %s %s %s\n", empleados[i].id, empleados[i].nombre, empleados[i].apellido_paterno, empleados[i].apellido_materno);
		}
	}
	
	if(empleado_encontrado) {
		printf("---------------------------------------------------\n");
		printf(" Ingrese el ID para consultar mas detalles:\n");
		scanf("%d", &id);
		for(i = 0; i < sumatoria; i++) {
			if(ids[i] == id) {
				mostrar_informacion = true;
				break;
			}
		}
		
		if(!mostrar_informacion) {
			registro_no_disponible();
		} else {
			for(i = 0; i < size_array; i++) {
				if(empleados[i].id == id) {
					informacion_a_detalle(empleados, i);
					break;
				}
			}
		}
		printf("---------------------------------------------------\n");
	} else {
		registro_no_disponible();
	}
	
}

/*
	Metodo que muestra todos los empleados disponibles, nuestra su ID y nombre
	completo
	@empleados: Array de tipo empleado donde estan todos los empleados registrados
	@size_array: Numero de la cantidad total de empleados registrados
*/
void consultar_empleados(Empleado empleados[], int size_array) {
	int i;
	printf("----------------------------------------\n");
	printf(" ID - Nombre completo\n");
	for(i = 0; i < size_array; i++) {
		printf(" %d   - %s %s %s\n", empleados[i].id, empleados[i].nombre, empleados[i].apellido_paterno, empleados[i].apellido_materno);
	}
	printf("----------------------------------------\n");
}

/*
	Metodo que solicita la informacion para registrar/actualizar informacion
	del empleado
	@id: Numero de identificacion del empleado
	@mensaje: Cadena donde los valores deberan ser "registrado" o "actualizado"
	@return: Empleado con nueva informacion
*/
Empleado registrar_empleado(int id, char mensaje[]) {
	printf("----------------------------------------\n");
	Empleado empleado;
	getchar();
    printf(" Ingrese el nombre: ");
    fgets(empleado.nombre, 50, stdin);
    empleado.nombre[strcspn(empleado.nombre, "\n")] = 0;
    
    printf(" Ingrese el apellido paterno: ");
    fgets(empleado.apellido_paterno, 50, stdin);
    empleado.apellido_paterno[strcspn(empleado.apellido_paterno, "\n")] = 0;
    
    printf(" Ingrese el apellido materno: ");
    fgets(empleado.apellido_materno, 50, stdin);
    empleado.apellido_materno[strcspn(empleado.apellido_materno, "\n")] = 0;
    
    printf(" Ingrese la CURP: ");
    fgets(empleado.curp, 20, stdin);
    empleado.curp[strcspn(empleado.curp, "\n")] = 0;
    
    printf(" Ingrese la direccion: ");
    fgets(empleado.direccion, 50, stdin);
    empleado.direccion[strcspn(empleado.direccion, "\n")] = 0;
    
    printf(" Ingrese el telefono: ");
    fgets(empleado.telefono, 14, stdin);
    empleado.telefono[strcspn(empleado.telefono, "\n")] = 0;
    
    printf(" Ingrese el email: ");
    fgets(empleado.email, 50, stdin);
    empleado.email[strcspn(empleado.email, "\n")] = 0;
    
    empleado.id = id;
    printf("------------------------------------------\n");
    printf(" Empleado %s satisfactoriamente.\n", mensaje);
    printf("------------------------------------------\n");
    return empleado;
}

/*
	Metodo que busca al empleado y actualiza su informacion
	@empleados: Array de tipo empleado donde estan todos los empleados registrados
	@size_array: Numero de la cantidad total de empleados registrados
*/
void actualizar_empleado(Empleado empleados[], int size_array) {
	int i;
	int id;
	Empleado empleado;
	bool empleado_encontrado = false;
	
	consultar_empleados(empleados, size_array);
	printf(" Ingrese el ID del empleado: ");
	scanf("%d", &id);
	
	for(i = 0; i < size_array; i++) {
		if(empleados[i].id == id) {
			empleado_encontrado = true;
			empleado = registrar_empleado(id, "actualizado");
			empleados[i] = empleado;
			break;
		}
	}
	
	if(!empleado_encontrado) {
		registro_no_disponible();
	}
}

/*
	Metodo que elimina la informacion de un empleado que este disponible
	@empleados: Array de tipo empleado donde estan todos los empleados registrados
	@size_array: Numero de la cantidad total de empleados registrados
*/
void eliminar_empleado(Empleado empleados[], int size_array) {
	int i;
	int id;
	bool eliminar_empleado;
	bool empleado_encontrado = false;
	
	consultar_empleados(empleados, size_array);
	printf(" Ingrese el ID del empleado: ");
	scanf("%d", &id);
	
	for(i = 0; i < size_array; i++) {
		if(empleados[i].id == id) {
			empleado_encontrado = true;
			eliminar_empleado = validar_eliminacion();
			if(!eliminar_empleado) {
				break;	
			}
			do {
				empleados[i] = empleados[i+1];
				i++;
			} while(i != size_array);
			contador--;
			printf("----------------------------------------\n");
			printf(" Registro eliminado correctamente.\n");
			printf("----------------------------------------\n");
			break;
		}
	}
	
	if(!empleado_encontrado) {
		registro_no_disponible();
	}
	
}

/*
	Metodo que valida la confirmacion/cancelacion de eliminar la informacion
	@return: boleeano donde true = confirmar la eliminacion y false = cancelar
	la eliminacion
*/
bool validar_eliminacion(void) {
	int opcion;
	printf("------------------------------------------\n");
	printf(" ¿ESTAS SEGURO DE ELIMINAR LA INFORMACION?.\n");
	printf(" 1. Confirmar la eliminacion.\n");
	printf(" 2. Cancelar la eliminacion.\n");
	scanf("%d", &opcion);
	printf("------------------------------------------\n");
	return opcion == 1;
}

/*
	Metodo que muestra mensaje cuando se ingresa un caracter en
	opciones numericas
*/
void mensaje_error(void) {
	printf("------------------------------------------------------------\n");
	printf(" ERROR: La entrada no es un numero. Vuelva a ingresarlo\n");
	printf("------------------------------------------------------------\n");
	fflush(stdin);
}

/*
	Metodo que muestra mensaje cuando no se encuentra registro o
	informacion de un empleado
*/
void registro_no_disponible(void) {
	printf("-------------------------------------------------\n");
	printf(" El registro no existe. Verifique su informacion.\n");
	printf("-------------------------------------------------\n");
}
