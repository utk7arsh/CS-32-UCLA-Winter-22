#include <iostream>
#include <stack>
#include <queue>
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
    queue<Coord> q;
    q.push(Coord(sr, sc));
    maze[sr][sc] = '$';

    while (!q.empty()) {
        Coord ctop = q.front();
        q.pop();

        int r = ctop.r();
        int c = ctop.c();

        if (r == er && c == ec) {
            return true;
        }

        if (maze[r][c - 1] == '.') {          //West
            q.push(Coord(r, c - 1));
            maze[r][c - 1] = '$';
        }
        if (maze[r + 1][c] == '.') {          //South
            q.push(Coord(r + 1, c));
            maze[r + 1][c] = '$';
        }
        if (maze[r][c + 1] == '.') {          //East
            q.push(Coord(r, c + 1));
            maze[r][c + 1] = '$';
        }
        if (maze[r - 1][c] == '.') {          //North
            q.push(Coord(r - 1, c));
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
//        "X.X...X..X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10, 10, 4, 6, 1, 1))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}

//#include <queue>
//using namespace std;
//
// 
// Testing a new main
//int main()
//{
//    queue<Coord> coordQueue;   // declare a queue of Coords
//
//    Coord a(5, 6);
//    coordQueue.push(a);           // enqueue item at back of queue
//    coordQueue.push(Coord(3, 4));  // enqueue item at back of queue
//        Coord b = coordQueue.front(); // look at front item
//    coordQueue.pop();             // remove the front item from queue
//    if (coordQueue.empty())       // Is the queue empty?
//        cout << "empty!" << endl;
//    cout << coordQueue.size() << endl; // num of elements
//}