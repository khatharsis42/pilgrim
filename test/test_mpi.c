#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    int world_size;

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Barrier(MPI_COMM_WORLD);

    //MPI_Allreduce(&world_size, &rank, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    //MPI_Allreduce(&rank, &world_size, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    int outcount;
    int indices[2];
    MPI_Request reqs[2];
    if(rank == 0) {
        for(int i = 0; i < 3; i++) {
            MPI_Isend(&rank, 1, MPI_INT, 1, 999, MPI_COMM_WORLD, &(reqs[0]));
            MPI_Isend(&rank, 1, MPI_INT, 1, 999, MPI_COMM_WORLD, &(reqs[1]));
            MPI_Waitsome(2, reqs, &outcount, indices, MPI_STATUSES_IGNORE);
        }
    }

    int data;
    if(rank == 1) {
        for(int i = 0; i < 3; i++) {
            MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 999, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 999, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    MPI_Finalize();

    return 0;
}
