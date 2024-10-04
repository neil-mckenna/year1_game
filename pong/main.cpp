#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem> // C++17

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::A,   // Player1 UP
    Keyboard::Z,   // Player1 Down
    Keyboard::Up,  // Player2 UP
    Keyboard::Down // Player2 Down
};

sf::Font font;
sf::Text text;

static int leftScore = 0;
static int rightScore = 0;

// game parameters
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;

CircleShape ball;
RectangleShape paddles[2];

// ball movement

Vector2f ballVelocity;
bool isPlayer1Serving = false;

const float initialVelocityX = 100.f;
const float initialVelocityY = 60.f;

// ball collision
const float velocityMultiplier = 1.1f;

void Reset()
{
    // Set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius / 2, ballRadius / 2); //Should be half the ball width and height

    // reset paddle position
    paddles[0].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
    paddles[1].setPosition(Vector2f(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f));

    // reset Ball Position
    ball.setPosition(gameWidth / 2, gameHeight / 2);

    // reset ball speed
    ballVelocity = { (isPlayer1Serving ? initialVelocityX : -initialVelocityX), initialVelocityY };

    // Update text
    text.setString("Score: " + std::to_string(leftScore) + " : " + std::to_string(rightScore));
    // Keep score  text centered
    text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * 0.5f), 0);
    text.setFillColor(sf::Color::White); // Set the text color
}


void Load() {

    // Set size and origin of paddles
    for (auto &p : paddles) {
        p.setSize(paddleSize);
        p.setOrigin(paddleSize / 2.f);
    }

    Reset();

    // Load font-face from res directory
    font.loadFromFile("../res/fonts/Roboto/Roboto-Regular.ttf");

    // Set text elemetn to use font
    text.setFont(font);

    // set the character size to 24 pxiels
    text.setCharacterSize(24);

}

void Update(RenderWindow &window)
{
    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();

    // check and consume events
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
            return;
        }
    }

    // Quit Via ESC key
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        window.close();
    }

    // handle paddle movement
    float direction = 0.0f;
    if (Keyboard::isKeyPressed(controls[0]))
    {

        direction--;
    }

    if (Keyboard::isKeyPressed(controls[1]))
    {
        direction++;
    }

    // left paddle with boundaries
    if (paddles[0].getPosition().y <= 0 + paddleSize.y / 2) {
        //cout << "Hit roof " << endl;
        paddles[0].move(Vector2f(0.f, 0.5f)); // Top boundary clamp
    }
    else if (paddles[0].getPosition().y >= gameHeight - paddleSize.y / 2) {
        //cout << "Hit bottom " << endl;
        paddles[0].move(Vector2f(0.f, -0.5f)); // Bottom clamp
    }
    else {
        paddles[0].move(sf::Vector2f(0.f, direction * paddleSpeed * dt));
    }

    // Move the paddle towards the ball's y position for simple AI
    //cout << "Y Pos" << paddles[1].getPosition().y << endl;

    if (
        paddles[1].getPosition().y < ball.getPosition().y + ballRadius &&
        paddles[1].getPosition().y >= 0 &&
        paddles[1].getPosition().y < gameHeight - paddleSize.y / 2

        )
    {
        paddles[1].move(0.f, paddleSpeed * dt);  // Move down
    }
    else if (
        paddles[1].getPosition().y > ball.getPosition().y + ballRadius
        && paddles[1].getPosition().y >= 0 + paddleSize.y / 2
        )
    {
        paddles[1].move(0.f, -paddleSpeed * dt);  // Move up
    }



    // ball movement
    ball.move(ballVelocity * dt);

    // check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    if (by > gameHeight - ballRadius) { //bottom wall
        // bottom wall
        ballVelocity.x *= velocityMultiplier;
        ballVelocity.y *= -velocityMultiplier;
        ball.move(Vector2(0.f, -10.f));
    }
    else if (by < 0 + ballRadius) { //top wall
        // top wall
        ballVelocity.x *= velocityMultiplier;
        ballVelocity.y *= -velocityMultiplier;
        ball.move(Vector2(0.f, 10.f));
    }
    else if (bx > gameWidth) {
        // right wall
        leftScore++;
        Reset();
    }
    else if (bx < 0) {
        // left wall
        rightScore++;
        Reset();
    }
    // paddle collision
    else if (
        //ball is inline or behind paddle AND
        bx < paddleSize.x + paddleOffsetWall &&
        //ball is below top edge of paddle AND
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        //ball is above bottom edge of paddle
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
    {
        // bounce off left paddle
        ballVelocity.x *= -velocityMultiplier;
        ballVelocity.y *= velocityMultiplier;
        ball.move(Vector2(10.f, 0.f));
    }
    else if
        (
            //ball is inline or behind paddle AND
            bx > gameWidth - paddleSize.x - paddleOffsetWall &&
            //ball is below top edge of paddle AND
            by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
            //ball is above bottom edge of paddle
            by < paddles[1].getPosition().y + (paddleSize.y * 0.5)

        )
    {
        // bounce off right paddle
        // bounce off left paddle
        ballVelocity.x *= -velocityMultiplier;
        ballVelocity.y *= velocityMultiplier;
        ball.move(Vector2(-10.f, 0.f));
    }

}


void Render(RenderWindow &window)
{
    text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * 0.5f), 0);

    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
    window.draw(text); // Draw the text

}

int main()
{
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");

    // this was debug to find current working directory
    /*
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "Current working directory: " << currentPath << std::endl;
    */

    Load();

    while (window.isOpen())
    {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }

    return 0;
}