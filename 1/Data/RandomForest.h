#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include "DecisionTree.h"
using namespace std;

class RandomForest {
public:
    RandomForest(int n_trees, int max_depth) : n_trees(n_trees), max_depth(max_depth) {}

    void fit(const std::vector<std::vector<double>>& X, const std::vector<int>& y) {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = 0; i < n_trees; ++i) {
            // Bootstrap sampling
            std::vector<std::vector<double>> X_sample;
            std::vector<int> y_sample;
            for (size_t j = 0; j < X.size(); ++j) {
                int idx = gen() % X.size();
                X_sample.push_back(X[idx]);
                y_sample.push_back(y[idx]);
            }

            DecisionTree tree(max_depth);
            tree.fit(X_sample, y_sample);
            trees.push_back(tree);
        }
    }

    int predict(const std::vector<double>& x) const {
        std::map<int, int> votes;
        for (const auto& tree : trees) {
            int prediction = tree.predict(x);
            votes[prediction]++;
        }

        int majority_vote = -1;
        int max_votes = 0;
        for (const auto& vote : votes) {
            if (vote.second > max_votes) {
                max_votes = vote.second;
                majority_vote = vote.first;
            }
        }
        return majority_vote;
    }
    void splitFeaturesAndLabels(const vector<vector<double>>& df, vector<vector<double>>& X, vector<int>& y) {
        if (df.empty()) return;

        size_t n_samples = df.size();
        size_t n_features = df[0].size() - 1; // Assuming the last column is the label

        X.resize(n_samples, vector<double>(n_features));
        y.resize(n_samples);
        cout << n_samples << endl;
        for (size_t i = 0; i < n_samples; ++i) {
            for (size_t j = 0; j < n_features; ++j) {
                X[i][j] = df[i][j];
            }
            y[i] = static_cast<int>(df[i][n_features]);
            cout << y[i] << " ";
        }
    }
    vector<std::vector<int>> kFoldSplit(int n_samples, int k) {
        std::vector<int> indices(n_samples);
        std::iota(indices.begin(), indices.end(), 0);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(indices.begin(), indices.end(), gen);

        std::vector<std::vector<int>> folds(k);
        for (int i = 0; i < n_samples; ++i) {
            folds[i % k].push_back(indices[i]);
        }
        return folds;
    }
private:
    int n_trees;
    int max_depth;
    std::vector<DecisionTree> trees;
};

