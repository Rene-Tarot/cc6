#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int diskSize = 100;
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

void printFifo(int *array, int size, int pos) {
    double promedio;
    double temporal;
    double media;
    double distancia;
    double sumaDistancia;
    double desviacion;
    
    printf("First In First Out\n"); 
    printf("Posicion Inicial: %d\n", pos);
    
    printf("Listado: ");
    for (int i = 0; i < size - 1; i++) { 
        printf("%i, ", array[i]);
    }
    if (size >= 1) printf("%i", array[size-1]); 
    printf("\n"); 

    printf("Promedio: ");

    //promedio de la posicion inicial
    temporal = array[0];
    promedio = temporal - pos;
    temporal= 0.0;
    

    if(promedio<0){
    	promedio= promedio * -1;
    }
    

    for (int i = 0; i < size; ++i)
    {
    	temporal = array[i] - array[i+1];

    	if(temporal<0){
    	promedio= promedio * -1;
    	}
    	promedio = promedio + temporal;
    }

    promedio = promedio / size;
    printf("%f\n", promedio);

    printf("Desviacion Estandar: ");

    for (int i = 0; i < size; ++i)
    {
    	media = media + array[i];
    }
    media = media/size;

    for (int i = 0; i < size; ++i)
    {
    	distancia = array[i] - media;
    	distancia = distancia*distancia;
    	sumaDistancia += distancia;
    }
    sumaDistancia = sumaDistancia/size;
    desviacion = sqrt(sumaDistancia);

    printf("%f\n", desviacion);

}

void swap(int* xp, int* yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
/*
void printScan(int *array, int size, int pos, char dir){
	int izquerda[size];
	int derecha[size]; 
	size_t tmn= NELEMS(izquerda);
	printf("Scan\n");
	int min;

	//separa las peticiones por izquerda y derecha de la cabeza.
	for (int i = 0; i < tmn; ++i)
	{
		if (pos>= array[i])
		{
			izquerda[i]= array[i];
		}else if (pos<=array[i])
		{
			derecha[i]= array[i];
		}
	}

	//ordena el array en forma ascendente.
	for (int i = 0; i < size-1; i++)
	{
		min=i;
		for (int j = i+1; j < size; i++)
			if (izquerda[j] < izquerda[min])
				min =j;
		swap(&izquerda[min], &izquerda[i]);
	}
	
	for (int i = 0; i < size-1; i++)
	{
		min=i;
		for (int j = i+1; j < size; i++)
			if (derecha[j] < derecha[min])
				min =j;
		swap(&derecha[min], &derecha[i]);
	}


}
*/
int main(int argc, char *argv[])
{
	int count;
	int initPos;
	char direction;
    
    printf("Ingrese la direccion de la cabeza (i, d):\n");
    scanf("%c", &direction);

    printf("Ingrese la posicion inicial:\n");
    scanf("%d", &initPos);

    printf("Ingrese la cantidad de requerimientos a disco:\n");
    scanf("%d", &count);

	// crear array 
    int *array = malloc(count * sizeof(*array));
    if (!array) {
        printf("There was a problem with malloc.");
        exit(EXIT_FAILURE);
    }
	
    printf("Ingrese las peticiones de disco:\n");
    for (int i = 0; i < count; i++) scanf("%d", &array[i]);

    

    printFifo(array, count, initPos);
	//printScan(array, count, initPos, direction);

    
    free(array);
	return 0;
}