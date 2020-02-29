#include <SFML/Graphics.hpp>
#include "screenitems.hpp"
#include <vector>
#include <iostream>
#include "enum.hpp"
#include "cli.hpp"
#include <stack>
#include <tuple>

void check_winner(int (&arr)[9])
{
    //winning combinations
    int wins[8][3] = {{0, 4, 8}, {2, 4, 6}, {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}};
    for (size_t i = 0; i < 8; i++)
    {
        if (((arr[wins[i][0]] == arr[wins[i][1]]) && (arr[wins[i][0]] == arr[wins[i][2]])) && arr[wins[i][0]] != empty)
        {
            std::cout << " win win win win win win win " << '\n';
        }
    }
}

// sf::Vector2f index2coord(int index)
// {
//     if (index < 5)
//     {
//         return sf::Vector2f((index - 6) * 200, 400);
//     }
//     else if (index < 2)
//     {
//         return sf::Vector2f((index - 3) * 200, 200);
//     }
//     else
//     {
//         return sf::Vector2f((index)*200, 0);
//     }
// }

int main()
{

    std::stack<std::pair<int, states>> moves;
    sf::RenderWindow window{sf::VideoMode{800, 600}, "finffw5"};
    window.setFramerateLimit(60);

    int positions[9] = {empty}; //init all to 0
    print_cli(positions);

    while (window.isOpen())
    {
        while (true)
        {
            int input = -1;
            std::cout << "\033[1;36mPlayerA 0-8 number : \033[0m\n";
            std::cin >> input;
            if (input == 99)
            {
                std::cout << "removing last move" << std::endl;
                positions[std::get<0>(moves.top())] = empty;
                moves.pop();
                print_cli(positions);
                gui_handler(moves, window);
                break;
            }
            else if (input >= 0 && input < 9)
            {
                if (positions[input] == empty)
                {
                    moves.push(std::make_pair(input, crosses));
                    positions[input] = crosses;
                    break;
                }
                else
                {
                    std::cout << "cant place here" << std::endl;
                }
            }
            else
            {
                std::cout << "\033[1;36mInvalid Input \033[0m\n";
            }
        }
        gui_handler(moves, window);
        print_cli(positions);
        check_winner(positions);

        while (true)
        {
            int input2 = -1;
            std::cout << "\033[1;31m PlayerB 0-8 number: \033[0m\n";
            std::cin >> input2;
            if (input2 == 99)
            {
                std::cout << "removing last move" << std::endl;
                positions[std::get<0>(moves.top())] = empty;
                moves.pop();
                print_cli(positions);
                gui_handler(moves, window);
                break;
            }
            else if (input2 >= 0 && input2 < 9)
            {
                if (positions[input2] == empty)
                {
                    moves.push(std::make_pair(input2, noughts));
                    positions[input2] = noughts;
                    break;
                }
                else
                {
                    std::cout << "cant place here" << std::endl;
                }
            }
            else
            {
                std::cout << "\033[1;31m Invalid Input \033[0m\n";
            }
        }
        gui_handler(moves, window);
        print_cli(positions);
        check_winner(positions);
    }
}
