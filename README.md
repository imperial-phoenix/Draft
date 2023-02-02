# Draft
Interview preparation project.

## Project structure
* *CMake:* Includes macros and functions, find_modules, and one-off scripts
* *Src:* Stores the source of out binaries and libraries
    * *Include:* Common header files
* *Extern:* Configuration for external projects we are building from source
* *Test:* Contains code for unit tests

# Coding style
## Common
* Abbreviations should be written in the form when only the first character of the abbreviation is written in uppercase

* Order of including header files
    * Common (root) platform header files
    * Third party header files
    * Header files of the language's standard library
    * Project libraries header files
    * Header files with prototypes of functions implemented in the source code of the file
```
#include <Windows.h>       // platform header

#include <gtest.h>         // third party header

#include <stdarg.h>        // standard library header
#include <string>          // stl header

#include "Include/List.h"  // project library header

#include <Include/Stack.h> // own header
```

* Grouped code areas must be preceded by three lines of comments
```
////////////////////////////////////////////////////////
///               Static functions                   ///
////////////////////////////////////////////////////////

InSum(int a, int b)
{
   ...
}


InSub(int a, int b)
{
   ...
}


////////////////////////////////////////////////////////
///                    List api                      ///
////////////////////////////////////////////////////////

CreateList()
{
   ...
}

```

## Separators
### Horizontal
* The \t must be replaced with 3 spaces

### Vertical
* Logical blocks of code are separated by **one** empty line
* Empty line before comments
* The declaration of functions, structures and enumerations is separated by **two** empry lines

## Naming
### File
* The filename is written in CamelCase notation

### Variables
* The variable name is written in CamelCase notation
* Local variable names **must** start with a lowercase character
* Global variable names **must** be prefixed with g_
* Function parameters **must** start with an uppercase character

### Structures
* Structure **names** must consists of uppercase characters, which can be separated by underscores
* Struct fields must start with an uppercase character

### Enumerations
???

### Macros
* Macro names are written using uppercase characters separated by underscores

## Functions
* The function name is written in CameCase notation
* The names of static functions must begin with the prefix *In* (from *Internal*)
* The names of functions that return pointers and perform memory allocation for the returned pointer must contain one of the words *Create*, *Open*, *Convert* in their name.
* The names of functions that return pointers and do not allocate memory for returned pointer must contain one of the words *Get*, *Set* in their name


## Code design
### Functions
* Each word of the function signature is written on a new line
* Function parameters are written along with direction macros (*IN*, *OUT*, *OPTIONAL*)

### Switch-case
```
switch (condition)
{
case 1:
{
   ...
   break;
}
case 2:
{
   ...
   break;
}

default:
   break;
}
```