#include <climits>
#include "../../includes/Text/TextEntity.h"
#include "../../includes/System/System.h"
#include "../../includes/System/EntityContainer.h"

void TextEntity::update() {
    float frameTimeSeconds = (float) System::frameTimeMcs / 1000000;
    float frameDistance = frameTimeSeconds * speed * System::timeFactor;

    if (direction == Direction::Right) {
        worldCoordinates.x += frameDistance;
    }

    if (direction == Direction::Left) {
        worldCoordinates.x -= frameDistance;
    }

    if (direction == Direction::Up) {
        worldCoordinates.y += frameDistance;
    }

    if (direction == Direction::Down) {
        worldCoordinates.y -= frameDistance;
    }

    text.setPosition(System::cToGl(worldCoordinates));
    System::window->draw(text);

    if(liveTimeSeconds != 0 && liveClock.getElapsedTime().asSeconds() >= liveTimeSeconds){
        EntityContainer::remove(this);
    }
}


sf::Text &TextEntity::getText() {
    return text;
}

void TextEntity::setText(const sf::Text &text) {
    TextEntity::text = text;
}

TextEntity::TextEntity(const sf::Color &color, int size) : color(color), size(size) {
    text.setCharacterSize((unsigned int) size);
    text.setFillColor(color);
    text.setFont(*System::gameFont);

    setDrawOrder(INT_MAX);

    EntityContainer::add(this);
}

void TextEntity::setString(const std::string &string) {
    text.setString(string);

}

float TextEntity::getLiveTimeSeconds() const {
    return liveTimeSeconds;
}

void TextEntity::setLiveTimeSeconds(float liveTimeSeconds) {
    TextEntity::liveTimeSeconds = liveTimeSeconds;
}

Direction TextEntity::getDirection() const {
    return direction;
}

void TextEntity::setDirection(Direction direction) {
    TextEntity::direction = direction;
}

float TextEntity::getSpeed() const {
    return speed;
}

void TextEntity::setSpeed(float speed) {
    TextEntity::speed = speed;
}