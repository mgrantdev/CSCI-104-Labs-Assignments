#include "stones.h"
#include <queue> // to use std::priority_queue
using namespace std;

int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> pq;
    for (int i = 0; i < stones.size(); i++)
    {
        pq.push(stones[i]);
    }
    // this is to prevent infinitive loops
    bool isLastStone = false;
    while (!pq.empty() && !isLastStone)
    {
        isLastStone = pq.size() == 1;
        int stone1 = pq.top();
        pq.pop();
        if (!pq.empty())
        {
            int stone2 = pq.top();
            pq.pop();
            // this is to ensure don't push a stone of weight 0
            if (stone1 != stone2)
            {
                int newStone = (stone1 > stone2) ? stone1 - stone2 : stone2 - stone1;
                pq.push(newStone);
            }
        }
        // this is to prevent the removal of last stone
        else pq.push(stone1);
    }
    return pq.empty() ? 0 : pq.top();
}
