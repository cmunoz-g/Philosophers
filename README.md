# 🧠 Philosophers

Multi-threaded C program simulating the Dining Philosophers problem. Demonstrates concurrency, synchronization, and deadlock prevention using threads and mutexes.

## Build and run

```bash
# Clone
 git clone https://github.com/cmunoz-g/Philosophers.git
 cd Philosophers/philo

# Build
make

# Run
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments**

* `number_of_philosophers`: number of philosophers and forks.
* `time_to_die`: time (ms) before a philosopher dies without eating.
* `time_to_eat`: time (ms) spent eating.
* `time_to_sleep`: time (ms) spent sleeping.
* `[number_of_times_each_philosopher_must_eat]`: optional; simulation ends once all philosophers have eaten this many times.

## Features

* **Deadlock prevention** — philosophers only eat when both forks are available.
* **Precision logging** — state changes (eating, sleeping, thinking, death) tracked with millisecond precision.
* **Robust error handling** — safe handling of system calls like `usleep`.
* **Resource cleanup** — mutexes and dynamic allocations freed safely.

## Implementation details

* **Threads**: each philosopher is represented by a thread. A monitor thread observes and detects deaths or completion.
* **Mutexes**: each fork guarded by a mutex; other mutexes protect shared state.
* **Logic**: fork acquisition order prevents deadlocks; philosophers alternate between eating, sleeping, and thinking.
* **Cleanup**: helper functions (`clean`, `clean_mutex`) ensure resources are released.
