/*
 * RSA.h
 *
 *  Created on: 24 Nov 2017
 *      Author: betran
 */

#ifndef RSA_H_
#define RSA_H_

#include <CkRsa.h>
#include <iostream>
#include <string.h>


class Rsa{

    CkRsa _rsa;

public:

    Rsa() {

        //  Any string argument automatically begins the 30-day trial.
        bool success = _rsa.UnlockComponent("30-day trial");
        if (success != true) {
            std::cout << "RSA component unlock failed" << "\r\n";
            return;
        }

        //  Generate a 2048-bit RSA key pair.
        success = _rsa.GenerateKey(2048);

        //  This will receive the signature in a hex-encoded string.
        // Therefore, set the encoding mode to "hex":
        _rsa.put_EncodingMode("hex");

        // It is important to match the byte-ordering. For other RSA libraries
        // to be verifying  the signature
        _rsa.put_LittleEndian(false);
    }

    std::string get_public_key() {

        //  Public Key exported in char buffer of XML format:
        const char* pub = _rsa.exportPublicKey();
        std::string pub_key(pub, 0, strlen(pub));
        return pub_key;
    }

    std::string get_signed_data(std::string data){

        //  Sign the string using the  sha256 hash algorithm.
        //  Other valid choices are "md2", "sha256", "sha384"
        const char* sig = _rsa.signStringENC(data.c_str(), "sha256");
        std::string signature(sig, 0, strlen(sig));
        return signature;
    }

    bool verify_data(std::string signature, std::string data){

        //  Verify the signature:
        return _rsa.VerifyStringENC(data.c_str(),"sha256", signature.c_str());
    }

    bool set_public_key(std::string public_key)
    {
        return _rsa.ImportPublicKey((const char*)public_key.c_str());
    }
};




#endif /* RSA_H_ */
