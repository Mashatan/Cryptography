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

#pragma once

#include <QObject>
#include <QClipboard>
#include <QMainWindow>
#include <QDir>
#include <vector>

#define PI 3.14

#ifndef MAX
#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
#endif

// The class is singleton pattern.
class AMGlobal : public QObject
{
    Q_OBJECT
public:
    virtual ~AMGlobal();

    static AMGlobal * Instance();
    // After call this method, all of instances is freed and Instance method return NULL.
    static void FreeForEver();
    
    int          DigitsNum( int number );
    QString      RightJustifiedDigits( int number, int maximum );
    QString      StrippedName(const QString &fullFileName);
    QString      PathFriendlyforDisplay(QString path, int maxLength);

    static double RadianToDegree(double radian);
    static double DegreeToRadian(double degree);

    // Store and restore all of position widgets. 
    bool         SavePositionUI( QMainWindow *widget );
    bool         RestorePositionUI( QMainWindow *widget );
    

    // Quick sort for sorting key and value type.
    template <class T> void QuickSort(std::vector<T> &array, const int left, const int right)
    {
        T after;
        if (left < right)
        {
            int i = left;
            int j = right + 1;
            after = array[left];
            do
            {
                do 
                { 
                    i++; 
                } 
                while (array[i].value < after.value && i < right);
                do 
                { 
                    j--; 
                } while (array[j].value > after.value && j > left);

                if (i < j)
                {
                    SwapItem(array, i, j);
                }
            } while (i < j);

            SwapItem(array, left, j);

            QuickSort(array, left, j - 1);
            QuickSort(array, j + 1, right);
        }
    }


private:
    
    // Private constructor, prevents instantiation from other classes.
    AMGlobal();

    static AMGlobal* m_ptrInstance;
    static bool g_bFreeForEver;
    QMainWindow *m_ptrMainWindows;
    QString     PathDataApp();

    template <class T> void SwapItem(std::vector<T> &array, const int A, const int B)
    {
        T after = array[A];
        array[A] = array[B];
        array[B] = after;
    };
};


