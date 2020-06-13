#include <iostream>

#include <fcntl.h>
#include <chrono>
#include <thread>
#include "connection/ConnectionMap.h"
#include "connection/I2CConnection.h"
#include "board/RectangularBoard.h"
#include "rules/AggregateRule.h"
#include "rules/CountRule.h"
#include "simulator/Simulator.h"

int main() {
    int i2c = open("/dev/i2c-1", O_RDWR);
    if (i2c < 0) {
        std::cout << "Falied to open the i2c bus" << std::endl;
        return -1;
    }

    ConnectionMap connectionMap(1, 1);
    connectionMap.setConnection(0, 0, std::make_unique<I2CConnection>(i2c, 0x13));
    RectangularBoard board{1, 1};
    AggregateRule rule;
    rule.append(std::unique_ptr<Rule>(new CountRule(0, 1, {std::pair<int, std::pair<int, int> >(1, std::pair<int, int>(3, 3))})));
    rule.append(std::unique_ptr<Rule>(new CountRule(1, 1, {std::pair<int, std::pair<int, int> >(1, std::pair<int, int>(2, 3))})));
    rule.append(std::unique_ptr<Rule>(new CountRule(1, 0, {})));

    Simulator simulator(board, rule);

    while (true) {
        using namespace std::chrono_literals;
        auto next = std::chrono::system_clock::now() + 1s;

        board.print();
        simulator.step();
        connectionMap.sendBoard(board);

        std::cout << "Step" << std::endl;
        std::this_thread::sleep_until(next);
    }
    return 0;
}