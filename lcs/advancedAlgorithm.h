#pragma once

#include <vector>
#include <cstdio>
#include <string>


std::vector<std::vector<unsigned int> > calculateSuffixPrefixLCS (const std::string &a,
                                                                  const std::string &b)
{
    std::vector<std::vector<unsigned int> > ans;
    ans.resize(a.size());
    for (size_t i = 0;i < ans.size();i++){
        ans[i].resize(b.size());
    }
    std::vector <std::pair<unsigned int, unsigned int> > curDp, prevDp;
    curDp.resize(b.size());
    prevDp.resize(b.size());

    for (size_t i = 0;i < a.size();i++){
        for (size_t j = 0;j < b.size();j++){
            unsigned int u;
            if (j == 0){
                u = i + 1;
            }
            else{
                u = curDp[j - 1].first;
            }
            unsigned int l = prevDp[j].second;
            if (u > l && a[i] != b[j]){
                curDp[j].first = u;
                curDp[j].second = l;
            }
            else{
                curDp[j].first = l;
                curDp[j].second = u;
            }
        }
        std::swap(curDp, prevDp);
    }
    for (size_t j = 0;j < b.size();j++){
        for (size_t i = 0;i < prevDp[j].second;i++){
            if (j == 0){
                ans[i][j] = 1;
            }
            else{
                ans[i][j] = ans[i][j - 1] + 1;
            }
        }
        for (size_t i = prevDp[j].second;i < a.size();i++){
            if (j == 0){
                ans[i][j] = 0;
            }
            else{
                ans[i][j] = ans[i][j - 1];
            }
        }
    }
    return ans;
}