#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define the ThreadData structure to hold requested resources and available resources pointer
struct ThreadData {
    int requested;    // Requested resources for the thread
    int *available;   // Pointer to available resources in the system
    int MAX;          // Maximum number of resources
};


// Mutex lock to synchronize access to shared resources
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function implementing the banker's algorithm for resource allocation
void *banker_algorithm(void *threadDataPtr) {
    // Cast the argument back to the ThreadData structure
    struct ThreadData *data = (struct ThreadData *)threadDataPtr;
    int requested = data->requested;
    int *available = data->available;

    // Lock the mutex to ensure mutual exclusion while accessing shared resources
    pthread_mutex_lock(&mutex);

    // Check if the requested resources can be allocated
    if (requested <= *available && requested > 0) {
        // Allocate resources and update available resources
        *available -= requested;

        // Displace resources - update maximum available resources as well
        // Display system state after each allocation
        printf("Thread %lu: \nResources allocated successfully.\n", pthread_self());

    } else {
        // Print message if requested resources cannot be allocated
        printf("Thread %lu: \nNot enough resources.\n", pthread_self());
    }

    // Unlock the mutex after accessing shared resources
    pthread_mutex_unlock(&mutex);

    // Display system state after releasing the lock
    printf("System State: Maximum Resources: %d, Available Resources(MAX - Requested(if allocated else 0)): %d, Requested Resources: %d\n\n", data->MAX, *available, requested);
    //Available resources are resources left after allocation

    // Free the allocated memory for the structure to prevent memory leaks
    free(threadDataPtr);

    // Exit the thread
    pthread_exit(NULL);
}


int main() {
    int MAX;            // Maximum number of resources
    int available;      // Available resources

    // Prompt the user to input the maximum number of resources
    printf("\nEnter the maximum number of resources: ");
    scanf("%d", &MAX);

    available = MAX;    // Initialize available resources

    int num_threads;

    // Prompt the user to input the number of threads
    printf("\nEnter the number of threads: ");
    scanf("%d", &num_threads);
    printf("\n");

    int requested[num_threads];  // Array to store resource requests for each thread
    pthread_t threads[num_threads];  // Array to store thread IDs

    // Get resource requests from the user for each thread
    for (int i = 0; i < num_threads; ++i) {
        printf("Enter requested resources for Thread %d: ", i + 1);
        scanf("%d", &requested[i]);
    }
    printf("\n");

    // Create threads and execute the banker_algorithm function for each thread
    for (int i = 0; i < num_threads; ++i) {
        // Create a struct instance to pass multiple arguments to the thread
        struct ThreadData *data = malloc(sizeof(struct ThreadData));
        data->requested = requested[i];
        data->available = &available;
        data->MAX = MAX;  // Store the maximum resources in the ThreadData structure


        // Check if thread creation is successful, handle errors if any
        if (pthread_create(&threads[i], NULL, banker_algorithm, (void *)data) != 0) {
            perror("\nThread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish execution before proceeding
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Print a message indicating that all threads have finished executing
    printf("\nExecution finished for all the threads\n\n");

    return 0;
}

