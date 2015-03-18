A program that works exactly like the Unix "wc" program.

To compile:
    # make

To run:
    # ./wordcount ...

-----------------------------------
Some functions you'll need:

    getopt - Helps parse command-line options.
    fprintf - Write a formatted string to a stream.

    fopen - Open a file as a stream.
    fclose - Close a stream
    fgetc - Read a single byte from a stream.
    fread - Read a bunch of bytes from a file (more efficient than fgetc).

    perror - Print the last failure to stderr.

Getting help for C functions.

    man 3 <name-of-function>
