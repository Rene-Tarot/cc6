#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define   MAX_INGES  4
#define IZQUIERDA 1
#define DERECHA 0 
#define TRUE 1
#define FALSE 0

pthread_mutex_t lock;
pthread_mutex_t imprimir;
pthread_cond_t colas[2];


int ingesEnElPuente;
int flow;
int waiting[2];


//struct para pasar argumentos al thread
struct passing
{
	int donde; 
	int ingeniero;
};
typedef struct passing struct1;


//Funcion que mira si se puede pasar en el puente
int check(int direccion)
{
	if (ingesEnElPuente == 0)
	{
		return TRUE;
	}else if ((ingesEnElPuente<MAX_INGES)&&(flow==direccion))
	{
		return TRUE;
	}else{
		return FALSE;
	}
}

void accessBridge(int direccion)
{
	pthread_mutex_lock(&lock);

	if (!check(direccion))
	{
		waiting[direccion]++;
		while(!check(direccion)){
			
			pthread_cond_wait(&colas[direccion], &lock);
			waiting[direccion]--;
		}
	}
	ingesEnElPuente++;
	flow=direccion;
	pthread_mutex_unlock(&lock);
}

void exitBridge(int direccion)
{
	pthread_mutex_lock(&lock);

	ingesEnElPuente--;
	if (ingesEnElPuente>0)
	{
		pthread_cond_signal(&colas[direccion]);
	}else{
		int siguiente = 1 - direccion;
		if (siguiente != 0)
		{
			pthread_cond_signal(&colas[siguiente]);
		}else{
			pthread_cond_signal(&colas[direccion]);
		}
	}
	pthread_mutex_unlock(&lock);
}

void *deadMeat(void * arg)
{
	
	struct1 *argumentos;
	argumentos=(struct1*)arg;
	int cualInge = argumentos->ingeniero;
    int destino = argumentos->donde;
    int sleep3 = rand()%4;
    int sleep4 = (rand()%5)+1;

    pthread_mutex_lock(&imprimir);
    if (destino == 0)
    {
    	printf("Llega Inge %d a cola Derecha\n", cualInge);
    }else if (destino == 1)
    {
    	printf("Llega Inge %d a cola Izquierda\n", cualInge);
    }
    pthread_mutex_unlock(&imprimir);

	sleep(sleep3);
	pthread_mutex_lock(&imprimir);
	accessBridge(destino);
	printf("Inge %d Cruza Puente\n", cualInge);
	pthread_mutex_unlock(&imprimir);

	
	sleep(sleep4);
	pthread_mutex_lock(&imprimir);
	exitBridge(destino);
	printf("Inge %d Sale del puente\n", cualInge);
	pthread_mutex_unlock(&imprimir);

	pthread_exit(NULL);
	
}

int main(int argc, char const *argv[])
{
	int personas; //numero de personas o Threads
	struct1 *Allen;
	Allen=(struct1 *)malloc(sizeof(struct1));
	pthread_mutex_init(&lock, NULL);//inizializar el lock
	pthread_mutex_init(&imprimir, NULL);//Lock para impimir
	pthread_cond_init(&colas[0], NULL);
	pthread_cond_init(&colas[1], NULL);
	
	///////////////////////////////////////////////////////////////
	/* imprimir la cantidad de threads a crear */
	printf("Cuantas personas cruzaran el puente? ");
	scanf("%d", &personas);
	//crear arreglo para crear las direcciones
	int *puente = malloc(personas * sizeof(*puente));
    if (!puente) {
        printf("There was a problem with malloc.");
        exit(EXIT_FAILURE);
    }
	int seed = time(NULL);
    srand(seed);
    //Llenar el array con 1,0 randomizado
    for (int i = 0; i < personas; ++i)
    {
    	puente[i]= rand()%2;
    }

    for (int i = 0; i < personas; ++i)
    {
    	int inge = i+1;
    	
    	if(puente[i] == 0)
    	{
    		printf("Inge %d camina hacia la Derecha\n", inge);

    	}else{
    		printf("Inge %d camina hacia la Izquierda\n", inge);
    	}	
    }
    printf("\n");
    ////////////////////////////////////////////////////////////
    
	pthread_t tid[personas]; // id de los threads


    //crear threads
    for (int i = 0; i < personas; ++i)
    {
    	Allen->donde=puente[i];
    	Allen->ingeniero=i+1;
    	pthread_create(&tid[i], NULL, deadMeat, (void*) Allen);
    	sleep(1);
    }
	//esperar personas
	for (int i = 0; i < personas; i++)
	{
		pthread_join(tid[i], NULL);
	}

    free(puente);
	return 0;
}