# UNIX top

## About

top (table of processes) - is a task manager program found in many Unix-like operating systems that displays information about CPU and memory utilization.

## My top project

First **programming in UNIX systems** course project  - process statistics sniffer.

 Uses linux procfs to produce an output similar to the top command. 

In addition allows for setting limits that would signal processes exceeding them. 

## Usage

* just listing
```bash
mytop
```

* keeps running and continuously checking if there are processes that exceed RSS limit of 10M. These processes are listed.
```bash
mytop --rsslim=10M --watch
```

* help
```bash
mytop --help
```

## Author
Piotr Woś
