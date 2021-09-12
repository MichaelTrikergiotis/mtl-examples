// writing and reading files using the mtl by Michael Trikergiotis
// 06/12/2020
//
// This is a more detailed explanation of how to write and read files using mtl including all
// the appropriate error handling.
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.


// C++ standard library headers we have to include
#include <string>     // std::string
#include <vector>     // std::vector
#include <cstdlib>    // std::exit
#include <filesystem> // std::filesystem::path, std::filesystem::is_regular_file,
                      // std::filesystem::remove

// mtl headers we have to include
#include "../mtl/console.hpp" // mtl::console::println
#include "../mtl/filesystem.hpp" 
// mtl::filesystem::write_file, mtl::filesystem::read_file,
// mtl::filesystem::write_all_lines, mtl::filesystem::read_all_lines




// How to properly use mtl::filesystem::write_file to write and then append to a file
// and then how to use and mtl::filesystem::read_file to read from a file. 
void write_read_files()
{
    mtl::console::println("-----------");
    mtl::console::println("[EXAMPLE 1]");
    mtl::console::println("-----------");

    const std::string question = "How are things going today? Are you doing well?";
    const std::string answer   = "Yes I am. Thank you for asking.";

    const std::filesystem::path filename ("document.txt");

    // we use try/catch because the all the filesystem functions can throw an exception in 
    // exceptional cases, like in the case that while you are reading or writing a big file to a
    // USB drive and the USB is removed, in that case an exception will be thrown
    try
    {
        // before we start we want to delete the file if it exists
        std::filesystem::remove(filename);


        // ----- WRITE A FILE -----

        // writes one string to a file
        bool written_ok = mtl::filesystem::write_file(filename, question);

        // check the file was written ok, a case where the file couldn't be written is if
        // you didn't have permission to write to the requested file
        if(written_ok)
        {
            mtl::console::println("The file was written correctly.");
        }
        // if you couldn't write to the file print an error message and exit
        else
        {
            mtl::console::println("Error. Couldn't write the file. Exiting.");
            std::exit(1);
        }


        // ----- READ A FILE -----

        // Before reading a file the proper thing to do is to check the file exists. That is
        // because when calling mtl::filesystem::read_file or mtl::filesystem::read_all_lines with
        // a file that doesn't exist in debug build it will assert. Although not recommended, you
        // can disable the assertion from happening by defining the MTL_DISABLE_SOME_ASSERTS
        // before including the mtl/filesystem.hpp header.
        bool file_exists = std::filesystem::is_regular_file(filename);

        if(file_exists)
        {
            mtl::console::println("The file exists.");
        }
        else
        {
            mtl::console::println("Error. The file doesn't exist.");
            std::exit(1);
        }


        // read the file we have previously written and have already checked it exists, one case
        // where the file couldn't be read is if you didn't have permission to read from the
        // requested file
        std::string read_data;
        bool read_ok = mtl::filesystem::read_file(filename, read_data);

        // if the file could be read correctly
        if(read_ok)
        {
            mtl::console::println("The file was read correctly.");

            // check what we read was correct
            if(question == read_data)
            {
                mtl::console::println("The file contents were correct.");
            }
            else
            {
                mtl::console::println("Error. The file contents were read incorrectly!!!");
                std::exit(1);
            }
        }
        // if you couldn't read from the file print an error message and exit
        else
        {
            mtl::console::println("Error. Couldn't read the file. Exiting.");
            std::exit(1);
        }



        // ----- APPEND TO A FILE -----

        // now let's try to append to the already existing file using mtl::filesystem::write_file,
        // you can append to an already existing file by passing true as the last parameter, if
        // the file doesn't exist it will be created, if it exists it will be appended
        bool appended_ok = mtl::filesystem::write_file(filename, answer, true);
        
        // check the file was appended ok, a case where the file couldn't be appended is if
        // you didn't have permission to write to the requested file
        if(appended_ok)
        {
            mtl::console::println("The file was written correctly.");
        }
        // if you couldn't append to the file print an error message and exit
        else
        {
            mtl::console::println("Error. Couldn't write the file. Exiting.");
            std::exit(1);
        }



        // ----- READ FILE AGAIN -----

        // check the file exists like you should every time before reading a file
        bool file_exists_again = std::filesystem::is_regular_file(filename);

        if(file_exists_again)
        {
            mtl::console::println("The file exists.");
        }
        else
        {
            mtl::console::println("Error. The file doesn't exist.");
            std::exit(1);
        }

        // read the file after we checked it exists again
        std::string read_appended_data;
        bool read_appended_ok = mtl::filesystem::read_file(filename, read_appended_data);

        if(read_appended_ok)
        {
            mtl::console::println("The file was read correctly.");

            // the read data should now be a combination of the question and the answer
            const std::string desired_data = question + answer;

            // check what we read was correct
            if(desired_data == read_appended_data)
            {
                mtl::console::println("The file contents were correct.");
            }
            else
            {
                mtl::console::println("Error. The file contents were read incorrectly!!!");
                std::exit(1);
            }
        }
        // if you couldn't read from the file print an error message and exit
        else
        {
            mtl::console::println("Error. Couldn't read the file. Exiting.");
            std::exit(1);
        }

        // not let's delete the file that we created

        // check the file exists
        bool file_exists_after = std::filesystem::is_regular_file(filename);

        // if the file exists
        if(file_exists_after)
        {
            // delete the file
            std::filesystem::remove(filename);
        }
        // if the file doesn't exist print an error and exit
        else
        {
            mtl::console::println("Error. The file doesn't exist.");
            std::exit(1);
        }
    }
    // catch any exceptions
    catch(const std::exception& ex)
    {
        // print the exception and exit
        mtl::console::println("The following exception was thrown :");
        mtl::console::println(ex.what());
        std::exit(1);
    }  
}




// How to properly use mtl::filesystem::write_all_lines to write and then append multiple elements
// each to a separate line of a file and then how to use and mtl::filesystem::read_all_lines to
// read all lines from a file.
void write_read_lines()
{
    mtl::console::println("-----------");
    mtl::console::println("[EXAMPLE 2]");
    mtl::console::println("-----------");

    const std::vector<std::string> rgb_colors  = { "Red", "Green", "Blue" };
    const std::vector<std::string> cmyk_colors = { "Cyan", "Magenta", "Yellow", "Black"};
    
    const std::filesystem::path filename ("colors.txt");


    // before we start we want to delete the file if it exists
    std::filesystem::remove(filename);


    // we use try/catch because the all the filesystem functions can throw an exception in 
    // exceptional cases, like in the case that while you are reading or writing a big file to a
    // USB drive and the USB is removed, in that case an exception will be thrown
    try
    {
        // ----- WRITE ALL LINES -----

        // writes multiple elements each on their own line to a file
        bool written_ok = mtl::filesystem::write_all_lines(filename, rgb_colors.begin(), 
                                                                     rgb_colors.end());

        // check the file was written ok, a case where the file couldn't be written is if
        // you didn't have permission to write to the requested file
        if(written_ok)
        {
            mtl::console::println("The file was written correctly.");
        }
        // if you couldn't write to the file print an error message and exit
        else
        {
            mtl::console::println("Error. Couldn't write the file. Exiting.");
            std::exit(1);
        }


        // ----- READ ALL LINES -----

        // Before reading a file the proper thing to do is to check the file exists. That is
        // because when calling mtl::filesystem::read_file or mtl::filesystem::read_all_lines with
        // a file that doesn't exist in debug build it will assert. Although not recommended, you
        // can disable the assertion from happening by defining the MTL_DISABLE_SOME_ASSERTS
        // before including the mtl/filesystem.hpp header.
        bool file_exists = std::filesystem::is_regular_file(filename);

        if(file_exists)
        {
            mtl::console::println("The file exists.");
        }
        else
        {
            mtl::console::println("Error. The file doesn't exist.");
            std::exit(1);
        }


        // read all lines from the file we have previously written and have already checked it
        // exists, one case where the file couldn't be read is if you didn't have permission to
        // read the requested file
        std::vector<std::string> read_colors;
        bool read_ok = mtl::filesystem::read_all_lines(filename, read_colors);

        // if the file could be read correctly
        if(read_ok)
        {
            mtl::console::println("The file was read correctly.");

            // check what we read was correct
            if(read_colors == rgb_colors)
            {
                mtl::console::println("The file contents were correct.");
            }
            else
            {
                mtl::console::println("Error. The file contents were read incorrectly !!!");
                std::exit(1);
            }
        }
        // if you couldn't read from the file print an error message and exit
        else
        {
            mtl::console::println("Error. Couldn't read the file. Exiting.");
            std::exit(1);
        }



        // ----- APPEND ALL LINES -----

        // now let's try to append newlines to the already existing file using 
        // mtl::filesystem::write_all_lines you can append to an already existing file by passing
        // true as the last parameter, if the file doesn't exist it will be created, if it exists
        // it will be appended
        bool appended_ok = mtl::filesystem::write_all_lines(filename, cmyk_colors.begin(), 
                                                            cmyk_colors.end(), true);
        
        // check the file was appended ok, a case where the file couldn't be appended is if
        // you didn't have permission to write to the requested file
        if(appended_ok)
        {
            mtl::console::println("The file was written correctly.");
        }
        // if you couldn't append to the file print an error message and exit
        else
        {
            mtl::console::println("Error. Couldn't write the file. Exiting.");
            std::exit(1);
        }



        // ----- READ FILE AGAIN -----

        // check the file exists like you should every time before reading a file
        bool file_exists_again = std::filesystem::is_regular_file(filename);

        if(file_exists_again)
        {
            mtl::console::println("The file exists.");
        }
        else
        {
            mtl::console::println("Error. The file doesn't exist.");
            std::exit(1);
        }

        // read all lines from the file after we checked it exists again
        std::vector<std::string> read_appended_colors;
        bool read_appended_ok = mtl::filesystem::read_all_lines(filename, read_appended_colors);

        if(read_appended_ok)
        {
            mtl::console::println("The file was read correctly.");

            // the read data should now be a combination of the RGB colors and CMYK colors
            const std::vector<std::string> colors = { "Red", "Green", "Blue", "Cyan", "Magenta", 
                                                      "Yellow", "Black" };

            // check what we read was correct
            if(colors == read_appended_colors)
            {
                mtl::console::println("The file contents were correct.");
            }
            else
            {
                mtl::console::println("Error. The file contents were read incorrectly !!!");
                std::exit(1);
            }
        }
        // if you couldn't read from the file print an error message and exit
        else
        {
            mtl::console::println("Error. Couldn't read the file. Exiting.");
            std::exit(1);
        }
    }
    // catch any exceptions
    catch(const std::exception& ex)
    {
        // print the exception and exit
        mtl::console::println("The following exception was thrown :");
        mtl::console::println(ex.what());
        std::exit(1);
    }  



    // not let's delete the file that we created

    // check the file exists
    bool file_exists_after = std::filesystem::is_regular_file(filename);

    // if the file exists
    if(file_exists_after)
    {
        // delete the file
        std::filesystem::remove(filename);
    }
    // if the file doesn't exist print an error and exit
    else
    {
        mtl::console::println("Error. The file doesn't exist.");
        std::exit(1);
    }
}

int main()
{
    // example for how to write and read files
    write_read_files();

    // print a divider between examples
    mtl::console::println("\n\n=====================================================\n\n");

    // example for how to write a container in different lines of a file and how to read all lines
    // from a file
    write_read_lines();
}