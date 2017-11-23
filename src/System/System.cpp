#include <SFML/Window/Mouse.hpp>
#include <windows.h>
#include <psapi.h>
#include <sstream>
#include <iomanip>
#include <random>
#include <chrono>
#include <climits>
#include <iostream>
#include "System.h"
#include "ViewHandler.h"
#include "GameTime.h"
#include "..\Text\TextEntity.h"

namespace System {
    unsigned int screenWidth = 1850;
    unsigned int screenHeight = 900;
    std::string title = "New World";
    float groundLevel = 0;
    float worldWidth = 9900;
    int gridSize = 50;
    int entitySequence = 1;

    //sys
    sf::Clock fpsClock;
    sf::Clock frameClock;
    sf::Clock timeSinceStart;

    sf::Font *debugFont;
    sf::Font *gameFont;
    unsigned int seed = 0;

    sf::RenderWindow *window;
    sf::Event event;
    std::deque<sf::Event> eventDeque;
    long long int frameTimeMcs;
    sf::Uint32 screenMode = sf::Style::Default;
    float timeFactor = 1;
    //sys

    //utility
    sf::Color c_background(231, 254, 250);
    sf::Color c_grey(236, 237, 227);
    sf::Color c_red(186, 24, 24);
    sf::Color c_green(92, 184, 92);
    sf::Color c_blue(65, 123, 216);
    //utility

    //player
    double cash = 2000000;
    bool spawningUnit = false;

    bool dayEndProcessed = false;
    bool dayStartProcessed = false;

    float salaryTotal = 0;
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
    int debug = 1;
    //debug

    void refreshDayTime() {
        auto localTimeFactor = 1000 / timeFactor;

        if (dayClock.getElapsedTime().asMilliseconds() >= localTimeFactor / 2) {
            dayClock.restart();

            gameTime = gameTime + 1;
        }

        if (gameTime.isDayEndHour() && !dayEndProcessed) {
            auto *salarySpent = new TextEntity(System::c_red, 40);
            salarySpent->setFixed(true);
            salarySpent->setString("Salaries: -" + System::f_to_string(salaryTotal) + "$");
            salarySpent->setLeft(12);
            salarySpent->setTop(-100);
            salarySpent->setDirection(Direction::Down);
            salarySpent->setLiveTimeSeconds(3);


            dayEndProcessed = true;
            dayStartProcessed = false;
        }

        if (gameTime.isDayStartHour() && !dayStartProcessed) {
            dayStartProcessed = true;
            dayEndProcessed = false;
        }
    }

    void refreshSystem() {
        window->setTitle("Incorporated ~ [" + std::to_string(fps) + " FPS]");

        frameTimeMcs = frameClock.restart().asMicroseconds();
        framesPassed++;

        if (fpsClock.getElapsedTime().asSeconds() >= 1) {
            fps = framesPassed;

            framesPassed = 0;
            fpsClock.restart();
        }
    }

    void refreshDebugPanel() {
        if (debug) {
            auto mousePosition = sf::Mouse::getPosition(*window);
            auto coordMap = window->mapPixelToCoords(mousePosition);

            PROCESS_MEMORY_COUNTERS pmc = {};
            GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
            SIZE_T mem = pmc.WorkingSetSize;

            g_x = coordMap.x;
            g_y = System::screenHeight - coordMap.y;

            debugPanelTextNodes["g_coordinates"].setString(
                    "global: {" + std::to_string((int) g_x) + "," + std::to_string((int) g_y) + "}");
            debugPanelTextNodes["fps"].setString("fps: " + std::to_string(fps));
            debugPanelTextNodes["mouse"].setString(
                    "mouse: {" + std::to_string(mousePosition.x) + "," + std::to_string(mousePosition.y) + "}");
            debugPanelTextNodes["entity_count"].setString("entities: " + std::to_string(entitiesOnScreen));
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
            debugPanelTextNodes["p_cash"].setString("p_cash: " + std::to_string(System::cash));
            debugPanelTextNodes["p_time"].setString("p_time:" + gameTime.get());
            debugPanelTextNodes["p_time_factor"].setString("p_time_factor:" + std::to_string(timeFactor));
            debugPanelTextNodes["d_level"].setString("d_level:" + std::to_string(System::debug));

            std::string dcs = "d_counters:";
            for (auto e:debugCounters) {
                dcs += e.first + "->" + std::to_string(e.second) + ";";
            }
            debugPanelTextNodes["d_counters"].setString(dcs);

            int i = 1;
            for (auto n:debugPanelTextNodes) {
                n.second.setPosition(cToGl(sf::Vector2f(ViewHandler::left + 12, ViewHandler::top - 600 - i * 12)));
                System::window->draw(n.second);
                i++;
            }
        }
    }

    void initWindow() {
        if (window) {
            delete window;
            window = nullptr;

            delete ViewHandler::view;
            ViewHandler::view = nullptr;
        }

        if (screenMode == sf::Style::Fullscreen) {
            auto boundaries = getScreenBoundaries();

            screenWidth = (unsigned int) boundaries.right;
            screenHeight = (unsigned int) boundaries.bottom;
        }

        sf::Image icon;
        icon.loadFromFile("resources/app/icon.png");

        window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), title, screenMode);

        window->clear(c_background);
//        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        ViewHandler::view = new sf::View();
        ViewHandler::view->reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
        ViewHandler::view->setCenter(screenWidth / 2, screenHeight / 2);

        window->setView(*ViewHandler::view);
    }

    sf::Text createDebugString(const std::string &alias) {
        sf::Text label;
        label.setFillColor(sf::Color::Black);
        label.setFont(*debugFont);
        label.setCharacterSize(10);

        debugPanelTextNodes[alias] = label;
        return label;
    }

    void initDebug() {
        createDebugString("fps");
        createDebugString("mem");
        createDebugString("g_coordinates");
        createDebugString("mouse");
        createDebugString("entity_count");
        createDebugString("v_direction");
        createDebugString("v_boundaries");
        createDebugString("v_zoom");
        createDebugString("p_cash");
        createDebugString("p_time");
        createDebugString("p_time_factor");
        createDebugString("d_level");
        createDebugString("d_counters");
    }

    sf::Vector2f cToGl(sf::Vector2f worldCoordinates) {
        worldCoordinates.y = System::screenHeight - worldCoordinates.y;
        return worldCoordinates;
    }

    sf::Vector2f cToGl(float x, float y) {
        return {x, System::screenHeight - y};
    }

    sf::Vector2f cFromGl(sf::Vector2f glCoordinates) {
        glCoordinates.y = System::screenHeight - glCoordinates.y;
        return glCoordinates;
    }

    sf::Vector2f cFromGl(float x, float y) {
        return {x, y - System::screenHeight};
    }

    sf::Vector2f getGlobalMouse() {
        return {System::g_x, System::g_y};
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
}

