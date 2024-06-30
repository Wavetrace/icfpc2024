#include <iostream>
#include <tuple>
#include <vector>
#include <stack>
#include <string>

using namespace std;

using Maze = vector<vector<char>>;
using Node = tuple<int, int>;

int dbg = 0;

void print_maze(const Maze& maze) {
    for (auto& vec: maze) {
        for (auto& c: vec) {
            cout << c;
        }
        cout << '\n';
    }
}

string to_string(const Node& node) {
    const auto& [row, col] = node;
    string s;
    s += '(';
    s.append(to_string(row));
    s += ',';
    s.append(to_string(col));
    s += ')';

    return s;
}

class DFS {
public:
    DFS(Maze maze);
    string do_dfs();
    Node find_start();
    Node move_from(Node n, char direction);
    char invert_direction(char direction);
    string find_path(Node curr, Node next);
    vector<Node> get_children(Node curr) ;

private:
    Maze maze_;
    Maze visited_;
    Maze parent_direction_; // For each node, record direction to move to get to
                            // parent.
};

DFS::DFS(Maze maze) : maze_(maze) {}

string DFS::do_dfs() {
    const auto& [startrow, startcol] = find_start();

    // vector<char> tmp(maze_[0].size(), 'N'); // 'N' is not visited, 'Q' is in q, 'V' is visited.
    // for (int i = 0; i < maze_.size(); i++) {
    //     visited_.push_back(tmp);
    // }

    visited_ = maze_;

    vector<char> tmp2(maze_[0].size(), '-');
    for (int i = 0; i < maze_.size(); i++) {
        parent_direction_.push_back(tmp2);
    }

    if (dbg) cout << "Found start pos: " << startrow << ',' << startcol << '\n';

    string moves{};
    stack<Node> s;
    auto curr = Node{startrow, startcol};
    s.push(curr);
    visited_[startrow][startcol] = 'Q'; // mark as in-queue
    while (!s.empty()) {
        auto next = s.top();
        s.pop();
        moves.append(find_path(curr, next));
        curr = next;
        vector<Node> children = get_children(curr);
        for (const auto& [row, col]: children) {
            s.push({row, col});
            visited_[row][col] = 'Q';
        }
        visited_[get<0>(curr)][get<1>(curr)] = 'V';
        if (dbg) print_maze(visited_);
    }
    return moves;
}

Node DFS::find_start() {
    int maxrow = maze_.size();
    int maxcol = maze_[0].size();

    for (int row = 0; row < maxrow; row++) {
        for (int col = 0; col < maxcol; col++) {
            if (maze_[row][col] == 'L') return tuple(row, col);
        }
    }
    return Node{-1, -1}; // should not happen
}

Node DFS::move_from(Node n, char direction) {
    const auto [row, col] = n;
    if (direction == 'L') return {row, col-1};
    else if (direction == 'U') return {row-1, col};
    else if (direction == 'R') return {row, col+1};
    else if (direction == 'D') return {row+1, col};
    throw std::runtime_error("unexpected move direction!");
}

char DFS::invert_direction(char direction) {
    switch (direction) {
    case 'L': return 'R';
    case 'U': return 'D';
    case 'R': return 'L';
    case 'D': return 'U';
    default:
        throw std::runtime_error("Unknown direction!");
    }
}

string DFS::find_path(Node curr, Node next)
{
    string path_from_curr_to_next;
    if (curr == next) return {};
    // Use parent direction matrix to traverse back from curr to parent of
    // next.
    const auto [next_row, next_col] = next;
    Node next_parent = move_from(next, parent_direction_[next_row][next_col]);

    while (curr != next_parent) {
        const auto& [row, col] = curr;
        char direction = parent_direction_[row][col];
        curr = move_from(curr, direction);
        path_from_curr_to_next += direction;
    }
    // Add step from next_parent to next
    path_from_curr_to_next +=
        invert_direction(parent_direction_[next_row][next_col]);

    return path_from_curr_to_next;
}

vector<Node> DFS::get_children(Node curr) {
    vector<Node> children;
    // check left, up, right, down
    const auto& [row, col] = curr;
    // left
    if (col-1 >= 0) {
        if (maze_[row][col-1] == '.') {
            if (visited_[row][col-1] == '.') {
                children.push_back(Node{row, col-1});
                parent_direction_[row][col-1] = 'R';
            }
        }
    }
    // up
    if (row-1 >= 0) {
        if (maze_[row-1][col] == '.') {
            if (visited_[row-1][col] == '.') {
                children.push_back(Node{row-1, col});
                parent_direction_[row-1][col] = 'D';
            }
        }
    }
    // right
    if (col+1 < maze_[0].size()) {
        if (maze_[row][col+1] == '.') {
            if (visited_[row][col+1] == '.') {
                children.push_back(Node{row, col+1});
                parent_direction_[row][col+1] = 'L';
            }
        }
    }
    // down
    if (row+1 < maze_.size()) {
        if (maze_[row+1][col] == '.') {
            if (visited_[row+1][col] == '.') {
                children.push_back(Node{row+1, col});
                parent_direction_[row+1][col] = 'U';
            }
        }
    }

    if (dbg)
        cout << to_string(curr) << " has children ";
    for (const auto& node: children) {
        if (dbg) cout << to_string(node) << ',';
    }
    if (dbg) cout << '\n';
    return children;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        if (string(argv[1]) == "dbg")
            dbg = 1;
    }
    Maze maze;
    vector<char> row{};
    char ch;
    // Read maze from file/stdin
    while (ch = cin.get()) {
        if (cin.eof()) break;
        if (ch == '\n') {
            if (row.size() == 0) break;
            maze.push_back(std::move(row));
            row = {};
        }
        else row.push_back(ch);
    }

    if (dbg) cout << "DFS - processing maze:\n";
    if (dbg) print_maze(maze);

    DFS dfs(std::move(maze));
    std::cout << dfs.do_dfs() << '\n';
}
