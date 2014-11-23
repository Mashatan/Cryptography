/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** AMCipherBase.cpp
** 
**
** Author: Ali Mashatan
** Email : ali.mashatan@gmail.com
** Source: https://github.com/Mashatan
** -------------------------------------------------------------------------*/

#include <openssl/md5.h>
#include "AMCipherBase.h"
#include <QFileInfo>

#ifndef MAX
#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
#endif


#define NO_ERROR    0
#define READ_ERROR  -7
#define WRITE_ERROR -8

AMCipherBase::AMCipherBase(QString key)
{
    m_Key = key;
}

bool AMCipherBase::Load(QString filename, ostream &dest,bool raw)
{
    bool result = false;
    QFileInfo info (filename);
    if ( info.exists() == false )
    {
        return result;
    }

    ifstream     iFile;
    
    iFile.open( filename.toStdWString().c_str(), std::ios::binary );
    iFile.seekg(0, ios::beg);
    if (raw == false)
    {
        result = LoadStream(iFile, dest);
    }
    else {
        dest << iFile.rdbuf();
        result = true;
    }
    iFile.close();
    return result;
}

bool AMCipherBase::Save( QString filename, istream &source )
{
    ofstream encryptData;
    encryptData.open( filename.toStdWString().c_str(), std::ios::binary );
    bool result = false;
    result = SaveStream(source, encryptData);
    encryptData.flush();
    encryptData.close();
    return result;
}

#define RAND(a,b) (((a = 36969 * (a & 65535) + (a >> 16)) << 16) + \
    (b = 18000 * (b & 65535) + (b >> 16))  )

// Filling buffer with random int.
void AMCipherBase::FillRandBuf(char *buf, const int len)
{   
    static unsigned long range[2];
    static unsigned long count = 4;
    static char          random[4];
    int                  i;

    range[0] = 100; 
    range[1] = 100000000;
    for(i = 0; i < len; ++i)
    {
        if(count == 4)
        {
            *(unsigned long*)random = RAND(range[0], range[1]);
            count = 0;
        }

        buf[i] = random[count++];
    }
}

const int OP_SIZE = 1032;
const int IP_SIZE = 1024;

int AMCipherBase::Encrypt ( istream &source, ostream &dest )
{   
    unsigned char outbuf[OP_SIZE];
    int olen, tlen, n;
    unsigned char inbuff[IP_SIZE];
    EVP_CIPHER_CTX ctx;
    unsigned char key[16];
    unsigned char *iv = (unsigned char*)malloc (m_ByteOfNumber);
    
    memset(key, 0, 16);
    memcpy( key, m_Key.toLatin1().constData(), MIN(m_Key.length(),16) );
    //Making IV with random integer.
    FillRandBuf( (char*)iv, m_ByteOfNumber);

    //Writing IV at the beginning file.
    source.seekg ( 0, ios::beg);
    dest.write((char*)iv, m_ByteOfNumber);
    
    // Initialize cipher method.
    EVP_CIPHER_CTX_init (& ctx);
    EVP_EncryptInit_ex(&ctx, m_CipherType, NULL, key, iv);
    memset(iv, 0, m_ByteOfNumber);
    free (iv);
    
    // Initialize MD5
    MD5_CTX MD5Context;
    unsigned char MD5Array[MD5_DIGEST_LENGTH];
    MD5_Init(&MD5Context);

    for (;;)
    {
        memset (&inbuff, 0, IP_SIZE);

        // Reading from file.
        source.read((char*)inbuff, IP_SIZE);
        n = source.gcount();
        if (n == 0)
        {
            break;
        }

        // Updating MD5
        MD5_Update(&MD5Context, inbuff, n);

        //Updating cipher
        if (EVP_EncryptUpdate (& ctx, outbuf, & olen, inbuff, n) != 1)
        {
            printf ("error in encrypt update\n");
            return 0;
        }

        if ( n != IP_SIZE )
        {
            //finalize cipher.
            if (EVP_EncryptFinal (& ctx, outbuf + olen, & tlen) != 1)
            {
                printf ("error in encrypt final\n");
                return 0;
            }
            olen += tlen;
        }
        dest.write((char*)outbuf, olen);
    }

    //finalize MD5
    MD5_Final(MD5Array, &MD5Context);
    EVP_CIPHER_CTX_cleanup (& ctx);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) 
    {
        printf("%02x", MD5Array[i]);
    }
    printf("\n");

    return NO_ERROR;
}


int AMCipherBase::Decrypt( istream &source, ostream &dest )
{   
    unsigned char outbuf[OP_SIZE];
    unsigned char inbuff[IP_SIZE];
    EVP_CIPHER_CTX chipherContext;
    unsigned char key[16];
    int nReadCount=0;
    int olen = 0;
    int tlen = 0;
    unsigned char *iv; 

    iv = (unsigned char *) malloc(m_ByteOfNumber);
    memset(key, 0, 16);
    memcpy( key, m_Key.toLatin1().constData(), MIN(m_Key.length(),16) );

    //Reading IV at the beginning file.
    source.seekg(0, ios::beg);
    source.read((char*)iv, m_ByteOfNumber);
    
    // Initialize cipher method.
    EVP_CIPHER_CTX_init (&chipherContext);
    EVP_DecryptInit_ex ( &chipherContext, m_CipherType, NULL, key, iv );
    memset( iv, 0, m_ByteOfNumber );
    free(iv);

    // Initialize MD5
    MD5_CTX MD5Context;
    unsigned char MD5Array[MD5_DIGEST_LENGTH];
    MD5_Init(&MD5Context);

    while (true)
    {
        memset (&inbuff, 0, IP_SIZE);
        source.read( (char*)inbuff, IP_SIZE );
        nReadCount = source.gcount();

        if (nReadCount == 0)
        {
            break;
        }
        memset ( &outbuf, 0, OP_SIZE);
        {
            // Updating cipher method.
            if (EVP_DecryptUpdate (&chipherContext, outbuf, &olen, inbuff, nReadCount) != 1)
            {
                printf ("error in decrypt update\n");
                return 0;
            }
            // Updating MD5.
            MD5_Update(&MD5Context, outbuf, olen);
        }
        if (  nReadCount != IP_SIZE)
        {
            // Finalize cipher method.
            if (EVP_DecryptFinal(&chipherContext, outbuf + olen, &tlen) != 1)
            {
                printf ("error in decrypt final\n");
                return 0;
            }
            olen += tlen;
        }
        dest.write((char*)outbuf, olen);
    }

    // Finalize MD5.
    MD5_Final(MD5Array, &MD5Context);
    EVP_CIPHER_CTX_cleanup (& chipherContext);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) 
    {
        printf("%02x", MD5Array[i]);
    }
    printf("\n");

    // Finalize cipher.
    EVP_CIPHER_CTX_cleanup(&chipherContext);

    return NO_ERROR;
}


bool AMCipherBase::LoadStream( istream &source, ostream &dest )
{
    if (this->Decrypt(source, dest) != NO_ERROR)
    {
        return false;
    }
    return true;
}

bool AMCipherBase::SaveStream( istream &source, ostream &dest )
{
    if (this->Encrypt(source, dest) != NO_ERROR)
    {
        return false;
    }
    return true;
}
