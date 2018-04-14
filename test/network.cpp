#include <iostream>
#include <network.hpp>
#include <thread>
#include <chrono>

using namespace UeberKasino;

int main() {
  auto &net = Network::get();
  net.on_game_update([](Game game) {
    std::cout << "Received game update!" << std::endl;

    std::cout << "state:     " << game.gstate << std::endl
              << "game id:   " << game.game_uid << std::endl
              << "dealer id: " << game.dealer_uid << std::endl;
  });

  net.on_dealer_update([](Dealer dealer){
    std::cout << "Received dealer update!" << std::endl;


    std::string name{ dealer.uid };
    std::cout << "dealer id: " << name << std::endl;
  });

  while (true)
  {
    std::this_thread::sleep_for(std::chrono::seconds{10});
  }

  return 0;
}
