#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <algorithm>
#include "gtest/gtest.h"
using namespace std;

class CustomTestListener:public ::testing::EmptyTestEventListener{
private:
    int totaltests = 10;

public:
    int failtests = 0;

    void OnTestPartResult(const ::testing::TestPartResult& test_part_result){
        if (test_part_result.type() == ::testing::TestPartResult::kNonFatalFailure) {
                // 每次断言成功时增加计数器
                failtests++;
        }
    }
};


class Solution72{
public:
    int minDistance(string word1, string word2) {
        // cout << "minDistance" << endl;
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        for (int i=1; i < dp.size(); i++) dp[i][0] = i;
        for (int i=1; i < dp[0].size(); i++) dp[0][i] = i;

        for (int i=1; i < dp.size(); i++){
            for (int j=1; j < dp[i].size(); j++){
                if (word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1];
                else{
                    dp[i][j] = min(min(dp[i][j-1], dp[i-1][j]), dp[i-1][j-1]) + 1;
                }
            }
        }

        return dp[word1.size()][word2.size()];
    }
};


class Solution2697{
public:
    string makeSmallestPalindrome(string s) {
        int n_size = s.size(), res = 0;
        for (int i =0; i < n_size/2; i++){
            if (s[i] == s[n_size - i - 1]) continue;
            else if (s[i] < s[n_size - i - 1]) {
                s[n_size - i - 1] = s[i];
                res++;
            }
            else{
                s[i] = s[n_size - i - 1];
                res++;
            }
        }
        // cout << s << s[0] << res << endl;
        return s;
    }
};


class Solution2008 {
public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        sort(rides.begin(), rides.end(), [](vector<int> a, vector<int> b ){ return a[1] < b[1];});
        // for (int i=0; i < rides.size(); i++) cout << rides[i][0] << " " << rides[i][1] << " " << rides[i][2] << endl;
        vector<int> dp(rides.size()+1, 0);
        for (int i=0; i < rides.size(); i++){
            int j=i-1;
            for (; j >= 0; j--){
                if (rides[i][0] >= rides[j][1]) break;
            }
            dp[i+1] = max(dp[j + 1] + rides[i][2] + rides[i][1] - rides[i][0], dp[i]);
        }
        for (int i=0; i < dp.size(); i++) cout << dp[i] << " ";
        return dp[rides.size()];
    }
}; 


struct TreeNode{
    TreeNode():val(0), left(nullptr), right(nullptr){}
    TreeNode(int v):val(v), left(nullptr), right(nullptr){}
    TreeNode(int v, TreeNode* l, TreeNode* r):val(0), left(l), right(r){}
    int val;
    TreeNode* left;
    TreeNode* right;
};

class Solution2415{
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        dfs(1, root->left, root->right);
        return root;
    }

    void dfs(int level, TreeNode* root1, TreeNode* root2){
        if (root1 == nullptr) return;

        if (level % 2 == 1){
            swap(root1->val, root2->val);
        }

        dfs(level+1, root1->left, root2->right);
        dfs(level+1, root2->left, root1->right);
    }


};

