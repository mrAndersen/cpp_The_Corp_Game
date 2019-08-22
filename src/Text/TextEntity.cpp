#include <climits>
#include "TextEntity.h"
#include "../System/System.h"
#include "../System/EntityContainer.h"
#include "../System/ViewHandler.h"

TextEntity::TextEntity(const sf::Color &color, int size) : Entity() {
    text.setCharacterSize((unsigned int) size);
    text.setFillColor(color);
    text.setFont(*System::titleFont);

    setDrawOrder(D_Text_Entities);
    setDirection(Up);
    EntityContainer::add(this);
}

void TextEntity::updateLogic() {
    float frameTimeSeconds = (float) System::frameTimeMcs / 1000000;
    float frameDistance = frameTimeSeconds * speed * System::timeFactor;

    if (fixed) {
        totalEntityDistance += frameDistance;

        worldCoordinates.x = ViewHandler::left + leftOffset;
        worldCoordinates.y = ViewHandler::top - topOffset;
    } else {
        totalEntityDistance = frameDistance;
    }

    if (direction == Right) {
        worldCoordinates.x += totalEntityDistance;
    }

    if (direction == Left) {
        worldCoordinates.x -= totalEntityDistance;
    }

    if (direction == Up) {
        worldCoordinates.y += totalEntityDistance;
    }

    if (direction == Down) {
        worldCoordinates.y -= totalEntityDistance;
    }

    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    text.setPosition(System::cToGl(worldCoordinates));

    System::window->draw(text);

    if (liveTimeSeconds != 0 && liveClock.getElapsedTime().asSeconds() >= liveTimeSeconds) {
        EntityContainer::remove(this);
    }else{
        Entity::updateLogic();
    }
}

sf::Text &TextEntity::getText() {
    return text;
}

void TextEntity::setText(const sf::Text &text) {
    TextEntity::text = text;
}



void TextEntity::setString(const sf::String &string) {
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

float TextEntity::getLeftOffset() const {
    return leftOffset;
}

void TextEntity::setLeftOffset(float leftOffset) {
    TextEntity::leftOffset = leftOffset;
}

float TextEntity::getTopOffset() const {
    return topOffset;
}

void TextEntity::setTopOffset(float topOffset) {
    TextEntity::topOffset = topOffset;
}