// how to sort dates with the help of mtl by Michael Tikergiotis
// 21/07/2021
// 
// An example showcasing how someone could utilize mtl to sort dates.
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.


#include <string>                 // std::string
#include <vector>                 // std::vector
#include <stdexcept>              // std::invalid_argument
#include <cstdlib>                // std::exit
#include <algorithm>              // std::sort
#include "../mtl/string.hpp"         // mtl::string::replace, mtl::string::split
#include "../mtl/conversion.hpp"     // mtl::to_num
#include "../mtl/console.hpp"        // mtl::console::println



// Compares two dates that should be formatted with the European date format of day/month/year.
// Returns true if the right-hand side date is before the left-hand side date, or vice versa.
// Throws std::invalid_argument if any of the two dates are incorrectly formatted.
bool date_comparator(const std::string& rhs_date, const std::string& lhs_date)
{
    std::string rhs = rhs_date;
    std::string lhs = lhs_date;

    // converts all hyphens to forward slashes, changes the format of the dates
    // from 01-02-2020 to 01/02/2020, this doesn't require any heap allocations
    mtl::string::replace(rhs, '-', '/');  
    mtl::string::replace(lhs, '-', '/');

    // converts all dots to forward slashes, changes the format of the dates
    // from 01.02.2020 to 01/02/2020, this doesn't require any heap allocations
    mtl::string::replace(rhs, '.', '/');
    mtl::string::replace(lhs, '.', '/');
    
    // split a date passed as an std::string to an std::vector<std:::string> with three parts,
    // the day, the month, and the year
    auto parts_rhs = mtl::string::split(rhs, "/");
    auto parts_lhs = mtl::string::split(lhs, "/");

    // check that each container has three elements, if it isn't, then it means that one or both
    // of the dates aren't correctly formatted, so we have to throw an exception
    if ((parts_rhs.size() != 3) || (parts_lhs.size() != 3))
    {
        throw std::invalid_argument("Error. One or more dates are incorrectly formatted.");
    }

    // convert each part to an integer using mtl::to_num, you have to provide the type of number
    // you want mtl::to_num to convert to instead of auto, it throws std::invalid_argument if
    // the conversion is not possible, please note there are two other versions of mtl::to_num 
    // named mtl::to_num_noex that serve the same purpose but don't throw an exception on
    // error, those are not covered in this example
    int day_rhs = mtl::to_num(parts_rhs[0]);
    int month_rhs = mtl::to_num(parts_rhs[1]);
    int year_rhs = mtl::to_num(parts_rhs[2]);
    
    int day_lhs = mtl::to_num(parts_lhs[0]);
    int month_lhs = mtl::to_num(parts_lhs[1]);
    int year_lhs = mtl::to_num(parts_lhs[2]);
  

    // compare years
    if (year_rhs < year_lhs)
    {
        return true;
    }
    else if (year_rhs > year_lhs)
    {
        return false;
    }
    // if the years are equal, then compare by months
    else
    {
        // compare months
        if (month_rhs < month_lhs)
        {
            return true;
        }
        else if (month_rhs > month_lhs)
        {
            return false;
        }
        // if the months are equal, then compare by days
        else
        {
            // compare days
            if (day_rhs < day_lhs)
            {
                return true;
            }
            // if the number representing the right-hand side day is larger than the number
            // representing the left-hand side day or if they are equal, we have to return false
            else
            {
                return false;
            }
        }
    }
}



int main()
{
    // just a container of strings that represent dates in an unsorted order, all dates are in
    // European format, some dates are separated with forward slashes, some are separated 
    // with hyphens and some others by dots to make sorting more difficult
    std::vector<std::string> dates
    {
        "04.05.2020",
        "02-05-2020",
        "05/11/2020",
        "03/05/2020",
        "12/04/2021",
        "04-05-2020",
        "09/03/2021",
        "04/07/2018",
        "02/04/2019",
        "01/03/2020",
        "09.04.2019",
        "22.04.2019",
    };


    // try to sort, due to erroneous format of the dates this can throw, so we enclose it in
    // a try/catch block
    try
    {
        // sort the dates using a lambda function
        std::sort(dates.begin(), dates.end(), [](auto& rhs, auto& lhs)
        {
            // compare two dates using a function
            return date_comparator(rhs, lhs);
        });
    }
    // catch exceptions that prevent the correct sorting due to incorrectly formatted dates
    catch(const std::invalid_argument& ex)
    {
        // print the exception message to the console followed by a newline at the end
        mtl::console::println(ex.what());
        // print two items to the console, each in a new line
        mtl::console::println("Sorting failed.", "Exiting.");
        // exit the application with a non-zero exit code
        std::exit(1);
    }


    mtl::console::println("--------------");
    mtl::console::println("SORTED DATES :");
    mtl::console::println("--------------");
    // print all dates to the console, each in a new line
    for (const auto& date : dates)
    {
        mtl::console::println(date);
    }
}
