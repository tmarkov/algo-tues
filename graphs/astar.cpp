#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <string> 

using namespace std;

struct Point
{
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

struct Node {
    int distance;
    Point point;
    string path;
    
    Node(int distance, Point p, string path) : distance(distance), path(path) {
        this->point = Point(p.x, p.y);
    }
};

class Compare
{
private:
    Point target;
public:
    Compare(const Point& target) {
        this->target = Point(target.x, target.y);
    }
    
    bool operator() (const Node& a, const Node& b)
    {
        int cost_a = a.distance + abs(a.point.x - this->target.x) + abs(a.point.y - this->target.y);
        int cost_b = b.distance + abs(b.point.x - this->target.x) + abs(b.point.y - this->target.y);
        
        return cost_a < cost_b;
    }
};

string to_string(Point p) {
    return to_string(p.x) + ' ' + to_string(p.y)+ '\n';
}

int main(void) {
    int dirs[] = {-1, 1};
    
    int x, y, m, n;
    cin >> x >> y;
    Point pacman(x, y);
    cin >> x >> y;
    Point target(x, y);
    cin >> m >> n;
    
    string grid[m];
    for (int i = 0; i < m; i++) {
        cin >> grid[i];
    }
    
    Compare comp(target);
    
    priority_queue<Node, vector<Node>, Compare> pq(comp);
    pq.push(Node(0, pacman, to_string(pacman)));
    
    
    while (pq.top().point.x != target.x || pq.top().point.y != target.y) {
        Node next = pq.top();
        pq.pop();
    
        grid[next.point.x][next.point.y] = '%';
        int dist = next.distance + 1;
        
        for (int dir : dirs) {
            x = next.point.x + dir;
            if (x >= 0 && x < m && grid[x][next.point.y] != '%') {
                Point pn = Point(x, next.point.y);
                pq.push(Node(dist, pn, next.path + to_string(pn)));
            }
            
            y = next.point.y + dir;
            if (y >= 0 && y < n && grid[next.point.x][y] != '%') {
                Point pn = Point(next.point.x, y);
                pq.push(Node(dist, pn, next.path + to_string(pn)));
            }
        }
    }
    
    cout << pq.top().distance << '\n';
    cout << pq.top().path;
       
    return 0;
}
