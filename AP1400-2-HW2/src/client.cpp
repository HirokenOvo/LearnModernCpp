#include "client.h"
#include "crypto.h"
#include "server.h"

Client::Client(std::string id, const Server &server)
    : server{&server}, id{id}, public_key{}, private_key{}
{
  crypto::generate_key(public_key, private_key);
}

std::string Client::get_id() const { return this->id; }

std::string Client::get_publickey() const { return this->public_key; }

double Client::get_wallet() const { return this->server->get_wallet(id); }

std::string Client::sign(std::string txt) const
{
  return crypto::signMessage(private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value)
{
  if (get_wallet() >= value)
  {
    if (server->get_client(receiver) == nullptr)
    {
      std::cout << "receiver client not found" << std::endl;
      return false;
    }
    std::string trx{id + "-" + receiver + "-" + std::to_string(value)};
    const_cast<Server &>(*server).add_pending_trx(trx, sign(trx));
    return true;
  }
  else
  {
    std::cout << "coins not enough" << std::endl;
    return false;
  }
}

size_t Client::generate_nonce()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, 999999999);
  return distr(gen);
}