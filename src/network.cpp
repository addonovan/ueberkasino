#include <CheckStatus.h>
#include <DDSEntityManager.h>
#include <iostream>
#include <network.hpp>
#include <thread>

void _cb(UeberKasino::Player player) {
  (void)(player);
  std::cout << "received player callback" << std::endl;
}

void _cb(UeberKasino::Dealer dealer) { on_receive(Network::get(), dealer); }

void _cb(UeberKasino::Game game) { on_receive(Network::get(), game); }

namespace UeberKasino {

// I literally do not understand these types at all

typedef dds_io<Player, PlayerSeq, PlayerTypeSupport_var, PlayerTypeSupport,
               PlayerDataWriter_var, PlayerDataWriter, PlayerDataReader_var,
               PlayerDataReader>
    player_io;

typedef dds_io<Dealer, DealerSeq, DealerTypeSupport_var, DealerTypeSupport,
               DealerDataWriter_var, DealerDataWriter, DealerDataReader_var,
               DealerDataReader>
    dealer_io;

typedef dds_io<Game, GameSeq, GameTypeSupport_var, GameTypeSupport,
               GameDataWriter_var, GameDataWriter, GameDataReader_var,
               GameDataReader>
    game_io;

auto *p_io = new player_io{(char *)"player", true, false};

auto *d_io = new dealer_io{(char *)"dealer", false, true};

auto *g_io = new game_io{(char *)"game", false, true};

Network::Network() {}

void Network::send(Player player_event)
{
  p_io->publish(player_event);
}

void Network::on_game_update(GameUpdate callback)
{
  m_game_cb = callback;
}

void Network::on_dealer_update(DealerUpdate callback)
{
  m_dealer_cb = callback;
}

}
