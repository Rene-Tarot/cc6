#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t lock;
pthread_mutex_t imprimir;
pthread_mutex_t sumar;
pthread_cond_t nitrogenoC;
pthread_cond_t hidrogenoC;
pthread_cond_t oxigenoC;
//Moleculas en la solutcion
int nitrogenoSolucion;
int hidrogenoSolucion;
int oxigenoSolucion;

void *ni(void * arg){
	//imprime su id
	pthread_mutex_lock(&imprimir);
	printf("Se crea id%d Nitrogeno\n", pthread_self());
	pthread_mutex_unlock(&imprimir);

	//sumar moleculas en la solucion
	pthread_mutex_lock(&sumar);
	nitrogenoSolucion++;
	pthread_mutex_unlock(&sumar);

	//imprimir reaccion menor
	pthread_mutex_lock(&lock);
	if ((nitrogenoSolucion % 1 == 0)&&(hidrogenoSolucion % 3 == 0))
	{
		printf(">>>>>>>>>>>>>>>Una molecula de NH3\n");
	}
	pthread_mutex_unlock(&lock);

	//despertar cuando hay solucion completa
	pthread_mutex_lock(&lock);
	if ((nitrogenoSolucion%1==0)&&(hidrogenoSolucion%3==0)&&(oxigenoSolucion%2==0))
	{
		pthread_cond_broadcast(&nitrogenoC);
		pthread_cond_broadcast(&hidrogenoC);
		pthread_cond_broadcast(&oxigenoC);
	}
	pthread_mutex_unlock(&lock);

	//duerme si la reaccion no esta completa
	pthread_mutex_lock(&lock);
	while(!((nitrogenoSolucion%1==0)&&(hidrogenoSolucion%3==0)&&(oxigenoSolucion%2==0)))
	{
		pthread_cond_wait(&nitrogenoC, &lock);
	}
	pthread_mutex_unlock(&lock);

	//imprimir id
	pthread_mutex_lock(&imprimir);
	printf("id%d Nitrogeno\n", pthread_self());
	pthread_mutex_unlock(&imprimir);

	//imprimir mensaja
	pthread_mutex_lock(&imprimir);
	printf("FUEGO!!!!!!!!!!\n");
	printf("### Reaccion Exitosa! Convertimos un Acido en.... Agua?\n");
	pthread_mutex_unlock(&imprimir);	

	pthread_exit(NULL);
}
void *hi(void * arg){
	pthread_mutex_lock(&imprimir);
	printf("Se crea id%d Hidrógeno\n", pthread_self());
	pthread_mutex_unlock(&imprimir);


	pthread_mutex_lock(&sumar);
	hidrogenoSolucion++;
	pthread_mutex_unlock(&sumar);

	pthread_mutex_lock(&lock);
	if ((nitrogenoSolucion % 1 == 0)&&(hidrogenoSolucion % 3 == 0))
	{
		printf(">>>>>>>>>>>>>>>Una molecula de NH3\n");
	}
	pthread_mutex_unlock(&lock);

	pthread_mutex_lock(&lock);
	if ((nitrogenoSolucion%1==0)&&(hidrogenoSolucion%3==0)&&(oxigenoSolucion%2==0))
	{
		pthread_cond_broadcast(&nitrogenoC);
		pthread_cond_broadcast(&hidrogenoC);
		pthread_cond_broadcast(&oxigenoC);
	}
	pthread_mutex_unlock(&lock);

	pthread_mutex_lock(&lock);
	while(!((nitrogenoSolucion%1==0)&&(hidrogenoSolucion%3==0)&&(oxigenoSolucion%2==0)))
	{
		pthread_cond_wait(&hidrogenoC, &lock);
	}
	pthread_mutex_unlock(&lock);

	pthread_mutex_lock(&imprimir);
	printf("id%d Hidrógeno\n", pthread_self());
	pthread_mutex_unlock(&imprimir);

	pthread_exit(NULL);
}
void *ox(void * arg){
	pthread_mutex_lock(&imprimir);
	printf("Se crea id%d Oxigeno\n", pthread_self());
	pthread_mutex_unlock(&imprimir);

	pthread_mutex_lock(&sumar);
	oxigenoSolucion++;
	pthread_mutex_unlock(&sumar);

	pthread_mutex_lock(&lock);
	if (oxigenoSolucion % 2 == 0)
	{
		printf(">>>>>>>>>>>>>>>Una molecula de O2\n");
	}
	pthread_mutex_unlock(&lock);

	pthread_mutex_lock(&lock);
	if ((nitrogenoSolucion%1==0)&&(hidrogenoSolucion%3==0)&&(oxigenoSolucion%2==0))
	{
		pthread_cond_broadcast(&nitrogenoC);
		pthread_cond_broadcast(&hidrogenoC);
		pthread_cond_broadcast(&oxigenoC);
	}
	pthread_mutex_unlock(&lock);

	pthread_mutex_lock(&lock);
	while(!((nitrogenoSolucion%1==0)&&(hidrogenoSolucion%3==0)&&(oxigenoSolucion%2==0)))
	{
		pthread_cond_wait(&oxigenoC, &lock);
	}
	pthread_mutex_unlock(&lock);

	pthread_mutex_lock(&imprimir);
	printf("id%d Oxigeno\n", pthread_self());
	pthread_mutex_unlock(&imprimir);

	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	int reacciones;
	int nitrogeno;
	int hidrogeno;
	int oxigeno;
	int total;
	int seed = time(NULL);
    srand(seed);
    int reaccion;
    pthread_mutex_init(&imprimir, NULL);//Lock para impimir
    pthread_mutex_init(&lock, NULL);//inizializar el lock
    pthread_mutex_init(&sumar, NULL);//lock para sumar
    pthread_cond_init(&nitrogenoC, NULL);
    pthread_cond_init(&hidrogenoC, NULL);
    pthread_cond_init(&oxigenoC, NULL);

	printf("NH3 + O2 ➝ Agua?\n");
	printf("Cuántas reacciones crear: ");
	scanf("%d", &reacciones);
	printf("\n");


	nitrogeno = reacciones;
	hidrogeno = reacciones*3;
	oxigeno = reacciones*2;
	total = nitrogeno+hidrogeno+oxigeno;
	pthread_t tid[total];

	printf("Se crearán %d Nitrógeno, %d Hidrógeno y %d Oxígeno.\n", nitrogeno, hidrogeno, oxigeno);
	int nitrogenoC=nitrogeno;
	int hidrogenoC=hidrogeno;
	int oxigenoC=oxigeno;

	int iter = total;
	int indice = 0;
	while(iter>0){
		reaccion = rand()%3; 

		if ((reaccion==0) && (nitrogenoC>0))
		{
			iter--;
			nitrogeno--;
			printf("Se crea id%d Nitrogeno\n", &tid[indice]);
			pthread_create(&tid[indice], NULL, ni, reaccion);
			indice++;
			nitrogenoC--;
			sleep(1);

		} else if ((reaccion==1) && (hidrogenoC>0))
		  {
			iter--;
			hidrogeno--;
			pthread_create(&tid[indice], NULL, hi, reaccion);
			indice++;
			hidrogenoC--;
			sleep(1);

		  } else if ((reaccion==2) && (oxigenoC>0))
		    {
				iter--;
				oxigeno--;
				pthread_create(&tid[indice], NULL, ox, reaccion);
				indice++;
				oxigenoC--;
				sleep(1);
		    }
	}


	//esperar reacciones
	for (int i = 0; i < total; i++)
	{
		pthread_join(tid[i], NULL);
	}

	printf("Fin.\n");
	return 0;
}