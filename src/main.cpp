/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.cpp
**
**
** Author: Ali Mashatan
** Email : ali.mashatan@gmail.com
** Source: https://github.com/Mashatan
** -------------------------------------------------------------------------*/


#include <AMCipherAes128Ofb.h>
#include <AMCipherBase.h>
#include <AMEstimatedTime.h>

#include <QFileDialog>
#include <QApplication>

using namespace std;


// key word for encrypting and decrypting.
#define KEY_WORD "3A62A292FB649649E0E92AB94003F94"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Mashatan");
    QCoreApplication::setOrganizationDomain("github.com/Mashatan");
    QCoreApplication::setApplicationName("Cryptography");

    QApplication app( argc, argv );

    AMCipherBase * orginal = new AMCipherAes128Ofb(KEY_WORD);
    stringstream data;

    cout << "Start." << endl;


    // time-evaluation of load function.
    AMEstimatedTime time;
    time.Start();
    //Loading orginal context to data stream.
    bool result = orginal->Load("test/orginal.txt", data, true);
    time.Finish();
    printf("%s\n", time.Print().toStdString().c_str());
    
    if (result == true)
    {
        cout << "Load done." << endl;
    }
    else {
        cout << "Load failed." << endl;
    }
    delete orginal;
    //encrypting data stream to file (crypt.txt).
    AMCipherBase * crypt = new AMCipherAes128Ofb(KEY_WORD);
    if (crypt->Save("test/crypt.txt", data) == true)
    {
        cout << "Save done." << endl;
    }
    else
    {
        cout << "Save failed." << endl;
    }
    delete crypt;

    //Loading crypt file and storing it to other file for validation with original file.
    stringstream datatest;
    AMCipherBase * cryptTest = new AMCipherAes128Ofb(KEY_WORD);
    if ( cryptTest->Load( "test/crypt.txt", datatest ) == true )
    {
        ofstream     encryptData;
        encryptData.open( "test/OrgFCrypt.txt", std::ios::binary );
        datatest.seekg(0, ios::beg);
        encryptData << datatest.rdbuf();
        encryptData.close();
        cout << "Load verify done." << endl;
    } else 
    {
        cout << "Load verify failed." << endl;
    }
    delete cryptTest;

    system("pause");
    return 1;
}


