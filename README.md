# tee

My own version of the Unix `tee` command, written in C using only the low-level
file I/O system calls (`open`, `read`, `write`, `close`).

This is **Exercise 4-1** from *The Linux Programming Interface* by Michael Kerrisk
(Chapter 4: File I/O: The Universal I/O Model).

## What it does

`tee` reads from standard input and writes everything it reads to **both**
standard output and a file.

```
./tee file      # erase the file first, then write to it
./tee -a file   # append to the end of the file instead
```

## Build

```
cc -Wall -o tee tee.c
```

## Example

```
$ echo "one" | ./tee out.txt
one
$ echo "two" | ./tee -a out.txt
two
$ cat out.txt
one
two
```

## What I practised

- File descriptors: `STDIN_FILENO` (0), `STDOUT_FILENO` (1), and the one `open()` returns
- `open()` flags: `O_WRONLY | O_CREAT | O_TRUNC` vs. `O_WRONLY | O_CREAT | O_APPEND`
- A `read()`/`write()` loop that writes exactly `numRead` bytes each time
- Checking every system call for `-1` and reporting errors with `perror()`
