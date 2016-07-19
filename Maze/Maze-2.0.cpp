#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <time.h>
#include <windows.h>
#include <queue>
#include <conio.h>

using namespace std;

#define LIMITSTEP 240
#define WALL "■"
#define MOUSE "⊙"
#define ISNULLSTR " "

#define ISWALL '*'
#define ISNULL '#'
#define FLAG '$'
#define PATH '@'
#define ISVISIT '@'
#define UNVISIT '$'
#define ONEPATH '@'

#define QUIT 'q'
#define UP 'w'
#define LEFT 'a'
#define RIGHT 'd'
#define DOWN 's'
#define CHANGE 'p'

#define judge( m )  ( ( m == ISWALL ) ? ( WALL ) : ( ISNULLSTR ) )
#define random_judge( m ) ( ( m > 15000 ) ? ( ISWALL ) : ( ISNULL ) )
#define is_legal_move( lines, cols ) \
        (  is_move( lines, cols ) && m._m[ lines ][ cols ] != ISWALL  )
#define is_move( lines, cols ) \
        ( 0 <= lines && lines <= limitLines && 0 <= cols && cols <= limitCols  )

const int limitCols = 25;
const int limitLines = 20;
const int constBeginCols = limitCols>>1;
const int constBeginLines = limitLines>>1;
const int limitTime = 100;
const int limitDirect = 4;
const int limitNumPath = 10000;
int moveCols[] = { -1, 1, 0, 0 };
int moveLines[] = { 0, 0, 1, -1 };

// 坐标结构
typedef pair< int, int > P;

// 地图
typedef struct _node node;
struct _node{
     unsigned char _m[ limitLines+2 ][ limitCols+2 ];
    _node(){
        memset( _m, ISWALL, sizeof( _m ) );
    }
};

// 存放所有路径的图
typedef struct _path path;
struct _path{
    P * _m[ limitNumPath ];
    int _n[ limitNumPath ];
    P tmpPath[ LIMITSTEP ];
    int tmpStore;
    int store;
    bool isExeed;

    _path(){
        memset( _m, 0, sizeof( _m ) );
        memset( _n, 0, sizeof( _n ) );
        tmpStore = 0;
        store = 0;
        isExeed = false;
    }
};

void gotoXY( short int lines, short int cols );
void printmap( node & m );
void random_map( node & m );
void unitTest();
void random_dfs_map( node & m, node & flag, P pos, int seed );
bool islink( node & m );
void bfs( node & m, node & flag );
void makemap( node & m );
void getXY( P & pos );
void getshortestpath( node & m, node & flag );
void game( node & m );
void edit( node &m );
void dfs( path  & p, node & m, node & flag, P beginPoint );
void printonepath( path & p, int num );
void cancelprintonepath( path & p, int num );
void deletepath( path &p );
void firstinterface();
void editgameinterface();
void firstinterface();
void editgameinterface();
void run();
void playgameinterface();

int main(void)
{
    //unitTest();
    run();
    return 0;
}

void run()
{
    node flag, m;
    path p;
    P pos;
    char ch;

    pos.first = constBeginLines;
    pos.second = constBeginCols;
    bool isEdit = false;

    firstinterface();
    while( 1 ){
        ch = getch();
        firstinterface();
        if( ch == '1' ){
            playgameinterface();
            if( isEdit == true ){
                isEdit = false;
            }
            else{
                makemap( m );
            }

            game( m );
        }

        else if( ch == '2' ){
            editgameinterface();
            while( 1 ){
                ch = getch();
                editgameinterface();
                if( ch == '4' ){
                    break;
                }

                else if( ch == '1' ){
                    makemap( m );
                    edit( m );
                    isEdit = true;
                }

                else if( ch == '2' ){
                    if( islink( m ) ){
                        getshortestpath( m, flag );
                    }
                    else{
                        puts( "The maze is unlink!" );
                    }
                }

                else if( ch == '3' ){
                    if( !islink( m ) ){
                        puts( "The maze is unlink!" );
                        continue;
                    }
                    system( "cls" );
                    printmap( m );

                    memset( &flag, UNVISIT, sizeof( flag ) );
                    dfs( p, m, flag, pos );

                    gotoXY( limitLines+1, 0 );
                    printf( "ALL PATH NUM: %d\n", p.store );
                    for( int i=0; i < p.store; ++ i ){
                        gotoXY( limitLines+1, 30 );
                        printf( "This num of path: %d\n", i+1 );
                        printonepath( p, i );
                        Sleep( 1000 );
                        cancelprintonepath( p, i );
                    }
                }
            }
        }

        else if( ch == '3' ){
            system( "cls" );
            gotoXY( 10, 40 );
            puts( "THE END" );
            exit(0);
        }
    }
}


void editgameinterface()
{
    system( "cls" );
    puts( "Press [1], to edit maze" );
    puts( "Press [2] to test for shortest path in the maze" );
    puts( "Press [3] to test for all path in the maze " );
    puts( "Press [4] to quit" );
}

void firstinterface()
{
    system( "cls" );
    puts( "Press [1], choose play game" );
    puts( "Press [2], choose edit maze" );
    puts( "Press [3], choose quit the game" );
}

void playgameinterface()
{
    system( "cls" );
    printf( "MOVE Tips: 'a' is Left, 's' is Down, 'd' is Right, 'w' is Up \n" );
    puts( "Press any to start game" );
    getch();
}


void unitTest()
{
    node tmp, flag;
    path p;
    P beginPoint;

    makemap( tmp );
    printmap( tmp );
    //bfs( tmp, flag );
    //cout << (int)flag._m[ constBeginLines ][ constBeginCols ] << endl;
    //getshortestpath( tmp, flag );
    //game( tmp );
    //edit( tmp );

    beginPoint.first = constBeginLines;
    beginPoint.second = constBeginCols;
    dfs( p, tmp, flag, beginPoint );

    gotoXY( limitLines+1, 0 );
    printf( "ALL　PATH NUM: %d\n", p.store );

    for( int i=0; i < p.store; ++ i ){
        gotoXY( limitLines+1, 30 );
        printf( "This num of path: %d\n", i+1 );
        printonepath( p, i );
        Sleep( 1000 );
        cancelprintonepath( p, i );
    }

    deletepath( p );
}

void deletepath( path &p )
{
    for( int i=0; i < p.store; ++ i ){
        delete [] p._m[i];
    }
}

void printonepath( path & p, int num )
{
    for( int i=0; i < p._n[num]; ++ i ){
        gotoXY( p._m[num][i].first, ( p._m[num][i].second )<<1 );
        putchar( ONEPATH );
        Sleep( 50 );
    }
}

void cancelprintonepath( path & p, int num )
{
        for( int i=0; i < p._n[num]; ++ i ){
        gotoXY( p._m[num][i].first, ( p._m[num][i].second )<<1 );
        printf( "%s", ISNULLSTR );
        Sleep( 50 );
    }
}

void dfs( path  & p, node & m, node & flag, P beginPoint )
{
    // 若是 超过 总规定 路径 数目， 直接返回
    if( p.isExeed == true || p.store >= limitNumPath ){
        p.isExeed = true;
        return ;
    }

    // 若是 找到 该途径， 进行拷贝处理
    if( beginPoint.first == limitLines && beginPoint.second == limitCols ){
        // 分配 途径 内存 并 拷贝 临时路径
        p._m[ p.store ] = new P [ p.tmpStore ];
        memcpy( p._m[ p.store ], &p.tmpPath, p.tmpStore*sizeof( P ) );
        p._n[ p.store ] = p.tmpStore;

        -- p.tmpStore;
        ++ p.store;
        return ;
    }

    // 进行 深搜 递归 处理
    P pos;
    for( int i=0; i < limitDirect; ++ i ){
        pos.first = beginPoint.first + moveLines[i];
        pos.second = beginPoint.second + moveCols[i];

        if( is_legal_move( pos.first, pos.second ) && flag._m[ pos.first ][ pos.second ] != ISVISIT ){
            p.tmpPath[ p.tmpStore ] = pos;
            flag._m[ pos.first ][ pos.second ] = ISVISIT;
            ++ p.tmpStore;

            dfs( p, m, flag, pos );
            flag._m[ pos.first ][ pos.second ] = UNVISIT;
        }
    }

    -- p.tmpStore;
}

void edit( node &m )
{
    P pos, tmpPos;
    pos.first = constBeginLines;
    pos.second = constBeginCols;
    tmpPos = pos;

    gotoXY( limitLines+2, 0 );
    printf( "MOVE Tips: 'a' is Left, 's' is Down, 'd' is Right, 'w' is Up, 'p' is edit, 'q' is save and quit" );

    gotoXY( pos.first, (pos.second)<<1 );
    while( 1 ){
        char ch = getch();
        if( ch == UP ){
            tmpPos.first = pos.first -1;
            tmpPos.second = pos.second;
        }
        if( ch == UP ){
            tmpPos.first = pos.first -1;
            tmpPos.second = pos.second;
        }

        else if( ch == DOWN ){
            tmpPos.first = pos.first +1;
            tmpPos.second = pos.second;
        }

        else if( ch == LEFT ){
            tmpPos.first = pos.first;
            tmpPos.second = pos.second -1;
        }

        else if( ch == RIGHT ){
            tmpPos.first = pos.first;
            tmpPos.second = pos.second +1;
        }

        else if( ch == QUIT ){
            return;
        }

        else if( ch == CHANGE ){
            m._m[ pos.first ][ pos.second ] = ( m._m[ pos.first ][ pos.second ] == ISWALL ? ( ISNULL ) : ( ISWALL ) );
            gotoXY( pos.first, (pos.second)<<1 );
            printf( "%s", ( m._m[ pos.first ][ pos.second ] == ISWALL ? ( WALL ) : ( ISNULLSTR ) ) );
        }

        if( is_move( tmpPos.first, tmpPos.second ) ){
            pos = tmpPos;
            gotoXY( pos.first, (pos.second)<<1 );
        }
    }
}

void game( node & m )
{
    //system( "cls" );
    gotoXY( limitLines+2, 0 );
    printf( "MOVE Tips: 'a' is Left, 's' is Down, 'd' is Right, 'w' is Up " );

    P tmpPos, pos, timePos;
    timePos.first = 5;
    timePos.second = limitCols+2;
    long long gameTime = limitTime*1000;
    tmpPos.first = constBeginLines;
    tmpPos.second = constBeginCols;

    pos = tmpPos;
    gotoXY( tmpPos.first, (tmpPos.second)<<1 );
    while( !( pos.first == limitLines && pos.second == limitCols ) ){
        if( !gameTime ){
            system( "cls" );
            puts( "You lose the game !" );
            return ;
        }

        gotoXY( pos.first, (pos.second)<<1 );
        if( kbhit() ){
            char ch = getch();

            if( ch == UP ){
                tmpPos.first = pos.first -1;
                tmpPos.second = pos.second;
            }
            else if( ch == DOWN ){
                tmpPos.first = pos.first +1;
                tmpPos.second = pos.second;
            }
            else if( ch == LEFT ){
                tmpPos.first = pos.first;
                tmpPos.second = pos.second -1;
            }
            else if( ch == RIGHT ){
                tmpPos.first = pos.first;
                tmpPos.second = pos.second +1;
            }

            if( is_legal_move( tmpPos.first, tmpPos.second ) ){
                gotoXY( pos.first, (pos.second)<<1 );
                printf( "%s", ISNULLSTR );

                gotoXY( tmpPos.first, (tmpPos.second)<<1 );
                printf( "%s", MOUSE );

                pos = tmpPos;
            }
        }

        Sleep(1);
        -- gameTime;
        gotoXY( timePos.first, (timePos.second)<<1 );
        printf( "Time: %7I64d (ms)", gameTime );
    }

    system( "cls" );
    puts( "You win the game !" );
}

void getshortestpath( node & m, node & flag )
{
    P pos, tmpPos, minPos;
    pos.first = constBeginLines;
    pos.second = constBeginCols;

    system( "cls" );
    printmap( m );

    bfs( m, flag );
    while( !( pos.first == limitLines && pos.second == limitCols ) ){
        minPos = pos;

        for( int i=0; i < limitDirect; ++ i ){
            tmpPos.first = pos.first + moveLines[i];
            tmpPos.second = pos.second + moveCols[i];

            if( 0 <= tmpPos.first && tmpPos.first <= limitLines
                && 0 <= tmpPos.second && tmpPos.second <= limitCols
                && m._m[ tmpPos.first ][ tmpPos.second ] != ISWALL
                && flag._m[ tmpPos.first ][ tmpPos.second ] < flag._m[ minPos.first ][ minPos.second ] ){

                minPos = tmpPos;
            }
        }

        pos = minPos;
        gotoXY( minPos.first, (minPos.second)<<1 );
        putchar( PATH );
    }
}

void makemap( node & m )
{
    while( 1 ){
        node tmp;
        random_map( tmp );

        for( int i=0; i < 2; ++ i ){
            if( islink( tmp ) ){
                system( "cls" );
                printmap( tmp );
                //cout << t << endl;
                m = tmp;
                return;
            }
            for( int j=0; j < 10; ++ j ){
                P pos;
                pos.first = ( rand()%( limitLines-2 ) ) + 1;
                pos.second = ( rand()%( limitCols-2 ) ) + 1;
                while( tmp._m[pos.first][pos.second] != ISWALL  ){
                    pos.first = ( rand()%( limitLines-2 ) ) + 1;
                    pos.second = ( rand()%( limitCols-2 ) ) + 1;
                }

                tmp._m[pos.first][pos.second] = ISNULL;
            }
            //++ t;
        }//++ t;
    }
}

void getXY( P & pos )
{
    // 获得句柄， 获得 光标位置
    HANDLE hStdout;
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &pBuffer);

    pos.first = pBuffer.dwCursorPosition.Y;
    pos.second = pBuffer.dwCursorPosition.X;
}

bool islink( node & m )
{
    node flag;
    bfs( m, flag );

    return flag._m[ constBeginLines ][ constBeginCols ] != LIMITSTEP;
}

void bfs( node & m, node & flag )
{
    P pos, tmpPos;
    queue < P > que;

    memset( &flag, LIMITSTEP, sizeof( flag ) );
    pos.first = limitLines;
    pos.second = limitCols;
    flag._m[ pos.first ][ pos.second ] = 0;
    que.push( pos );

    while( que.size() ){
        pos = que.front();
        que.pop();

        for( int i=0; i < limitDirect; ++ i ){
            tmpPos.first = pos.first + moveLines[i];
            tmpPos.second = pos.second + moveCols[i];

            if( 0 <= tmpPos.first && tmpPos.first <= limitLines
                && 0 <= tmpPos.second && tmpPos.second <= limitCols
                && m._m[ tmpPos.first ][ tmpPos.second ] != ISWALL && flag._m[ tmpPos.first ][ tmpPos.second ] == LIMITSTEP ){

                  flag._m[ tmpPos.first ][ tmpPos.second ] = flag._m[ pos.first ][ pos.second ] + 1;
                  que.push( tmpPos );
            }
        }
    }
}

void gotoXY( short int lines, short int cols )
{
    COORD pos = { cols, lines };
    HANDLE thisConsoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleCursorPosition( thisConsoleHandle, pos );
}

void printmap( node & m )
{
    for( int i=0; i <= limitLines; ++ i ){
        for( int j=0; j <= limitCols; ++ j ){
            gotoXY( i, j<<1 );
            printf( "%s", judge( m._m[i][j] ) );
        }
    }

    gotoXY( constBeginLines, constBeginCols<<1 );
    printf( "%s", MOUSE );
    gotoXY( limitLines, limitCols );
}

void random_map( node & m )
{
    int seed = time( NULL );
    srand( seed );
    node flag;
    P randPos;

    // 生成一个合适的随机点
    for( int i=0; i < 1; ++ i ){
        randPos.first = rand()%limitLines;
        randPos.second = rand()%limitCols;
    }

    random_dfs_map( m, flag, randPos, rand() );

      //围成一圈
    for( int i=0; i < limitCols+1; ++ i ){
        m._m[0][i] = ISWALL;
        m._m[limitLines][i] = ISWALL;
    }

    for( int i=0; i < limitLines+1; ++ i ){
        m._m[i][0] = ISWALL;
        m._m[i][limitCols] = ISWALL;
    }

    // 打开右下方接口
    m._m[limitLines-1][limitCols-1] = ISNULL;
    m._m[limitLines-2][limitCols-1] = ISNULL;
    m._m[limitLines-1][limitCols-2] = ISNULL;
    m._m[limitLines][limitCols] = ISNULL;
    m._m[limitLines-1][limitCols] = ISNULL;
    m._m[limitLines][limitCols-1] = ISNULL;
    // 标记 起始点
    m._m[ constBeginLines ][ constBeginCols ] = ISNULL;
}

void random_dfs_map( node & m, node & flag, P pos, int seed )
{
    if( flag._m[ pos.first ][ pos.second ] != FLAG ){
        flag._m[ pos.first ][ pos.second ] = FLAG;
        P tmpPos1, tmpPos2, posArray[ limitDirect ][2];
        int tmpDirect;
        srand( seed );


        for( int i=0; i < limitDirect; ++ i ){
            int k = 0;
            for( int j=0; j < limitDirect; ++ j ){
                tmpPos1.first = pos.first + moveCols[j];
                tmpPos1.second = pos.second + moveLines[j];
                tmpPos2.first = tmpPos1.first + moveCols[j];
                tmpPos2.second = tmpPos1.second + moveLines[j];

                if( 0 <= tmpPos2.first && tmpPos2.first < limitLines
                    && 0 <= tmpPos2.second && tmpPos2.second < limitCols
                    && flag._m[ tmpPos2.first ][ tmpPos2.second ] != FLAG ){

                        posArray[ k ][ 0 ] = tmpPos1;
                        posArray[ k ][ 1 ] = tmpPos2;
                        ++ k;
                }
            }

            if( k ){
                tmpDirect = rand()%k;
                m._m[ posArray[ tmpDirect ][ 0 ].first ][ posArray[ tmpDirect ][ 0 ].second ] = ISNULL;
                m._m[ posArray[ tmpDirect ][ 1 ].first ][ posArray[ tmpDirect ][ 1 ].second ] = ISNULL;

                random_dfs_map( m, flag, posArray[ tmpDirect ][ 1 ], rand() );
            }
            else{
                break;
            }
        }
    }
}

