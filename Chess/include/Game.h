#pragma once

#include <chrono>
#include "Board.h"
#include "Chess.h"
#include "PriorityAlgo.h"
#include "MyExceptions.h"
#include "Threads.h"
#include "Move.h"

void computerGame(const std::string&, COLOR, int, int);
void userGame(const std::string&, COLOR, int, int);