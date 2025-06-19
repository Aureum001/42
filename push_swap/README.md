# Push Swap Project

## Overview
The Push Swap project is a sorting algorithm implementation that utilizes two stacks to sort a list of integers. The project includes a checker functionality to verify the correctness of the sorting operations.

## File Structure
```
push_swap
├── src
│   ├── push_swap.c       # Entry point of the program
│   ├── checker.c         # Implements the checker functionality
│   ├── operations.c      # Contains stack operations
│   ├── sorting.c         # Implements sorting algorithms
│   └── utils.c           # Provides utility functions
├── includes
│   └── push_swap.h       # Header file with function prototypes
├── Makefile               # Build instructions
└── README.md              # Project documentation
```

## Compilation
To compile the project, run the following command in the terminal:

```
make
```

This will generate the executable for the Push Swap program.

## Usage
To run the Push Swap program, use the following command:

```
./push_swap [list of integers]
```

Replace `[list of integers]` with the integers you wish to sort.

## Checker
To use the checker functionality, you can pipe commands into the program:

```
./checker [list of integers]
```

You can then input commands such as `sa`, `sb`, `pa`, `pb`, `ra`, `rb`, `rra`, `rrb` to manipulate the stacks and verify the sorting.

## Functionality
- **Sorting**: The program sorts a list of integers using a custom sorting algorithm.
- **Checker**: The checker verifies if the sorting operations were applied correctly.

## Notes
- Ensure that the input integers are valid and do not contain duplicates.
- The project is designed to handle various edge cases and provide error messages for invalid inputs.