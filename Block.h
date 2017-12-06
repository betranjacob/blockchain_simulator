/*
 * Block.h
 *
 *  Created on: 23 Nov 2017
 *      Author: betran
 */

#ifndef BLOCK_H_
#define BLOCK_H_
#include <iostream>
#include <string>
#include <map>
#include <sha256.h>

class Block {

    int _index=0;
    std::string _timestamp="";
    // A table of Block data info.
    // Block data can be (Users wallet, balance)  or recent-transactions (sender:reciever, amount).
    std::map<std::string, int> _data={};
    std::string _previous_hash="";

public:
    // Constructor to create a Block in the chain
    Block(int index,
          std::string timestamp,
          std::map<std::string, int> data,
          std::string previous_hash=""):
              _index(index),
              _timestamp(timestamp),
              _previous_hash(previous_hash) {
        _data.insert(data.begin(), data.end());
    }

    int inline get_id() const { return _index; }

    std::string get_previous_hash() const {
        return this->_previous_hash;
    }

    std::string format_data() const {

        std::string data_accounts = "Accounts { ";
        std::string data_transactions = "Trx { ";

        // Iterate through map and separately append accounts and transactions.
        for (std::pair<std::string, int> d : _data)
            if(d.first.find("->") == std::string::npos){
                data_accounts = data_accounts + "[" + d.first + ":" + std::to_string(d.second) + "] ";
            }else{
                data_transactions = data_transactions + "[" + d.first + ":" + std::to_string(d.second) + "] ";
            }

        // Close the braces
        data_accounts = data_accounts + "}";
        data_transactions = data_transactions + "}";
        return data_accounts  + " --- " + data_transactions;
    }

    // Generate the hash of the this block
    std::string hash_block() const {

        return sha256(std::to_string(_index) +
                      _timestamp +
                      format_data() +
                      _previous_hash);
    }

    Block& operator=(const Block &other){

        this->_index = other._index;
        this->_previous_hash = other._previous_hash;
        this->_data = other._data;
        this->_timestamp = other._timestamp;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &out, const Block &b) {

        out << "Block #" << b._index << " " << b.format_data() << std::endl;
        return out;
    }

};

#endif /* BLOCK_H_ */
