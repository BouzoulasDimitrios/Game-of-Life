#include <SFML/Graphics.hpp>
#include <iostream>
#include<unistd.h>

int grid_dim = 90;
int cell_pos = 10;
bool grid[90][90] = {};

class UI{


    public:
        
        sf::RectangleShape cellShape = sf::RectangleShape(sf::Vector2f(50, 50));
        sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(900, 950), "Game of life!", sf::Style::Close);
                
        sf::Vector2f buttonSize = sf::Vector2f(250.f, 50.f);
        sf::Font font;

        sf::Text buttonText1 = sf::Text("Start", font);
        sf::Text buttonText2 = sf::Text("Randomize", font);
        sf::Text buttonText3 = sf::Text("Pause", font);
        sf::Text buttonText4 = sf::Text("Clear", font);

        sf::RectangleShape button1 = sf::RectangleShape(buttonSize);
        
        sf::RectangleShape button2 = sf::RectangleShape(buttonSize);
        sf::RectangleShape button3 = sf::RectangleShape(buttonSize);
        sf::RectangleShape button4 = sf::RectangleShape(buttonSize);

        sf::FloatRect textRect1 = sf::FloatRect(buttonText1.getLocalBounds());
        sf::FloatRect textRect2 = sf::FloatRect(buttonText1.getLocalBounds());
        sf::FloatRect textRect3 = sf::FloatRect(buttonText1.getLocalBounds());
        sf::FloatRect textRect4 = sf::FloatRect(buttonText1.getLocalBounds());

        sf::Event event = sf::Event();

    UI(){

        sf::Color button_color(38, 30, 29);

        font.loadFromFile("arial.ttf");

        cellShape.setFillColor(sf::Color::Black);
        cellShape.setOutlineThickness(1);
        cellShape.setOutlineColor(sf::Color::Green);

        sf::Vector2f buttonPos1(0.f, 900.f);
        sf::Vector2f buttonPos2(225.f, 900.f);
        sf::Vector2f buttonPos3(450.f, 900.f);
        sf::Vector2f buttonPos4(675.f, 900.f);

        button1.setPosition(buttonPos1);
        button2.setPosition(buttonPos2);
        button3.setPosition(buttonPos3);
        button4.setPosition(buttonPos4);

        button1.setFillColor(button_color);
        button2.setFillColor(button_color);
        button3.setFillColor(button_color);
        button4.setFillColor(button_color);

        buttonText1.setCharacterSize(20);
        buttonText2.setCharacterSize(20);
        buttonText3.setCharacterSize(20);
        buttonText4.setCharacterSize(20);

        buttonText1.setCharacterSize(20);
        buttonText2.setCharacterSize(20);
        buttonText4.setCharacterSize(20);
        buttonText4.setCharacterSize(20);

        buttonText1.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);
        buttonText2.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top  + textRect2.height/2.0f);
        buttonText3.setOrigin(textRect3.left + textRect3.width/2.0f, textRect3.top  + textRect3.height/2.0f);
        buttonText4.setOrigin(textRect4.left + textRect4.width/2.0f, textRect4.top  + textRect4.height/2.0f);

        buttonText1.setPosition(button1.getPosition() - sf::Vector2f(30,-15) + button1.getSize()/2.0f);
        buttonText2.setPosition(button2.getPosition() - sf::Vector2f(60,-15) + button2.getSize()/2.0f);
        buttonText3.setPosition(button3.getPosition() - sf::Vector2f(40,-15) + button3.getSize()/2.0f);
        buttonText4.setPosition(button4.getPosition() - sf::Vector2f(40,-15) + button4.getSize()/2.0f);
        
        button1.setOutlineThickness(1.f);
        button2.setOutlineThickness(1.f);
        button3.setOutlineThickness(1.f);
        button4.setOutlineThickness(1.f);
        
        button1.setOutlineColor(sf::Color::Black);
        button2.setOutlineColor(sf::Color::Black);
        button3.setOutlineColor(sf::Color::Black);
        button4.setOutlineColor(sf::Color::Black);
    
    }

    void draw(){

        window.draw(button1);
        window.draw(buttonText1);
        window.draw(button2);
        window.draw(buttonText2);
        window.draw(button3);
        window.draw(buttonText3);
        window.draw(button4);
        window.draw(buttonText4);

    }

};


bool count_alive_neighbours(int x, int y){

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


void edit_board(UI& ui){ 
    
    sf::RectangleShape  cellShape(sf::Vector2f(9, 9));
    
    // Determine which cell was clicked
    int mouse_x = ui.event.mouseButton.x , mouse_y = ui.event.mouseButton.y;

    if(( 0 <= mouse_x && mouse_x <= 1000) && (0 <= mouse_y && mouse_y <= 900)){ //;

        int x = ui.event.mouseButton.x / cell_pos;
        int y = ui.event.mouseButton.y / cell_pos;

        // Toggle the color of the cell;
        grid[x][y] = !grid[x][y];

        // Redraw the grid with updated colors
        for (int i = 0; i < grid_dim; i++) {
            for (int j = 0; j < grid_dim; j++) {
                cellShape.setPosition(i * cell_pos, j * cell_pos);
                
                if(x == i && y == j){

                    if (grid[i][j]) {
                        cellShape.setFillColor(sf::Color::Green);
                    } else {
                        cellShape.setFillColor(sf::Color::Black);
                    }
                    ui.window.draw(cellShape);

                }
                
            }
        }
    }
}


void randomize_board(UI & ui){

        // Redraw the grid with updated colors
        for (int i = 0; i < grid_dim; i++) {
            for (int j = 0; j < grid_dim; j++) {

                ui.cellShape.setPosition(i * cell_pos, j * cell_pos);
                
                if(rand()%2)
                    grid[i][j] = !grid[i][j];

                if (grid[i][j]) {
                    ui.cellShape.setFillColor(sf::Color::Green);
                } else {
                    ui.cellShape.setFillColor(sf::Color::Black);
                }
                ui.window.draw(ui.cellShape);

            }
        }
}


void update_board(UI & ui){

    bool temp_grid[grid_dim][grid_dim] = {};

    // Redraw the grid with updated colors
    for (int i = 0; i < grid_dim; i++){
        for(int j = 0; j < grid_dim; j++){
            count_alive_neighbours(i,j) ? temp_grid[i][j] = 1 : temp_grid[i][j] = 0; 
            ui.window.draw(ui.cellShape);
        }
    }

    for (int i = 0; i < grid_dim; i++){
        for(int j = 0; j < grid_dim; j++){
            ui.cellShape.setPosition(i * cell_pos, j * cell_pos);
            temp_grid[i][j] ? ui.cellShape.setFillColor(sf::Color::Green) : ui.cellShape.setFillColor(sf::Color::Black);
            ui.window.draw(ui.cellShape);
            grid[i][j] = temp_grid[i][j];
        }
    }

}


void clear_board(UI & ui){

    for (int x = 0; x < grid_dim; x++) {
        for (int y = 0; y < grid_dim; y++) {
            ui.cellShape.setPosition(x * cell_pos, y * cell_pos);
            ui.cellShape.setFillColor(sf::Color::Black);
            grid[x][y] = false;
            ui.window.draw(ui.cellShape);
        }
    }

}


int main()
{
    bool waiting_to_start = true;
    bool is_paused = false;

    UI ui;

    // Draw the grid
    for (int x = 0; x < grid_dim; x++) {
        for (int y = 0; y < grid_dim; y++) {
            ui.cellShape.setPosition(x * cell_pos, y * cell_pos);
            if (grid[x][y]) {
                ui.cellShape.setFillColor(sf::Color::Green);
            }
            ui.window.draw(ui.cellShape);
        }
    }

    ui.draw();
    ui.window.display();

    while (ui.window.isOpen()){

        while (ui.window.pollEvent(ui.event)){

            if (ui.event.type == sf::Event::Closed)
                ui.window.close();
        
            if (ui.event.type == sf::Event::MouseButtonPressed) {
                if (ui.event.mouseButton.button == sf::Mouse::Left) {

                    if(waiting_to_start)
                        edit_board(ui);

                    if(ui.button1.getGlobalBounds().contains(ui.event.mouseButton.x, ui.event.mouseButton.y))
                        waiting_to_start = false, is_paused = false;
            
                    if(ui.button2.getGlobalBounds().contains(ui.event.mouseButton.x, ui.event.mouseButton.y) && (waiting_to_start))
                        randomize_board(ui);
                    
                    if(ui.button3.getGlobalBounds().contains(ui.event.mouseButton.x, ui.event.mouseButton.y))
                        waiting_to_start = true, is_paused = true;

                    if(ui.button4.getGlobalBounds().contains(ui.event.mouseButton.x, ui.event.mouseButton.y) && waiting_to_start)
                        clear_board(ui);

                    ui.draw();
                    ui.window.display();

                }   
            }
        }


        if(!waiting_to_start && !is_paused){
            update_board(ui);
            unsigned int microsecond = 200000;
            usleep(1 * microsecond);
            ui.draw();
            ui.window.display();

        }

    }

    return 0;
}