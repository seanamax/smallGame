
# Can run just copy!

```c++
#include <iostream>
#include <windows.h>
#include <queue>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <conio.h>
using namespace std;
void unit_test();

class snake{
private:
    char _snakeBody = '*';
    char _cancel = '\0';
    static const int integralX = 40;
    static const int integralY = 24;
    static const int _sleepTime = 10;
    static const int _columnEdge = 78;
    static const int _rowEdge = 23;
    static const int _allTime = 15;
    static const int allDirection = 4;
    static const int maxIntegral = 300;

    int integral;
    int moveRow[ 4 ] = { -1, 0, 1, 0 };
    int moveColumn[ 4 ] = { 0, 1, 0, -1 };
    bool isUsed[ _rowEdge ][ _columnEdge ];
    pair < int, int > nowPoint, targetPoint, _tmpPoint;
    queue < pair< int, int > > snakeBody;
    int direction, _tmpDirection;

public:
    snake(){
        memset( isUsed, 0, sizeof( isUsed ) );
        direction = 0;
        integral = 1;
        nowPoint.first = targetPoint.first = 15;
        nowPoint.second = targetPoint.second = 40;
        isUsed[ nowPoint.first ][ nowPoint.second ] = true;
        snakeBody.push( nowPoint );
    }

    void gotoxy( int x, int y ){
        COORD pos = { x, y };
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
    }

    void printPoint( int row, int column, bool isPrint )
    {
        gotoxy( column, row );
        printf( "%c", isPrint ? _snakeBody : _cancel );
    }

    void printInformation(){
        gotoxy( integralX, integralY );
        printf( "%s%d", "Player integral is: ", integral );
    }

    bool run(){
        srand( time( 0 ) );

        while( 1 ){
            if( integral >= maxIntegral ){
                return true;
            }

            printInformation();

            while( isUsed[ targetPoint.first ][ targetPoint.second ] ){
                targetPoint.first = ( rand()%( _rowEdge-2 ) ) + 1;
                targetPoint.second = ( rand()%( _columnEdge-2 ) ) + 1;
            }
            printPoint( targetPoint.first, targetPoint.second, true );

            while( nowPoint != targetPoint ){
                _tmpDirection = direction;
                for( int _useTime=0, allTime=_allTime-integral/_sleepTime; _useTime < allTime; ++ _useTime ){
                    if( kbhit() ){
                        char _ch = getch();
                        if( ( _ch == 'w' || _ch == 'W' ) && direction != 2 ){
                            _tmpDirection = 0;
                        }
                        else if( ( _ch == 'd' || _ch == 'D' ) && direction != 3 ){
                            _tmpDirection = 1;
                        }
                        else if( ( _ch == 's' || _ch == 'S' ) && direction != 0 ){
                            _tmpDirection = 2;
                        }
                        else if( ( _ch == 'a' || _ch == 'A' ) && direction != 1 ){
                            _tmpDirection = 3;
                        }
                    }
                    else{
                        Sleep( _sleepTime );
                    }
                }

                direction = _tmpDirection;
                for( int _dire=0; _dire < allDirection; ++ _dire ){
                    if( _dire == direction ){
                        nowPoint.first += moveRow[ _dire ];
                        nowPoint.second += moveColumn[ _dire ];
                        break;
                    }
                }

                if( !isUsed[ nowPoint.first ][ nowPoint.second ] && nowPoint.first > 0 && nowPoint.first < _rowEdge && nowPoint.second > 0 && nowPoint.second <_columnEdge ){
                    snakeBody.push( nowPoint );
                    if( nowPoint != targetPoint ){
                        printPoint( nowPoint.first, nowPoint.second, true );
                        isUsed[ nowPoint.first ][ nowPoint.second ] = true;
                        printPoint( snakeBody.front().first, snakeBody.front().second, false );
                        isUsed[ snakeBody.front().first ][ snakeBody.front().second ] = false;
                        snakeBody.pop();
                    }
                    else{
                        isUsed[ nowPoint.first ][ nowPoint.second ] = true;
                        ++ integral;
                    }
                }
                else{
                    return false;
                }
            }

        }
    }
};

int main()
{
    unit_test();
    return 0;
}


void unit_test()
{
    snake _test;
    _test.run();

//    snake _test;
//    _test.printPoint( 3, 0, 1 );
//    _test.printPoint( 3, 1, 1 );
//    _test.printPoint( 2, 1, 1 );
//    Sleep( 1000 );
//    _test.printPoint( 2, 1, 0 );

//    const int all = 80;
//    snake _test;
//    srand( time( NULL ) );
//    while( 1 ){
//        Sleep( 50 );
//        _test.print( rand()%all, rand()%25, rand()&1 );
//    }


//    const int everySleepTime = 15;
//    const int allTime = 10000;
//    for( int i=0; i < allTime; ++ i ){
//        if( kbhit() ){
//            char _ch = getch();
//            putchar( _ch );
//        }
//        else{
//            Sleep( everySleepTime );
//        }
//    }

}

```
