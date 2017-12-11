#include <SFML/Window/Mouse.hpp>
#include <windows.h>
#include <psapi.h>
#include <sstream>
#include <iomanip>
#include <random>
#include <chrono>
#include <climits>
#include <iostream>
#include <codecvt>
#include "System.h"
#include "ViewHandler.h"
#include "GameTime.h"
#include "..\Text\TextEntity.h"
#include "ResourceLoader.h"
#include "../../version.h"
#include "EntityContainer.h"
#include "ControlPanel.h"

namespace System {
    unsigned int screenWidth = 1850;
    unsigned int screenHeight = 900;
    std::string title = "New World";
    float worldWidth = 9900;
    int gridSize = 50;
    int entitySequence = 1;

    //sys
    Scenes activeScene;
    Scenes loadingScene;
    sf::Clock saveTimer;
    sf::Clock sceneChangeTimer;
    sf::Clock fpsClock;
    sf::Clock frameClock;
    sf::Clock timeSinceStart;
    sf::Font *textFont;
    sf::Font *titleFont;
    sf::Font *titleFontI8N;

    unsigned int seed = 0;

    sf::RenderWindow *window;
    sf::Event event;
    bool selectionAllowed = false;
    long long int frameTimeMcs;
    sf::Uint32 screenMode = sf::Style::Default;
    float timeFactor = 1;
    std::string locale = "en";
    //sys

    //utility
    sf::Color c_background(231, 254, 250);
    sf::Color c_grey(236, 237, 227);
    sf::Color c_red(186, 24, 24);
    sf::Color c_yellow(229, 234, 93);
    sf::Color c_green(92, 184, 92);
    sf::Color c_blue(65, 123, 216);
    //utility

    //player
    double cash = 500000;
    float accountantsBonus = 1.f;
    bool spawningUnit = false;
    sf::Clock selectionCooldown;
    bool dayEndProcessed = false;
    bool dayStartProcessed = false;
    int buttonReload = 150;

    sf::Clock dayClock = {};
    GameTime gameTime(10, 30);

    int startWorkHour = 10;
    int endWorkHour = 19;
    //player

    //debug
    std::map<std::string, sf::Text> debugPanelTextNodes;
    std::map<std::string, int> debugCounters;
    float g_x = 0;
    float g_y = 0;
    int framesPassed = 0;
    int entitiesOnScreen = 0;
    int fps = 0;
    int debug = 0;
    std::string versionType = VERSION_TYPE;
    std::string version = VERSION;
    //debug

    void refreshDayTime() {
        auto localTimeFactor = 1000 / timeFactor;

        if (dayClock.getElapsedTime().asMilliseconds() >= localTimeFactor / 2) {
            dayClock.restart();

            gameTime = gameTime + 1;
        }

        if (gameTime.isDayEndHour() && !dayEndProcessed) {
            System::cash -= EntityContainer::counters[E_Stats_Daily_Loss];
            auto *salarySpent = new TextEntity(System::c_red, 40);

            salarySpent->setFixed(true);
            salarySpent->setString("Salaries: -" + System::f_to_string(EntityContainer::counters[E_Stats_Daily_Loss]) + "$");
            salarySpent->setLeftOffset(System::screenWidth / 2);
            salarySpent->setTopOffset(System::screenHeight / 2);
            salarySpent->setDirection(Direction::Down);
            salarySpent->setLiveTimeSeconds(5);

            dayEndProcessed = true;
            dayStartProcessed = false;
        }

        if (gameTime.isDayStartHour() && !dayStartProcessed) {
            dayStartProcessed = true;
            dayEndProcessed = false;
        }
    }

    void refreshSystem() {
        window->setTitle("Forest Corporation ~ " + std::to_string(fps) + "FPS");

        frameTimeMcs = frameClock.restart().asMicroseconds();
        framesPassed++;

        if (fpsClock.getElapsedTime().asSeconds() >= 1) {
            fps = framesPassed;

            framesPassed = 0;
            fpsClock.restart();
        }
    }

    void refreshDebugPanel() {
        auto kernelText = sf::Text();
        std::string s;

        s += versionType + " ";
        s += version + " ";
        s += std::to_string(screenWidth) + "x";
        s += std::to_string(screenHeight) + " ";

        kernelText.setString(s);

        if (activeScene == SC_Game) {
            kernelText.setFillColor(sf::Color::White);
        } else {
            kernelText.setFillColor(sf::Color::Black);
        }

        kernelText.setPosition(cToGl({ViewHandler::left + 12, ViewHandler::bottom + 20}));
        kernelText.setFont(*textFont);
        kernelText.setCharacterSize(11);
        window->draw(kernelText);

        if (debug) {
            auto mousePosition = sf::Mouse::getPosition(*window);
            auto coordMap = window->mapPixelToCoords(mousePosition);

            PROCESS_MEMORY_COUNTERS pmc = {};
            GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
            SIZE_T mem = pmc.WorkingSetSize;

            g_x = coordMap.x;
            g_y = screenHeight - coordMap.y;


            debugPanelTextNodes["menu_stats"].setString(
                    "menu_stats: v_size->" + std::to_string(EntityContainer::items[SC_Main_Menu].size()));
            debugPanelTextNodes["game_stats"].setString(
                    "game_stats: v_size->" + std::to_string(EntityContainer::items[SC_Game].size()));

            debugPanelTextNodes["active_scene"].setString("active_scene: " + std::to_string(activeScene));
            debugPanelTextNodes["loading_scene"].setString("loading_scene: " + std::to_string(loadingScene));

            debugPanelTextNodes["g_coordinates"].setString(
                    "global: {" + std::to_string((int) g_x) + "," + std::to_string((int) g_y) + "}");
            debugPanelTextNodes["fps"].setString("fps: " + std::to_string(fps));
            debugPanelTextNodes["mouse"].setString(
                    "mouse: {" + std::to_string(mousePosition.x) + "," + std::to_string(mousePosition.y) + "}");
            debugPanelTextNodes["v_direction"].setString(
                    "v_direction: " + std::to_string(ViewHandler::viewDirectionMovement));
            debugPanelTextNodes["mem"].setString("mem:" + std::to_string((int) mem / 1024 / 1024) + "mb");


            debugPanelTextNodes["v_boundaries"].setString(
                    "v_boundaries: "
                            "{t=" + std::to_string((int) ViewHandler::top) + ","
                            "b=" + std::to_string((int) ViewHandler::bottom) + ","
                            "l=" + std::to_string((int) ViewHandler::left) + ","
                            "r=" + std::to_string((int) ViewHandler::right) + "}"
            );

            debugPanelTextNodes["v_zoom"].setString("v_zoom: " + std::to_string(ViewHandler::zoom));
            debugPanelTextNodes["p_cash"].setString("p_cash: " + std::to_string(cash));
            debugPanelTextNodes["p_time"].setString("p_time:" + gameTime.get());
            debugPanelTextNodes["p_time_factor"].setString("p_time_factor:" + std::to_string(timeFactor));
            debugPanelTextNodes["d_level"].setString("d_level:" + std::to_string(debug));
            debugPanelTextNodes["spawning"].setString("spawning:" + std::to_string(spawningUnit));
            debugPanelTextNodes["selection_cd"].setString(
                    "selection_cd:" + std::to_string(selectionCooldown.getElapsedTime().asSeconds()));

            std::string dcs;
            for (auto e:debugCounters) {
                dcs += e.first + "->" + std::to_string(e.second) + ";";
            }
            debugPanelTextNodes["d_counters"].setString(dcs);

            int i = 1;
            for (auto n:debugPanelTextNodes) {
                n.second.setPosition(cToGl(sf::Vector2f(ViewHandler::left + 12, ViewHandler::top - 600 - i * 12)));
                window->draw(n.second);
                i++;
            }
        }
    }

    void initWindow() {
        if (window) {
            delete window;
            window = nullptr;

            delete ViewHandler::views[SC_Game];
            delete ViewHandler::views[SC_Main_Menu];

            ViewHandler::views[SC_Game] = nullptr;
            ViewHandler::views[SC_Main_Menu] = nullptr;
        }

        if (screenMode == sf::Style::Fullscreen) {
            auto boundaries = getScreenBoundaries();

            screenWidth = (unsigned int) boundaries.right;
            screenHeight = (unsigned int) boundaries.bottom;
        }

        sf::Image icon;
        icon.loadFromFile("resources/app/icon.png");

        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), title, screenMode, settings);

        window->clear(c_background);
        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        ViewHandler::views[SC_Game] = new sf::View();
        ViewHandler::views[SC_Game]->reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
        ViewHandler::views[SC_Game]->setCenter(screenWidth / 2, screenHeight / 2);

        ViewHandler::views[SC_Main_Menu] = new sf::View();
        ViewHandler::views[SC_Main_Menu]->reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
        ViewHandler::views[SC_Main_Menu]->setCenter(screenWidth / 2, screenHeight / 2);

        window->setView(*ViewHandler::views[activeScene]);
    }

    sf::Text createDebugString(const std::string &alias) {
        sf::Text label;
        label.setFillColor(sf::Color::Black);
        label.setFont(*textFont);
        label.setCharacterSize(11);

        debugPanelTextNodes[alias] = label;
        return label;
    }

    void initDebug() {
        createDebugString("menu_stats");
        createDebugString("game_stats");
        createDebugString("active_scene");
        createDebugString("loading_scene");
        createDebugString("fps");
        createDebugString("mem");
        createDebugString("g_coordinates");
        createDebugString("mouse");
        createDebugString("v_direction");
        createDebugString("v_boundaries");
        createDebugString("v_zoom");
        createDebugString("p_cash");
        createDebugString("p_time");
        createDebugString("p_time_factor");
        createDebugString("d_level");
        createDebugString("d_counters");
        createDebugString("spawning");
        createDebugString("selection_cd");
    }

    sf::Vector2f cToGl(sf::Vector2f worldCoordinates) {
        worldCoordinates.y = screenHeight - worldCoordinates.y;
        return worldCoordinates;
    }

    sf::Vector2f cToGl(float x, float y) {
        return {x, screenHeight - y};
    }

    sf::Vector2f cFromGl(sf::Vector2f glCoordinates) {
        glCoordinates.y = screenHeight - glCoordinates.y;
        return glCoordinates;
    }

    sf::Vector2f cFromGl(float x, float y) {
        return {x, y - screenHeight};
    }

    sf::Vector2f getGlobalMouse() {
        return {g_x, g_y};
    }

    RECT getScreenBoundaries() {
        RECT w_Desktop{};
        GetWindowRect(GetDesktopWindow(), &w_Desktop);

        return w_Desktop;
    }

    struct f_punctuation : std::numpunct<char> {
    protected :
        char do_thousands_sep() const override { return ','; }

        std::string do_grouping() const override { return "\03"; }
    };

    std::string f_to_string(const double value, const int n) {
        std::ostringstream out;

        out.imbue(std::locale(out.getloc(), new f_punctuation));
        out.precision(n);
        out << std::fixed;
        out << value;

        return out.str();
    }

    std::string formatNewLines(const std::string &in, const size_t every_n) {
        std::string out;
        out.reserve(in.size() + in.size() / every_n);
        bool nextSpaceLine = false;

        for (std::string::size_type i = 0; i < in.size(); i++) {
            if (nextSpaceLine && in[i] == ' ') {
                out.push_back('\n');
                nextSpaceLine = false;
                continue;
            }

            if (!(i % every_n) && i) {
                if (in[i] == ' ') {
                    out.push_back('\n');
                } else {
                    nextSpaceLine = true;
                }
            } else {
                out.push_back(in[i]);
            }
        }
        return out;
    }

    int getRandom(int min, int max) {
        seed = fpsClock.getElapsedTime().asMicroseconds();
        std::mt19937 generator(seed);

        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }

    int roundToMultiple(float target, int multiple) {
        const auto ratio = static_cast<double>(target) / multiple;
        const auto iratio = std::lround(ratio);
        return iratio * multiple;
    }

    bool mouseInsideRect(const sf::Vector2f &leftTop, const sf::Vector2f &rightBottom) {
        return g_x >= leftTop.x &&
               g_x <= rightBottom.x &&
               g_y >= rightBottom.y &&
               g_y <= leftTop.y;
    }

    sf::String join(std::vector<std::string> &array, char delimiter) {
        sf::String s;

        for (int i = 0; i < array.size(); ++i) {
            s += array[i];

            if (i != array.size() - 1) {
                s += delimiter;
            }
        }

        return s;
    }

    std::vector<std::string> split(std::string source, char delimiter) {
        std::vector<std::string> vector;
        std::string temp;

        for (int index = 0; index < source.size(); ++index) {
            if (source[index] == delimiter || index == source.size()) {
                vector.push_back(temp);
                temp = "";
            } else {
                temp += source[index];
            }
        }

        vector.push_back(temp);
        temp = "";

        if (vector[vector.size() - 1] == "") {
            vector.resize(vector.size() - 1);
        }

        return vector;
    }

    void handleGlobalLogic() {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::Resized) {
            screenWidth = window->getSize().x;
            screenHeight = window->getSize().y;

            initWindow();
        }

        if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            auto boundaries = getScreenBoundaries();

            switch (screenMode) {
                case sf::Style::Default:
                    screenMode = sf::Style::Fullscreen;
                    initWindow();
                    break;
                case sf::Style::Fullscreen:
                    screenMode = sf::Style::Default;

                    screenWidth = (unsigned int) boundaries.right * 8 / 10;
                    screenHeight = (unsigned int) boundaries.bottom * 4 / 5;

                    initWindow();
                default:
                    break;
            }
        }
    }

    void changeScene(Scenes scene) {
        System::timeFactor = 1;

        if (scene == SC_Main_Menu) {
            ControlPanel::mainMenu["resume"]->setVisible(!EntityContainer::items[SC_Game].empty());
            ControlPanel::mainMenu["start"]->setVisible(EntityContainer::items[SC_Game].empty());

            System::activeScene = SC_Main_Menu;
            System::sceneChangeTimer.restart();
        }

        if (scene == SC_Game) {
            System::activeScene = SC_Game;
            System::sceneChangeTimer.restart();
        }
    }
}

