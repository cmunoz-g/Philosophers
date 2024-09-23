# 🧠 Philosophers

## Introduction
The **Philosophers** project is part of the 42 curriculum, focusing on multi-threaded programming and synchronization mechanisms in C. The project is based on the classic "Dining Philosophers Problem," a fundamental problem in concurrent programming, which illustrates the challenges of resource sharing and deadlock prevention.

## Problem Description
The "Dining Philosophers Problem" involves a group of philosophers seated around a circular table. There is a bowl of spaghetti in the center, and between each pair of philosophers is a single fork. Each philosopher can be in one of three states:

- **Eating**: A philosopher can only eat if they have acquired both the fork on their left and the fork on their right.
- **Thinking**: A philosopher who is not eating is thinking.
- **Sleeping**: After eating, a philosopher will sleep for a specified duration.

The challenge is to ensure that no philosopher starves while avoiding deadlocks and race conditions. A deadlock occurs when all philosophers pick up the fork on their right at the same time and are unable to pick up the fork on their left, leading to an infinite wait.

## Solution Overview
The implementation uses:
1. **Threads**: Each philosopher is represented by a thread that executes actions concurrently. An additional thread serves as a monitor, overseeing the philosophers' states.
2. **Mutexes**: Each fork is protected by a mutex to prevent simultaneous access by multiple philosophers, avoiding race conditions. Additional mutexes protect other shared data.
4. **Memory Management**: All dynamically allocated memory and mutexes are properly cleaned up using the `clean` and `clean_mutex` functions to avoid memory leaks and ensure safe resource deallocation.

### Key Features
- **Deadlock Prevention**: Philosophers only pick up both forks if both are available, ensuring no deadlock occurs. Logic for which fork to go for is implemented.
- **Precision Logging**: States (eating, sleeping, thinking, death) are logged with millisecond precision to monitor behavior accurately.
- **Robust Error Handling**: Implements error handling mechanisms for system calls like `usleep` to maintain stability and reliability.
- 
## How to Use
1. **Clone the Repository**:
    ```bash
    git clone https://github.com/cmunoz-g/Philosophers.git
    ```
2. **Navigate to the Project Directory**:
    ```bash
    cd Philosophers/philo
    ```
3. **Compile the Program**:
    ```bash
    make
    ```
4. **Run the Program**:
    ```bash
    ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
    ```
   - `number_of_philosophers`: Number of philosophers and forks.
   - `time_to_die`: Time (in milliseconds) before a philosopher dies if they haven't started eating.
   - `time_to_eat`: Time (in milliseconds) a philosopher spends eating.
   - `time_to_sleep`: Time (in milliseconds) a philosopher spends sleeping.
   - `[number_of_times_each_philosopher_must_eat]`: Optional argument. If provided, the simulation ends when all philosophers have eaten at least this many times.
