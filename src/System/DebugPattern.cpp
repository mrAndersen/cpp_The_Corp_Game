#include "../Objects/ElevatorCabin.h"
#include "../Office/OfficeClerk.h"
#include "../Characters/Clerk.h"
#include "../Characters/Manager.h"
#include "DebugPattern.h"
#include "System.h"

namespace DebugPattern {

    void process() {

        if (System::event.type == sf::Event::KeyPressed && System::event.key.code == sf::Keyboard::V) {
            int debugMax = 2;
            System::debug = System::debug == debugMax ? 0 : System::debug + 1;
        }

        if (System::event.type == sf::Event::KeyPressed && System::event.key.code == sf::Keyboard::G) {
            auto count = 4;

            for (int i = 0; i < count; ++i) {
                auto c = new Clerk({System::g_x + (i * 72) - 150, System::g_y});
                c->spawn();
            }
        }

        if (System::event.type == sf::Event::KeyPressed && System::event.key.code == sf::Keyboard::H) {
            auto count = 4;

            for (int i = 0; i < count; ++i) {
                auto m = new Manager({System::g_x + (i * 72) - 150, System::g_y});
                m->spawn();
            }
        }

        if (System::event.type == sf::Event::KeyPressed && System::event.key.code == sf::Keyboard::Numpad4) {
            auto o = new OfficeClerk({1000, 175});
            o->spawn();

            auto o2 = new OfficeClerk({400, 175});
            o2->spawn();
        }

        if (System::event.type == sf::Event::KeyPressed && System::event.key.code == sf::Keyboard::Numpad2) {
            auto top = 600;

            for (int i = 0; i <= top; ++i) {
                if ((i % 150 == 0 || i == 0) && i != top) {
                    auto a2 = new ElevatorShaftMiddle({775, 175 + (float) i});
                    a2->spawn();
                    auto o = new OfficeClerk({1150, 175 + (float) i});
                    o->spawn();
                    auto o2 = new OfficeClerk({400, 175 + (float) i});
                    o2->spawn();
                }

                if (i == top) {
                    auto t2 = new ElevatorShaftTop({775, 175 + (float) i});
                    t2->spawn();
                    auto c2 = new ElevatorCabin({775, 175 + (float) (900 - 150)});
                    c2->spawn();
                }
            }
        }


        if (System::event.type == sf::Event::KeyPressed && System::event.key.code == sf::Keyboard::Numpad1) {
            auto top = 9000;

            for (int i = 0; i <= top; ++i) {

                if ((i % 150 == 0 || i == 0) && i != top) {
                    auto a = new ElevatorShaftMiddle({25, 175 + (float) i});
                    auto a2 = new ElevatorShaftMiddle({775, 175 + (float) i});
                    auto a3 = new ElevatorShaftMiddle({1525, 175 + (float) i});

                    a->spawn();
                    a2->spawn();
                    a3->spawn();

                    auto o = new OfficeClerk({1150, 175 + (float) i});
                    o->spawn();

                    auto o2 = new OfficeClerk({400, 175 + (float) i});
                    o2->spawn();
                }

                if (i == top) {
                    auto t = new ElevatorShaftTop({25, 175 + (float) i});
                    auto t2 = new ElevatorShaftTop({775, 175 + (float) i});
                    auto t3 = new ElevatorShaftTop({1525, 175 + (float) i});
                    t->spawn();
                    t2->spawn();
                    t3->spawn();

                    auto c = new ElevatorCabin({25, 175 + (float) (900 - 150)});
                    auto c2 = new ElevatorCabin({775, 175 + (float) (900 - 150)});
                    auto c3 = new ElevatorCabin({1525, 175 + (float) (900 - 150)});
                    c->spawn();
                    c2->spawn();
                    c3->spawn();
                }
            }
        }

        if (System::event.type == sf::Event::KeyPressed && System::event.key.code == sf::Keyboard::Numpad3) {
            auto top = 900;

            for (int i = 0; i <= top; ++i) {

                if ((i % 150 == 0 || i == 0) && i != top) {
                    auto a = new ElevatorShaftMiddle({25, 175 + (float) i});
                    auto a2 = new ElevatorShaftMiddle({775, 175 + (float) i});
                    auto a3 = new ElevatorShaftMiddle({1525, 175 + (float) i});

                    a->spawn();
                    a2->spawn();
                    a3->spawn();

                    auto o = new OfficeClerk({1150, 175 + (float) i});
                    o->spawn();

                    auto o2 = new OfficeClerk({400, 175 + (float) i});
                    o2->spawn();
                }

                if (i == top) {
                    auto t = new ElevatorShaftTop({25, 175 + (float) i});
                    auto t2 = new ElevatorShaftTop({775, 175 + (float) i});
                    auto t3 = new ElevatorShaftTop({1525, 175 + (float) i});
                    t->spawn();
                    t2->spawn();
                    t3->spawn();

                    auto c = new ElevatorCabin({25, 175 + (float) (900 - 150)});
                    auto c2 = new ElevatorCabin({775, 175 + (float) (900 - 150)});
                    auto c3 = new ElevatorCabin({1525, 175 + (float) (900 - 150)});
                    c->spawn();
                    c2->spawn();
                    c3->spawn();
                }
            }
        }

    }
}
