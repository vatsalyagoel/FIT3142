#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    double start, finish;
    int rank, value = 0, size;
    MPI_Status status;

    MPI_Init(NULL, NULL);
    start = MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    while(value >= 0) {
        if(rank == 0) {
            scanf("%d", &value);
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0 , MPI_COMM_WORLD);
        }
        else {
            MPI_Recv(&value, 1, MPI_INT, rank - 1, 0 , MPI_COMM_WORLD, &status );

            if(rank < size - 1)
                MPI_Send(&value, 1, MPI_INT, rank + 1, 0 , MPI_COMM_WORLD);
        }

        printf("Process %d of %d recieved %d\n", rank, size, value);
    } 
    finish = MPI_Wtime();
    MPI_Finalize();
    printf("Parallel Elapsed time: %f seconds\n", finish-start);
}