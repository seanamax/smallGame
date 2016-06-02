#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

namespace Tetris
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

// �����
class _Pair{
public:
    short _col;
    short _line;
};

// ��ת ��Ԫ����
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

// ���� ϵͳ�ӿڣ� ���� ����ض���
class _sysAPI{
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

    // ���� ����
    void setConSoleTitle( char * title ){
        SetConsoleTitle( title );
    }

    // ���� ���� ��С
    void setConsoleSize( int line, int col ){
        HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
        COORD pos = { line, col };
        SMALL_RECT rc = { 0, 0, line-1, col-1 };       // �����0��ʼ

        // ��������Ľӿ����ĺ���֣� ���ܴ� �ṹ�� Pair ��ȥ�� ����ȥ��ûЧ��
        // ���ң� SetConsoleScreenBufferSize() �������� �������Σ���Ȼ����� ������
        SetConsoleScreenBufferSize( hOut, pos );
        SetConsoleWindowInfo( hOut, true, &rc );
        SetConsoleScreenBufferSize( hOut, pos );
    }
};

// ��ӡ ��Ԫ����
class _printUnitTetris{
// ����ϵͳ�ӿڣ� ����
private:
    _sysAPI sysAPI;

public:
    // ��ӡ ��Ԫ����˹���� ��ָ��λ�ã� ָ����ʼλ��Ϊ startPoint
    void printUnitTetris( const unitTetris &tmpUnitTetris, Pair startPoint ){
        for( int tmpLines = startPoint._line, iTmp=0; iTmp < unitTetrisSize; ++ iTmp, ++ tmpLines ){
            for( int tmpCols = startPoint._col, jTmp=0; jTmp < unitTetrisSize; ++ jTmp, ++ tmpCols ){
                sysAPI.cursorGotoXY( tmpLines, tmpCols );
                printFlag( tmpUnitTetris._matrix[ iTmp ][ jTmp ] );
            }
        }
    }

    void printFlag( bool flag ){
        putchar( flag ? '#' : '\0' );
    }
};

// ���� ��ӡ��Ԫ����
class _cancelPrintUnitTetris{
private:
    _sysAPI sysAPI;

public:
    void cancelPrintUnitTetris( Pair startPoint ){
        for( int tmpLines=startPoint._line, iTmp=0; iTmp < unitTetrisSize; ++ iTmp, ++ tmpLines ){
            for( int tmpCols=startPoint._col, jTmp=0; jTmp < unitTetrisSize; ++ jTmp, ++ tmpCols ){
                sysAPI.cursorGotoXY( tmpLines, tmpCols );
                putchar( '\0' );
            }
        }
    }
};

class _interface{
private:
    Pair boundary;
    _sysAPI sysAPI;

public:
    _interface(){
        boundary._col = 60;
        boundary._line = 25;
        printInter();
    }

    void printInter(){
        for( int i=0; i < boundary._line; ++ i ){
            sysAPI.cursorGotoXY( i, 0 );
            putchar( '|' );
            putchar( '|' );
            sysAPI.cursorGotoXY( i, boundary._col-1 );
            putchar( '|' );
            putchar( '|' );
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
    //unitTest();
    //std::cout << "fuck" << std::endl;
    unitTest();
    return 0;
}



void unitTest()
{
//    Tetris::unitTetris tmp;
//    tmp._matrix[0][0] = true;
//    for( int i=0; i < Tetris::unitTetrisSize; ++ i ){
//        for( int j=0; j < Tetris::unitTetrisSize; ++ j ){
//            std::cout << ( tmp._matrix[i][j] == true ? '#' : ' ' );
//        }std::cout << std::endl;
//    }
//
//    //Tetris::unitTetris tmp;
//    tmp.clear();
//    for( int i=0; i < Tetris::unitTetrisSize; ++ i ){
//        for( int j=0; j < Tetris::unitTetrisSize; ++ j ){
//            std::cout << ( tmp._matrix[i][j] == true ? '#' : ' ' );
//        }std::cout << std::endl;
//    }
    //tmp._matrix[0][0] = tmp._matrix[0][1] = tmp._matrix[0][2] = true;
//    Tetris::viewTetris view;
//    Tetris::Pair woord, spinCentre;
//    tmp._matrix[0][0] = tmp._matrix[0][1] = tmp._matrix[1][1] = tmp._matrix[2][1] = tmp._matrix[3][1] = true;
//    spinCentre._col = spinCentre._line = 2;
//    Tetris::unitSpinTetris spin( tmp, spinCentre );
//    woord._col = 20;
//    woord._line = 5;
//    view.print.printUnitTetris( tmp, woord );
//    //spin.unitSpinTetris( tmp, spinCentre );
//    Sleep( 500 );
//    view.print.printUnitTetris( spin.unitTetris_matrix(), woord );
//    Sleep( 500 );
//    view.cancelPrint.cancelPrintUnitTetris( woord );
    //spin.show();


//    Tetris::_interface inter;
//    Tetris::_sysAPI sysAPI;
//    char s[30];
//    SetConsoleTitle( "0" );
//    for( int i=1; i <= 1000; ++ i ){
//        Sleep( 100 );
//        sysAPI.setTitle( itoa( i, s, 10 ) );
//    }

//test();
    //Sleep( 500 );
    Tetris::Pair c;
    c._col = c._line = 30;
    Tetris::_sysAPI sysAPI;
    sysAPI.setConsoleSize( c._col, c._line );
    getchar();
    sysAPI.setConsoleSize( 60, 45 );
//    //Tetris::_sysAPI sysAPI;
//    sysAPI.test( c );
    //test();


//      int i;
//  textmode(C80);
//  window(1,1,80,3);
//  textcolor(YELLOW);
//  textbackground(BLUE);
//  clrscr();
//  getchar();

//getchar();
   // test();
}



