# Operating Systems Fundamentals

A comprehensive implementation of core operating system concepts through practical programming exercises.

## Project Overview

This repository contains a series of task assignments exploring fundamental operating system concepts through hands-on implementation. The project demonstrates key OS mechanisms including inter-process communication, shared libraries, process management, and system programming.

## Components

### TA1: Introduction
- Basic system concepts and C/C++ programming fundamentals for OS development

### TA3: Dynamic Libraries
- Implementation of the Mandelbrot set computation as a shared library
- Demonstrates shared library creation, linking, and usage
- Features proper makefile configuration with RPATH for runtime library resolution

### TA6: Signal-Based IPC
- Inter-process communication using UNIX signals (SIGUSR1/SIGUSR2)
- Binary data transmission between processes using custom signal handling
- Bit manipulation for encoding/decoding information via signals

## Technologies Used

- **Languages**: C, C++
- **Build System**: Make
- **Environment**: Linux
- **IPC Mechanisms**: Signals
- **Libraries**: Standard C/C++ libraries, Dynamic shared libraries
- **Development Tools**: Visual Studio Code

## Key Learnings

- Dynamic memory management and shared library implementation
- Process creation, management, and identification
- Inter-process communication via signals
- Binary data manipulation and bit operations
- System call usage and signal handling
- Makefile configuration for complex build processes

## Usage

Each task directory contains its own implementation and can be built using the provided makefiles:

```bash
# For TA3 (Mandelbrot shared library)
cd TA3
make
./main

# For TA6 (Signal-based IPC)
cd TA6
gcc signal_reciever.c -o receiver
./receiver
# Note the PID and use another terminal to send signals
```

## Requirements

- GCC/G++ compiler
- Linux environment
- Make build system
