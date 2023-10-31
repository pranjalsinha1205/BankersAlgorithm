# Multithreaded implementation of Banker's Algorithm


# QUESTION STATEMENT

Project Title: Multithreaded Banker’s Algorithm Implementation

Problem Statement:

Write a multithreaded program that implements the banker's algorithm. Create n threads that request and release resources from the bank. The banker will grant the request only if it leaves the system in a safe state. It is important that shared data be safe from concurrent access. To ensure safe access to shared data, you can use mutex locks.

Ensure:

1)	The program should be dynamic such that the threads are created at runtime based on the input from the user.

2)	The resources must be displaced after each allocation.

3)	The system state should be visible after each allocation.


# INTRODUCTION

Multithreading is a programming and execution technique that allows multiple threads to exist within the context of a single process. A thread is the smallest unit of execution within a process, and multithreading enables multiple threads to run concurrently.

The Banker's algorithm is a resource allocation and deadlock avoidance algorithm used in operating systems. It is designed to ensure that processes request resources in a safe and deadlock-free manner.

In the Banker's algorithm, the system keeps track of the maximum resources that a process may request, the resources currently allocated to processes, and the available resources in the system. When a process requests resources, the algorithm checks whether granting the request will leave the system in a safe state. A state is considered safe if there is a sequence of resource allocations and deallocations in which every process can complete its execution without getting stuck in a deadlock.

The purpose of this project is to show the multithreaded implementation of the Banker’s Algorithm. The implementation is done in the C programming language while keeping the fundamental principles of Banker’s Algorithm in focus. This project also uses MUTEX(Mutual Exclusion) locks to prevent concurrent access to shared resources thus stopping a deadlock to happen.

A deadlock can happen if all of the 4 conditions given below are happening:-
i)	Mutual Exclusion
ii)	Hold and wait
iii)	No preemption
iv)	Circular wait

The Banker’s Algorithm is there to avoid the deadlock and keep the system in a safe state.


# HOW I THOUGHT OF THE SOLUTION (REQUIREMENTS OF THE SOLUTION)

First of all, I tried to understand the depth of the problem. The problem required me to do three things :-
i)	To make the program dynamic and create threads at runtime, meaning I need to take inputs from the user at runtime
ii)	The updation of resources
iii)	The visibility of the system state

Then, keeping in mind the fundamental principles of Banker’s Algorithm, Safe States, Resource Requests, and Deadlock Avoidance, I tried to think of a solution tailored around these principles. In order to make the code readable I tried to make it as modular as I could.

I made a structure ThreadData and encapsulated thread-specific data, ensuring encapsulation and thread safety. 
In accordance with the hint in the question, I also used Mutex locks to enable mutual exclusion and safeguarding shared resources from concurrent access, thereby avoiding the problem of erroneous output.

My main focus was on making the program as dynamic as I could. The program was designed to be adaptable, accommodating a variable number of threads and their resource requests. User inputs at runtime tailored the program's behavior, aligning it with real-world scenarios. 

# PSEUDOCODE

STRUCT ThreadData:
    INT requested
    POINTER available
    INT MAX

FUNCTION banker_algorithm(ARGUMENTS):
    CAST ARGUMENTS TO ThreadData STRUCTURE
    EXTRACT requested, available, AND MAX FROM ThreadData

    ACQUIRE MUTEX LOCK

    IF requested <= *available AND requested > 0:
        *available -= requested
        PRINT "Thread ID: ", THREAD_ID, "\nResources allocated successfully.\n"
    ELSE:
        PRINT "Thread ID: ", THREAD_ID, "\nNot enough resources.\n"

    PRINT "System State: Maximum Resources: ", MAX, ", Available Resources(MAX - Requested(if allocated else 0)): ", *available, ", Requested Resources: ", requested, "\n\n"

    RELEASE MUTEX LOCK
    FREE ARGUMENTS STRUCTURE

    THREAD EXIT

INT main():

    INT MAX
    INT available

    PRINT "Enter the maximum number of resources: "
    SCAN MAX
    available = MAX

    INT num_threads
    PRINT "Enter the number of threads: "
    SCAN num_threads

    ARRAY OF INT requested[num_threads]
    ARRAY OF POINTER threads[num_threads]

    FOR i FROM 0 TO num_threads - 1:
        PRINT "Enter requested resources for Thread ", i + 1, ": "
        SCAN requested[i]

    FOR i FROM 0 TO num_threads - 1:
        STRUCT ThreadData *data = ALLOCATE MEMORY FOR ThreadData STRUCTURE
        SET data.requested TO requested[i]
        SET data.available TO ADDRESS OF available
        SET data.MAX TO MAX

        IF pthread_create(&threads[i], NULL, banker_algorithm, (void *)data) != 0:
            PRINT "\nThread creation failed\n"
            EXIT PROGRAM WITH FAILURE

    FOR i FROM 0 TO num_threads - 1:
        WAIT FOR threads[i] TO FINISH EXECUTION

    PRINT "\nExecution finished for all the threads\n\n"

# SNAPSHOT

![pic1](https://github.com/pranjalsinha1205/BankersAlgorithm/assets/112460531/e597d6c5-d007-42be-a04b-e78296698f65)

