#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <set>
#include <map>

class DecisionTree {
public:
    DecisionTree(int max_depth) : max_depth(max_depth) {}

    void fit(const std::vector<std::vector<double>>& X, const std::vector<int>& y) {
        if (X.empty() || y.empty()) return;
        n_features = X[0].size();
        root = buildTree(X, y, 0);
    }

    int predict(const std::vector<double>& x) const {
        return predictFromNode(x, root);
    }

private:
    struct Node {
        int feature_index;
        double threshold;
        int label;
        Node* left;
        Node* right;
        Node(int fi, double th, int lbl) : feature_index(fi), threshold(th), label(lbl), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int max_depth;
    int n_features;

    Node* buildTree(const std::vector<std::vector<double>>& X, const std::vector<int>& y, int depth) {
        if (depth >= max_depth || X.empty() || y.empty()) {
            int most_common_label = getMostCommonLabel(y);
            return new Node(-1, 0.0, most_common_label);
        }

        int best_feature;
        double best_threshold;
        double best_gini = std::numeric_limits<double>::max();
        std::vector<std::vector<double>> left_X, right_X;
        std::vector<int> left_y, right_y;

        // Find the best split
        for (int feature_index = 0; feature_index < n_features; ++feature_index) {
            std::set<double> thresholds;
            for (const auto& row : X) {
                thresholds.insert(row[feature_index]);
            }
            for (double threshold : thresholds) {
                std::vector<std::vector<double>> left_X_temp, right_X_temp;
                std::vector<int> left_y_temp, right_y_temp;
                for (size_t i = 0; i < X.size(); ++i) {
                    if (X[i][feature_index] < threshold) {
                        left_X_temp.push_back(X[i]);
                        left_y_temp.push_back(y[i]);
                    }
                    else {
                        right_X_temp.push_back(X[i]);
                        right_y_temp.push_back(y[i]);
                    }
                }
                double gini = computeGini(left_y_temp, right_y_temp);
                if (gini < best_gini) {
                    best_gini = gini;
                    best_feature = feature_index;
                    best_threshold = threshold;
                    left_X = left_X_temp;
                    right_X = right_X_temp;
                    left_y = left_y_temp;
                    right_y = right_y_temp;
                }
            }
        }

        if (left_X.empty() || right_X.empty()) {
            int most_common_label = getMostCommonLabel(y);
            return new Node(-1, 0.0, most_common_label);
        }

        Node* node = new Node(best_feature, best_threshold, -1);
        node->left = buildTree(left_X, left_y, depth + 1);
        node->right = buildTree(right_X, right_y, depth + 1);
        return node;
    }

    double computeGini(const std::vector<int>& left_y, const std::vector<int>& right_y) const {
        auto gini = [](const std::vector<int>& y) {
            std::map<int, int> counts;
            for (int label : y) {
                counts[label]++;
            }
            double impurity = 1.0;
            for (const auto& pair : counts) {
                double prob = static_cast<double>(pair.second) / y.size();
                impurity -= prob * prob;
            }
            return impurity;
            };
        double left_gini = gini(left_y);
        double right_gini = gini(right_y);
        double total_size = left_y.size() + right_y.size();
        return (left_y.size() / total_size) * left_gini + (right_y.size() / total_size) * right_gini;
    }

    int predictFromNode(const std::vector<double>& x, Node* node) const {
        if (node->left == nullptr && node->right == nullptr) {
            return node->label;
        }
        if (x[node->feature_index] < node->threshold) {
            return predictFromNode(x, node->left);
        }
        else {
            return predictFromNode(x, node->right);
        }
    }

    int getMostCommonLabel(const std::vector<int>& y) const {
        if (y.empty()) return -1;
        std::map<int, int> count_map;
        for (int label : y) {
            count_map[label]++;
        }
        int most_common_label = y[0];
        int max_count = 0;
        for (const auto& pair : count_map) {
            if (pair.second > max_count) {
                max_count = pair.second;
                most_common_label = pair.first;
            }
        }
        return most_common_label;
    }
};

