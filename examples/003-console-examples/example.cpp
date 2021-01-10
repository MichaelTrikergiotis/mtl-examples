// various examples from how to use mtl::console by Michael Trikergiotis
// 09/12/2020
//
// Various examples for how to use the functions found in the namespace mtl::console.
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.


// C++ standard library headers we have to include
#include <string>  // std::string
#include <vector>  // std::vector
#include <list>    // std::list


// mtl headers we have to include
#include "../mtl/string.hpp"     // mtl::string::join
#include "../mtl/console.hpp"    
// mtl::console::print, mtl::console::println, mtl::console::print_all 
// mtl::console::print_color, mtl::console::println_color, mtl::console::overtype,
// mtl::console::clear



// How to print a single variable to the console with mtl::console::print and mtl::console::println.
void example_1()
{
    // this will output Hello to the console
    mtl::console::print("Hello ");
    // this will output World to the console followed by a newline
    mtl::console::println("World.");
}

// How to print multiple variables of different types to the console with mtl::console::print and 
// mtl::console::println.
void example_2()
{
    // mtl::console::print and mtl::console::println can output various types of variables
    const int   i = 333;
    const float f = 444.44f;
    const std::string same  = " same line";
    const std::string other = "other line";

    // all variables will be printed in the same line
    mtl::console::print("same line ", i, " same line ", f, same);
    // let just print a newline
    mtl::console::println();
    // all variables will be printed in a newline
    mtl::console::println("other line", i, "other line", f, other);
}

// How to print containers to the console with the use of mtl::console::print_all.
void example_3()
{
    // mtl::console::print_all is very flexible and can output containers in different ways

    const std::vector<std::string> names { "Bill", "Bob", "Jill", "Jace", "Jannet", "Maria" };
    // print all names from the container in the same line separated by a comma and a space
    mtl::console::print_all(names.begin(), names.end(), ", ");

    // print multiple newlines
    mtl::console::println("\n----\n");

    // mtl::console::print_all supports various kinds of containers
    const std::list<double> numbers { 0.1, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    // print all numbers two in each line, each element can be separated by the requested string,
    // each line can start with the requested string, each line can end with the requested string
    mtl::console::print_all(numbers.begin(), numbers.end(), " | ", 2, "- ", " -");

    mtl::console::println("----\n");

    const std::vector<int> big_numbers {1, 22, 333, 4444, 55555, 666666, 7777777, 88888888, 
                                        1, 22, 333, 4444, 55555, 666666, 7777777, 88888888,
                                        1, 22, 333, 4444, 55555, 666666, 7777777, 88888888,
                                        1, 22, 333, 4444, 55555, 666666, 7777777, 88888888};
    // mtl::console::print_all can align elements it prints, the ways you can pad the elements are
    // to the front, to the back, both ways but mostly to the front and both ways but mostly to the
    // back
    mtl::console::print_all(big_numbers.begin(), big_numbers.end(), " ][ ", 4, "-[ ", " ]-", 
                            mtl::console::print_pad::both_back);

}

// How to print color to the console with the use of mtl::console::print_color and 
// mtl::console::println_color. You can select foreground and background colors. Please note 
// different OS, terminals and terminal themes can alter the appearance of colors greatly.
void example_4()
{
    mtl::console::print("[Please note different OS, terminals and terminal themes ");
    mtl::console::println("can alter the appearance of colors greatly.]");
    mtl::console::print_color("Let there be color.", mtl::console::color::cyan);
    mtl::console::println();
    mtl::console::println("No color for this line.");
    mtl::console::print_color("WE NEED MORE ", mtl::console::color::magenta);
    mtl::console::print_color("[RED] "  , mtl::console::color::red);
    mtl::console::print_color("[GREEN] ", mtl::console::color::green);
    mtl::console::print_color("[BLUE]" , mtl::console::color::blue);
    
    mtl::console::print("\n----\n");

    mtl::console::println_color("[CYAN BACKGROUND]",    mtl::console::color::default_color,
                                                        mtl::console::color::cyan );
    mtl::console::println_color("[MAGENTA BACKGROUND]", mtl::console::color::default_color,
                                                        mtl::console::color::magenta );
    mtl::console::println_color("[YELLOW BACKGROUND]",  mtl::console::color::default_color,
                                                        mtl::console::color::yellow );
    mtl::console::println_color("[BLACK BACKGROUND]",   mtl::console::color::default_color,
                                                        mtl::console::color::black );  

    mtl::console::println_color("You can have different foreground and background colors.",
                                mtl::console::color::blue, mtl::console::color::white);
    mtl::console::println_color("You can have bright red text color and yellow background color.",
                                mtl::console::color::bright_red, mtl::console::color::yellow);
    mtl::console::println_color("You can have bright yellow text color and red background color.",
                                mtl::console::color::bright_yellow, mtl::console::color::red);                                                     
}


// You can type over already printed characters in the same line with mtl::console::overtype.
// You can clear the console with the use of mtl::console::clear.
void example_5()
{
    // printing normally to the console
    const std::string numbers = "1234567890";
    mtl::console::print("Normal    : ", numbers, '\n');

    // printing then overtyping
    mtl::console::print("Overtyped : ", numbers);
    // you can type over already printed characters as long as they are on the same line
    mtl::console::overtype("**********");
    mtl::console::println('\n');

    mtl::console::println("Using mtl::console::clear() clears the console.");
    mtl::console::println("The mtl::console::clear() will not be showcased in this example.");
}

int main()
{
    mtl::console::println("Various examples for how to use the mtl::console.");

    // print the examples with nice dividers between them.
    mtl::console::println("[EXAMPLE 1]");
    example_1();
    mtl::console::println("---------------------------------------------------\n");

    mtl::console::println("[EXAMPLE 2]");
    example_2();
    mtl::console::println("---------------------------------------------------\n");

    mtl::console::println("[EXAMPLE 3]");
    example_3();
    mtl::console::println("---------------------------------------------------\n");

    mtl::console::println("[EXAMPLE 4]");
    example_4();
    mtl::console::println("---------------------------------------------------\n");

    mtl::console::println("[EXAMPLE 5]");
    example_5();
}