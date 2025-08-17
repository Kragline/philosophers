# Philosophers

_I never thought philosophy would be so deadly._

This project is about learning the basics of **multithreading** in C by simulating the classical **Dining Philosophers Problem**.  
You will learn to create and manage threads, use mutexes to avoid data races, and ensure proper synchronization between concurrent processes.

---

## Mandatory Part

### Program Name
`philo`

### Files to Turn In
- `Makefile`
- `*.h`
- `*.c`  
(All inside the `philo/` directory)

### Makefile Rules
- `NAME`
- `all`
- `clean`
- `fclean`
- `re`

### Arguments
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` : number of philosophers and forks  
- `time_to_die` (ms): time a philosopher can live without eating  
- `time_to_eat` (ms): time it takes a philosopher to eat  
- `time_to_sleep` (ms): time a philosopher spends sleeping  
- `number_of_times_each_philosopher_must_eat` (optional): simulation stops once all philosophers have eaten this many times; otherwise, it stops when a philosopher dies  

### External Functions Allowed
- `memset`
- `printf`
- `malloc`
- `free`
- `write`
- `usleep`
- `gettimeofday`
- `pthread_create`
- `pthread_detach`
- `pthread_join`
- `pthread_mutex_init`
- `pthread_mutex_destroy`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`

### Rules
- Each philosopher is represented as a **thread**.  
- One fork between each pair of philosophers (two for each, except when only one philosopher exists).  
- Forks’ state must be protected with **mutexes**.  
- No global variables allowed.  
- The program must not have **data races**.  

### Logs
Program must display state changes with the following format:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

- `timestamp_in_ms`: current time in milliseconds  
- `X`: philosopher number  
- Death message must appear **within 10ms** of the actual death.  
- Log messages must not overlap.  

---

## Description
This program simulates philosophers sitting at a round table:  
- They alternate between **eating**, **sleeping**, and **thinking**.  
- Eating requires **two forks**.  
- Simulation ends when a philosopher dies or when all have eaten the required number of times (if provided).  

---

## Compilation
```bash
make
```

## Usage Example
```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
```
