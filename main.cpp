/*
 * main.cpp
 *
 *  Created on: 23 Nov 2017
 *      Author: Betran Jacob
 */




#include "Block.h"
#include "CurrentTime.h"
#include "BlockChain.h"
#include "BlockData.h"
#include "RSA.h"
#include <memory>
#include <iomanip>

// A Block can have multiple account wallets and transactions.
// For simplicity we currently use only two accounts and one transaction.
void create_and_add_block(std::shared_ptr<BlockChain> bc, std::shared_ptr<Wallet> cus_1, std::shared_ptr<Wallet> cus_2, double amount)
{

    cus_1->update_balance_and_create_signature(cus_2, false, 100);
    Transaction tx1(cus_1, cus_2, 100.0);

    // Create the block.
    Block B(1, get_current_date_time(), {{cus_1->get_name(), cus_1->get_balance()},
                                          {cus_2->get_name(), cus_2->get_balance()},
                                          {tx1.sender->get_name()+"->"+tx1.receiver->get_name(), tx1.tx_amount}},
                                          bc->get_latest_block().hash_block());
    bc->add_block(B);
}

int main()
{
    // Create 4 wallets.
    std::shared_ptr<Wallet> w1 = std::make_shared<Wallet>("Betran", 1000.0);
    std::shared_ptr<Wallet> w2 = std::make_shared<Wallet>("Jacob", 2000.0);
    std::shared_ptr<Wallet> w3 = std::make_shared<Wallet>("Bob", 1500.0);
    std::shared_ptr<Wallet> w4 = std::make_shared<Wallet>("Beth", 2500.0);

    // Create a Block Chain,
    std::shared_ptr<BlockChain> Truster = std::make_shared<BlockChain>("Truster");

    create_and_add_block(Truster, w1, w2, 100);
    create_and_add_block(Truster, w2, w3, 200);
    create_and_add_block(Truster, w3, w4, 100);
    create_and_add_block(Truster, w4, w1, 500);

    // Run the hash algorithm from the latest to genesis block.
    std::cout << "Block chain " << std::quoted(Truster->get_name()) << " has " << Truster->length() << " blocks " << std::endl;
    std::cout << "Checking chain validity : ";
    std::cout << std::boolalpha << Truster->is_chain_valid() << std::endl;
}
