# abf
abf is a [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) interpreter written in x86-64 Assembly for Linux.

### Usage
```
Usage: abf [OPTION] FILE
abf is a brainfuck interpreter written in Assembly.

Options:
    -s, --tape-size=NUM    The tape size to use (default: 5000)
                           Change this if your program overflows the default tape size

The FILE argument must point to a file containing a brainfuck program.

Examples:

  Execute a program from stdin:
    $ echo "+++++++++++++++++++++++++++++++++.-----------------------." | abf -

  Execute a program from a file:
    $ abf hello_world.bf

  Execute a program from a file with tape size 1000:
    $ abf -s 10000 large_tape.bf
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


### Interesting programs
Here are some interesting programs you can run with this interpreter.

| Program name    | Description                        | Command                                                                                                                                                  | Source                                                      |
| --------------- | ---------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------- |
| Hello World     | The typical "Hello World!" program | <code>curl "https://gist.githubusercontent.com/kidk/44b8cd699c5879f1084f/raw/e7ae1b5be4b5a9f117b2948e5391b6d464327996/hello-world.b" &#124; abf -</code> | [Source](https://gist.github.com/kidk/44b8cd699c5879f1084f) |
| Towers of Hanoi | Towers of Hanoi visualization      | <code>curl "http://www.clifford.at/bfcpu/hanoi.bf" &#124; abf -</code>                                                                                   | [Source](http://www.clifford.at/bfcpu/)                     |



### Code overview
The interpreter source code can be found in [`bf/bf.S`](bf/bf.S). It directly executes system calls from Assembly and thus does not depend on any libraries to read from stdin/write to stdout.

The rest of the program (handling command-line arguments, reading input files etc.) is written in C.

### Memory Safety
The interpreter does bounds checks to avoid over/underrunning the program string and machine tape (it will show an error message when that happens and terminate safely). 

### [License](LICENSE)
This is free as in freedom software. Do whatever you like with it.
