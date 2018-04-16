#ifndef __UEBERKASINO_NETWORK_H__
#define __UEBERKASINO_NETWORK_H__

#include <UeberKasinoDcps.h>
#include <memory>
#include <mutex>

#include <io.hpp>

namespace UeberKasino {

typedef std::function<void(Game)> GameUpdate;
typedef std::function<void(Dealer)> DealerUpdate;

class Network {

private:
  GameUpdate m_game_cb;
  DealerUpdate m_dealer_cb;

public:
  void send(Player player_event);
  void on_game_update(GameUpdate callback);
  void on_dealer_update(DealerUpdate callback);

  // Singleton Stuff
private:
  Network();
  Network(Network const &) = delete;
  void operator=(Network const &) = delete;

public:
  static Network &get() {
    static Network instance;
    return instance;
  }

  friend void on_receive(const Network &net, Game game) {
    if (net.m_game_cb) {
      net.m_game_cb(game);
    }
  }

  friend void on_receive(const Network &net, Dealer dealer) {
    if (net.m_dealer_cb) {
      net.m_dealer_cb(dealer);
    }
  }
};
};

// Direct callbacks from io.hpp

void _cb(UeberKasino::Player);
void _cb(UeberKasino::Dealer);
void _cb(UeberKasino::Game);

#endif
