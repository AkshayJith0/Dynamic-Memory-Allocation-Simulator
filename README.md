# Dynamic Memory Allocation Simulator

A C++ console-based simulator with an interactive HTML/JavaScript GUI for demonstrating dynamic memory allocation and memory management concepts.

## Features

- First-Fit memory allocation
- Best-Fit memory allocation
- Dynamic memory block splitting
- Memory deallocation
- Automatic merging of adjacent free blocks (coalescing)
- Visual memory map
- Memory block table with addresses, sizes, and status
- Fragmentation statistics
- Console activity log

## Memory Allocation Techniques

### First-Fit

First-Fit searches the memory blocks from the beginning and allocates the process to the first free block that is large enough.

### Best-Fit

Best-Fit searches all available free blocks and allocates the process to the smallest free block that can satisfy the requested size.

## Memory Management

When a block is larger than the requested size, the simulator splits the block into an allocated block and a remaining free block.

When memory is freed, adjacent free blocks are merged together to reduce fragmentation.

## Fragmentation

The simulator displays:

- Total free memory
- Total used memory
- Number of free blocks

A larger number of separated free blocks indicates greater external fragmentation.

## Project Structure

```text
Dynamic-Memory-Allocation-Simulator/
│
├── memory_allocator.cpp
├── memory_allocator_gui.html
├── README.md
└── .gitignore
