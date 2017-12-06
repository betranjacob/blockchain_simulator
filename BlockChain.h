/*
 * BlockChain.h
 *
 *  Created on: 23 Nov 2017
 *      Author: betran
 */

#ifndef BLOCKCHAIN_H_
#define BLOCKCHAIN_H_

#include <vector>
#include <string>
#include "Block.h"
#include "CurrentTime.h"

class BlockChain{

private:
    std::string _name;
    std::vector<Block> _chain;
    int _chain_length=0;

    Block _create_genesis_block() {
        return Block(0, get_current_date_time(), {{"Betran", 100}, {"Jacob", 50}, {"Beth", 200}}, "## Genesis ##");
    }
public:

    // Create a Block chain
    BlockChain(std::string name):_name(name){
        //Block b =_create_genesis_block();
        //std::cout << "Adding Block " << b.get_id() << " length "<< _chain_length <<" previous-hash:" << b.get_previous_hash() << " and hash:" << b.hash_block() << std::endl;
        _chain.push_back(_create_genesis_block());
        _chain_length++;
    }

    // Get the last Block from the chain
    Block get_latest_block() {
        return _chain.back();
    }

    std::string get_name() const { return _name; }

    // Genesis block was created locally, so we subtract that.
    int length() const { return _chain_length-1;  }

    // Append new Block
    void add_block(Block b){
        //std::cout << "Adding Block " << b.get_id() << " length "<< _chain_length <<" previous-hash:" << b.get_previous_hash() << " and hash:" << b.hash_block() << std::endl;
        _chain.push_back(b);
        _chain_length++;
    }

    // Check if the BC has not been compromised.
    bool is_chain_valid(){

        // Genesis Block
        Block previous =_chain.front();

        for(int i=1; i<_chain_length; ++i){
            Block current = _chain[i];
            if(current.get_previous_hash() != previous.hash_block()){
                //std::cout << i << " is not equal to " << i-1 << std::endl;
                //std::cout << current.get_previous_hash() << " is not equal to " << previous.hash_block() << std::endl;
                return false;
            }
            //std::cout << current.get_previous_hash() << " is equal to " << previous.hash_block() << std::endl;
            previous = current;
        }
        return true;
    }
};



#endif /* BLOCKCHAIN_H_ */
