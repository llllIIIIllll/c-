#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> t;
        for (int i = 0; i < numRows; i++)
        {
            vector<int> tmp;
            for (int j = 0; j < i + 1; j++)
            {
                if (j == 0 || j == i)
                    tmp.push_back(1);
                else
                    tmp.push_back(t[i-1][j-1] + t[i-1][j]);
            }
            t.push_back(tmp);
        }
        return t;
    }
    vector<int> getRow(int rowIndex) {
        vector<int> tmp = this->generate(rowIndex).at(rowIndex);
        return tmp;
    }
    

};