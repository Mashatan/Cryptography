/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** AMEstimatedTime.h
**
**
** Author: Ali Mashatan
** Email : ali.mashatan@gmail.com
** Source: https://github.com/Mashatan
** -------------------------------------------------------------------------*/
#pragma once 


#include <stdlib.h>
#include <vector>
#include <math.h>
#include <windows.h>
#include <QString>
#include <chrono>
#include <string>

class AMEstimatedTime
{
public:
    struct TimeData
    {
        int hour;
        int min;
        int second;
        int millisecond;
        int microsecond;
        int nanoSecond;
    };

    AMEstimatedTime();
    void     Init();
    void     Start  ( );
    void     Finish ( );
    qint64   GetDiffTime();
    QString  Print();
    QString  Estimiate(quint64 current, quint64 w );

private:
    double      m_dFreq;
    std::chrono::high_resolution_clock::time_point  m_nCounterStart;
    TimeData    m_TimeDateFinish;
    quint64     m_nDiffTime;
    quint64     m_nSumTime;
    int         m_nNumTime;

    quint64    GetCounter  ();
    void       Parse( quint64 value );

};
