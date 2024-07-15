#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include "SVM.h"

using namespace std;
class OvRSVM {
public:
    OvRSVM(double learning_rate = 0.001, double lambda_param = 0.01, int n_iters = 1000)
        : learning_rate(learning_rate), lambda_param(lambda_param), n_iters(n_iters) {}

    void fit(const std::vector<std::vector<double>>& X, const std::vector<int>& y) {
        std::set<int> unique_labels(y.begin(), y.end());
        for (int label : unique_labels) {
            std::vector<int> binary_y(y.size());
            for (size_t i = 0; i < y.size(); ++i) {
                binary_y[i] = (y[i] == label) ? 1 : -1;
            }
            SVM svm(learning_rate, lambda_param, n_iters);
            svm.fit(X, binary_y);
            svms.push_back(svm);
            labels.push_back(label);
        }
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
    int predict(const std::vector<double>& X) const {
        std::vector<double> scores;
        for (const auto& svm : svms) {
            double score = dotProduct(X, svm.getWeights()) - svm.getBias();
            scores.push_back(score);
        }
        int max_index = std::distance(scores.begin(), std::max_element(scores.begin(), scores.end()));
        return labels[max_index];
    }

private:
    double learning_rate;
    double lambda_param;
    int n_iters;
    std::vector<SVM> svms;
    std::vector<int> labels;

    double dotProduct(const std::vector<double>& a, const std::vector<double>& b) const {
        double result = 0.0;
        for (size_t i = 0; i < a.size(); ++i) {
            result += a[i] * b[i];
        }
        return result;
    }
};
