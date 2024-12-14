#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <fstream>
#include <sstream>

class LoginMenu
{
private:
    //Font
    sf::Font font;

    // Background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    //Login Buttons
    sf::Text usernameText;
    sf::Text passwordText;
    sf::Text loginText;
    sf::Text registerText;


    // Input fields
    sf::Text usernameInput;
    sf::Text passwordInput;

    sf::RectangleShape usernameBox;
    sf::RectangleShape passwordBox;
    sf::RectangleShape loginButton;
    sf::RectangleShape registerButton;

    // Hide password
    sf::Texture passwordTexture; 
    sf::Sprite passwordSprite;

    sf::Text errorMessage;

    std::string username = "";
    std::string password = "";

    bool isUsernameSelected;
    bool isPasswordSelected;

public:
    // Functions
    void Begin(sf::RenderWindow& window);
    int HandleInput(const sf::Event& event, GameState& gameState, sf::RenderWindow& window);
    void Update(float deltaTime, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    void UpdateTextPositions(sf::RenderWindow& window);
};

