#include <climits>
#include "TextEntity.h"
#include "System/System.h"
#include "System/EntityContainer.h"
#include "System/ViewHandler.h"

void TextEntity::update() {
    float frameTimeSeconds = (float) System::frameTimeMcs / 1000000;
    float frameDistance = frameTimeSeconds * speed * System::timeFactor;

    if (fixed) {
        totalEntityDistance += frameDistance;

        worldCoordinates.x = ViewHandler::left + left;
        worldCoordinates.y = ViewHandler::top + top;
    } else {
        totalEntityDistance = frameDistance;
    }

    if (direction == Direction::Right) {
        worldCoordinates.x += totalEntityDistance;
    }

    if (direction == Direction::Left) {
        worldCoordinates.x -= totalEntityDistance;
    }

    if (direction == Direction::Up) {
        worldCoordinates.y += totalEntityDistance;
    }

    if (direction == Direction::Down) {
        worldCoordinates.y -= totalEntityDistance;
    }

    text.setPosition(System::cToGl(worldCoordinates));
    System::window->draw(text);

    if (liveTimeSeconds != 0 && liveClock.getElapsedTime().asSeconds() >= liveTimeSeconds) {
        EntityContainer::remove(this);
    }
}


sf::Text &TextEntity::getText() {
    return text;
}

void TextEntity::setText(const sf::Text &text) {
    TextEntity::text = text;
}

TextEntity::TextEntity(const sf::Color &color, int size) : Entity() {
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

float TextEntity::getSpeed() const {
    return speed;
}

void TextEntity::setSpeed(float speed) {
    TextEntity::speed = speed;
}

bool TextEntity::isFixed() const {
    return fixed;
}

void TextEntity::setFixed(bool fixed) {
    TextEntity::fixed = fixed;
}

float TextEntity::getScreenLeft() const {
    return screenLeft;
}

void TextEntity::setScreenLeft(float screenLeft) {
    TextEntity::screenLeft = screenLeft;
}

float TextEntity::getScreenTop() const {
    return screenTop;
}

void TextEntity::setScreenTop(float screenTop) {
    TextEntity::screenTop = screenTop;
}
