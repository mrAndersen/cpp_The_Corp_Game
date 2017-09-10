#include <SFML/Graphics.hpp>


class Debug {
protected:
    sf::Font openSans;

    //debug dictionary
    std::map<std::string, sf::Text> debugPanelTextNodes;

    int mouseX = 0;
    int mouseY = 0;

    int charactersOnScreenCount = 0;
    int fps = 0;
public:
    void setFps(int fps) {
        Debug::fps = fps;
    }

    void setCharactersOnScreenCount(int charactersOnScreenCount) {
        Debug::charactersOnScreenCount = charactersOnScreenCount;
    }

    void setMouseX(int mouseX) {
        Debug::mouseX = mouseX;
    }

    int getMouseY() const {
        return mouseY;
    }

    void setMouseY(int mouseY) {
        Debug::mouseY = mouseY;
    }

    void refreshTitleStats(sf::RenderWindow *w) {
        w->setTitle("New world [" + std::to_string(fps) + " FPS]");
    }

    void refreshDebugPanel(sf::RenderWindow *w) {
        debugPanelTextNodes["fps"].setString("fps: " + std::to_string(fps));
        w->draw(debugPanelTextNodes["fps"]);

        debugPanelTextNodes["mouse"].setString("x:" + std::to_string(mouseX) + " y:" + std::to_string(mouseY));
        w->draw(debugPanelTextNodes["mouse"]);

        debugPanelTextNodes["characters_count"].setString("characters: " + std::to_string(charactersOnScreenCount));
        w->draw(debugPanelTextNodes["characters_count"]);
    }

    Debug() {
        openSans.loadFromFile("resources/fonts/open-sans.ttf");

        //Mouse Coordinates
        sf::Text t_fps;
        t_fps.setPosition(20, 20);
        t_fps.setFillColor(sf::Color::Black);
        t_fps.setFont(openSans);
        t_fps.setCharacterSize(10);
        debugPanelTextNodes["fps"] = t_fps;

        //Mouse Coordinates
        sf::Text t_mouse;
        t_mouse.setPosition(20, 40);
        t_mouse.setFillColor(sf::Color::Black);
        t_mouse.setFont(openSans);
        t_mouse.setCharacterSize(10);
        debugPanelTextNodes["mouse"] = t_mouse;

        //Mouse Coordinates
        sf::Text t_characters_count;
        t_characters_count.setPosition(20, 60);
        t_characters_count.setFillColor(sf::Color::Black);
        t_characters_count.setFont(openSans);
        t_characters_count.setCharacterSize(10);
        debugPanelTextNodes["characters_count"] = t_characters_count;
    }
};
