#include "../../includes/Animation/Static.h"
#include "../../includes/System/System.h"

const std::string &Static::getName() const {
    return name;
}

void Static::setName(const std::string &name) {
    Static::name = name;
}

int Static::getWidth() const {
    return width;
}

void Static::setWidth(int width) {
    Static::width = width;
}

int Static::getHeight() const {
    return height;
}

void Static::setHeight(int height) {
    Static::height = height;
}

const sf::Sprite &Static::getSprite() const {
    return sprite;
}

void Static::setSprite(const sf::Sprite &sprite) {
    Static::sprite = sprite;
}

const sf::Texture &Static::getTexture() const {
    return texture;
}

void Static::setTexture(const sf::Texture &texture) {
    Static::texture = texture;
}

bool Static::clicked(sf::Vector2f targetCoordinates) {
    return false;
}

void Static::updateFrameTime() {
    frameTimeMs = clock.restart().asMilliseconds();
    totalAnimationFrameTimeMs += frameTimeMs;
}

bool Static::isAnimationResolutionReached() {
    return false;
}

void Static::createAnimationFrames() {
    rect.setOrigin(width / 2, height / 2);
    rect.setFillColor(System::green);
    rect.setPosition(System::convertToGLCoordinates(worldCoordinates));
    rect.setSize(sf::Vector2f(width, height));
}

void Static::update() {
    updateAnimation();
}

void Static::updateAnimation() {
    renderCurrentFrame();
}

void Static::updateLogic() {

}

void Static::renderCurrentFrame() {
    System::window->draw(rect);

    if (System::animationDebug) {
        sf::RectangleShape skeleton;

        skeleton.setSize(sf::Vector2f(width, height));
        skeleton.setFillColor(sf::Color::Transparent);
        skeleton.setOutlineColor(System::red);
        skeleton.setOrigin(width / 2, height / 2);
        skeleton.setPosition(System::convertToGLCoordinates(worldCoordinates.x, worldCoordinates.y));
        skeleton.setOutlineThickness(1);
        System::window->draw(skeleton);

        sf::Text debugString;
        debugString.setString("{" + std::to_string((int) worldCoordinates.x) + "," + std::to_string((int) worldCoordinates.y) + "}");
        debugString.setFillColor(sf::Color::Black);
        debugString.setOrigin(width / 2, height / 2);
        debugString.setPosition(System::convertToGLCoordinates(worldCoordinates.x, worldCoordinates.y + 12));
        debugString.setFont(System::openSans);
        debugString.setCharacterSize(8);

        System::window->draw(debugString);
    }
}

const sf::Vector2f &Static::getWorldCoordinates() const {
    return worldCoordinates;
}

void Static::setWorldCoordinates(const sf::Vector2f &worldCoordinates) {
    Static::worldCoordinates = worldCoordinates;
}
