# Thread Synchronization Project

## Overview
This project simulates customers and cooks at Ben’s Chili Bowl restaurant using **POSIX threads (pthreads)**, **mutexes**, and **condition variables**.

Customers place orders, and cooks fulfill them. The restaurant acts as a synchronized queue where customers (producers) add orders and cooks (consumers) remove them.

---

## Files

| File | Description |
|------|--------------|
| `main.c` | Creates and manages customer and cook threads. |
| `BENSCHILLIBOWL.c` | Implements restaurant logic, order queue handling, and thread synchronization. |
| `BENSCHILLIBOWL.h` | Contains struct definitions and function prototypes (do not modify). |
| `Makefile` | Builds and runs the program. |

---

## How It Works
- **Customers** create orders, pick random menu items, and add them to the restaurant.
- **Cooks** repeatedly take orders from the queue, fulfill them, and free memory.
- **Mutexes** protect shared restaurant data.
- **Condition variables** ensure threads wait when the restaurant is full or empty.
- The program ends when all expected orders are completed.

---

## Build Instructions
To compile:
```bash
make
