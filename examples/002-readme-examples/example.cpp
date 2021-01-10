// various examples from the readme.md of mtl by Michael Trikergiotis
// 15/11/2020
//
// These examples are taken from the readme.md of mtl :
// https://github.com/MichaelTrikergiotis/mtl
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.


// C++ standard library headers we have to include
#include <string>  // std::string
#include <vector>  // std::vector
#include <cmath>   // std::sqrt, std::pow
#include <cstdlib> // std::exit


// mtl headers we have to include
#include "../mtl/string.hpp"     // mtl::string::split, mtl::string::join_all, mtl::string::join
#include "../mtl/console.hpp"    // mtl::console::println, mtl::console::print
#include "../mtl/random.hpp"     // mtl::rng
#include "../mtl/stopwatch.hpp"  // mtl::chrono::stopwatch
#include "../mtl/filesystem.hpp" // mtl::filesystem::write_all_lines, 
                                 // mtl::filesystem::read_all_lines


// How to split an std::string using the mtl.
void example_1()
{
    const std::string names = "Joe, Jill, Bill, Nick, Maria, Helen";
    // split an std::string to tokens by the given delimiter
    std::vector<std::string> tokens = mtl::string::split(names, ", ");
    
    // check the result is what we want
    std::vector<std::string> desired_result { "Joe", "Jill", "Bill", "Nick", "Maria", "Helen" };
    if(tokens == desired_result)
    {
        // to print something to the console followed by a newline
        mtl::console::println("Example 1 produced correct results.");
    }
    else
    {
        mtl::console::println("Error. Example 1 produced incorrect results!!!");
    }
}

// How to join multiple elements of a container to an std::string using the mtl.
void example_2()
{
    const std::vector<std::string> tokens { "Joe", "Jill", "Bill", "Nick", "Maria", "Helen" };
    // join all elements of a container to an std::string each seperate with a delimiter
    std::string joined_names = mtl::string::join_all(tokens.begin(), tokens.end(), ", ");

    // check the result is what we want
    const std::string names = "Joe, Jill, Bill, Nick, Maria, Helen";
    if(joined_names == names)
    {
        mtl::console::println("Example 2 produced correct results.");
    }
    else
    {
        mtl::console::println("Error. Example 2 produced incorrect results!!!");
    }
}

// How to join variables of different types and then print them to console.
void example_3()
{
    const std::string planet = " planet ";
    // join multiple different types of arguments to a single std::string
    // the types of the arguments here are const char*, char, const std::string, float and 
    // const char*
    std::string message = mtl::string::join("Hello from ", 'a', planet, 12.24f, 
                                            " light-years away.");
    // print the joined string to the console followed by a newline
    mtl::console::println(message);

    // second part
    // print multiple different types of arguments to the console, this will produce the same
    // output as the lines above, notice that the last argument is a newline character
    mtl::console::print("Hello from ", 'a', planet, 12.24f, " light-years away.", '\n');

    // check the result is what we want
    const std::string desired_result = "Hello from a planet 12.24 light-years away.";
    if(message == desired_result)
    {
        mtl::console::println("Example 3 produced correct results.");
    }
    else
    {
        mtl::console::println("Error. Example 3 produced incorrect results!!!");
    }
}


// How to generate a random number between 1 and 10 using the mtl.
void example_4()
{
    // create a random number generator that will generate integers from 1 to 10
    mtl::rng<int> rng_1to10 (1, 10);
    // generate a new random integer from 1 to 10
    int random_number = rng_1to10.next();

    // check the result is what we want
    if((random_number >= 1) && ( random_number <= 10))
    {
        mtl::console::println("Example 4 produced correct results.");
    }
    else
    {
        mtl::console::println("Error. Example 4 produced incorrect results!!!");
    }
}


// Just create a function that takes some time to finish.
void my_super_slow_function()
{
    size_t size = 1000000;
    mtl::console::println("Started some math calculations to simulate a slow function.");
    std::vector<double> numbers;
    for(size_t i = 0; i < size; i++)
    {
        // perform some expensive math functions
        double number = std::sqrt(std::pow(std::sqrt(static_cast<double>(i + 10)), 1.01));
        numbers.push_back(number);
    }
    
    mtl::console::println("Finished math calculations to simulate a slow function.");
}

// How to time a function with a stopwatch using the mtl.
void example_5()
{
    // create a stopwatch
    mtl::chrono::stopwatch sw;
    // start the stopwatch
    sw.start();
    // call the function we want to measure
    my_super_slow_function();
    // stop the stopwatch
    sw.stop();
    // get the elapsed time in microseconds, there are also functions that allow you to get the
    // elapsed time in nanoseconds, milliseconds, seconds and minutes
    // the non-Unicode shorthand for microseconds is us
    double time_taken_us = sw.elapsed_micro();

    mtl::console::print("my_super_slow_function() finished execution in ", time_taken_us,
                        " microseconds.\n");

    // check the result is what we want
    if(time_taken_us > 100.0)
    {
        mtl::console::println("Example 5 produced correct results.");
    }
    else
    {
        mtl::console::println("Error. Example 5 produced incorrect results!!!");
    }
}

// How to write the elements of a container each on a newline of a file and how to read all lines
// from a file using the mtl.
void example_6()
{
    const std::vector<std::string> countries { "Italy", "Brazil", "Greece", "Japan" };
    // write all elements of the container each on a new line
    bool written_ok = mtl::filesystem::write_all_lines("countries.txt", countries.begin(), 
                                                                        countries.end());
    
    // check that we could write the file correctly
    if(written_ok)
    {
        mtl::console::println("The file was written correctly for example 6.");
    }
    // if we couldn't write the file print an error message and exit
    else
    {
        mtl::console::println("Error. Couldn't write to file. Exiting.");
        std::exit(1);
    }

    std::vector<std::string> read_countries;
    // read all lines of a file to a container, the container element type has to be std::string
    bool read_ok = mtl::filesystem::read_all_lines("countries.txt", read_countries);

    // check that we could read the file correctly and also the result is what we want
    if (read_ok)
    {
        mtl::console::println("The file was read correctly for example 6.");

        if(countries == read_countries)
        {
            mtl::console::println("Example 6 produced correct results.");
        }
        else
        {
            mtl::console::println("Error. Example 6 produced incorrect results!!!");
        }
    }
    else
    {
        mtl::console::println("Error. The file for example 6 was not read correctly!!!");
    }   
}

int main()
{
    mtl::console::println("Various examples for how to use the mtl.");

    // print the examples with nice dividers between them.
    mtl::console::println("[EXAMPLE 1]");
    example_1();
    mtl::console::println("-----------------------------------------------");

    mtl::console::println("[EXAMPLE 2]");
    example_2();
    mtl::console::println("-----------------------------------------------");

    mtl::console::println("[EXAMPLE 3]");
    example_3();
    mtl::console::println("-----------------------------------------------");

    mtl::console::println("[EXAMPLE 4]");
    example_4();
    mtl::console::println("-----------------------------------------------");

    mtl::console::println("[EXAMPLE 5]");
    example_5();
    mtl::console::println("-----------------------------------------------");

    mtl::console::println("[EXAMPLE 6]");
    example_6();
}