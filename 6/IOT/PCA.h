#pragma once
#include <iostream>
#include <vector>
#include "Eigen/Dense"

using namespace std;
class PCA {
public:
    PCA(int n_components) : n_components(n_components) {}

    void fit(const std::vector<std::vector<double>>& data) {
        // Convert data to Eigen matrix
        Eigen::MatrixXd data_matrix = toEigenMatrix(data);

        // Center the data (subtract the mean of each feature)
        Eigen::VectorXd mean = data_matrix.colwise().mean();
        Eigen::MatrixXd centered = data_matrix.rowwise() - mean.transpose();

        // Compute the covariance matrix
        Eigen::MatrixXd covariance = (centered.adjoint() * centered) / double(data_matrix.rows() - 1);

        // Compute the eigenvalues and eigenvectors of the covariance matrix
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(covariance);
        Eigen::VectorXd eigenvalues = eig.eigenvalues().reverse();
        Eigen::MatrixXd eigenvectors = eig.eigenvectors().rowwise().reverse();

        // Select the top n_components eigenvectors
        components = eigenvectors.leftCols(n_components);
    }

    std::vector<std::vector<double>> transform(const std::vector<std::vector<double>>& data) {
        // Convert data to Eigen matrix
        Eigen::MatrixXd data_matrix = toEigenMatrix(data);

        // Center the data
        Eigen::VectorXd mean = data_matrix.colwise().mean();
        Eigen::MatrixXd centered = data_matrix.rowwise() - mean.transpose();

        // Project the data onto the principal components
        Eigen::MatrixXd transformed = centered * components;

        // Convert Eigen matrix back to std::vector<std::vector<double>>
        return toStdVector(transformed);
    }

private:
    int n_components;
    Eigen::MatrixXd components;

    Eigen::MatrixXd toEigenMatrix(const std::vector<std::vector<double>>& data) {
        Eigen::MatrixXd mat(data.size(), data[0].size());
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[i].size(); ++j) {
                mat(i, j) = data[i][j];
            }
        }
        return mat;
    }

    std::vector<std::vector<double>> toStdVector(const Eigen::MatrixXd& mat) {
        std::vector<std::vector<double>> vec(mat.rows(), std::vector<double>(mat.cols()));
        for (size_t i = 0; i < mat.rows(); ++i) {
            for (size_t j = 0; j < mat.cols(); ++j) {
                vec[i][j] = mat(i, j);
            }
        }
        return vec;
    }
};