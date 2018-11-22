#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h> //libreria para manejo de directorios
#include "Params.h"

//OJO! ls IGNORA el params!

int main(){

	struct dirent *de;
	DIR *dr = opendir("."); //Abro la carpeta en donde estoy
	if(dr == NULL){
		fprintf(stderr,"Error -1: NO se ha podido abrir el Directorio");
		return 0;
	}
	else{
		while((de = readdir(dr)) != NULL) //Mientras la carpeta leida no sea NULL
			printf("%s\n",de->d_name); //Obtengo el nombre de la carpeta y la imprimo por pantalla

		closedir(dr); //cierro el directorio
		return 0;
	}
	return 0;
}