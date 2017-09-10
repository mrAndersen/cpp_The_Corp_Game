#include <SFML/Graphics.hpp>

class CharacterAnimation {
protected:
    float x = 0;
    float y = 0;

    int width = 0;
    int height = 0;

    int totalFrames = 8;
    int currentFrame = 0;

    sf::Sprite sprite;
    sf::Texture texture;

    sf::Time timeSinceCreation;
    sf::Clock clock;

    //frame coordinates inside sprite
    std::vector<sf::IntRect> frames;

    //milliseconds
    float animationResolution = 62;
    float totalAnimationFrameTimeMs = 0;

    float movementResolution = 62;
    float totalMovementFrameTimeMs = 0;

    //pixels per second
    float speed = 120;

    void renderCurrentFrame(sf::RenderWindow *w) {
        auto frame = frames[currentFrame];

        sprite.setPosition(x, y);
        sprite.setTextureRect(frame);
        sprite.setTextureRect(frames[currentFrame]);

        w->draw(sprite);
    }

public:


    float getX() const {
        return x;
    }

    void setX(float x) {
        CharacterAnimation::x = x;
    }

    float getY() const {
        return y;
    }

    void setY(float y) {
        CharacterAnimation::y = y;
    }

    int getWidth() const {
        return width;
    }

    void setWidth(int width) {
        CharacterAnimation::width = width;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int height) {
        CharacterAnimation::height = height;
    }

    const sf::Texture &getTexture() const {
        return texture;
    }

    void setTexture(const sf::Texture &texture) {
        CharacterAnimation::texture = texture;
    }

    void updateFrameTime() {
        int frameTimeMs = clock.restart().asMilliseconds();

        totalAnimationFrameTimeMs += frameTimeMs;
        totalMovementFrameTimeMs += frameTimeMs;
    }

    bool isAnimationResolutionReached() {
        if (totalAnimationFrameTimeMs >= animationResolution) {
            totalAnimationFrameTimeMs = 0;
            return true;
        } else {
            return false;
        }
    }

    bool isMovementResolutionReached() {
        if (totalMovementFrameTimeMs >= movementResolution) {
            totalMovementFrameTimeMs = 0;
            return true;
        } else {
            return false;
        }
    }


    void createAnimationFrames() {
        sprite.setTexture(texture);
        sprite.setOrigin(width / 2, height / 2);
//        sprite.scale(-1.f, 1.f);

        for (int i = 0; i < totalFrames; ++i) {
            sf::IntRect rect(i * width, 0, width, height);
            frames.push_back(rect);
        }

        this->sprite.setTextureRect(frames[0]);
    }

    void updateAnimation(sf::RenderWindow *w) {
        if (isAnimationResolutionReached()) {
            this->currentFrame = (currentFrame == (totalFrames - 1)) ? 0 : currentFrame + 1;
        }

        if (isMovementResolutionReached()) {
            this->x += (this->movementResolution / 1000) * speed;
        }

        this->renderCurrentFrame(w);
        this->updateFrameTime();
    }
};