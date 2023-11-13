#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

// 8 puzzle

array<int, 9> goal, initial_state;

int calculate_mismatch(array<int, 9> state) {
    int cnt = 0;
    for ( int i = 0 ; i < 9 ; i++ )
        cnt += (goal[i] != state[i]);

    return cnt;
}

int calculate_manhatan(array<int, 9> state) {
    int cnt = 0;
    
    map<int, pair<int, int>>mp, mp1;
    for( int i=0 ; i<9 ; i++ ){
        int val = state[i];
        int x = i / 3;
        int y = i % 3;
        mp[val] = {x, y};
    }

    for( int i=0 ; i<9 ; i++ ){
        int val = goal[i];
        int x = i / 3;
        int y = i % 3;
        mp1[val] = {x, y};
    }    
    
    for( int i=0 ; i<8 ; i++ )
        cnt += abs(mp[i].first - mp1[i].first) + abs(mp[i].second - mp1[i].second);

    return cnt;
}

void print_state(array<int, 9>&s ){
    for( int i=0 ; i<9 ; i++ )
        cout << s[i] << " \n"[(i+1) % 3 == 0];
    cout << endl;
}


int32_t main()
{
    // input
    for ( int i = 0 ; i < 9 ; i++ )cin >> goal[i];
    for ( int i = 0 ; i < 9 ; i++ )cin >> initial_state[i];

    set<array<int, 9>> visited;
    map<array<int, 9>, array<int, 9>>parent;
    priority_queue<pair<pair<int, int>, array<int, 9>>,
            vector<pair<pair<int, int>, array<int, 9>>>,
           greater<pair<pair<int, int>, array<int, 9>>>
            >pq; // heuristic value + cost, cost, state


    auto push_to_priority_queue = [&](int cost,array<int, 9> &state){
        pq.push({{calculate_mismatch(state) + cost , cost}, state});
    };

    push_to_priority_queue(0, initial_state);
    parent[initial_state] = initial_state;
    visited.insert(initial_state);

    int cnt = 0;
    while (pq.size()) {
        cnt++;
        auto [p, state] = pq.top();
        pq.pop();

        auto [total, cost]  = p;

        if( state == goal ){
            break;;
        }

        int empty = -1;
        for( int i=0 ; i<9 ; i++ )if(state[i] == 0)empty = i;

        int x = empty / 3, y = empty % 3;
        auto now = state;

        // up
        if( (x-1) > -1 ){
            int pos = (x-1) * 3 + y;
            swap(state[pos], state[empty]);
            if(!visited.count(state)){
                push_to_priority_queue(cost + 1, state);
                parent[state] = now;
                visited.insert(state);
            }
            swap(state[pos], state[empty]);
        }

        //down
        if( (x+1) < 3 ){
            int pos = (x+1) * 3 + y;
            swap(state[pos], state[empty]);            
            if(!visited.count(state)){
                push_to_priority_queue(cost + 1, state);
                parent[state] = now;
                visited.insert(state);
            }
            swap(state[pos], state[empty]);
        }

        // left 
        if( (y-1) > -1 ){
            int pos = (y-1) + x * 3;
            swap(state[pos], state[empty]);
            if(!visited.count(state)){
                push_to_priority_queue(cost + 1, state);
                parent[state] = now;
                visited.insert(state);
            }
            swap(state[pos], state[empty]);
        }

        // right
        if( (y+1) < 3 ){
            int pos = (y+1) + x * 3;
            swap(state[pos], state[empty]);
            if(!visited.count(state)){
                push_to_priority_queue(cost + 1, state);
                parent[state] = now;
                visited.insert(state);
            }
            swap(state[pos], state[empty]);
        }

    }

    vector<array<int, 9>>ans;

    if(goal == parent[goal]){
        cout << "impossible" << endl;
        return 0;
    }

    // backtracking the path
    do{
        ans.push_back(goal);
        goal = parent[goal];
    }while( parent[goal] != goal );
    ans.push_back(goal);

    reverse(ans.begin(), ans.end());
    cout << cnt << endl;
    cout << ans.size() << endl;
    for(auto x : ans)
        print_state(x);

    return 0;
}
