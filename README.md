# abf
abf is a [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) interpreter written in x86-64 Assembly for Linux.

Additionally, this repository contains some example programs written in Brainfuck.

### Usage
```
Usage: abf [OPTION] FILE
abf is a brainfuck interpreter written in Assembly.

Options:
    -s, --tape-size=NUM    The tape size to use (default: 250)
                           Change this if your program overflows the default tape size

The FILE argument must point to a file containing a brainfuck program.

Examples:

  Execute a program from stdin:
    $ echo "+++++++++++++++++++++++++++++++++.-----------------------." | abf -

  Execute a program from a file:
    $ abf hello_world.bf

  Execute a program from a file with tape size 1000:
    $ abf -s 1000 large_tape.bf
```

### Installation
Installation should be pretty easy on a normal x86-64 Linux system.

1. Clone the repository
    ```shell
    git clone https://github.com/xarantolus/asm-bf
    ```
2. Change to its directory
    ```shell
    cd asm-bf
    ```
3. Install 
    ```shell
    sudo make install
    ```
4. Test if the installation worked by running an example program
    ```shell
    echo "+++++++++++++++++++++++++++++++++.-----------------------." | abf -
    ```
    This should output `!` and a new line.


### Programs included
There are some [programs](programs/) included in this repository. You can of course execute them with this interpreter.

| Program name | Description                        | File                                      | Source                                                      |
| ------------ | ---------------------------------- | ----------------------------------------- | ----------------------------------------------------------- |
| Hello World  | The typical "Hello World!" program | [hello_world.bf](programs/hello_world.bf) | [Source](https://gist.github.com/kidk/44b8cd699c5879f1084f) |

### Code overview
The interpreter source code can be found in [`bf/bf.S`](bf/bf.S). It directly executes system calls from Assembly and thus does not depend on any libraries to read from stdin/write to stdout.

The files in `cmdline` contain the handling of command-line arguments while the `file` directory contains code for reading files to memory.

### Memory Safety
The interpreter does bounds checks to avoid over/underrunning the program string and machine tape (it will show an error message when that happens and terminate safely). 

### [License](LICENSE)
The interpreter (meaning all files *except* for those in the `programs` directory) is released under the MIT license.
