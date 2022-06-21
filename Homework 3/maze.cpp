//#include <iostream>
//#include <stack>
//#include <string>
//using namespace std;
//
//class Coord
//{
//public:
//    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
//    int r() const { return m_r; }
//    int c() const { return m_c; }
//private:
//    int m_r;
//    int m_c;
//};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    
    maze[sr][sc] = '$';

        if (sr == er && sc == ec) {
            return true;
        }

        if (maze[sr][sc - 1] == '.') {          //West
            if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) {
                return true;
            }
        }
        if (maze[sr + 1][sc] == '.') {          //South
            if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)) {
                return true;
            }
        }
        if (maze[sr][sc + 1] == '.') {          //East
            if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) {
                return true;
            }
        }
        if (maze[sr - 1][sc] == '.') {          //North
            if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)) {
                return true;
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