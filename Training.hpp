#ifndef Training_hpp   
#define Training_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Training
{
    public:
        Training();
        void setPokerTraining(string poker_training);
        void setPokerTest(string poker_test);
        vector<vector<int>> HashTraining();
        vector<vector<int>> HashTest();

    private:
        string poker_training;
        string poker_test;

};
// Função hash para pair<int, int>
struct hash_pair {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2; // combinando os hashes
    }
};
#endif