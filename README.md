# My CPU Monitor

A lightweight, real-time CPU performance monitor written in C. This tool parses the Linux `/proc/stat` filesystem to calculate aggregate CPU load and uses system piping to identify the top resource-consuming processes.

## Features
* **Real-time Monitoring:** Tracks global CPU utilization percentage.
* **Process Tracking:** Identifies the top CPU-consuming process automatically.
* **Zero Dependencies:** Written in standard C; no external libraries required.
* **Flicker-Free UI:** Uses ANSI escape codes for smooth terminal updates.

## How to Compile
You will need `gcc` installed on your Linux system. Open your terminal in the project folder and run:

```bash
gcc index.c -o cpu_monitor
