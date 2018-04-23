#ifndef __UEBERKASINO_NETWORK_H__
#define __UEBERKASINO_NETWORK_H__

#include <UeberKasinoDcps.h>
#include <memory>
#include <mutex>

#include <io.hpp>

namespace UeberKasino {

/** A callback for when the network receives a game update. */
typedef std::function<void(Game)> GameUpdate;

/** A callback for when the netwrok receives a dealer update. */
typedef std::function<void(Dealer)> DealerUpdate;

/**
 * A singleton which will listen to the OpenSplice network and
 * fire off callbacks, should they be registered.
 */
class Network {

private:
  /** The callback for game updates. */
  GameUpdate m_game_cb;

  /** The callback for dealer updates. */
  DealerUpdate m_dealer_cb;

public:
  /**
   * Sends a player update to the network.
   */
  void send(Player player_event);

  /**
   * Registers a `callback` for when a new Game packet arrives
   * from the OpenSplice network.
   */
  void on_game_update(GameUpdate callback);

  /**
   * Registers a `callback` for when a new Dealer packet arrives
   * from the OpenSplice network.
   */
  void on_dealer_update(DealerUpdate callback);

  // Singleton Stuff
private:

  /** Default constructor, must exist for lazy instantiation */
  Network();

  /** There can be only one */
  Network(Network const &) = delete;

  /** There can be only one. */
  void operator=(Network const &) = delete;

public:

  /**
   * Gets a reference to the network singleton.
   */
  static Network &get() {
    static Network instance;
    return instance;
  }

  /**
   * Dispatches the network's game callback handler with the received
   * message.
   */
  friend void on_receive(const Network &net, Game game) {
    if (net.m_game_cb) {
      net.m_game_cb(game);
    }
  }

  /**
   * Dispatches the network's dealer callback handler with the received
   * message.
   */
  friend void on_receive(const Network &net, Dealer dealer) {
    if (net.m_dealer_cb) {
      net.m_dealer_cb(dealer);
    }
  }
};
};

// Direct callbacks from io.hpp

/** Unused but required for generic io.hpp. */
void _cb(UeberKasino::Player);

/** Direct callback used by the io.hpp file. See on_receive. */
void _cb(UeberKasino::Dealer);

/** Direct callback used by the io.hpp file. See on_receive. */
void _cb(UeberKasino::Game);

#endif
