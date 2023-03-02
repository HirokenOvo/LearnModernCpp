#ifndef SERVER_H
#define SERVER_H
#include "client.h"
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>
extern std::vector<std::string> pending_trxs;

class Server {
public:
  Server() = default;
  // create a new Client with the specified id.
  // If this id already exists, the server should add a random 4 digit number at
  // the end of it automatically. each client should be assigned with 5 coins at
  // the begining.
  std::shared_ptr<Client> add_client(std::string id);
  // get a pointer to a Client using its id.
  std::shared_ptr<Client> get_client(std::string id) const;
  // return the wallet value of the client with username id.
  double get_wallet(std::string id) const;
  static bool parse_trx(std::string trx, std::string &sender,
                        std::string &receiver, double &value);
  bool add_pending_trx(std::string trx, std::string signature);
  size_t mine();
  friend void show_wallets(const Server &server);

private:
  // Map each client to its wallet.
  // The wallet is the amount of money the client has.
  std::map<std::shared_ptr<Client>, double> clients;
};

inline void show_wallets(const Server &server) {
  std::cout << std::string(20, '*') << std::endl;
  for (const auto &client : server.clients)
    std::cout << client.first->get_id() << " : " << client.second << std::endl;
  std::cout << std::string(20, '*') << std::endl;
}
#endif // SERVER_H