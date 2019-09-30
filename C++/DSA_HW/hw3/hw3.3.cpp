#include <bits/stdc++.h>
#include <bits/extc++.h>
#define maxn 20
using namespace std;
using namespace __gnu_pbds;
const long long MIN = -1000;
const long long MAX = 1000;
int n;
uint64_t cardA[maxn];
uint64_t cardB[maxn];
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
gp_hash_table<uint64_t, int, custom_hash> trans_table;
int get_idx(string str) {
    int idx;
    switch(str[1]) {
    case 'A':
        idx = 0;
        break;
    case 'T':
        idx = 36;
        break;
    case 'J':
        idx = 40;
        break;
    case 'Q':
        idx = 44;
        break;
    case 'K':
        idx = 48;
        break;
    default:
        idx = ((str[1] - '0') - 1)<<2;
    }
    switch(str[0]) {
    case 'C':
        break;
    case 'D':
        idx += 1;
        break;
    case 'H':
        idx += 2;
        break;
    case 'S':
        idx += 3;
        break;
    }
    return idx;
}
int get_remaining_points(uint64_t board, bool maxplayer) {
    int sum = 0;
    if (maxplayer) {
        int card = (board & ((1LL<<n) - 1));
        for (int i = 0; i < n; ++i) {
            if (card & 1) {
                sum += (cardA[i]>>2) + 1;
            }
            card >>= 1;
        }
        return -sum;
    }
    else {
        int card = (board & ((1LL<<(n<<1)) - 1))>>n;
        for (int i = 0; i < n; ++i) {
            if (card & 1) {
                sum += (cardB[i]>>2) + 1;
            }
            card >>= 1;
        }
        return sum; 
    }
}
bool is_card_available(uint64_t board, int i, bool maxplayer) {
    int lastc = (board>>((n<<1) + 18));
    if (maxplayer) {
        if ((board & (1LL<<i)) == 0) return false;
        if (lastc == 52) return true; // if lastcard == 52: pass
        if ((lastc % 4) == (cardA[i] % 4))
            return true;
        if ((lastc>>2) + 1 == (cardA[i]>>2) + 1)
            return true;
    }
    else {
        if ((board & (1LL<<(i+n))) == 0) return false;
        if (lastc == 52) return true;
        if ((lastc % 4) == (cardB[i] % 4))
            return true;
        if ((lastc>>2) + 1 == (cardB[i]>>2) + 1)
            return true;
    }
    return false;
}
uint64_t set_board(uint64_t board, int i, bool maxplayer, long long alpha, long long beta) {
    board &= ((1LL<<(n<<1)) - 1LL);
    board += ((long long)maxplayer<<(n<<1));
    board += (beta<<((n<<1) + 2));
    board += (alpha<<((n<<1) + 10));
    board &= ((1LL<<((n<<1) + 18)) - 1LL);
    if (maxplayer) {
        board ^= (1LL<<i);
        board += (cardA[i]<<((n<<1) + 18));
    }
    else {
        board ^= (1LL<<(i+n));
        board += (cardB[i]<<((n<<1) + 18));
    }
    return board;
}
int minimax(uint64_t board, bool maxplayer, long long alpha, long long beta) {
    if (trans_table.find(board) != trans_table.end())
        return trans_table[board];
    if ((board & ((1LL<<n) - 1LL)) == 0 
        || ((board & ((1LL<<(n<<1)) - 1LL))>>n) == 0) {        
        trans_table[board] = get_remaining_points(board, maxplayer);
        return trans_table[board];
    }
    int best_score = (maxplayer == true) ? MIN: MAX;
    bool flag = false;
    for (int i = 0; i < n; ++i) {
        if (!is_card_available(board, i, maxplayer)) continue;
        flag = true;
        uint64_t cur_board = set_board(board, i, maxplayer, alpha, beta);
        if (maxplayer) {
            int score = minimax(cur_board, false, alpha, beta);
            best_score = max(best_score, score); 
            alpha = max(alpha, (long long)best_score);
            if (beta <= alpha) {
                break;
            }
        }
        else {    
            int score = minimax(cur_board, true, alpha, beta);
            best_score = min(best_score, score);
            beta = min(beta, (long long)best_score);
            if (beta <= alpha) {
                break; 
            }
        }
    }
    if (!flag) {
        uint64_t cur_board = board & ((1LL<<(n<<1)) - 1LL);
        cur_board += ((long long)maxplayer<<(n<<1));
        cur_board += (beta<<((n<<1) + 2));
        cur_board += (alpha<<((n<<1) + 10));
        cur_board &= ((1LL<<((n<<1) + 18)) - 1LL);
        cur_board += (52LL<<((n<<1) + 18));
        if (maxplayer) {
            int score = minimax(cur_board, false, alpha, beta);
            best_score = max(best_score, score);
        }
        else {
            int score = minimax(cur_board, true, alpha, beta);
            best_score = min(best_score, score);
        }
    }
    if (rand() & 1) trans_table[board] = best_score;
    return best_score;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    string str;
    uint64_t board = (1LL<<(n<<1)) - 1LL;
    board += (1LL<<(n<<1));
    board += (MAX<<((n<<1) + 2));
    board += (MIN<<((n<<1) + 10));
    board &= ((1LL<<((n<<1) + 18)) - 1LL);
    board += (52LL<<((n<<1) + 18));
    for (int i = 0; i < n; ++i) {
        cin >> str;
        cardA[i] = get_idx(str);
    }
    for (int i = 0; i < n; ++i) {
        cin >> str;
        cardB[i] = get_idx(str);
    }
    int score = minimax(board, true, MIN, MAX);
    if (score > 0) {
        cout << "Alice" << '\n' << score << '\n';
    }
    else {
        cout << "Bob" << '\n' << -score << '\n';
    }
    return 0;
}
/*
input:
15
SK S5 H4 DT DK H5 H3 SQ S9 D9 C5 C4 CJ H6 C8
D2 SA CQ S3 S2 H7 C6 S8 S7 D6 C7 H2 DQ D3 D5

output:
Bob
3
*/