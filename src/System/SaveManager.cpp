#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include "SaveManager.h"
#include "EntityContainer.h"
#include "..\Office\OfficeClerk.h"

int SaveManager::saveCurrentState(const std::string &fileName) {
    std::ofstream saveFile(fileName, std::ofstream::binary);
    std::string contents;

    for (auto entity:EntityContainer::getSaveable()) {
        contents.append(entity->serialize() + "\n");
    }

    saveFile.write(contents.c_str(), contents.size());
    saveFile.close();

    return contents.size();
}

void SaveManager::handleSaveEvent() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        saveCurrentState();
    }
}