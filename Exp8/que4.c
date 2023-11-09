#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>

// Define the remote procedure that will be called
float *average_1_svc(float *arr, struct svc_req *req) {
    static float result;
    int i;
    for (i = 0; i < 5; i++) {
        result += arr[i];
    }
    result /= 5;
    return &result;
}

int main(int argc, char **argv) {
    // Register the remote procedure with the RPC system
    if (registerrpc(1, 1, 1, average_1_svc, NULL) == -1) {
        fprintf(stderr, "Failed to register remote procedure\n");
        exit(1);
    }

    // Start the RPC server
    svc_run();

    return 0;
}
