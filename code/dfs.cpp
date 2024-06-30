#include <iostream>
#include <tuple>
#include <vector>
#include <stack>

using namespace std;

using Maze = vector<vector<char>>;
using Node = tuple<int, int>;

tuple<int, int> find_start(const Maze& m) {
    int maxrow = m.size();
    int maxcol = m[0].size();

    for (int row = 0; row < maxrow; row++) {
        for (int col = 0; col < maxcol; col++) {
            if (m[row][col] == 'L') return tuple(row, col);
        }
    }
    return Node{-1, -1}; // should not happen
}

Node move_from(Node n, char direction) {
    const auto [row, col] = n;
    if (direction == 'L') return {row, col-1};
    else if (direction == 'U') return {row-1, col};
    else if (direction == 'R') return {row, col+1};
    else if (direction == 'D') return {row+1, col};
    throw std::runtime_error("unexpected move direction!");
}

char invert_directon(char direction) {
    switch (direction) {
    case 'L': return 'R';
    case 'U': return 'D';
    case 'R': return 'L';
    case 'D': return 'U';
    default:
        throw std::runtime_error("Unknown direction!");
    }
}

string find_path(Node curr, Node next)
{
    string path_from_curr_to_next;
    if (curr == next) return {};
    // Use parent direction matrix to traverse back from curr to parent of
    // next.
    const auto [next_row, next_col] = next;
    Node next_parent = move_from(next, parent_direction[next_row][next_col]);

    for (while curr != next_parent) {
        const auto& [row, col] = curr;
        char direction = parent_direction[row][col];
        curr = move_from(curr, direction);
        path_from_curr_to_next.append(direction);
    }
    // Add step from next_parent to next
    path_from_curr_to_next.append(
        invert_direction(parent_direction[next_row][next_col]));

    return path_from_curr_to_next;
}

vector<Node> get_children(Node curr) {
    vector<Node> children;
    // check left, up, right, down
    const auto& [row, col] = curr;
    // left
    if (col-1 >= 0) {
        if (maze[row][col-1] == '.') {
            if (visited[row][col-1] == 'N') {
                children.push_back(Node{row, col-1});
                parent_direction(row, col) = 'R';
            }
        }
    }
    // up
    if (row-1 >= 0) {
        if (maze[row-1][col] == '.') {
            if (visited[row-1][col] == 'N') {
                children.push_back(Node{row-1, col});
                parent_direction(row-1, col) = 'D';
            }
        }
    }
    // right
    if (col+1 < maze[0].size()) {
        if (maze[row][col+1] == '.') {
            if (visited[row][col+1] == 'N') {
                children.push_back(Node{row, col+1});
                parent_direction(row, col) = 'L';
            }
        }
    }
    // down
    if (row+1 < maze.size()) {
        if (maze[row+1][col] == '.') {
            if (visited[row+1][col] == 'N') {
                children.push_back(Node{row+1, col});
                parent_direction(row+1, col) = 'U';
            }
        }
    }

    return children;
}

int main() {
    Maze maze;
    vector<char> row{};
    char ch;
    while (ch = cin.get()) {
        if (cin.eof()) break;
        if (ch == '\n') {
            maze.push_back(std::move(row));
            row = {};
        }
        else row.push_back(ch);
    }

    for (auto& vec: maze) {
        for (auto& c: vec) {
            cout << c;
        }
        cout << '\n';
    }

    const auto& [startrow, startcol] = find_start(maze);
    Maze visited;
    Maze parent_direction; // For each node, record direction to move to get to parent.
    vector<char> tmp(maze[0].size(), 'N'); // 'N' is not visited, 'Q' is in q, 'V' is visited.
    for (int i = 0; i < maze.size(); i++) {
        visited.push_back(tmp);
    }

    cout << "Found start pos: " << startrow << ',' << startcol << '\n';

    string moves{};
    stack<Node> s;
    auto curr = Node{startrow, startcol};
    s.push(curr);
    visited[startrow][startcol] = 'Q'; // mark as in-queue
    while (!s.empty()) {
        auto next = s.top();
        s.pop();
        //if (visited[get<0>(next)][get<1>(next)] == 'V') continue;
        moves.append(find_path(curr, next);
        curr = next;
        vector<Node> children = get_children(curr);
        for (const auto& [row, col]: children) {
            s.push({row, col});
            visited[row][col] = 'Q';
        }
        visited[get<0>(curr)][get<1>(curr)] = 'V';
    }
}
