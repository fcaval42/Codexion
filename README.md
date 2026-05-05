*This project has been created as part of the 42 curriculum by fcaval.*

# 🛜 Codexion

> Master the race for resources before the deadline masters you.

## ✨ Description

Codexion is a multithreaded simulation written in C with POSIX threads.  
Each coder is a thread sitting in a circular workspace and competing for shared USB dongles in order to compile.

The project is about much more than "making threads run":

- synchronizing access to shared resources
- avoiding invalid concurrent states
- handling contention fairly
- detecting burnout with precise timing
- keeping logs readable and race-free

### 🎯 Goal

The goal of the program is to simulate a group of coders that repeatedly:

1. take two dongles
2. compile
3. debug
4. refactor

The simulation stops when:

- one coder burns out because they did not start compiling in time
- or every coder has compiled at least `number_of_compiles_required` times

### 🧠 Core Idea

Each coder needs **two shared resources at the same time**.  
That makes the problem a classic concurrency challenge close to the dining philosophers problem, with extra constraints:

- a **dongle cooldown**
- a **fair scheduler**
- a **separate monitor thread**
- strict logging rules

## 👀 Visual Overview

```

```

Each coder uses:

- the dongle on the left
- the dongle on the right

So neighbors always share one resource.

### Lifecycle

```text
take 2 dongles -> compile -> debug -> refactor -> repeat
                           |
                           v
                     burnout if deadline is missed
```

### Thread roles

```text
Coder threads:
  request dongles -> wait -> compile -> debug -> refactor

Monitor thread:
  checks deadlines -> prints burnout -> stops simulation
```

## 🚀 Instructions

### Requirements

- `make`

### Compilation

```bash
make
```

### Cleaning

```bash
make clean
make fclean
make re
```

### Execution

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

### Example

```bash
./codexion 4 800 200 200 200 5 10 fifo
```

### Arguments

- `number_of_coders`: number of coder threads and number of dongles
- `time_to_burnout`: maximum time in ms before a coder burns out if they do not start compiling again
- `time_to_compile`: duration of the compile phase in ms
- `time_to_debug`: duration of the debug phase in ms
- `time_to_refactor`: duration of the refactor phase in ms
- `number_of_compiles_required`: number of successful compiles each coder must complete before the simulation stops normally
- `dongle_cooldown`: cooldown in ms after a dongle is released before it can be taken again
- `scheduler`: arbitration policy, either `fifo` or `edf`

## 🧪 Log Format

The program prints state changes as timestamped lines:

```text
timestamp coder_id has taken a dongle
timestamp coder_id is compiling
timestamp coder_id is debugging
timestamp coder_id is refactoring
timestamp coder_id burned out
```

Example:

```text
0 1 has taken a dongle
1 1 has taken a dongle
1 1 is compiling
201 1 is debugging
401 1 is refactoring
```

## 🧱 Blocking Cases Handled

### Deadlock Prevention

The implementation avoids a simple "lock left then lock right forever" strategy.  
Instead, each dongle is requested independently and granted only when:

- the coder is at the top of the waiting queue for that dongle
- the dongle is available
- the cooldown is over

This avoids the classic situation where all threads hold one resource and wait forever for the second.

### Coffman Conditions

The project naturally contains some Coffman conditions because resources are shared and exclusive.  
The implementation reduces deadlock risk by controlling **resource granting order** through a waiting heap instead of letting each thread blindly keep a partially acquired state forever.

In practice:

- mutual exclusion still exists
- contention still exists
- but acquisition is regulated by arbitration and release logic

### Starvation Prevention

Starvation is addressed through the scheduler:

- `fifo`: requests are served in arrival order
- `edf`: requests are served according to the earliest deadline

For equal priorities, insertion sequence is used as a deterministic tie-breaker.

### Dongle Cooldown Handling

After release, a dongle does not become immediately reusable.

The code stores:

- `available`
- `available_at_ms`

A dongle can only be granted when the current time is greater than or equal to `available_at_ms`.

### Precise Burnout Detection

A dedicated monitor thread continuously checks coder deadlines and stops the simulation as soon as a coder burns out.

This design separates:

- worker behavior
- death detection

That makes burnout detection more precise than relying on each coder thread to detect its own failure.

### Log Serialization

All displayed states are protected by a dedicated mutex so two threads never interleave text on the same line.

That keeps the output:

- readable
- deterministic enough for analysis
- compliant with the subject requirements

## 🔒 Thread Synchronization Mechanisms

### `pthread_mutex_t`

Mutexes are the main synchronization primitive used in the project.

They protect:

- each dongle state
- each coder state
- the global stop flag
- the output stream

#### Shared state protected by mutexes

| Protected data | Mutex |
|---|---|
| dongle availability, cooldown, waiting heap | dongle mutex |
| compile count, deadlines, last compile start | coder `state_mutex` |
| simulation stop flag | `stop_mutex` |
| logs / terminal output | `log_mutex` |

### `pthread_cond_t`

`pthread_cond_t` is declared and initialized for dongles because it is allowed by the subject.  
In the current version of the project, the final waiting logic is based on:

- mutexes
- polling with short `usleep`
- heap-based arbitration

So condition variables are **not actively used in the final wait path**.

### Thread-Safe Communication

There is no direct message passing between coders.  
Threads communicate indirectly through shared protected state:

- dongle availability
- coder deadlines
- compile counters
- global stop state

The monitor reads coder state safely through mutex-protected fields, and coders check the global stop flag through `sim_is_stopped()`.

### Race Condition Prevention

Examples of avoided races:

- two coders taking the same dongle at the same time
- a monitor reading a deadline while another thread updates it
- several threads writing logs at the same time
- one thread reading `stop` while another thread updates it

## ⚙️ Technical Choices

### Scheduling Policy

#### FIFO 📥

For FIFO, every request is inserted with the same priority.  
The heap then uses insertion order to keep "first come, first served" behavior.

#### EDF ⏰

For EDF, the priority is the coder deadline:

```text
deadline = last_compile_start_ms + time_to_burnout
```

The most urgent coder gets the smallest priority value and is served first.

### Priority Queue / Heap

Each dongle owns its own waiting heap.

This heap stores:

- priority
- sequence number
- coder id

That allows the dongle to choose who should receive the resource next without relying on OS scheduling luck.

### Timing Strategy

The project uses millisecond timestamps based on `gettimeofday()`.

Timing is used for:

- global simulation start
- coder deadlines
- burnout detection
- action durations
- dongle cooldown
- log timestamps

### Stop Strategy

The simulation ends in two cases:

- the monitor detects a burnout
- a coder notices that all coders reached the required compile count

In both cases, a shared stop flag is set and the threads progressively exit their loops safely.

## 🗂️ Project Structure

```text
.
├── 1.parsing/        # argument validation and parsing helpers
├── 2.init/           # simulation, coders, dongles initialization / cleanup
├── 3.thread/         # coder routines, sim state, logs
├── 4.heap/           # custom priority queue implementation
├── 5.dongles/        # dongle acquisition / release logic
├── 6.monitor/        # burnout detection thread
├── codexion.h        # shared declarations
├── main.c            # entry point
└── Makefile
```

## 📝 Usage Notes

- The project is intentionally timing-sensitive.
- Different machines may produce slightly different timestamps.
- The overall ordering should remain logically correct even if exact milliseconds vary a little.
- In a circular topology, neighboring coders must never compile simultaneously because they share one dongle.

## 📚 Resources

### References

- POSIX Threads Programming
- `man pthread_create`
- `man pthread_mutex_init`
- `man pthread_mutex_lock`
- `man pthread_cond_init`
- `man gettimeofday`
- The dining philosophers problem
- General documentation about EDF scheduling and fairness in concurrent systems

### AI Usage

AI was used as a learning and support tool during the project, mainly for:

- clarifying concurrency concepts
- discussing synchronization design choices
- reviewing logic around mutexes, cooldowns, and scheduling
- helping structure documentation and explanations

AI was **not** used as a blind copy-paste tool.  
All generated ideas had to be reviewed, understood, tested, and adapted to the actual project constraints.

## 🌱 Possible Improvements

- replace polling-based waits with a fully condition-variable-based design
- add more debug tooling for comparing FIFO and EDF behavior
- improve visual tracing for deadlines and waiting queues
- add a richer test harness for edge-case timing analysis
