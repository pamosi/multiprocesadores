// Author: Wes Kendall
// Copyright 2011 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header intact.
//
// Example of checking the MPI_Status object from an MPI_Recv call
//
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
  	MPI_Init(0, 0);

  	int world_size, world_rank;
  	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  	if (world_size != 2) {
		if(world_rank==0)
    			printf("Se esperaban 2 procesos\n");
  	}else{
  		const int MAX_NUMBERS = 100;
  		int numbers[MAX_NUMBERS];
  		int number_amount;
  		if (world_rank == 0) {
    			// Pick a random amount of integers to send to process one
    			srand(time(NULL));
    			number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;
    			// Send the amount of integers to process one
    			MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
    			printf("0 envio %d numeros a 1\n", number_amount);
  		} else if (world_rank == 1) {
    			MPI_Status status;
    			// Receive at most MAX_NUMBERS from process zero
    			MPI_Recv(numbers, MAX_NUMBERS, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    			// After receiving the message, check the status to determine how many
    			// numbers were actually received
    			MPI_Get_count(&status, MPI_INT, &number_amount);
    			// Print the amount of numbers, and also print additional information
    			printf("1 recibio %d numeros desde 0. Fuente del mensaje = %d, etiqueta = %d\n", number_amount, status.MPI_SOURCE, status.MPI_TAG);
  		}
	}
  	MPI_Barrier(MPI_COMM_WORLD);
  	MPI_Finalize();
}
