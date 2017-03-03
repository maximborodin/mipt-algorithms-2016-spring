#pragma once

#include <vector>
#include <cstdio>
#include <string>

std::vector<std::vector<unsigned int> > trivialCalculate (const std::string &a,
                                                          const std::string &b)
{
    std::vector<std::vector<unsigned int> > ans;
    ans.resize(a.size());
    for (size_t i = 0;i < a.size();i++){
        ans[i].resize(b.size());
    }
    for (size_t k = 0;k < a.size();k++){
        std::string c = a.substr (k, a.size() - k);
        std::vector<std::vector<unsigned int> >  lcs;
        lcs.resize(c.size());
        for (size_t i = 0;i < c.size();i++){
            lcs[i].resize(b.size());
        }
        for (size_t i = 0;i < c.size();i++){
            for (size_t j = 0;j < b.size();j++){
                if (i == 0 && j == 0) {
                    if (c[i] == b[j]) {
                        lcs[i][j] = 1;
                    }
                    else {
                        lcs[i][j] = 0;
                    }
                }
                else if (i == 0){
                    if (c[i] == b[j]){
                        lcs[i][j] = 1;
                    }
                    else{
                        lcs[i][j] = lcs[i][j - 1];
                    }
                }
                else if (j == 0){
                    if (c[i] == b[j]){
                        lcs[i][j] = 1;
                    }
                    else{
                        lcs[i][j] = lcs[i - 1][j];
                    }
                }
                else if (c[i] == b[j]){
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                }
                else{
                    lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
                }
            }
        }
        for (size_t i = 0;i < b.size();i++){
            ans[k][i] = (lcs.back())[i];
        }
    }
    return ans;
}