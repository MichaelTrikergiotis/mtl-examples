// random password generator using the mtl by Michael Trikergiotis
// 04/11/2020
//
// An example showcasing how the mtl can be used to create a random password generator. 
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.

// C++ standard library headers we have to include
#include <string>    // std::string, std::getline
#include <iostream>  // std::cin
#include <stdexcept> // std::invalid_argument, std::overflow_error
#include <cstdlib>   // std::exit
#include <vector>    // std::vector

// mtl headers we have to include
#include "../mtl/conversion.hpp"   // mtl::numeric_cast, mtl::to_num
#include "../mtl/algorithm.hpp"    // mtl::contains
#include "../mtl/random.hpp"       // mtl::random_choice
#include "../mtl/console.hpp"      // mtl::console::println, mtl::console::print
                                   // mtl::console::print_all
#include "../mtl/string.hpp"       
// mtl::string::strip, mtl::string::join, mtl::string::to_lower, mtl::string::to_upper, 
// mtl::string::to_string, mtl::string::pad_front




const std::vector<std::string> yes = {"y", "yes", "yeah", "yep"};
const std::vector<std::string> no  = {"n", "no", "nah", "nope"};

bool answer(const std::string& message)
{
    // print an std::string to the console followed by a newline
    mtl::console::println(message);
    std::string user_input;
    // read user input
    std::getline(std::cin, user_input);
    // remove spaces from the front and back
    mtl::string::strip(user_input);
    // convert the std::string to lowercase
    mtl::string::to_lower(user_input);
    // checks user_input is contained in the container
    if(mtl::contains(yes, user_input))
    {
        return true;
    }
    // checks user_input is contained in the container
    else if(mtl::contains(no, user_input))
    {
        return false;
    }
    else
    {
        // print a message to the console and exit
        mtl::console::print("The input was incorrect.");
        mtl::console::println(" You have to use either [y / yes] or [n / no].");
        mtl::console::println("Exiting.");
        std::exit(1);
    }
}

const std::string lowercase_characters = "abcdefghijklmnopqrstuvwxyz";
const std::string uppercase_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string numeric_characters   = "1234567890";
const std::string special_characters   = "~`!@#$%^&*()-_=+";

std::string generate_password(const size_t size, const bool lowercase, const bool uppercase, 
                              const bool numbers, const bool special)
{
    std::string character_set = "";
    if(lowercase)
    {
        // join two strings together
        character_set = mtl::string::join(character_set, lowercase_characters);
    }
    if(uppercase)
    {
        character_set = mtl::string::join(character_set, uppercase_characters);
    }
    if(numbers)
    {
        character_set = mtl::string::join(character_set, numeric_characters);
    }
    if(special)
    {
        character_set = mtl::string::join(character_set, special_characters);
    }

    std::string password;
    // set the password's size to the length we want so we can iterate over and change each 
    // character with random characters chosen from the set of characters
    password.resize(size);

    // iterate over all characters and change them to a random character
    for(auto& character : password)
    {
        // replace each character with a randomly chosen character from a container using 
        // mtl::random_choice, in this case the std::string which acts as a container of chars,
        // mtl::random_choice returns an iterator to a random position in the given container 
        character = *(mtl::random_choice(character_set));
    }

    return password;
}

// Prints a colored message with a rating for the strength of the generated passwords. Stronger
// passwords are more secure because they take a lot longer to crack using bruteforce methods. 
void rate_password_strength(const size_t password_length, const bool lowercase, 
                            const bool uppercase, const bool numbers, const bool special)
{
    mtl::console::print("\nGenerated passwords strength : ");
    if((password_length > 10) && (lowercase) && (uppercase) && (numbers) && (special))
    {
        // for strong passwords we print to the console using the green color for the foreground
        mtl::console::print_color("[STRONG]", mtl::console::color::green);
    }
    else if((password_length >= 8) && (password_length <= 10) && (lowercase) && (uppercase) &&
            (numbers) && (special))
    {
        // for medium strength passwords we print to the console using the yellow color for the
        // foreground
        mtl::console::print_color("[MEDIUM]", mtl::console::color::yellow);
    }
    else
    {
        // for weak passwords we print to the console using the red color for the foreground
        mtl::console::print_color("[WEAK]", mtl::console::color::red);
    }
    mtl::console::println();
}

int main()
{
    std::string title = "=== [Welcome to the random password generator.] ===";
    // convert an std::string to uppercase
    mtl::string::to_upper(title);

    mtl::console::println(title);
    mtl::console::println("Please select password length : ");

    // get the length of the password from the user    
    std::string user_input;
    int password_length = 0;
    bool correct_pass_length = false;
    while(correct_pass_length == false)
    {
        try
        {
            // read user input
            std::getline(std::cin, user_input);
            // remove spaces from the front and back
            mtl::string::strip(user_input);
            // try to convert the std::string to an integer, if we can't an exception will be
            // thrown, please note that there is an alternative version of mtl::to_num called 
            // mtl::to_num_noex that does not throw exceptions and has two different overloads, but
            // we have chosen to showcase this version, please note that throwing exceptions
            // in C++ is slow due to how exceptions are designed, to be cheap when not thrown and
            // very expensive when thrown
            password_length = mtl::to_num(user_input);

            // if password is below 6 characters
            if(password_length < 6)
            {
                // if we are here then it means we successfully converted the std::string to an
                // integer
                mtl::console::println("Password length is too small. Select a number above 5.");
            }
            // if password is more than 20 characters
            else if(password_length > 20)
            {
                mtl::console::println("Password length is too big. Select a number below 21.");
            }
            else
            {
                correct_pass_length = true;
            }
        }
        // do not use a name for the captured exception because we don't want to use the exception
        // message instead we want to print our own message
        catch(const std::invalid_argument&)
        {
            mtl::console::print("Incorrect value. Not a number. Please type an integer number ");
            mtl::console::println("between 6 and 20.");
        }
    }

    size_t length = 0;
    try
    {
        // convert the signed integer to an unsigned integer safely with mtl::numeric_cast, if the
        // number can't be converted an exception will be thrown, please note that there is another
        // version of mtl::numeric_cast called mtl::numeric_cast_noex that doesn't throw
        // exceptions and has two different overloads, but we have chosen to showcase this version,
        // please note that throwing exceptions in C++ is slow due to how exceptions are designed,
        // to be cheap when not thrown and very expensive when thrown
        length = mtl::numeric_cast<size_t>(password_length);
    }
    catch(const std::overflow_error& exception)
    {
        // print error message and exit
        mtl::console::println(exception.what());
        std::exit(1);
    }

    

    // if we got the correct number let's ask what characters our password should contain
    mtl::console::println("Should the random password include :");
    bool lowercase = answer("[y / yes] or [n / no] ... lowercase ASCII [a to z] ?");
    bool uppercase = answer("[y / yes] or [n / no] ... uppercase ASCII [A to Z] ?");
    bool numbers   = answer("[y / yes] or [n / no] ... numbers [0 to 9] ?");
    bool special   = answer("[y / yes] or [n / no] ... special characters [!, @, #, $, ^ etc.]");

    // if no character set is chosen then complain and exit
    if((lowercase == false) && (uppercase == false) && (numbers == false) && (special == false))
    {
        mtl::console::print("You have not selected any type of character to be included in the ");
        mtl::console::println("random passwords. Can't generate passwords.");
        mtl::console::println("Exiting.");
        std::exit(1);
    }

    // print a colored message about the strength of the generated passwords
    rate_password_strength(length, lowercase, uppercase, numbers, special);

    // print a newline
    mtl::console::println();
    mtl::console::println("Here are 10 randomly generated passwords :");
    const size_t repetitions = 10;
    // convert the largest number to a string, we will use that string as a guide to find 
    // how many spaces to pad, so all numbers are aligned when they are printed to the console
    const std::string max_padding = mtl::string::to_string(repetitions);
    for(size_t i = 0; i < repetitions; i++)
    {
        std::string random_password;
        // generate a random password with the given parameters
        random_password = generate_password(length, lowercase, uppercase, numbers, special);
        // convert the loop counter to an std::string
        std::string counter = mtl::string::to_string(i + 1);
        // pad the front of the counter with enough spaces to match the number with the most
        // characters so everything will be aligned nicely
        mtl::string::pad_front(counter, max_padding);
        // print multiple variables of different types with a newline at the end
        mtl::console::print(counter, ".) ", random_password, '\n');
    }


    // generate and store 100 random passwords
    const size_t size = 100;
    std::vector<std::string> random_passwords;
    random_passwords.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        random_passwords.emplace_back(generate_password(length, lowercase, uppercase, numbers, 
                                                        special));
    }

    mtl::console::println("\nHere are 100 randomly generated passwords inside square brackets :");

    // print the container nicely to the console, where each password is contained inside
    // square brackets and there is a space between them, print 5 passwords per line and
    // each line should start with opening square bracket and end with closing square bracket
    mtl::console::print_all(random_passwords.begin(), random_passwords.end(), "] [", 5, "[", "]");
}