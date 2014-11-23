/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** AMCipherBase.h
** 
**
** Author: Ali Mashatan
** Email : ali.mashatan@gmail.com
** Source: https://github.com/Mashatan
** -------------------------------------------------------------------------*/

#pragma once 

//STL
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

//QT
#include <QString>
#include <QMap>
#include <QByteArray>

//OpenSSL
#include "openssl/aes.h"
#include <openssl/blowfish.h>
#include <openssl/evp.h>

using namespace std;

// the class base of cipher and uses from OpenSSL for provider encrypting and decrypting.
class AMCipherBase
{

public:
    AMCipherBase( QString key );
    // Load file crypt or raw to stream
    bool Load(QString filename, ostream &dest, bool raw= false);
    // Store file crypt from stream.
    bool Save(QString filename, istream &source);


protected:
    const EVP_CIPHER *m_CipherType;
    int m_ByteOfNumber;
    
    // Implementing kind of cipher in derived class. e.g. AES 128 OFB encryption mode.   
    virtual void Setup() = 0;
    
private:
    QString m_Key;

    bool LoadStream ( istream &source, ostream &dest );
    bool SaveStream   ( istream &source, ostream &dest );

    //
    int Encrypt ( istream &source, ostream &dest );
    int Decrypt( istream &source, ostream &dest );

    void FillRandBuf(char *buf, const int len);
};
