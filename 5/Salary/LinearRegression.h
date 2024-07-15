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

class LinearRegression {
public:
    LinearRegression() {}

    void fit(const std::vector<std::vector<double>>& X, const std::vector<double>& Y) {
        if (X.size() != Y.size()) {
            throw std::invalid_argument("The sizes of X and Y must be the same.");
        }

        int n = X.size();
        int m = X[0].size();

        // Initialize coefficients (including the intercept)
        coefficients = std::vector<double>(m + 1, 0.0);

        // Compute the means of X and Y
        std::vector<double> meanX(m, 0.0);
        double meanY = std::accumulate(Y.begin(), Y.end(), 0.0) / n;

        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                meanX[j] += X[i][j];
            }
            meanX[j] /= n;
        }

        // Compute the coefficients
        for (int j = 0; j < m; ++j) {
            double num = 0.0;
            double denom = 0.0;
            for (int i = 0; i < n; ++i) {
                num += (X[i][j] - meanX[j]) * (Y[i] - meanY);
                denom += (X[i][j] - meanX[j]) * (X[i][j] - meanX[j]);
            }
            coefficients[j + 1] = num / denom;
        }

        // Compute the intercept
        coefficients[0] = meanY;
        for (int j = 0; j < m; ++j) {
            coefficients[0] -= coefficients[j + 1] * meanX[j];
        }
    }

    double predict(const std::vector<double>& x) const {
        double prediction = coefficients[0];
        for (int j = 0; j < x.size(); ++j) {
            prediction += coefficients[j + 1] * x[j];
        }
        return prediction;
    }

    std::vector<double> predict(const std::vector<std::vector<double>>& X) const {
        std::vector<double> predictions;
        for (const auto& x : X) {
            predictions.push_back(predict(x));
        }
        return predictions;
    }

    const std::vector<double>& getCoefficients() const {
        return coefficients;
    }

    // Calculate Mean Squared Error (MSE)
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
    void splitFeaturesAndLabels(const std::vector<std::vector<double>>& df, std::vector<std::vector<double>>& X, std::vector<double>& y) {
        if (df.empty()) return;

        size_t n_samples = df.size();
        size_t n_features = df[0].size() - 1; // Assuming the last column is the label

        X.resize(n_samples, std::vector<double>(n_features));
        y.resize(n_samples);

        for (size_t i = 0; i < n_samples; ++i) {
            for (size_t j = 0; j < n_features; ++j) {
                X[i][j] = df[i][j];
            }
            y[i] = static_cast<int>(df[i][n_features]);
        }
    }

private:
    std::vector<double> coefficients;
};
