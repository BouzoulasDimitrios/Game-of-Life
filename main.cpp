#include <SFML/Graphics.hpp>
#include <iostream>
#include<unistd.h>

using namespace std;

bool grid[10][10] = {};

void edit_board(sf::RenderWindow & window, sf::Event & event,  sf::RectangleShape & cellShape ){

    // Determine which cell was clicked
    int mouse_x = event.mouseButton.x , mouse_y = event.mouseButton.y;

    if(( 0 <= mouse_x && mouse_x <= 500) && (0 <= mouse_y && mouse_y <= 500)){ //;

        int x = event.mouseButton.x / 50;
        int y = event.mouseButton.y / 50;

        // Toggle the color of the cell;
        grid[x][y] = !grid[x][y];

        // Redraw the grid with updated colors
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cellShape.setPosition(i * 50, j * 50);
                if (grid[i][j]) {
                    cellShape.setFillColor(sf::Color::White);
                } else {
                    cellShape.setFillColor(sf::Color::Black);
                }
                window.draw(cellShape);
            }
        }
    }
}


void randomize_board(sf::RenderWindow & window, sf::RectangleShape & cellShape){

        // Redraw the grid with updated colors
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {

                cellShape.setPosition(i * 50, j * 50);
                
                if(rand()%2)
                    grid[i][j] = !grid[i][j];

                if (grid[i][j]) {
                    cellShape.setFillColor(sf::Color::White);
                } else {
                    cellShape.setFillColor(sf::Color::Black);
                }
                window.draw(cellShape);

            }
        }
}


bool cout_alive_neighbours(int x, int y){

    int count = 0;

    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if((i == x && j == y) || ((i < 0 || j < 0) || (i > 10 || j > 10)) )
                continue;
            else if(grid[i][j] == 1)    
                count++;
        }
    }

    return grid[x][y] ? (count == 2 || count == 3) : count == 3;

}


bool update_board(sf::RenderWindow & window, sf::RectangleShape & cellShape){

        bool temp_grid[10][10] = {};

        // Redraw the grid with updated colors
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){

                if(cout_alive_neighbours(i, j)){
                    // cellShape.setFillColor(sf::Color::White);
                    temp_grid[i][j] = 1;
                }else{
                    temp_grid[i][j] = 0;
                    // cellShape.setFillColor(sf::Color::Black);
                }

                window.draw(cellShape);

            }
        }

        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                
                cellShape.setPosition(i * 50, j * 50);

                if(temp_grid[i][j]){
                    // cout<<"grid = "<<temp_grid[i][j]<<endl;
                    cellShape.setFillColor(sf::Color::White);
                    // temp_grid[i][j] = 1;
                }else{
                    cellShape.setFillColor(sf::Color::Black);
                }
                window.draw(cellShape);

                grid[i][j] = temp_grid[i][j];

            }
        }

        return false;
}

int main()
{
    bool waiting_to_start = true;
    // Create the window
    sf::RenderWindow window(sf::VideoMode(500, 600), "Game of life!");

    // Create a rectangle shape to represent a grid cell
    sf::RectangleShape cellShape(sf::Vector2f(50, 50));
    cellShape.setFillColor(sf::Color::Black);
    cellShape.setOutlineThickness(1);
    cellShape.setOutlineColor(sf::Color::White);

    sf::Vector2f buttonSize(250.f, 100.f);
    sf::Vector2f buttonPos1(0.f, 500.f);
    sf::Vector2f buttonPos2(250.f, 500.f);

    sf::RectangleShape button1(buttonSize);
    button1.setPosition(buttonPos1);
    sf::RectangleShape button2(buttonSize);
    button2.setPosition(buttonPos2);

    button1.setFillColor(sf::Color::Green);
    button2.setFillColor(sf::Color::Red);


    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text buttonText1("Start", font);
    buttonText1.setCharacterSize(20);
    buttonText1.setPosition(buttonPos1.x + 10.f, buttonPos1.y + 10.f);

    sf::Text buttonText2("Randomize", font);
    buttonText2.setCharacterSize(20);
    buttonText2.setPosition(buttonPos2.x + 10.f, buttonPos2.y + 10.f);

    buttonText1.setCharacterSize(20);

    buttonText2.setCharacterSize(20);

    // Draw the grid
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            cellShape.setPosition(x * 50, y * 50);
            if (grid[x][y]) {
                cellShape.setFillColor(sf::Color::White);
            }
            window.draw(cellShape);
        }
    }

    window.draw(button1);
    window.draw(buttonText1);
    window.draw(button2);
    window.draw(buttonText2);

    // Display the window
    window.display();

    // Main loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    if(waiting_to_start)
                        edit_board(window, event, cellShape);

                    if(button2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && waiting_to_start)
                                        randomize_board(window, cellShape);

                    if(button1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                        waiting_to_start = false;

                    // Display the updated grid
                    window.draw(button1);
                    window.draw(buttonText1);
                    window.draw(button2);
                    window.draw(buttonText2);
                    window.display();

                }   
            }
        }

        if(!waiting_to_start){
            
            update_board(window, cellShape);
            unsigned int microsecond = 1000000;
            usleep(1 * microsecond);//sleeps for 3 second
            cout<<"updating\n";
            window.draw(button1);
            window.draw(buttonText1);
            window.draw(button2);
            window.draw(buttonText2);
            window.display();

        }
    }

    return 0;
}
