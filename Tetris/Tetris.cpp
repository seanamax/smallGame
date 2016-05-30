#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <stack>

namespace smallGame
{
typedef struct _Pair Pair;
const int unitTetrisSize = 4;

class unitTetris{
public:
    bool _matrix[ unitTetrisSize ][ unitTetrisSize ];
    unitTetris(){
        clear();
    }

    void clear(){
        memset( _matrix, 0, sizeof( _matrix ) );
    }
};

class _Pair{
public:
    int _col;
    int _line;
};

class unitSpinTetris{
private:
    Pair _nowPoint;
    unitTetris _matrix;

public:
    // ��ת ��Ԫ ����˹����
    unitSpinTetris( const unitTetris & matrix, const Pair spinCentre ){
        // �� ��ת ����
        for( int i=0; i < unitTetrisSize; ++ i ){
            for( int j=0; j < unitTetrisSize; ++ j ){
                if( matrix._matrix[i][j] ){
                    _nowPoint._col = spinCentre._col + spinCentre._line - i;
                    _nowPoint._line = spinCentre._line - spinCentre._col + j;

                    _matrix._matrix[ _nowPoint._line ][ _nowPoint._col ] = true;
                }
            }
        }
    }

    // ��ӡ ���飬 ��Ҫ�� �����ö���
    unitTetris show(){
        for( int i=0; i < unitTetrisSize; ++ i ){
            for( int j=0; j < unitTetrisSize; ++ j ){
                _matrix._matrix[i][j] ? putchar( '#' ) : putchar( ' ' );
            }putchar( '\n' );
        }

        return _matrix;
    }

    // ���� ��Ԫ ����˹����
    unitTetris unitTetris_matrix(){
        return _matrix;
    }
};

class _printUnitTetris{
public:
    // ����ض��� �� ָ���� (x,y)
    void cursorGotoXY( int lines, int cols ){
        COORD loc;
        HANDLE hStdout;
        loc.X = cols;
        loc.Y = lines;
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition( hStdout, loc );
    }

    // ��ӡ ��Ԫ����˹���� ��ָ��λ�ã� ָ����ʼλ��Ϊ startPoint
    void printUnitTetris( const unitTetris &tmpUnitTetris, Pair startPoint ){
        for( int tmpLines = startPoint._line, iTmp=0; iTmp < unitTetrisSize; ++ iTmp, ++ tmpLines ){
            for( int tmpCols = startPoint._col, jTmp=0; jTmp < unitTetrisSize; ++ jTmp, ++ tmpCols ){
                cursorGotoXY( tmpLines, tmpCols );
                printFlag( tmpUnitTetris._matrix[ iTmp ][ jTmp ] );
            }
        }
    }

    void printFlag( bool flag ){
        putchar( flag ? '#' : '\0' );
    }
};

class _cancelPrintUnitTetris{
public:
    // ����ض��� �� ָ���� (x,y)
    void cursorGotoXY( int lines, int cols ){
        COORD loc;
        HANDLE hStdout;
        loc.X = cols;
        loc.Y = lines;
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition( hStdout, loc );
    }

    void cancelPrintUnitTetris( Pair startPoint ){
        for( int tmpLines=startPoint._line, iTmp=0; iTmp < unitTetrisSize; ++ iTmp, ++ tmpLines ){
            for( int tmpCols=startPoint._col, jTmp=0; jTmp < unitTetrisSize; ++ jTmp, ++ tmpCols ){
                cursorGotoXY( tmpLines, tmpCols );
                putchar( '\0' );
            }
        }
    }
};

// ��ͼ��
class viewTetris{
public:
    // ʵ���� ��ӡ ��Ԫ����˹����
    _printUnitTetris print;
    // ʵ���� ���� ��ӡ ��Ԫ����˹����
    _cancelPrintUnitTetris cancelPrint;
};

}

void unitTest();
int main(void)
{
    unitTest();
    return 0;
}

void unitTest()
{
    smallGame::unitTetris tmp;
//    tmp._matrix[0][0] = true;
//    for( int i=0; i < smallGame::unitTetrisSize; ++ i ){
//        for( int j=0; j < smallGame::unitTetrisSize; ++ j ){
//            std::cout << ( tmp._matrix[i][j] == true ? '#' : ' ' );
//        }std::cout << std::endl;
//    }
//
//    //smallGame::unitTetris tmp;
//    tmp.clear();
//    for( int i=0; i < smallGame::unitTetrisSize; ++ i ){
//        for( int j=0; j < smallGame::unitTetrisSize; ++ j ){
//            std::cout << ( tmp._matrix[i][j] == true ? '#' : ' ' );
//        }std::cout << std::endl;
//    }
    //tmp._matrix[0][0] = tmp._matrix[0][1] = tmp._matrix[0][2] = true;
    smallGame::viewTetris view;
    smallGame::Pair woord, spinCentre;
    tmp._matrix[0][0] = tmp._matrix[0][1] = tmp._matrix[1][1] = tmp._matrix[2][1] = tmp._matrix[3][1] = true;
    spinCentre._col = spinCentre._line = 2;
    smallGame::unitSpinTetris spin( tmp, spinCentre );
    woord._col = 20;
    woord._line = 5;
    view.print.printUnitTetris( tmp, woord );
    //spin.unitSpinTetris( tmp, spinCentre );
    Sleep( 500 );
    view.print.printUnitTetris( spin.unitTetris_matrix(), woord );
    //spin.show();
}
