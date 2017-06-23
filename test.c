#include <stdio.h>    // Standard input/output definitions
#include <stdlib.h>
#include <string.h>   // String function definitions
#include <unistd.h>   // para usleep()
#include <getopt.h>
#include <math.h>

#include "arduino-serial-lib.h"

float calculateSD(float data[]);

void error(char* msg)
{
    fprintf(stderr, "%s\n",msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int fd = -1,reader;
	int baudrate = 9600;  // default
	char temp='t';
	char h='h';
	short buffer;
	short nbytes=1;
	int sumTotalTemp=0,sumToralH=0, promt, promh,cont=0;

	fd = serialport_init("/dev/ttyACM0", baudrate);

	if( fd==-1 )
	{
		error("couldn't open port");
		return -1;
	}
	/* Abrimos los dos archivos */
 
  /* Bucle de lectura/escritura */
  	
	while(1){
		write(fd, &temp, nbytes);
		usleep(50000);
		reader = read(fd, &buffer, nbytes);
		printf("%u\n", buffer);    
		usleep(500000);
		sumTotalTemp=sumTotalTemp+buffer;
		write(fd, &h, nbytes);
		usleep(50000);
		reader = read(fd, &buffer, nbytes);     
		printf("%u\n", buffer);
		sumToralH=sumToralH+buffer;
		
		cont++;
		if(cont==12){
			break;
		}
	}
	close(fd);
	promt=sumTotalTemp/cont;
	printf("\nel promedio de temperatura es : %d\n",promt);
	promh=sumToralH/cont;
	printf("el promedio de humedad es : %d\n",promh);
	return 0;	
}

/* Ejemplo para calcular desviacion estandar y media */
float calculateSD(float data[])
{
    float sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for(i = 0; i < 10; ++i)
    {
        sum += data[i];
    }

    mean = sum/10;

    for(i = 0; i < 10; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / 10);
}

