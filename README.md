*This project has been created as part of the 42 curriculum by fcaval.*

# Codexion

## Description

### Goal

TODO: Explain the purpose of the project in a few sentences.

### Overview

TODO: Describe the simulation at a high level.

- Coders are represented by threads.
- Dongles are shared resources.
- The simulation stops when:
  - a coder burns out, or
  - all coders have compiled at least `number_of_compiles_required` times.

### Project Context

TODO: Summarize the concurrency challenge addressed by the project.

## Instructions

### Requirements

TODO: List any requirements needed to build and run the project.

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

- `number_of_coders`: TODO
- `time_to_burnout`: TODO
- `time_to_compile`: TODO
- `time_to_debug`: TODO
- `time_to_refactor`: TODO
- `number_of_compiles_required`: TODO
- `dongle_cooldown`: TODO
- `scheduler`: TODO

## Blocking Cases Handled

### Deadlock Prevention

TODO: Explain how your implementation prevents deadlocks.

### Coffman Conditions

TODO: Explain which conditions are broken or controlled in your solution.

### Starvation Prevention

TODO: Explain how FIFO and/or EDF scheduling help prevent starvation.

### Dongle Cooldown Handling

TODO: Explain how the cooldown is enforced after a dongle is released.

### Precise Burnout Detection

TODO: Explain how the monitor detects burnout and respects the required timing precision.

### Log Serialization

TODO: Explain how you ensure that log lines are not interleaved.

## Thread Synchronization Mechanisms

### `pthread_mutex_t`

TODO: Explain where mutexes are used and what shared data they protect.

Examples to cover:

- dongle state protection
- coder state protection
- log serialization
- simulation stop flag protection

### `pthread_cond_t`

TODO: Explain whether you use condition variables in your final implementation.

If yes:

TODO: Explain where and why they are used.

If no:

TODO: State that they are allowed by the subject but not used in the final version.

### Thread-Safe Communication

TODO: Explain how coders and the monitor communicate safely through shared state.

### Race Condition Prevention

TODO: Give concrete examples of race conditions avoided in your implementation.

## Technical Choices

### Scheduling Policy

TODO: Explain how `fifo` works in your implementation.

TODO: Explain how `edf` works in your implementation.

### Priority Queue / Heap

TODO: Explain how the heap is used to arbitrate access to dongles.

### Timing Strategy

TODO: Explain how timestamps are computed and used.

## Usage Notes

TODO: Add any important notes for evaluators or users.

Possible ideas:

- limits of the simulation
- expected behavior in edge cases
- interpretation of logs

## Resources

### References

TODO: Add documentation, articles, or tutorials used for the project.

Suggested categories:

- POSIX threads documentation
- mutex documentation
- condition variable documentation
- scheduling / concurrency references
- dining philosophers / resource sharing references

### AI Usage

TODO: Describe clearly how AI was used during the project.

Suggested points to include:

- explanation help
- review of concurrency concepts
- debugging assistance
- no blind copy-paste without understanding

## Possible Improvements

TODO: Add optional future improvements if you want.
