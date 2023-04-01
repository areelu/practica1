#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    // Declarar las variables a utilizar
    int lim;
    int size;
    int x0 = 1; // Iniciamos con x0 = 1
    int sum;
    int cicles = 10; // Declaramos 10 ciclos
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &lim);
    int left = (lim - 1 + size) % size;
    int right = (lim + 1) % size;
    int x = x0;

    for(int i=0; i<cicles; i++) { //Crear un bucle que itere sobre el número de ciclos, envie y reciba x y haga su suma acumulada
        MPI_Send(&x, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
        MPI_Recv(&sum, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        x += sum; //suma acumulativa de los x's
    }
    printf("Rank %d: final value = %d\n", lim, x);
    MPI_Finalize();
    return 0;
}
