*This project has been created as part of the 42 curriculum by hrabh*

## Description

Codexion is a project from the 42 Common Core that focuses on multithreading programming, inspired by the classic Dining Philosophers problem.

In this simulation, a group of coders works in a shared circular environment where each coder needs two USB dongles to compile their code. Each coder alternates between compiling, debugging, and refactoring.

The main challenge is to manage limited shared resources safely and efficiently using threads and synchronization mechanisms. The system must ensure that all coders can operate without deadlocks, starvation, or burnout.

To achieve this, a scheduling system is implemented to control access to dongles using either FIFO (First In, First Out) or EDF (Earliest Deadline First) strategies.

## Instructions

All project files are located in the `coders/` directory.

### Compilation

The project is compiled using a Makefile:

- `make`      : builds the program
- `make clean`: removes object files
- `make fclean`: removes object files and the executable
- `make re`   : rebuilds the project from scratch

### Execution

The program is executed as follows:

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler 

#Example
./codexion 5 2000 100 100 100 5 100 fifo
```

## Resources

For the success of this project, I used multiple resources to understand the core concepts of multithreading and scheduling systems.

### Learning Materials

- YouTube tutorials to understand:
  - Threads and multithreading programming
  - POSIX threads (pthreads)
  - Synchronization and mutex usage

- Heap Sort algorithm reference:
  https://www.programiz.com/dsa/heap-sort

### Artificial Intelligence Usage

I also used AI tools to:
- Clarify difficult concepts
- Understand multithreading behavior and synchronization
- Explain scheduling strategies such as FIFO and EDF
- Help debug and improve my implementation understanding

## Blocking Cases Handled

### Data Race
A data race occurs when multiple coder threads try to access and modify shared resources (dongles) at the same time without proper synchronization.

To prevent this issue, mutexes are used to ensure that only one coder can access a dongle at a time. Additionally, the scheduler (FIFO or EDF) controls the order of access, ensuring fair and deterministic resource allocation.

---

### Deadlock Prevention

Deadlocks are avoided by enforcing a consistent dongle acquisition strategy: each coder always takes the left dongle first, then the right dongle (or vice versa consistently for all coders). This removes circular waiting between left/right neighbors. Dongles are protected with mutexes, and the scheduler (FIFO/EDF) further controls access order.

### Thread Synchronization Mechanisms

The project uses `pthread_mutex_t` to protect shared dongles and ensure exclusive access during acquisition and release.

A separate monitor thread checks coder state and detects burnout based on timing conditions.

`pthread_cond_t` is used to manage waiting behavior when dongles are not available, allowing threads to sleep and be notified efficiently.

These mechanisms ensure safe synchronization between coder threads and prevent race conditions.