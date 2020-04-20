#pragma once

#include "enum.hpp"
#include <iostream>


//returns the Symbols seen in the CLI
char return_char(int (&arr)[9], int index)
{
    if (arr[index] == empty)
    {
        return ' ';
    };
    if (arr[index] == noughts)
    {
        return 'O';
    };
    if (arr[index] == crosses)
    {
        return 'X';
    }
    else
    {
        return '?';
    };
};


// prints borders and where symbols go
void print_cli(int (&arr)[9])
{
    std::cout << "┌ ─ ┬ ─ ┬ ─ ┐" << '\n';
    std::cout << "│ " << return_char(arr, 0) << " │ " << return_char(arr, 1) << " │ " << return_char(arr, 2) << " │" << '\n';
    std::cout << "├ ─ ┼ ─ ┼ ─ ┤" << '\n';
    std::cout << "│ " << return_char(arr, 3) << " │ " << return_char(arr, 4) << " │ " << return_char(arr, 5) << " │" << '\n';
    std::cout << "├ ─ ┼ ─ ┼ ─ ┤" << '\n';
    std::cout << "│ " << return_char(arr, 6) << " │ " << return_char(arr, 7) << " │ " << return_char(arr, 8) << " │" << '\n';
    std::cout << "└ ─ ┴ ─ ┴ ─ ┘" << '\n';
}

