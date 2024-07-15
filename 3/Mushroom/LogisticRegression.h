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
#include <random>
using namespace std;
class LogisticRegression {
private:
    std::vector<double> weights;
    double learning_rate;
    int iterations;

    double sigmoid(double z) {
        return 1.0 / (1.0 + std::exp(-z));
    }

    double predict_proba(const std::vector<double>& x) {
        double z = 0.0;
        for (size_t i = 0; i < weights.size(); ++i) {
            z += weights[i] * x[i];
        }
        return sigmoid(z);
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
    vector<vector<double>> kFoldSplit(int n_samples, int k) {
        std::vector<int> indices(n_samples);
        std::iota(indices.begin(), indices.end(), 0);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(indices.begin(), indices.end(), gen);

        std::vector<std::vector<double>> folds(k);
        for (int i = 0; i < n_samples; ++i) {
            folds[i % k].push_back(indices[i]);
        }
        return folds;
    }
    void update_weights(const std::vector<std::vector<double>>& X, const std::vector<int>& y) {
        for (int iter = 0; iter < iterations; ++iter) {
            std::vector<double> gradient(weights.size(), 0.0);
            for (size_t i = 0; i < X.size(); ++i) {
                double predicted = predict_proba(X[i]);
                for (size_t j = 0; j < weights.size(); ++j) {
                    gradient[j] += (y[i] - predicted) * X[i][j];
                }
            }
            for (size_t k = 0; k < weights.size(); ++k) {
                weights[k] += learning_rate * gradient[k];
            }
        }
    }

public:
    LogisticRegression(double lr = 0.01, int iters = 1000) : learning_rate(lr), iterations(iters) {}

    void fit(const std::vector<std::vector<double>>& X, const std::vector<int>& y) {
        weights.resize(X[0].size(), 0.0);
        update_weights(X, y);
    }

    int predict(const std::vector<double>& x) {
        return predict_proba(x) >= 0.5 ? 1 : 0;
    }

    std::vector<int> predict(const std::vector<std::vector<double>>& X) {
        std::vector<int> predictions;
        for (const auto& x : X) {
            predictions.push_back(predict(x));
        }
        return predictions;
    }




};
