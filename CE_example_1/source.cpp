#include <windows.h>
#include <thread>
#include <chrono>
#include <iostream>
#pragma warning (disable : 4996)

#include "CEngine.h"
#include "TModel.h"


int main() {
    CEngine engine(50, 50);
    engine.setPixelSize(5, 5);

    std::vector<TModel> pipes;
    std::vector<TModel> pipes_inv;

    /*for (int i = 0; i < 10; i++)
    {
        std::string temp = "========";
        int h = rand() % 12 + 6;
        for (int j = 0; j < h; j++)
        {
            temp += "  ||||  ";
        }

        pipes.push_back(TModel(temp.c_str(), 8 * h, 8, h));

    }

    for (int i = 0; i < 10; i++)
    {
        std::string temp = "";
        int h = rand() % 12 + 6;
        for (int j = 0; j < h; j++)
        {
            temp += "  ||||  ";
        }
        temp += "========";

        pipes_inv.push_back(TModel(temp.c_str(), 8 * h, 8, h));

    }

    TModel bird(
        "|**|"\
        "|**|",
        8,
        4,
        2
    );*/


    engine.setPixelSize(10, 10);

    //engine.addModel(&bird);

    /*for (int i = 0; i < pipes.size(); i++)
    {
        engine.addModel(&pipes[i]);
        pipes[i].setPosition(50 + i * (rand() % 50 + 20), 50 - pipes[i].getSize().height);
    }

    for (int i = 0; i < pipes_inv.size(); i++)
    {
        engine.addModel(&pipes_inv[i]);
        pipes_inv[i].setPosition(50 + i * (rand() % 50 + 20), 0);
    }*/

    float x = 0;
    float y = 0;

    while (engine.getState()) {
        if (GetAsyncKeyState(VK_SPACE)) {
            for (size_t i = 0; i < 10; i++)
            {
                y -= 0.01;
            }
        }

        //bird.move(0, y);


        /*for (int i = 0; i < pipes.size(); i++)
        {
            pipes[i].move(-0.1, 0);
            if (engine.detectCollision(bird, pipes[i])) {
                return 0;
            }
        }

        for (int i = 0; i < pipes_inv.size(); i++)
        {
            pipes_inv[i].move(-0.1, 0);
            if (engine.detectCollision(bird, pipes_inv[i])) {
                return 0;
            }
        }

        for (size_t i = 0; i < pipes.size(); i++)
        {
            if (pipes[i].getPosition().x < (0 - pipes[i].getSize().width)) {
                pipes[i].setPosition(50 + i * (rand() % 50 + 20), 50 - pipes[i].getSize().height);
            }
        }

        for (size_t i = 0; i < pipes_inv.size(); i++)
        {
            if (pipes_inv[i].getPosition().x < (0 - pipes_inv[i].getSize().width)) {
                pipes_inv[i].setPosition(50 + i * (rand() % 50 + 20), 0);
            }
        }*/


        y += 0.01;
        engine.run();
        engine.render();
        //std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    return 0;
}