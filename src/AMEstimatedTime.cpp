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

#include <AMEstimatedTime.h>


AMEstimatedTime::AMEstimatedTime()
{
    m_dFreq = 0;
    Init();
}

void AMEstimatedTime::Start(  )
{
    m_nCounterStart = std::chrono::high_resolution_clock::now();
}

quint64 AMEstimatedTime::GetCounter()
{
    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - m_nCounterStart).count();
    auto elapsed = ms;
    return elapsed;
}


void AMEstimatedTime::Finish( )
{
    qint64 value = GetCounter();
    m_nDiffTime = value;
    m_nNumTime++;
    m_nSumTime += value;
}

void AMEstimatedTime::Parse( quint64 value )
{
    quint64 factor = 1;
    factor = 1000000;

    m_TimeDateFinish.hour  = value / ( factor * 60 * 60);
    quint64 hourm = value % ( factor * 60 * 60);

    m_TimeDateFinish.min  = hourm  / ( factor * 60 );
    quint64 minm = hourm  % ( factor * 60 );

    m_TimeDateFinish.second  = minm   / ( factor );

    quint64 secm  = minm  % ( factor );

    m_TimeDateFinish.millisecond = secm  / ( factor/ 1000 );

    quint64 millisecondm = secm % long( double(factor) / 1000 );

    m_TimeDateFinish.microsecond = millisecondm / ( double(factor) / 1000000 );

}

QString widthComma(QString baseStr, QString addStr)
{
    if (baseStr.isEmpty() == false )
    {
        return baseStr +", "+ addStr;
    }
    return addStr;
};

QString AMEstimatedTime::Print()
{
    if ( m_nNumTime == 0 || m_nSumTime == 0)
    {
        return QString("<nothing>");
    }
    Parse( m_nSumTime / m_nNumTime );
    QString result="";
    if ( m_TimeDateFinish.hour > 0 )
    {
        result = widthComma(result, QString( "%1=hrs").arg( (long) m_TimeDateFinish.hour ) );
    }
    if ( m_TimeDateFinish.min > 0 )
    {
        result = widthComma(result, QString( "%1=min").arg( (long) m_TimeDateFinish.min ) );
    }
    if ( m_TimeDateFinish.second > 0 )
    {
        result = widthComma(result, QString( "%1=sec").arg( (long) m_TimeDateFinish.second ) );
    }
    result = widthComma(result, QString("%1=milsec").arg( (long) m_TimeDateFinish.millisecond ) );
    result = widthComma(result, QString("%1=micsec").arg( (long) m_TimeDateFinish.microsecond ) );
    return result;
}

qint64 AMEstimatedTime::GetDiffTime()
{
    return m_nDiffTime;
}

void AMEstimatedTime::Init()
{
    memset(&m_TimeDateFinish, 0, sizeof(m_TimeDateFinish));
    m_nNumTime = 0;
    m_nSumTime = 0;
}

QString AMEstimatedTime::Estimiate( quint64 current, quint64 w )
{
    if ( m_nNumTime == 0 || m_nSumTime == 0)
    {
        return QString("<nothing>");
    }
    quint64 rr = (quint64(m_nSumTime / m_nNumTime) /current) * w ;
    Parse( rr );
    QString result="";
    if ( m_TimeDateFinish.hour > 0 )
    {
        result = widthComma(result, QString( "%1=hrs").arg( (long) m_TimeDateFinish.hour ) );
    }
    if ( m_TimeDateFinish.min > 0 )
    {
        result = widthComma(result, QString( "%1=min").arg( (long) m_TimeDateFinish.min ) );
    }
    if ( m_TimeDateFinish.second > 0 )
    {
        result = widthComma(result, QString( "%1=sec").arg( (long) m_TimeDateFinish.second ) );
    }
    result = widthComma(result, QString("%1=milsec").arg( (long) m_TimeDateFinish.millisecond ) );
    result = widthComma(result, QString("%1=micsec").arg( (long) m_TimeDateFinish.microsecond ) );
    return result;
}