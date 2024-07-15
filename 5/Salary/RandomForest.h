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
#include <unordered_map>
#include <cstdlib>
#include <random>

using namespace std;
class DecisionTreeRegressor {
public:
    // Dummy implementation of a decision tree regressor for illustration
    void fit(const std::vector<std::vector<double>>& X, const std::vector<double>& Y) {
        // Fit a simple model (e.g., mean of Y)
        if (X.size() != Y.size()) {
            throw std::invalid_argument("The sizes of X and Y must be the same.");
        }
        meanY = std::accumulate(Y.begin(), Y.end(), 0.0) / Y.size();
    }

    double predict(const std::vector<double>& x) const {
        // Return the mean as the prediction
        return meanY;
    }

private:
    double meanY;
};

class RandomForestRegressor {
public:
    RandomForestRegressor(int n_trees, int max_depth, int min_samples_split)
        : n_trees(n_trees), max_depth(max_depth), min_samples_split(min_samples_split) {
        std::srand(std::time(nullptr));
    }

    void fit(const std::vector<std::vector<double>>& X, const std::vector<double>& Y) {
        if (X.size() != Y.size()) {
            throw std::invalid_argument("The sizes of X and Y must be the same.");
        }

        int n_samples = X.size();
        for (int i = 0; i < n_trees; ++i) {
            std::vector<std::vector<double>> X_sample;
            std::vector<double> Y_sample;
            sampleData(X, Y, X_sample, Y_sample);

            DecisionTreeRegressor tree;
            tree.fit(X_sample, Y_sample);
            trees.push_back(tree);
        }
    }
    double calculateMSE(const std::vector<double>& trueValues, const std::vector<double>& predictions) const {
        double mse = 0.0;
        for (size_t i = 0; i < trueValues.size(); ++i) {
            mse += std::pow(trueValues[i] - predictions[i], 2);
        }
        return mse / trueValues.size();
    }

    // Calculate Root Mean Squared Error (RMSE)
    double calculateRMSE(const std::vector<double>& trueValues, const std::vector<double>& predictions) const {
        return std::sqrt(calculateMSE(trueValues, predictions));
    }

    // Calculate R-squared (coefficient of determination)
    double calculateRSquared(const std::vector<double>& trueValues, const std::vector<double>& predictions) const {
        double meanTrue = std::accumulate(trueValues.begin(), trueValues.end(), 0.0) / trueValues.size();
        double totalVariance = 0.0;
        double residualVariance = 0.0;
        for (size_t i = 0; i < trueValues.size(); ++i) {
            totalVariance += std::pow(trueValues[i] - meanTrue, 2);
            residualVariance += std::pow(trueValues[i] - predictions[i], 2);
        }
        return 1.0 - (residualVariance / totalVariance);
    }
    double predict(const std::vector<double>& x) const {
        double total = 0.0;
        for (const auto& tree : trees) {
            total += tree.predict(x);
        }
        return total / trees.size();
    }

    std::vector<double> predict(const std::vector<std::vector<double>>& X) const {
        std::vector<double> predictions;
        for (const auto& x : X) {
            predictions.push_back(predict(x));
        }
        return predictions;
    }
    vector<vector<int>> kFoldSplit(int n_samples, int k) {
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
    int min_samples_split;
    std::vector<DecisionTreeRegressor> trees;

    void sampleData(const std::vector<std::vector<double>>& X, const std::vector<double>& Y,
        std::vector<std::vector<double>>& X_sample, std::vector<double>& Y_sample) {
        int n_samples = X.size();
        std::uniform_int_distribution<> dist(0, n_samples - 1);
        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = 0; i < n_samples; ++i) {
            int index = dist(gen);
            X_sample.push_back(X[index]);
            Y_sample.push_back(Y[index]);
        }
    }
};