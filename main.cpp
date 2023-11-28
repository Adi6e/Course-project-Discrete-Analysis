#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

struct coords
{
    double x;
    double y;
};

double euclid_dist(const coords &first, const coords &second)
{
    return sqrt((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));
}

class euristic
{
public:
    int index;
    double path;
    double distance;
    friend bool operator< (const euristic &first, const euristic &second)
    {
        if ((first.path + first.distance) != (second.path + second.distance))
            return (first.path + first.distance) > (second.path + second.distance);
        return first.index < second.index;
    }
    euristic(const int &new_index, const coords &u, const coords &v, const double &new_path)
    {
        index = new_index;
        path = new_path;
        distance = euclid_dist(u, v);
    }
};

double solve(const int u, const int v, int n, const vector<coords> &verticles, const vector<vector<int>> &g)
{
    vector<double> d(n, -10000);
    priority_queue<euristic> pq;
    d[u] = 0;
    pq.push(euristic(u, verticles[u], verticles[v], 0));
    while (!pq.empty())
    {
        euristic tmp = pq.top();
        pq.pop();
        if (tmp.index == v)
            break;
        if (tmp.path > d[tmp.index])
            continue;
        for (int i = 0; i < g[tmp.index].size(); ++i)
        {
            int next_vert = g[tmp.index][i];
            if (d[next_vert] < 0 || (d[tmp.index] + euclid_dist(verticles[tmp.index], verticles[next_vert])) < d[next_vert])
            {
                d[next_vert] = d[tmp.index] + euclid_dist(verticles[tmp.index], verticles[next_vert]);
                pq.push(euristic(next_vert, verticles[next_vert], verticles[v], d[next_vert]));
            }
        }
    }
    return d[v];
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<coords> verticles(n);
    for (auto &i : verticles)
        cin >> i.x >> i.y;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    int q;
    cin >> q;
    while (q)
    {
        int u, v;
        cin >> u >> v;
        double sol = solve(u - 1, v - 1, n, verticles, g);
        if (sol > 0)
            cout << fixed << setprecision(6) << sol << '\n';
        else
            cout << "-1\n";
        --q;
    }
    return 0;
}