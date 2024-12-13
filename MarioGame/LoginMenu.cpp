#include "LoginMenu.h"

void LoginMenu::Begin(sf::RenderWindow& window)
{
    // Load font
    if (!font.loadFromFile("./resources/font/IntroRustG-Base2Line.otf"))
        return;
    // Load background
    if (!backgroundTexture.loadFromFile("./resources/background/MenuUi.png"))
        return;
    // Load password icon
    if (!passwordTexture.loadFromFile("./resources/textures/Password/password.png"))
        return;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getLocalBounds().width,
        window.getSize().y / backgroundSprite.getLocalBounds().height
    );
    // Username Text
    usernameText.setFont(font);
    usernameText.setString("Username:");
    usernameText.setCharacterSize(30);
    usernameText.setFillColor(sf::Color::White);

    // Password Text
    passwordText.setFont(font);
    passwordText.setString("Password:");
    passwordText.setCharacterSize(30);
    passwordText.setFillColor(sf::Color::White);
    usernameInput.setFont(font);
    usernameInput.setString(" ");
    usernameInput.setCharacterSize(30);
    usernameInput.setFillColor(sf::Color::Black);
    passwordInput.setFont(font);
    passwordInput.setString(" ");
    passwordInput.setCharacterSize(30);
    passwordInput.setFillColor(sf::Color::Black);

    usernameBox.setSize(sf::Vector2f(300, 40));
    usernameBox.setFillColor(sf::Color::White);
    usernameBox.setOutlineColor(sf::Color::White);
    usernameBox.setOutlineThickness(2);
    passwordBox.setSize(sf::Vector2f(300, 40));
    passwordBox.setFillColor((sf::Color::White));
    passwordBox.setOutlineColor(sf::Color::White);
    passwordBox.setOutlineThickness(2);
    // Initialize input state
    isUsernameSelected = false;
    isPasswordSelected = false;
    sf::Color backgroundColor(148, 148, 255, 255);
    loginButton.setSize(sf::Vector2f(200, 50));
    loginButton.setFillColor(backgroundColor);
    loginButton.setOutlineColor(sf::Color::White);
    loginButton.setOutlineThickness(5.0f);
    loginText.setFont(font);
    loginText.setString("LOGIN");
    loginText.setCharacterSize(40);
    loginText.setFillColor(sf::Color::White);
    passwordSprite.setTexture(passwordTexture);
    passwordSprite.setScale(
        (passwordBox.getSize().x / 5) / passwordSprite.getGlobalBounds().height,
        (passwordBox.getSize().y) / passwordSprite.getGlobalBounds().height
    );

    UpdateTextPositions(window);
}

int LoginMenu::HandleInput(const sf::Event& event, GameState& gameState, sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
    if (event.type == sf::Event::Resized)
    {
        UpdateTextPositions(window);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {

        isUsernameSelected = usernameBox.getGlobalBounds().contains(worldPos);
        isPasswordSelected = passwordBox.getGlobalBounds().contains(worldPos);
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
    {
        if (isUsernameSelected && !username.empty())
        {
            username.pop_back();
            usernameInput.setString(username);
        }
        if (isPasswordSelected && !password.empty())
        {
            password.pop_back();
            std::string displayPassword(password.length(), '*');
            passwordInput.setString(displayPassword);
        }
    }
    if (passwordSprite.getGlobalBounds().contains(worldPos))
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            passwordInput.setString(password);
        }
        else
        {
            std::string displayPassword(password.length(), '*');
            passwordInput.setString(displayPassword);
        }
    }
    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode < 32 || event.text.unicode > 126)
            return 0;
        else
        {
            if (isUsernameSelected && username.length() < 20)  // Limit
            {
                username += static_cast<char>(event.text.unicode);
                //std::cout << username << "\n";
                usernameInput.setString(username);
            }
            else if (isPasswordSelected && password.length() < 20)  // Limit
            {
                password += static_cast<char>(event.text.unicode);
                std::string displayPassword(password.length(), '*');
                passwordInput.setString(displayPassword);
            }
        }

    }
    sf::Color backgroundColor(148, 148, 255, 255);
    //std::vector <std::pair <std::string, std::string>> accounts;

    std::ifstream fIn("./resources/account/accounts.csv");
    if (!fIn.is_open())
    {
        return 0;
    }
    std::string redundant;
    std::getline(fIn, redundant); // Read the header
    bool isValid = false;
    std::transform(username.begin(), username.end(), username.begin(), toupper);
    std::string data_username, data_password;
    std::string line;
    while (std::getline(fIn, line))
    {
        std::stringstream ss(line);
        std::getline(ss, data_username, ';');
        std::getline(ss, data_password);
        if (username == data_username && password == data_password)
        {
            isValid = true;
            break;
        }
    }


    if (loginButton.getGlobalBounds().contains(worldPos))
    {
        loginButton.setFillColor(sf::Color::Blue);
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (isValid == true)
                return 1;
            else
            {
                errorMessage.setFont(font);
                errorMessage.setString("Wrong username or password!");
                errorMessage.setFillColor(sf::Color::Red);
            }
        }
    }
    else
    {
        loginButton.setFillColor(backgroundColor);
    }
    return 0;
}

void LoginMenu::Update(float deltaTime, sf::RenderWindow& window)
{
    UpdateTextPositions(window);
}

void LoginMenu::Draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
    window.draw(usernameBox);
    window.draw(passwordBox);
    window.draw(usernameText);
    window.draw(passwordText);
    window.draw(usernameInput);
    window.draw(passwordInput);
    window.draw(loginButton);
    window.draw(loginText);
    window.draw(passwordSprite);
    window.draw(errorMessage);
}

void LoginMenu::UpdateTextPositions(sf::RenderWindow& window)
{
    sf::View view = window.getView();
    sf::Vector2f viewCenter = view.getCenter();

    float centerX = viewCenter.x;
    float centerY = viewCenter.y + 50;
    // Position username elements
    usernameBox.setPosition(centerX, centerY);
    usernameText.setPosition(centerX - 200, centerY);
    usernameInput.setPosition(centerX, centerY);
    // Position password elements
    passwordBox.setPosition(centerX, centerY + 60);
    passwordText.setPosition(centerX - 200, centerY + 60);
    passwordInput.setPosition(centerX, centerY + 68);
    // Position login button
    loginButton.setPosition(centerX - loginButton.getGlobalBounds().width / 2, centerY + 130);
    loginText.setPosition
    (
        loginButton.getPosition().x + (loginButton.getSize().x - loginText.getGlobalBounds().width) / 2,
        loginButton.getPosition().y + (loginButton.getSize().y - loginText.getGlobalBounds().height) / 2 - 10
    );
    passwordSprite.setPosition(
        passwordBox.getPosition().x + passwordBox.getLocalBounds().width - passwordSprite.getGlobalBounds().width,
        passwordBox.getPosition().y
    );
    errorMessage.setPosition(
        loginButton.getSize().x + 130,
        loginButton.getSize().y + 650
    );
}
