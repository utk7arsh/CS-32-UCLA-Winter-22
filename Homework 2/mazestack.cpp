#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    stack<Coord> stk;
    stk.push(Coord(sr, sc));
    maze[sr][sc] = '$';

    while (!stk.empty()) {
        Coord ctop = stk.top();
        stk.pop();

        int r = ctop.r();
        int c = ctop.c();

        if (r == er && c == ec) {
            return true;
        }

        if (maze[r][c - 1] == '.') {          //West
            stk.push(Coord(r, c - 1));
            maze[r][c - 1] = '$';
        }
        if (maze[r + 1][c] == '.') {          //South
            stk.push(Coord(r + 1, c));
            maze[r + 1][c] = '$';
        }
        if (maze[r][c + 1] == '.') {          //East
            stk.push(Coord(r, c + 1));
            maze[r][c + 1] = '$';
        }
        if (maze[r - 1][c] == '.') {          //North
            stk.push(Coord(r - 1, c));
            maze[r - 1][c] = '$';
        }
    }
    return false;

}

//int main()
//{
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X.X..X...X",
//        "X....XXX.X",
//        "X.XXXX.X.X",
//        "X......XXX",
//        "X.XX.X...X",
//        "X.X..X.X.X",
//        "X.X.XXXX.X",
//        "X.X.X....X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10, 10, 8,3 , 8, 5))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}