#include "server.h"
#include "client.h"
#include "crypto.h"
#include "server.h"
std::vector<std::string> pending_trxs;
std::shared_ptr<Client> Server::add_client(std::string id) {
  std::string nid{id};
  for (auto &[cli, coin] : this->clients) {
    if (cli->get_id() == id) {
      // create random int
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> distr(0, 9999);
      // add
      nid += std::to_string(distr(gen));
      break;
    }
  }
  std::shared_ptr<Client> nwClient{std::make_shared<Client>(nid, *this)};
  this->clients[nwClient] = 5.0;
  return nwClient;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
  for (auto const &[cli, coin] : this->clients) {
    if (cli->get_id() == id) {
      return cli;
    }
  }
  return nullptr;
}

double Server::get_wallet(std::string id) const {
  for (auto const &[cli, coin] : this->clients) {
    if (cli->get_id() == id) {
      return coin;
    }
  }
  throw std::runtime_error("client not find");
}

bool Server::parse_trx(std::string trx, std::string &sender,
                       std::string &receiver, double &value) {
  std::stringstream in(trx);
  std::vector<std::string> ve;
  for (std::string seg; std::getline(in, seg, '-');) {
    ve.push_back(seg);
  }
  if (ve.size() != 3) {
    throw std::runtime_error("trx is not standard!");
    return false;
  }
  sender = ve[0];
  receiver = ve[1];
  value = std::stod(ve[2]);
  return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) {
  std::string sender{}, receiver{};
  double value{};
  parse_trx(trx, sender, receiver, value);

  if (get_wallet(sender) >= value) {
    auto cSender = get_client(sender);
    if (crypto::verifySignature(cSender->get_publickey(), trx, signature)) {
      pending_trxs.push_back(trx);
      return true;
    } else {
      std::cout << "verifySignature failed" << std::endl;
      return false;
    }
  } else {
    std::cout << "sender has no enough coins" << std::endl;
    return false;
  }
}

size_t Server::mine() {
  std::string mempool{};
  for (const auto &seg : pending_trxs)
    mempool += seg;

  while (true) {
    for (const auto &[cli, coin] : clients) {
      size_t nonce{cli->generate_nonce()};
      std::string hash{crypto::sha256(mempool + std::to_string(nonce))};

      if (hash.find("000") < 7) {
        clients[cli] += 6.25;
        for (const auto &trx : pending_trxs) {
          std::string sender{}, receiver{};
          double value{};
          parse_trx(trx, sender, receiver, value);
          clients[get_client(sender)] -= value;
          clients[get_client(receiver)] += value;
        }
        pending_trxs.clear();
        return nonce;
      }
    }
  }
}