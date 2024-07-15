#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// A utility function to calculate the Euclidean distance between two points
double euclidean_distance(const vector<double>& point1, const vector<double>& point2) {
    double distance = 0.0;
    for (size_t i = 0; i < point1.size(); ++i) {
        distance += pow(point1[i] - point2[i], 2);
    }
    return sqrt(distance);
}

// A class for KNN Regression
class KNNRegressor {
public:
    KNNRegressor(int k) : k(k) {}

    void fit(const vector<vector<double>>& X, const vector<double>& y) {
        this->X_train = X;
        this->y_train = y;
    }

    vector<double> predict(const vector<vector<double>>& points) {
        vector<double> predictions;
        for (const auto& point : points) {
            predictions.push_back(predict_single(point));
        }
        return predictions;
    }
    //const std::vector<double>& getCoefficients() const {
    //    return coefficients;
    //}

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
private:
    int k;
    vector<vector<double>> X_train;
    vector<double> y_train;

    double predict_single(const vector<double>& point) {
        // Calculate distances from the input point to all points in the training set
        vector<pair<double, double>> distances; // {distance, target_value}
        for (size_t i = 0; i < X_train.size(); ++i) {
            double distance = euclidean_distance(point, X_train[i]);
            distances.push_back(make_pair(distance, y_train[i]));
        }

        // Sort the distances
        sort(distances.begin(), distances.end());

        // Average the target values of the k nearest neighbors
        double sum = 0.0;
        for (int i = 0; i < k; ++i) {
            sum += distances[i].second;
        }

        return sum / k;
    }
};