#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int et = 0;
int pxx[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
int at[] = {0, 1, 2, 3, 4, 0, 1, 2, 0, 3, 7, 9, 12, 0, 2, 4, 5, 0, 2, 3, 6, 0, 0, 0, 10, 0, 0, 0, 7};
int bt[] = {5, 5, 5, 5, 5, 8, 10, 7, 8, 6, 3, 5, 3, 7, 4, 1, 4, 7, 3, 5, 4, 4, 3, 8, 5, 10, 2, 7, 6};
int v[] = {1, 1, 1, 1, 1, 2, 2, 2, 3, 2, 1, 2, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1};

void output(void *vargp) {
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|PXX\t|QU\t|QM\t|AT\t|BT\t|ET\t|WT\t|RT\t|TT\t|\n");
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n\n");
} 

void FCFS(void *vargp) {
	printf(" --> FCFS\n");
	output(0);

	for (int i = 0; i < 29; ++i)
	{
		
		et = et + bt[i];

		printf("   p%d\t QU\t %d\t %d\t %d\t %d\t WT\t RT\t TT\n", pxx[i], bt[i], i, bt[i], et);
	
	}


	
} 

void PS(void *vargp) {
	printf(" --> PS\n");
	output(0);
} 

void RR(void *vargp) {
	printf(" --> RR\n");
	output(0);
} 

void MLFQS(void *vargp) {
	printf(" --> MLFQS\n");
	output(0);
} 

int menu(){
	int tmp;
	printf("############\n1 - FCFS\n2 - PS\n3 - RR\n4 - MLFQS\n0 - EXIT\n\nSeleccione Opción: ");
	scanf("%d", &tmp);
	return tmp;
}

// C Concepts 
// https://gist.github.com/Integralist/6c35d4f26c0c7bf5bdce7b95cfa906b3
int main ( int argc , char * argv []) {
	int op = 9;
	pid_t pid;
	while (op > 0){
		op = menu();
		printf("Procesando opción: %d\n", op);
		if ( op >5 || op<=0 ){
			printf("### END ###\n");
			break;
		}
		printf("### BEGIN ###\n");
		switch(op){
			case 1:
			FCFS(0);
			break;
			case 2:
			PS(0);
			break;
			case 3:
			RR(0);
			break;
			default:
			case 4:
			MLFQS(0);
			break;
		}
	}
	return 0;
}
