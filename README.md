# UNIX top

## About

top (table of processes) - is a task manager program found in many Unix-like operating systems that displays information about CPU and memory usage.

## My top project

First **programming in UNIX systems** course project  - process statistics sniffer.

 Uses linux *procfs* to produce an output similar to the top command. 

In addition it allows to display processes above provided rss limit. 


## Usage

* just listing
```bash
mytop
```

* help
```bash
mytop --help
```

* keeps running and continuously checking if there are processes that exceed RSS limit of 10M. These processes are listed.
```bash
mytop --rsslim=10M --watch
```

* with provided number of displayed rows in console
```bash
mytop --rows=42
```


## Author
Piotr Woś
