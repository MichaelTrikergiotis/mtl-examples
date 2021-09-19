// how to use mtl::frequency by Michael Trikergiotis
// 17/08/2021
//
// The function mtl::frequency can count any type of element in a container and produces an 
// std::unordered_map. The std::unordered_map contains the element and a number representing
// the count of times the element was encountered. These are some examples showcasing how 
// mtl::frequency could possibly be used. 
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.



#include <string>             // std::string
#include <vector>             // std::vector
#include <unordered_map>      // std::unordered_map
#include <utility>            // std::pair
#include <algorithm>          // std::remove_if, std::max_element, std::sort
#include "../mtl/console.hpp" // mtl::console::println, mtl::console::print
#include "../mtl/numeric.hpp" // mtl::frequency
#include "../mtl/random.hpp"  // mtl::rng
#include "../mtl/string.hpp"  // mtl::string::join, mtl::string::to_lower, mtl::string::replace, 
                              // mtl::string::split, mtl::string::pad, mtl::string::to_upper, 
                              // mtl::string::pad_back





// An example on how to use mtl::frequency to count different types of pets.
void example_1()
{
    // print a message for the first example
    mtl::console::println("--------------------------------------------------");
    mtl::console::println("[EXAMPLE 1 - COUNT EACH TYPE OF PET IN A PET SHOP]");
    mtl::console::println("--------------------------------------------------");

    // various pets
    const std::string cat = "cat";
    const std::string dog = "dog";
    const std::string parrot  = "parrot";
    const std::string rabbit  = "rabbit";
    const std::string hamster = "hamster";

    // a pet shop containing different pets
    const std::vector<std::string> pet_shop
    {
        cat, cat, cat, dog, dog, parrot, rabbit, hamster, dog, dog, dog, dog, cat, dog, parrot, 
        rabbit, rabbit, rabbit, rabbit, rabbit, rabbit, hamster, parrot, hamster, parrot, hamster,
        parrot, hamster, parrot, hamster
    };

    // find the frequency of each pet type
    auto pet_frequency = mtl::frequency(pet_shop.begin(), pet_shop.end());

    // print how many of each pet type there are in the shop
    for(auto& pet : pet_frequency)
    {
        mtl::console::print("There are ", pet.second, " ", pet.first, "s in the pet shop.\n");
    }
}



// An example on how to find the word frequency of a text.
void example_2()
{
    mtl::console::println("------------------------------------------------");
    mtl::console::println("[EXAMPLE 2 - COUNT THE WORD FREQUENCY OF A TEXT]");
    mtl::console::println("------------------------------------------------");

    // create some text
    const std::string text1 = "Some text to process.";
    const std::string text2 = "Some other text to process.";
    const std::string text3 = "Even more repetitive text.";
    const std::string text4 = "This is some more repetitive text.";

    // combine all text
    std::string combined_text = mtl::string::join(text1, " ", text2, " ", text3, " ",  text4);

    // print the combined text
    mtl::console::println("The text :");
    mtl::console::print("[", combined_text, "]\n\n");

    // convert all text to lowercase, this function doesn't perform any allocations
    mtl::string::to_lower(combined_text);

    // remove all occurrences of the dot character, this mtl::string::replace overload doesn't
    // perform any allocations
    mtl::string::replace(combined_text, '.', ' ');
    
    // split all words into separate strings to an std::vector<std::string>
    auto parts = mtl::string::split(combined_text, " ");

    // remove all empty parts using the erase-remove idiom
    parts.erase(std::remove_if(parts.begin(), parts.end(), [](const auto& word)
    {
        if(word.empty())
        {
            return true;
        }
        return false;
    }), parts.end());

    // find the frequency of each word
    auto word_frequency = mtl::frequency(parts.begin(), parts.end());

    
    // find the longest word
    auto longest_word = std::max_element(word_frequency.begin(), word_frequency.end(), 
    [](auto& rhs, auto& lhs)
    {
        return rhs.first.size() < lhs.first.size();
    });
  

    mtl::console::println("Word frequency :");
    // print all words and their frequency of appearance
    for(auto& freq_pair : word_frequency)
    {
        std::string word = freq_pair.first;
        // pad the current word with spaces to both sides but mostly to the back, to match the
        // longest word
        mtl::string::pad(word, longest_word->first, ' ', true);
        // convert the word to uppercase, this function doesn't perform any heap allocations
        mtl::string::to_upper(word);
        mtl::console::print("The word [ ", word, " ] appears ", freq_pair.second);
        mtl::console::println(" times in the text.");
    }
}



// Displays to the console the sorted frequency distribution for each random number of the
// container.
void display_sorted_frequency(const std::unordered_map<int, size_t>& container)
{
    // copy the std::unordered_map to a container that can be sorted
    std::vector<std::pair<int, size_t>> numbers(container.begin(), container.end());

    // sort the container based on the first element of the std::pair
    std::sort(numbers.begin(), numbers.end(),[](auto& rhs, auto& lhs)
    {
        return rhs.first < lhs.first;
    });

    // find the element with the max value
    auto max_element = std::max_element(numbers.begin(), numbers.end(), [](auto& rhs, auto& lhs)
    {
        return rhs.second < lhs.second;
    });
    // remember the maximum value
    size_t max_size = max_element->second;
    

    // print all elements to the console
    for(auto& number_pair : numbers)
    {
        // create a string with length equal to the frequency of appearance of a number in the
        // container
        std::string counter (number_pair.second, '#');
        // pad the string with the given character to match the longest string
        mtl::string::pad_back(counter, max_size - counter.size(), '_');      
        // print the pair followed by a newline
        mtl::console::print("[", number_pair.first , "][", counter, "]\n");
    }
}


// An example displaying the sorted frequency distribution of random numbers using mtl::frequency.
void example_3()
{
    mtl::console::println("--------------------------------------------------------");
    mtl::console::println("[EXAMPLE 3 - DISPLAY THE DISTRIBUTION OF RANDOM NUMBERS]");
    mtl::console::println("--------------------------------------------------------");

    // create a container to store random numbers
    std::vector<int> numbers (100);
    // fill the container with random numbers from 0 to 9
    mtl::rng small_num_rng(0, 9);
    for(auto& number : numbers)
    {
        number = small_num_rng.next();
    }

    // find the frequency of each number
    auto num_frequency = mtl::frequency(numbers.begin(), numbers.end());

    // display the frequency of each number in a visual way to the console
    display_sorted_frequency(num_frequency);
}



int main()
{
    // the first example
    example_1();

    // print a divider between examples
    mtl::console::println("\n\n================================================\n\n");

    // the second example
    example_2();   

    // print a divider between examples
    mtl::console::println("\n\n========================================================\n\n");

    // the third example
    example_3();
}