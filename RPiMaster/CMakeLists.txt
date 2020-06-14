cmake_minimum_required(VERSION 3.7)
project(CellularAutomataRPi)

set(CMAKE_CXX_STANDARD 14)

add_executable(host src/main.cpp src/simulator/Simulator.cpp src/simulator/Simulator.h src/board/RectangularBoard.cpp src/board/RectangularBoard.h src/rules/CountRule.cpp src/rules/CountRule.h src/rules/Rule.cpp src/rules/Rule.h src/rules/AggregateRule.cpp src/rules/AggregateRule.h src/connection/commands.h src/connection/Connection.cpp src/connection/Connection.h src/connection/I2CConnection.cpp src/connection/I2CConnection.h src/connection/ConnectionMap.cpp src/connection/ConnectionMap.h)