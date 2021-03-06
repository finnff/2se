// @finff jan2020

#include <SFML/Graphics.hpp>
#include "screenitems.hpp"
#include <vector>
#include <iostream>
#include "enum.hpp"
#include "cli.hpp"
#include <stack>
#include <tuple>

template <typename TO, typename FROM> //nodig voor sf::Mouse::getPosition
sf::Vector2<TO> ConvertToVector2(const sf::Vector2<FROM> &other)
{
    return sf::Vector2<TO>(
        static_cast<TO>(other.x),
        static_cast<TO>(other.y));
};

void check_winner(int (&arr)[9])
{
    //all winning combinations
    int wins[8][3] = {{0, 4, 8}, {2, 4, 6}, {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}};
    for (size_t i = 0; i < 8; i++)
    {
        if (((arr[wins[i][0]] == arr[wins[i][1]]) && (arr[wins[i][0]] == arr[wins[i][2]])) && arr[wins[i][0]] != empty)
        {
            std::cout << " Win Win Win Win Win Win Win " << '\n';
        }
    }
}

int getGuiPos(sf::RenderWindow &window)
{
    while(true){
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2f currmpos = ConvertToVector2<float>(sf::Mouse::getPosition(window));
            if((currmpos.x>=0.0   )&&(currmpos.y>=0.0)   &&(currmpos.x<200.0) &&(currmpos.y<200.0)){return 0;}//input region for 0 
            if((currmpos.x>=200.0 )&&(currmpos.y>=0.0)   &&(currmpos.x<400.0) &&(currmpos.y<200.0)){return 1;}//input region for 1 
            if((currmpos.x>=400.0 )&&(currmpos.y>=0.0)   &&(currmpos.x<600.0) &&(currmpos.y<200.0)){return 2;}//input region for 2 
            if((currmpos.x>=0.0   )&&(currmpos.y>=200.0) &&(currmpos.x<200.0) &&(currmpos.y<400.0)){return 3;}//input region for 3 
            if((currmpos.x>=200.0 )&&(currmpos.y>=200.0) &&(currmpos.x<400.0) &&(currmpos.y<400.0)){return 4;}//input region for 4 
            if((currmpos.x>=400.0 )&&(currmpos.y>=200.0) &&(currmpos.x<600.0) &&(currmpos.y<400.0)){return 5;}//input region for 5 
            if((currmpos.x>=0.0   )&&(currmpos.y>=400.0) &&(currmpos.x<200.0) &&(currmpos.y<600.0)){return 6;}//input region for 6 
            if((currmpos.x>=200.0 )&&(currmpos.y>=400.0) &&(currmpos.x<400.0) &&(currmpos.y<600.0)){return 7;}//input region for 7 
            if((currmpos.x>=400.0 )&&(currmpos.y>=400.0) &&(currmpos.x<600.0) &&(currmpos.y<600.0)){return 8;}//input region for 8

            if((currmpos.x>=600.0 )&&(currmpos.y>=0.0) &&(currmpos.x<800.0) &&(currmpos.y<200.0)){return 99;}//input region for undo (99)
            if((currmpos.x>=600.0 )&&(currmpos.y>=400.0) &&(currmpos.x<800.0) &&(currmpos.y<600.0)){
                int temp = -1;
                std::cout<<"Console Input Enabled"<<std::endl;
               std::cin >> temp;
               return temp;
            }//input region for Console input
    };
}
return 999;
};

int main()
{
    std::stack<std::pair<int, states>> moves;
    sf::RenderWindow window{sf::VideoMode{800, 600}, "finffw5"};
    window.setFramerateLimit(60);

    int positions[9] = {empty}; //init all to 0
    print_cli(positions);

    while (window.isOpen())
    {
        while (true) // player one loop.
        {
            int input = -1;
            std::cout << "\033[1;36mPlayerA 0-8 number : \033[0m\n";
//            std::cin >> input;
            input=getGuiPos(window);
            if (input == 99) // if 99, undo last move and give turn to other player.
            {
                std::cout << "removing last move" << std::endl;
                positions[std::get<0>(moves.top())] = empty;
                moves.pop();
                print_cli(positions);
                gui_handler(moves, window);
                break;
            }
            else if (input >= 0 && input < 9) // if valid input place on board
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
            check_winner(positions); // checks if there is a winning combination on the board.
        }
        gui_handler(moves, window); //update the SFML GUI
        print_cli(positions);       //Print the CLI
        sf::sleep(sf::milliseconds(100));

        while (true) // player 2 loop
        {
            int input2 = -1;
            std::cout << "\033[1;31m PlayerB 0-8 number: \033[0m\n";
//            std::cin >> input2;
            input2=getGuiPos(window);
            
            if (input2 == 99) // undo last move
            {
                std::cout << "removing last move" << std::endl;
                positions[std::get<0>(moves.top())] = empty;
                moves.pop();
                print_cli(positions);
                gui_handler(moves, window);
                break;
            }
            else if (input2 >= 0 && input2 < 9) //place on board.
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
        check_winner(positions);    // check if there is a winner
        print_cli(positions);       // print cli
        gui_handler(moves, window); // update GUI handler.
        sf::sleep(sf::milliseconds(100));
    }
}
