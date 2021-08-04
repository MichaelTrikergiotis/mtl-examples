# mtl-examples

## What is mtl

The [**mtl**](https://github.com/MichaelTrikergiotis/mtl) or by its full name the [**Modern Template Library**](https://github.com/MichaelTrikergiotis/mtl) is a C++ 17 header-only library that provides everything you ever wanted but the C++ standard library is missing. It provides a lot of functionality that other programming languages include by default in their standard libraries.

For a quick overview of what **mtl** provides you can check the [list of classes and functions](https://github.com/MichaelTrikergiotis/mtl/blob/main/docs/listing.md).

## What is mtl-examples

The **mtl-examples** repository contains detailed examples that teach you how to use the [mtl](https://github.com/MichaelTrikergiotis/mtl) in the most effective way. Read the detailed comments of each example to learn the best usage patterns and common mistakes to avoid.

Instead of the detailed examples from this repository you may wish to check some quick examples that are only few lines long from [here](https://github.com/MichaelTrikergiotis/mtl#examples). All quick examples are also included in this repository with added comments for each line.

For **mtl** documentation refer to the [documentation](https://github.com/MichaelTrikergiotis/mtl/blob/main/docs/documentation.md).

## Hello world using mtl

The simplest example of all, hello world. Using **mtl** to print something to the console is very easy.

```c++
#include "mtl/console.hpp"

int main()
{
    mtl::console::println("Hello World");
}
```

## How to compile

- For **mtl-examples** you need a **C++ 17** compiler. For compiler compatibility refer to the [compiler documentation](https://github.com/MichaelTrikergiotis/mtl/blob/main/docs/documentation.md#c-version-and-compiler-compatibility).
- For **mtl-examples** you need [CMake](https://cmake.org/).

### LINUX

Open the terminal and navigate to the root of **mtl-examples** :

1. ```mkdir build```
2. ```cd build```
3. ```cmake ..```
4. ```cmake --build .```

### WINDOWS

Open `x64 Native Tools Command Prompt for VS 2019` (`vcvars64.bat`) to the root of **mtl-examples** :

1. ```mkdir build```
2. ```cd build```
3. ```cmake ..```
4. ```cmake --build .```

------------------------------------------------------------

## License

The **mtl-examples** is licensed under the [MIT license](./LICENSE).

For third party licenses check [ThirdPartyNotices](./ThirdPartyNotices.txt).

**mtl** by Michael Trikergiotis 2016-2021

**mtl-examples** by Michael Trikergiotis 2020-2021
