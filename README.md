# Brainshell

Brainshell is an implementation of the brainfuck programming language as a shell scripting langauge. Brainshell can act like your main shell with the difference being that each character is typed by incrementing or decrementing the data tape.

## Usage

``` text
Usage: brainshell [file]
```

Brainshell can either run code being inputed to it from the console or can run brainshell (`.bsh`) files.
To run a command in brainshell you will need to set the values for the data tape to match the ASCII values of the command you want to run. For example if I want to run `echo "Hello World!"` I would have to set data tape cell 0 to 101 (e), cell 1 to 99 (c) and so on for every character.

Brainshell does not use the `.` and `,` characters for input and output.

## Build and Installation

To installed and use brainshell you will need to compile from source. To do so first clone the repository.

``` shell
git clone https://codeberg.org/Icosa-dev/brainshell.git
cd brainshell
```

Then from there you can run the following possible make commands:

``` shell
make                        # generate unoptimized dev binary
make dev                    # generate unoptimized dev binary
make release                # generate optimized (-O2) release binary
make clean                  # delete build directory and local executable
make install                # create optimized binary OR uses existing one and moves it to /usr/bin
make remove                 # if exists: removes brainshell binary from /usr/bin
```

#### NOTE: The default makefile requires clang to be installed. To use gcc instead set `CC = gcc` in Makefile
