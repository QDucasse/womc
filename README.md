# womc: word of mouth project in C

This undergrad project comes as an introductory project to the C programming language. 

### Structure

The project is structured as follows:

- `src` - contains the sources and correction of the project
- `tests` - contains samples in a `main()` to generate simple binaries to check with [valgrind](https://valgrind.org/)
- `mutests` - contains the code and file to run unit tests through [munit](https://nemequ.github.io/munit/)
- `doc` - contains the main subject and figures for the project
- `generator` - contains a simple python script to generate a file with a list of people formatted as `Firstname,LASTNAME,zipcode;`
- `data` - contains example of generated files 
- `bin` - is the target for object files and binaries
- `skeleton` - contains the basis to hand out to students

### Installation

The project can be installed with:

```bash
$ git clone git@github.com/QDucasse/womc.git
$ cd womc
$ git submodule init
$ git submodule update
```

Three executables can be generated: 
1. `womc` - the main executable
2. `tests` - samples to run through valgrind
3. `mutests` - unit tests 

```bash
$ make all # (or tests, mutests, womc by default)
```

> Note: The unit tests test both the functionalities and the handling of null pointers. The log should print a custom error and not segfault in those cases!

### License

```
MIT License

Copyright (c) 2022 Quentin DUCASSE

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```