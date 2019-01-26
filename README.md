# c-tail-log

> A tail -f like implementation in c with included colorizing support

## Installation

Building with makefile

`make`builds the main command line tool

`make writer` builds the writer tool for testing

***Note:*** Binaries are put into bin/ folder

## Usage

```
ctail [options][file]
```

## Flags

### help
Prints the help usage

```
-h --help
```

### color

Deactivates colored output:

```
-c --color
```

### silent
Suppress all errors:

```
-q --quiet
```

### debug mode
Show debug messages:

```
-d --debug
```

### verbose mode
Show info messages:

```
-v --verbose
```

### initial lines
Define how many lines should get printed at startup  

```
-l --lines (MAX of 64 | 5 by default)
```

## License

MIT License

Copyright (c) 2019 Michael Wiesendanger

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
