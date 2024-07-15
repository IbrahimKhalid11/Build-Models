#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <set>
#include <numeric>

class SVM {
public:
    SVM(double learning_rate = 0.001, double lambda_param = 0.01, int n_iters = 1000)
        : learning_rate(learning_rate), lambda_param(lambda_param), n_iters(n_iters) {}


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

    void fit(const std::vector<std::vector<double>>& X, const std::vector<int>& y) {
        int n_samples = X.size();
        int n_features = X[0].size();
        w = std::vector<double>(n_features, 0.0);
        b = 0.0;

        for (int iter = 0; iter < n_iters; ++iter) {
            for (int i = 0; i < n_samples; ++i) {
                double condition = y[i] * (dotProduct(X[i], w) - b);
                if (condition >= 1) {
                    for (int j = 0; j < n_features; ++j) {
                        w[j] -= learning_rate * (2 * lambda_param * w[j]);
                    }
                }
                else {
                    for (int j = 0; j < n_features; ++j) {
                        w[j] -= learning_rate * (2 * lambda_param * w[j] - X[i][j] * y[i]);
                    }
                    b -= learning_rate * y[i];
                }
            }
        }
    }

    int predict(const std::vector<double>& X) const {
        double linear_output = dotProduct(X, w) - b;
        return linear_output >= 0 ? 1 : -1;
    }

    std::vector<double> getWeights() const {
        return w;
    }

    double getBias() const {
        return b;
    }

private:
    double learning_rate;
    double lambda_param;
    int n_iters;
    std::vector<double> w;
    double b;

    double dotProduct(const std::vector<double>& a, const std::vector<double>& b) const {
        double result = 0.0;
        for (size_t i = 0; i < a.size(); ++i) {
            result += a[i] * b[i];
        }
        return result;
    }
};
