/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** AMGlobal.h
**
**
** Author: Ali Mashatan
** Email : ali.mashatan@gmail.com
** Source: https://github.com/Mashatan
** -------------------------------------------------------------------------*/

#include <AMGlobal.h>
#include <QApplication>
#include <QDesktopServices>
#include <stdarg.h>
#include <math.h>
#include <QSettings>

#ifdef  _WIN32
#include <Windows.h>
#include <WinBase.h>
#endif

AMGlobal* AMGlobal::m_ptrInstance = NULL;  
bool AMGlobal::g_bFreeForEver = false;


AMGlobal::AMGlobal()
{
}


AMGlobal::~AMGlobal()
{
}


AMGlobal* AMGlobal::Instance()
{
    if (g_bFreeForEver == true)
    {
        return NULL;
    }
    //if m_ptrInstance is NULL, a instant create otherwise last instance.
    if (m_ptrInstance == NULL)
    {
        m_ptrInstance = new AMGlobal;
    }

    return m_ptrInstance;
}


void AMGlobal::FreeForEver()
{
    delete m_ptrInstance;
    m_ptrInstance = NULL;
    g_bFreeForEver = true;
}


int AMGlobal::DigitsNum( int number )
{
    int digits = 0;
    if (number < 0) 
    {
        digits = 1;
    }
    while (number) 
    {
        number /= 10;
        digits++;
    }
    return digits;
}

QString AMGlobal::RightJustifiedDigits( int number, int maximum )
{
    QString digit = QString::number( number );
    digit = digit.rightJustified( DigitsNum(maximum) , '0' );
    return digit;
}

bool AMGlobal::SavePositionUI( QMainWindow *widget )
{
    QSettings settings(PathDataApp() + QCoreApplication::applicationName() + ".ini", QSettings::IniFormat);
    settings.beginGroup("GUI");
    settings.setValue("geometry", widget->saveGeometry());
    settings.setValue("windowState", widget->saveState());
    settings.endGroup();
    return true;
}


bool AMGlobal::RestorePositionUI( QMainWindow *widget )
{
    m_ptrMainWindows = widget;
    QSettings settings(PathDataApp() + QCoreApplication::applicationName() + ".ini", QSettings::IniFormat);
    settings.beginGroup("GUI");
    QVariant value;
    value = settings.value("windowState");
    if  ( value.isNull() == false && value.isValid() == true )
    {
        widget->restoreState    ( value.toByteArray() );
    }
    value = settings.value("geometry");
    if  ( value.isNull() == false && value.isValid() == true )
    {
        widget->restoreGeometry ( value.toByteArray() );
    }
    settings.endGroup();
    return true;
}

QString AMGlobal::PathDataApp()
{
    QString location = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#ifdef Q_WS_MAC
    location.insert(location.count() - QCoreApplication::applicationName().count(),
        QCoreApplication::organizationName() + "/");
#endif
    if ( location.at(location.length()-1) != QChar('/') )
    {
        location.append('/');
    }
    return location;
}


QString AMGlobal::StrippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

double AMGlobal::RadianToDegree( double radian )
{
    return radian * 180 / PI;
}

double AMGlobal::DegreeToRadian( double degree )
{
    return degree * PI / 180;
}

QString AMGlobal::PathFriendlyforDisplay( QString path, int maxLength )
{
    if ( path.size() <= maxLength  )
    {
        return path;
    }
    path = path.replace("\\", "/", Qt::CaseInsensitive);
    int firstIdx = path.indexOf( "/", 2 );
    QString firstStr = path.left( firstIdx );
    QString bodyStr  = path.right( path.length() - firstIdx  );
    int idx;
    while ( bodyStr.length() > maxLength )
    {
        idx = bodyStr.indexOf( "/" );
        if (idx == -1 )
        {
            break;
        }
        bodyStr  = bodyStr.remove( 0, idx+1 );
    }
    QString temp = firstStr +"/.../"+ bodyStr;
    return temp;
}
