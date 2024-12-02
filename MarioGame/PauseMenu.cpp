#include "PauseMenu.h"
#include <iostream>

void PauseMenu::Initialize(sf::RenderWindow& window)
{
    if (!font.loadFromFile("./resources/font/IntroRustG-Base2Line.otf"))
    {
        std::cout << "Failed to load font!" << std::endl;
    }

    // Resume Text
    resumeText.setFont(font);
    resumeText.setString("Resume");
    resumeText.setCharacterSize(30);
    sf::FloatRect resumeBounds = resumeText.getLocalBounds();
    resumeText.setOrigin(resumeBounds.width / 2.0f, resumeBounds.height / 2.0f);

    // Quit Text
    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(30);
    sf::FloatRect quitBounds = quitText.getLocalBounds();
    quitText.setOrigin(quitBounds.width / 2.0f, quitBounds.height / 2.0f);

    // Cập nhật vị trí ban đầu
    UpdateTextPositions(window);
}

void PauseMenu::UpdateTextPositions(sf::RenderWindow& window)
{
    // Lấy view hiện tại của cửa sổ (bao gồm cả phóng to hoặc zoom)
    sf::View view = window.getView();

    // Lấy tâm (center) và kích thước (size) của view
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    // Căn giữa menu dựa trên tâm của view
    float centerX = viewCenter.x;
    float centerY = viewCenter.y;

    // Cập nhật vị trí các text dựa trên view
    resumeText.setPosition(centerX, centerY - 30); // Resume nằm phía trên
    quitText.setPosition(centerX, centerY + 20);   // Quit nằm phía dưới
}


void PauseMenu::HandleInput(const sf::Event& event, GameState& gameState, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::R)
            gameState = GameState::Playing; // Quay lại chơi
        else if (event.key.code == sf::Keyboard::Q)
            gameState = GameState::Menu; // Thoát về menu chính
    }

    // Xử lý chuột
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            // Chuyển đổi tọa độ chuột sang không gian cửa sổ
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (resumeText.getGlobalBounds().contains(mousePos))
                gameState = GameState::Playing; // Quay lại chơi
            else if (quitText.getGlobalBounds().contains(mousePos))
                gameState = GameState::Menu; // Thoát về menu chính
        }
    }

    // Kiểm tra nếu cửa sổ thay đổi kích thước
    if (event.type == sf::Event::Resized)
    {
        // Cập nhật lại vị trí các thành phần
        UpdateTextPositions(window);
    }
}

void PauseMenu::Update(float deltaTime, sf::RenderWindow& window)
{
    // Kiểm tra nếu cửa sổ thay đổi kích thước thì cập nhật lại vị trí của menu
    UpdateTextPositions(window);
}

void PauseMenu::Render(sf::RenderWindow& window)
{
    // Vẽ Pause Menu
    window.draw(resumeText);
    window.draw(quitText);
}
