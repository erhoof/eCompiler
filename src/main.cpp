//
// Created by Pavel Bibichenko on 19.06.2020.
//

#include <iostream>

#include "../include/IO/Logger.h"
#include "../include/Core/Core.h"

int main(int argc, char* argv[]) {
    Logger::instance().log("eCompiler started.");

    Core::instance().loadFile("../data/main.ts");
    Core::instance().process();

    return 0;
}