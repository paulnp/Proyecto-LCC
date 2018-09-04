#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;


/* Como seria la idea general para resolver el tester de Sudoku? 
   1) generar la matriz -> 1 Proceso separado del Padre
   		1.1)sabemos que la Matriz es de 9x9, asi que un arreglo bi-dimensional cuadrado de caracteres bastará
		1.2)Es necesario abrir el archivo de entrada (fopen()), leer caracter por caracter 
			(al usar caracteres, estamos usando ASCII, ver esto)
			1.2.1) mientras se lee el archivo (mientras NOT feof() -> fgetc(). Leer caracter a caracter), se carga la matriz
			1.2.2) una vez leido el archio y cargada la matriz, se cierra el archivo (fclose())
	2)Empezar a bifurcar en serio
		2.1)la idea seria usar 3 procesos distintos y hacer que el Padre espere a los 3 hijos
			2.1.1) Proceso que verifique las Filas del Sudoku
				Este verificará fila por fila que en esa fila esten los números del 1 al 9 (SIN REPETICIÓN)
			2.1.2) Proceso que verifique las Columnas del Sudoku
				Este verificará Columna por Columna que en esa columna esten los números del 1 al 9 (SIN REPETICIÓN) 
			2.1.3) Proceso que verifique los cuadrantes 3x3 del Sudoku
				Este verificará por Cuadrante (hay 9 cuadrantes, empezando en las posiciones (0,0), (0,3)  (0,6) 
				(3,0), (3,3), (3,6) , (6,0) , (6,3) , (6,6))
		2.2) Estos Procesos deben reportar si su tarea falló en caso de que la jugada sea inválida, al primero que lo hace, se 
			 debe cortar TODO, el padre debe matar a los hijos restantes (se podria hacer con una variable global, pero lo dudo)
		2.3) si NINGUNO falla y TODOS terminan, entonces la jugada de Sudoku era válida, entonces, el Padre reporta que la jugada era válida
	3) Consideraciones
		3.1) Los Procesos pueden fallar por si solos en cualquier momento, hay que ver las excepciones que pueden tirar y sus códigos
		3.2) Ver lo de la Variable Global para controlar que todo este en órden
		3.3) Una vez hecho esto con procesos, pasarlo a Threads es tan fácil como reemplazar los Procesos por Threads
		3.4) Verificar si es mejor usar char[][] o int[][], si es mejor usar int, hay que tener en cuenta que hay que traducir
			 el ASCII del caracter al número INT
		3.5) Preguntar sobre como reportar errores (códigos de error? Strings?)
		3.6) Preguntar sobre input de funciones por Punteros (no recuerdo si asi como lo hice esta bien o va con "&" al llamar)
		3.7) recordar que las funciones de archivos devuelven un int, ver que hacer con esto
		3.8) parece que exit() no puede hacer más que devolver 0 (terminación normal) o 1 (terminación anormal), existen
			 un par de funciones llamadas <int atexit (void (* function) (void))> y <int on_exit(void (*function)(int , void *), void *arg)>
			 que permiten ejecutar funciones cuando se llama a exit(), preguntar sobre su uso y como hacer el pasaje
			 (ya que requiere pasajes de función por punteros, lo que hicimos en Orga para el Primer Proyecto)
		3.9) El Chequeo para saber donde estoy al hacer fork() se repite siempre, preguntar si no se puede modularizar en un función 
		3.10) Mientras se está chequeando las Filas y Columnas, siempre avanzar para adelante
			3.10.1) Ver como chequear que esten todos lo números (se me ocurre un array de booleans/int 1-based, entonces, si hay un 1
					en las 9 posiciones del arrgelo, la fila/columna/cuadrante es correcta, si hay algún número en 0 o hay un número 
					con más de una aparición, la fila/columna/cuadrante es incorrecta)

*/

/*
	Función para modularizar, esta se encarga de leer el archivo
	COMPLETAR, hay que hacer chequeos adicionales y ver si realmente estaria leyendo y asignando el valor
*/
void Lectura(FILE *Sud, char[][9] gril){

	int F = 0;
	int C = 0;
	while(!feof(Sud) && F < 9){
		while(C < 9){
			char num = fgetc(SudokuR); //obtengo el caracter
			if(num != EOF && num != ','){
				GrillaSudoku[F][C] = num; //si lo leido no es EOF o "," (la grilla esta separada por comas), lo añado a la matriz
				C++;
			} //buscar cuanto era EOF en Linux
			C = 0;
			F++;
		}	
	}
}

/* Función que verificará un Cuadrante del Sudoku
*	gril, grilla del Sudoku
*	F, Fila de Inicio del cuadrante
*	C, Columna de Inicio del Cuadrante
*	al retornar, devuelve Verdadero (El cuadrante es correcto) o Falso (El Cuadrante NO es válido, aquí se debe terminar todo)
*/
int VerificarFila(char[][9] gril, int F){

	return 0;
}

/* Función que verificará una Columna del Sudoku
*	gril, grilla del Sudoku
*	C, Columna de Inicio del Cuadrante
*	al retornar, devuelve Verdadero (La Columna es correcta) o Falso (La Columna NO es válida, aquí se debe terminar todo)
*/
int VerificarColumna(char[][9] gril, int C){

}

/* Función que verificará un Cuadrante del Sudoku
*	gril, grilla del Sudoku
*	F, Fila de Inicio del cuadrante
*	C, Columna de Inicio del Cuadrante
*	al retornar, devuelve Verdadero (El cuadrante es correcto) o Falso (El Cuadrante NO es válido, aquí se debe terminar todo)
*/
int VerificarCuadrante(char[][9] gril,int F, int C){

}

int main(){

	//Variable para manejar el archivo
	FILE *SudokuR;
	//Enteros que harán de booleans para los procesos
	int Proc1 = 0;
	int Proc2 = 0;
	int Proc3 = 0;
	//Matriz de 9x9 donde se guardará el sudoku
	char[9][9] GrillaSudoku;

	//Abro el archivo, para lectura (por el enunciado, debe llamarse "sudoku.txt").
	SudokuR = fopen("sudoku.txt", "r");

	if(!SudokuR){
		//Ocurrió un error al abrir el archivo, reportar dicho error, por ahora solo devuelvo 1, mejorar
		return 1;
	}
	/*
	 el archivo se abrió correctamente, hago el primer fork() para leer el archivo, mi hijo compartirá
	 el archivo abierto por lo dicho en la teoria Y LA MATRIZ, además, ámbos ejecutan concurrentemente por UNIX
	 El Padre debe esperar a este Hijo
	*/
	else{
		int PID = fork();

		if(PID == -1){
			//Hubo un error al crear el hijo, reporto dicha ocurrencia (reportar)
		}
		else{
			if(PID > 0){
				//Estoy en el Padre, en este caso, debo esperar a que mi hijo termine y devuelva
				wait(NULL);
			}
			else{
				//Estoy en el hijo, debo leer el archivo y cargar la matriz, delego en un procedimiento
				//para modularizar 
				Lectura(SudokuR, GrillaSudoku);
				//terminado el proceso, yo como hijo debo reportar que terminé
				exit(0);
			}
			//asumiendo que terminé de leer todo correctamente, deberia tener la matriz totalmente cargada
			//ya no necesito más el archivo, puedo cerrarlo y continuar
			fclose(SudokuR);
			//Creo el primer proceso de tres, este chequeará las filas
			PID = fork();
			//Acá habria que hacer el mismo chequeo que hice arriba para saber donde estoy
		}
	}




	return 0;
}