Below is a sample README for your C project:

---

# Mail Office Simulation (Project 2)

This project simulates a mail office environment where client and worker processes interact using shared memory and semaphores. The simulation demonstrates inter-process communication, process synchronization, and proper resource cleanup in a concurrent system.

---

## Features

- **Client Processes:**  
  - Each client (process Z) simulates a person arriving at the mail office.
  - Clients choose a random service type (1–3) and enter a corresponding service queue.
  - If the office is closed, the client immediately goes home.

- **Worker Processes:**  
  - Each worker (process U) simulates an office worker.
  - Workers serve clients from the service queues.
  - When no clients are waiting, workers take a break.
  - When the office is closed and all queues are empty, workers finish their work and go home.

- **Shared Memory & Semaphores:**  
  - Shared memory is used to store common variables (e.g., office open status, queue counters, and a line number for logging).
  - Semaphores synchronize access to these shared resources, ensuring that actions are logged in order and that clients and workers interact correctly.

- **Logging:**  
  - All process events (e.g., starting, serving, breaks, and closing) are logged sequentially to an output file (`proj2.out`).

---

## Prerequisites

- A Unix-like operating system (the code uses `fork()`, shared memory, and POSIX semaphores).
- A C compiler with support for POSIX threads and semaphores (e.g., `gcc`).

---

## Compilation

Compile the code using a command like:

```bash
gcc -Wall -Wextra -O2 -o proj2 proj2.c -pthread
```

*Note:* Depending on your system, you may need to link with additional libraries (for example, `-lrt` for real-time extensions).

---

## Usage

The program requires exactly five command-line arguments:

```bash
./proj2 NZ NU TZ TU F
```

Where:
- **NZ**: Number of client processes (simulated clients).
- **NU**: Number of worker processes.
- **TZ**: Maximum time (in milliseconds) a client waits before entering the office.
- **TU**: Maximum break time (in milliseconds) for a worker when there are no clients.
- **F**: A parameter that influences the closing time of the mail office (in milliseconds or used as a factor to calculate delay).

### Example

```bash
./proj2 10 3 1000 500 2000
```

This runs the simulation with:
- 10 client processes.
- 3 worker processes.
- Clients waiting up to 1000 milliseconds.
- Workers taking breaks up to 500 milliseconds.
- The office closing after a calculated delay based on the value 2000.

---

## Output

- The program writes its log to the file `proj2.out`.
- Log entries include sequential line numbers and messages indicating events such as:
  - Client arrival, service request, and departure.
  - Worker start, break, service, and departure.
  - Office closing notification.

---

## Cleanup

- After execution, the program cleans up all shared memory and semaphore resources.
- If any error occurs (e.g., during semaphore initialization or process creation), the program outputs an error message to `stderr` and performs cleanup.

---

## Notes

- The use of `srand(time(NULL))` in multiple processes may result in similar random values if processes start nearly simultaneously.
- Ensure that your system supports the necessary POSIX features (shared memory and semaphores) before running the simulation.

---

