#include <SFML/Graphics.hpp>
#include <System/Enum.h>
#include <System/System.cpp>

class EntityAnimation {
protected:
    std::string name = "";

    float x = 0;
    float y = 0;

    int width = 0;
    int height = 0;

    int totalFrames = 8;
    int currentFrame = 0;

    Direction direction = Direction::Right;

    sf::Sprite sprite;
    sf::Texture texture;

    sf::Time timeSinceCreation;
    sf::Clock clock;

    //frame coordinates inside sprite
    std::vector<sf::IntRect> frames;

    //milliseconds
    float animationResolution = 500;
    float totalAnimationFrameTimeMs = 0;
    float frameTimeMs = 0;

    //pixels per second
    float speed = 120;

    void renderCurrentFrame() {
        auto frame = frames[currentFrame];

        sprite.setPosition(x, y);
        sprite.setTextureRect(frame);

        if (direction == Direction::Left) {
            sprite.setScale(-1.f, 1.f);
        }

        if (direction == Direction::Right) {
            sprite.setScale(1.f, 1.f);
        }

        System::window->draw(sprite);
    }

public:
    bool contains(float x, float y) {
        return
                x > this->x &&
                x < x + this->width &&
                y > this->y &&
                y < y + this->height;

    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        EntityAnimation::name = name;
    }

    Direction getDirection() const {
        return direction;
    }

    void setDirection(Direction direction) {
        EntityAnimation::direction = direction;
    }

    float getX() const {
        return x;
    }

    void setX(float x) {
        EntityAnimation::x = x;
    }

    float getY() const {
        return y;
    }

    void setY(float y) {
        EntityAnimation::y = y;
    }

    int getWidth() const {
        return width;
    }

    void setWidth(int width) {
        EntityAnimation::width = width;
    }

    int getHeight() const {
        return height;
    }

    float getSpeed() const {
        return speed;
    }

    void setSpeed(float speed) {
        EntityAnimation::speed = speed;
    }

    void setHeight(int height) {
        EntityAnimation::height = height;
    }

    const sf::Texture &getTexture() const {
        return texture;
    }

    void setTexture(const sf::Texture &texture) {
        EntityAnimation::texture = texture;
    }

    void updateFrameTime() {
        frameTimeMs = clock.restart().asMilliseconds();
        totalAnimationFrameTimeMs += frameTimeMs;
    }

    bool isAnimationResolutionReached() {
        if (totalAnimationFrameTimeMs >= animationResolution) {
            totalAnimationFrameTimeMs = 0;
            return true;
        } else {
            return false;
        }
    }

    void createAnimationFrames() {
        sprite.setTexture(texture);
        sprite.setOrigin(width / 2, height / 2);

        for (int i = 0; i < totalFrames; ++i) {
            sf::IntRect rect(i * width, 0, width, height);
            frames.push_back(rect);
        }

        this->animationResolution = 1000 / frames.size();
        this->sprite.setTextureRect(frames[0]);
    }

    void updateAnimation() {
        if (isAnimationResolutionReached()) {
            this->currentFrame = (currentFrame == (totalFrames - 1)) ? 0 : currentFrame + 1;
        }

        if (direction == Direction::Right) {
            this->x += (frameTimeMs / 1000) * speed;
        }

        if (direction == Direction::Left) {
            this->x -= (frameTimeMs / 1000) * speed;
        }

        this->renderCurrentFrame();
        this->updateFrameTime();
    }
};