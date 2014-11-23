/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** AMCipherAes128Ofb.cpp
** 
**
** Author: Ali Mashatan
** Email : ali.mashatan@gmail.com
** Source: https://github.com/Mashatan
** -------------------------------------------------------------------------*/


#include "AMCipherAes128Ofb.h"


AMCipherAes128Ofb::AMCipherAes128Ofb( QString key ) :
    AMCipherBase(key)
{
    this->Setup();
}

AMCipherAes128Ofb::~AMCipherAes128Ofb()
{

}

void AMCipherAes128Ofb::Setup()
{
    m_CipherType = EVP_aes_128_ofb();
    m_ByteOfNumber = 16;
}
