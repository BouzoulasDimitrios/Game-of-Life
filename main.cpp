#include <SFML/Graphics.hpp>
#include <iostream>
#include<unistd.h>

using namespace std;

int grid_dim = 90;//20;
int cell_pos = 10;//25;
//bool grid[20][20] = {};
bool grid[90][90] = {};

void edit_board(sf::RenderWindow & window, sf::Event & event){ //,  sf::RectangleShape & cellShape ){
sf::RectangleShape  cellShape(sf::Vector2f(9, 9));
    // Determine which cell was clicked
    int mouse_x = event.mouseButton.x , mouse_y = event.mouseButton.y;

    if(( 0 <= mouse_x && mouse_x <= 1000) && (0 <= mouse_y && mouse_y <= 900)){ //;

        int x = event.mouseButton.x / cell_pos;
        int y = event.mouseButton.y / cell_pos;

        // Toggle the color of the cell;
        grid[x][y] = !grid[x][y];

        // Redraw the grid with updated colors
        for (int i = 0; i < grid_dim; i++) {
            for (int j = 0; j < grid_dim; j++) {
                cellShape.setPosition(i * cell_pos, j * cell_pos);
                
                if(x == i && y == j){
                    cout<<"\n\n HERE \n\n";

                    if (grid[i][j]) {
                        cellShape.setFillColor(sf::Color::Green);
                    } else {
                        cellShape.setFillColor(sf::Color::Black);
                    }
                    window.draw(cellShape);

                }
                
            }
        }
    }
}


void randomize_board(sf::RenderWindow & window, sf::RectangleShape & cellShape){

        // Redraw the grid with updated colors
        for (int i = 0; i < grid_dim; i++) {
            for (int j = 0; j < grid_dim; j++) {

                cellShape.setPosition(i * cell_pos, j * cell_pos);
                
                if(rand()%2)
                    grid[i][j] = !grid[i][j];

                if (grid[i][j]) {
                    cellShape.setFillColor(sf::Color::Green);
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
            if((i == x && j == y) || ((i < 0 || j < 0) || (i > grid_dim || j > grid_dim)) )
                continue;
            else if(grid[i][j] == 1)    
                count++;
        }
    }

    return grid[x][y] ? (count == 2 || count == 3) : count == 3;
}


void update_board(sf::RenderWindow & window, sf::RectangleShape & cellShape){

        bool temp_grid[grid_dim][grid_dim] = {};

        // Redraw the grid with updated colors
        for (int i = 0; i < grid_dim; i++){
            for(int j = 0; j < grid_dim; j++){

                cout_alive_neighbours(i,j) ? temp_grid[i][j] = 1 : temp_grid[i][j] = 0; 
                window.draw(cellShape);

            }
        }

        for (int i = 0; i < grid_dim; i++){
            for(int j = 0; j < grid_dim; j++){
                
                cellShape.setPosition(i * cell_pos, j * cell_pos);
                temp_grid[i][j] ? cellShape.setFillColor(sf::Color::Green) : cellShape.setFillColor(sf::Color::Black);
                window.draw(cellShape);
                grid[i][j] = temp_grid[i][j];

            }
        }


}

int main()
{
    bool waiting_to_start = true;
    bool is_paused = false;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(900, 950), "Game of life!", sf::Style::Close);

    // Create a rectangle shape to represent a grid cell
    sf::RectangleShape cellShape(sf::Vector2f(50, 50));

    cellShape.setFillColor(sf::Color::Black);
    cellShape.setOutlineThickness(1);
    cellShape.setOutlineColor(sf::Color::Green);

    sf::Vector2f buttonSize(250.f, 50.f);
    sf::Vector2f buttonPos1(0.f, 900.f);
    sf::Vector2f buttonPos2(225.f, 900.f);
    sf::Vector2f buttonPos3(450.f, 900.f);
    sf::Vector2f buttonPos4(675.f, 900.f);

    sf::RectangleShape button1(buttonSize);
    sf::RectangleShape button2(buttonSize);
    sf::RectangleShape button3(buttonSize);
    sf::RectangleShape button4(buttonSize);

    button1.setPosition(buttonPos1);
    button2.setPosition(buttonPos2);
    button3.setPosition(buttonPos3);
    button4.setPosition(buttonPos4);

    sf::Color button_color(38, 30, 29);

    button1.setFillColor(button_color);
    button2.setFillColor(button_color);
    button3.setFillColor(button_color);
    button4.setFillColor(button_color);
    
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text buttonText1("Start", font);
    buttonText1.setCharacterSize(20);
    buttonText1.setPosition(buttonPos1.x + 120.f, buttonPos1.y + 10.f);

    sf::Text buttonText2("Randomize", font);
    buttonText2.setCharacterSize(20);
    buttonText2.setPosition(buttonPos2.x + 10.f, buttonPos2.y + 10.f);

    sf::Text buttonText3("Pause", font);
    buttonText3.setCharacterSize(20);
    buttonText3.setPosition(buttonPos3.x + 10.f, buttonPos3.y + 10.f);

    sf::Text buttonText4("Clear", font);
    buttonText4.setCharacterSize(20);
    buttonText4.setPosition(buttonPos4.x + 10.f, buttonPos4.y + 10.f);

    buttonText1.setCharacterSize(20);
    buttonText2.setCharacterSize(20);
    buttonText4.setCharacterSize(20);
    buttonText4.setCharacterSize(20);

    sf::FloatRect textRect1 = buttonText1.getLocalBounds();
    buttonText1.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);
    buttonText1.setPosition(button1.getPosition() - sf::Vector2f(10,0) + button1.getSize()/2.0f);
    
    sf::FloatRect textRect2 = buttonText2.getLocalBounds();
    buttonText2.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top  + textRect2.height/2.0f);
    buttonText2.setPosition(button2.getPosition() - sf::Vector2f(10,0) + button2.getSize()/2.0f);

    sf::FloatRect textRect3 = buttonText3.getLocalBounds();
    buttonText3.setOrigin(textRect3.left + textRect3.width/2.0f, textRect3.top  + textRect3.height/2.0f);
    buttonText3.setPosition(button3.getPosition() - sf::Vector2f(10,0) + button3.getSize()/2.0f);
    
    sf::FloatRect textRect4 = buttonText4.getLocalBounds();
    buttonText4.setOrigin(textRect4.left + textRect4.width/2.0f, textRect4.top  + textRect4.height/2.0f);
    buttonText4.setPosition(button4.getPosition() - sf::Vector2f(10,0) + button4.getSize()/2.0f);

    button1.setOutlineThickness(1.f);
    button2.setOutlineThickness(1.f);
    button3.setOutlineThickness(1.f);
    button4.setOutlineThickness(1.f);
    
    button1.setOutlineColor(sf::Color::Black);
    button2.setOutlineColor(sf::Color::Black);
    button3.setOutlineColor(sf::Color::Black);
    button4.setOutlineColor(sf::Color::Black);

    // Draw the grid
    for (int x = 0; x < grid_dim; x++) {
        for (int y = 0; y < grid_dim; y++) {
            cellShape.setPosition(x * cell_pos, y * cell_pos);
            if (grid[x][y]) {
                cellShape.setFillColor(sf::Color::Green);
            }
            window.draw(cellShape);
        }
    }

    window.draw(button1);
    window.draw(buttonText1);
    window.draw(button2);
    window.draw(buttonText2);
    window.draw(button3);
    window.draw(buttonText3);
    window.draw(button4);
    window.draw(buttonText4);


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
                        edit_board(window, event);//, cellShape);
                    
                    if(button1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                        waiting_to_start = false, is_paused = false;

                    if(button2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && (waiting_to_start))
                        randomize_board(window, cellShape);

                    if(button3.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                        waiting_to_start = true, is_paused = true;

                    // if(button4.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && waiting_to_start){
                    //     for (int x = 0; x < grid_dim; x++) {
                    //         for (int y = 0; y < grid_dim; y++) {
                    //             cellShape.setPosition(x * cell_pos, y * cell_pos);
                    //             if (grid[x][y]) {
                    //                 cellShape.setFillColor(sf::Color::Green);
                    //             }
                    //             window.draw(cellShape);
                    //         }
                    //     }
                    // }


                    // Display the updated grid
                    // if(!is_paused){
                        cout<<"adfsjl"<<endl;
                        window.draw(button1);
                        window.draw(buttonText1);
                        window.draw(button2);
                        window.draw(buttonText2);
                        window.draw(button3);
                        window.draw(buttonText3);
                        window.draw(button4);
                        window.draw(buttonText4);
                        window.display();
                    // }
                }   


            }

        }

        if(!waiting_to_start && !is_paused){
            cout<<waiting_to_start<<endl;
            update_board(window, cellShape);
            unsigned int microsecond = 500000;
            usleep(1 * microsecond);//sleeps for 0.5s
            cout<<"updating\n";

            window.draw(button1);
            window.draw(buttonText1);
            window.draw(button2);
            window.draw(buttonText2);
            window.draw(button3);
            window.draw(buttonText3);
            window.draw(button4);
            window.draw(buttonText4);
            window.display();

        }

    }

    return 0;
}