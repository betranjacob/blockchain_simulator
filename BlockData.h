/*
 * BlockData.h
 *
 *  Created on: 24 Nov 2017
 *      Author: Betran Jacob
 */

#ifndef BLOCKDATA_H_
#define BLOCKDATA_H_

#include <string>
#include <vector>
#include <memory>
#include <exception>

#include "RSA.h"

enum class BlockDataType { Wallet, Transaction };

class Wallet{

    Rsa _rsa;
    std::string _public_key="";
    std::string _name;
    double _balance;
    std::string _last_tx_signature="";

public:


    Wallet(std::string n="Anonymous", double b=0.0):_name(n), _balance(b){
        _public_key = _rsa.get_public_key();
    }

    std::string get_name() { return _name; }

    double get_balance() { return _balance; }

    // Sign a transaction, reduce the available balance based on credit/debit.
    bool update_balance_and_create_signature(std::shared_ptr<Wallet> peer, bool isCredit, double money){

        // Reseting signature.
        _last_tx_signature = "";

        if(!isCredit && _balance < money)
                    return false;
        else {
            if(isCredit)
                _balance += money;
            // Create signature only if money is deducted.
            else {
                _balance -= money;
                std:: string tx = _name + "->" + peer->get_name() + ":" + std::to_string(money);
                _last_tx_signature = _rsa.get_signed_data(tx);
            }
            return true;
        }
    }

    std::string get_public_key(){
        return _public_key;
    }

    std::string get_last_signature(){

        return _last_tx_signature;
    }

};

class InvalidTransaction: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Invalid Transaction Exception";
  }
} InvalidTx;


class Transaction {

public:

    std::shared_ptr<Wallet> sender;
    std::shared_ptr<Wallet> receiver;
    double tx_amount;

    Transaction(std::shared_ptr<Wallet> sender, std::shared_ptr<Wallet> receiver, double tx_amount):sender(sender),
                                                                                                    receiver(receiver),
                                                                                                    tx_amount(tx_amount)
    {
        if(!_is_valid())
            throw InvalidTx;
    }

private:

    Rsa _rsa;

    bool _is_valid() {
        if(_rsa.set_public_key(sender->get_public_key())){
            if(_rsa.verify_data(sender->get_last_signature(),
                                sender->get_name()+"->"+receiver->get_name()+":"+std::to_string(tx_amount))){
                execute();
                return true;
            }
        }
        return false;
    }

    // This transaction is already validated and money deducted from sender.
    // Just send to the other end.
    void execute() {
        receiver->update_balance_and_create_signature(sender, true,tx_amount);
    }


};

class BlockData{

};


#endif /* BLOCKDATA_H_ */
