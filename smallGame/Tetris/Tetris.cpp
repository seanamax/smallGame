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

// 坐标点
class _Pair{
public:
    short _col;
    short _line;
};

// 旋转 单元区域
class unitSpinTetris{
private:
    Pair _nowPoint;
    unitTetris _matrix;

public:
    // 旋转 单元 俄罗斯方块
    unitSpinTetris( const unitTetris & matrix, const Pair spinCentre ){
        // 做 旋转 运算
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

    // 打印 方块， 主要做 调试用而已
    unitTetris show(){
        for( int i=0; i < unitTetrisSize; ++ i ){
            for( int j=0; j < unitTetrisSize; ++ j ){
                _matrix._matrix[i][j] ? putchar( '#' ) : putchar( ' ' );
            }putchar( '\n' );
        }

        return _matrix;
    }

    // 返回 单元 俄罗斯方块
    unitTetris unitTetris_matrix(){
        return _matrix;
    }
};

// 调用 系统接口， 例如 光标重定向
class _sysAPI{
public:
    // 光标重定向 到 指定的 (x,y)
    void cursorGotoXY( int lines, int cols ){
        COORD loc;
        HANDLE hStdout;
        loc.X = cols;
        loc.Y = lines;
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition( hStdout, loc );
    }

    // 设置 标题
    void setConSoleTitle( char * title ){
        SetConsoleTitle( title );
    }

    // 设置 窗口 大小
    void setConsoleSize( int line, int col ){
        HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
        COORD pos = { line, col };
        SMALL_RECT rc = { 0, 0, line-1, col-1 };       // 坐标从0开始

        // 这个函数的接口做的很奇怪， 不能传 结构体 Pair 进去， 传进去了没效果
        // 而且， SetConsoleScreenBufferSize() 函数必须 调用两次，不然会出现 滚动条
        SetConsoleScreenBufferSize( hOut, pos );
        SetConsoleWindowInfo( hOut, true, &rc );
        SetConsoleScreenBufferSize( hOut, pos );
    }
};

// 打印 单元区域
class _printUnitTetris{
// 调用系统接口， 例如
private:
    _sysAPI sysAPI;

public:
    // 打印 单元俄罗斯方块 到指定位置， 指定开始位置为 startPoint
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

// 撤销 打印单元区域
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

// 视图类
class viewTetris{
public:
    // 实例化 打印 单元俄罗斯方块
    _printUnitTetris print;
    // 实例化 撤销 打印 单元俄罗斯方块
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



