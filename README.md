mad - material database

#####Concept
It stores properties of isotopes, elements and materials for various purposes. 
But it is not meant to be used for visualization or simulation.

All classes are nested in a namespace called ```MAD```.

#####Installation
It requires jintonic/unic to be compiled. 
The path to an installed jintonic/unic in a local machine can be specified in the second line of the Makefile.

The installation path can be specified in the 1st line of the Makefile.

```make && make install``` will copy libMAD.so to /prefix/lib/, and *.h to /prefix/include/MAD/

#####Usage
```cpp
#include <MAD/LiquidXenon.h>
using namespace MAD;
```
