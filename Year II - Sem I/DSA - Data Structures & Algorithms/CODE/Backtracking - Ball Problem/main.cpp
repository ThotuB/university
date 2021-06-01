#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

unsigned Map[10][10];
unsigned rows, cols;

void read_map(ifstream &in){
    in >> rows >> cols;
    for (unsigned i = 0 ; i < rows ; i++){
        for (unsigned j = 0 ; j < cols ; j++){
            in >> Map[i][j];
        }
    }
}

void print_map(){
    for (unsigned i = 0 ; i < rows ; i++){
        for (unsigned j = 0 ; j < cols ; j++){
            cout << Map[i][j] << " ";
        }
        cout << '\n';
    }
}

bool valid(int x, int y, int nextX, int nextY){
    if ( ( nextX == cols ) || ( nextX == -1 ) || ( nextY == rows ) || ( nextY == -1 ) ) {
        return true;
    }
    if ( Map[nextY][nextX] < Map[y][x] ){
        return true;
    }
    return false;
}

bool solution(deque<pair<int, int>> path){
    int x = path.back().first;
    int y = path.back().second;
    // OUT OF BOUNDS
    if ( ( x == cols ) || ( x == -1 ) || ( y == rows ) || ( y == -1 ) ) {
        return true;
    }
    return false;
}

void print_path(deque<pair<int, int>> path){
    for (unsigned i = 0 ; i < path.size() ; i++){
        cout << "(" << path[i].second+1 << ", " << path[i].first+1 << ")-" << Map[path[i].second][path[i].first] << " ";
    }
    cout << '\n';
}

void ball_problem(int x, int y, unsigned step, deque<pair<int, int>> path){
    static int dirX[] = {1, 0, -1, 0};
    static int dirY[] = {0, 1, 0, -1};

    for (unsigned dir = 0 ; dir < 4 ; dir++){
        int nextX = x + dirX[dir];
        int nextY = y + dirY[dir];

        if ( valid(x, y, nextX, nextY) ){
            path.push_back(pair<int, int>(nextX, nextY));

            if ( solution(path) ){
                print_path(path);
            }
            else {
                ball_problem(nextX, nextY, step+1, path);
            }

            path.pop_back();
        }
    }
}

int main(){
    ifstream fin("mat.txt");
    read_map(fin);
    print_map();

    deque<pair<int, int>> path;
    path.push_back(pair<int, int>(1, 1));
    ball_problem(1, 1, 0, path);
}