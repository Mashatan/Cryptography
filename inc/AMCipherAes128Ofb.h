/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** AMCipherAes128Ofb.h
** 
**
** Author: Ali Mashatan
** Email : ali.mashatan@gmail.com
** Source: https://github.com/Mashatan
** -------------------------------------------------------------------------*/

#pragma once 

#include "AMCipherBase.h"

using namespace std;

class AMCipherAes128Ofb : public AMCipherBase
{

public:
    AMCipherAes128Ofb( QString key );
    virtual ~AMCipherAes128Ofb();
    
protected:
    // Implementing AES 128 OFB encryption mode.
    virtual void Setup();

};
