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
#include "Data.h"
#include "SVM.h"
#include "LogisticRegression.h"
using namespace std;
int main() {

    string filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/Train.csv";
    Data obj(filepath);

    DataFrame df = obj.load(filepath);
    obj.print(df);            // Print the first 5 rows
    //    obj.print(df,df.size());   // Print all rows


    cout << endl << "*****************************************************" << endl;

    auto sh = obj.shape(df);             // found the shape
    cout << "shape: " << "ROWS : " << sh.first << " , COLUMNS : " << sh.second << endl;

    cout << endl << "*****************************************************" << endl;
    obj.dropColumnByIndex(df, 0);

    vector<string> columns = df[0];  // print name of columns
    cout << "Columns : ";
    for (string column : columns) {
        cout << column << " | ";
    }

    cout << endl << "*****************************************************" << endl;

    obj.info(df);

    cout << endl << "************************Unique*****************************" << endl;
    //Warehouse_block Mode_of_Shipment Customer_care_calls Customer_rating Cost_of_the_Product Prior_purchases Product_importance Gender Discount_offered Weight_in_gms Reached.on.Time_Y.N
    obj.unique(df, "Warehouse_block");
    obj.unique(df, "Mode_of_Shipment");
    obj.unique(df, "Customer_care_calls");
    obj.unique(df, "Customer_rating");
    obj.unique(df, "Prior_purchases");
    obj.unique(df, "Product_importance");
    cout << endl << "*************************Value_counts*********************" << endl;
    obj.value_counts(df, "Warehouse_block");
    cout << endl;
    obj.value_counts(df, "Mode_of_Shipment");
    cout << endl;
    obj.value_counts(df, "Customer_care_calls");
    cout << endl;
    obj.value_counts(df, "Customer_rating");
    cout << endl;
    obj.value_counts(df, "Prior_purchases");
    cout << endl;
    obj.value_counts(df, "Product_importance");
    //cout << endl << "*****************************************************" << endl;

    std::cout << "replace:\n"
        << "*Gender \nm -> 0 \nf -> 1 \n\n"
        << "*Warehouse_block \nA -> 0\nB -> 1\nC -> 2\nD -> 3\nE -> 4\n\n"
        << "*Mode_of_Shipment \nFlight -> 0\nRoad -> 1\nShip -> 2\n\n"
        << "*Product_importance \nhigh -> 0\nmedium -> 1\nlow -> 2\n\n";

    obj.replace(df, "Gender", "M", "0");
    obj.replace(df, "Gender", "F", "1");

    obj.replace(df, "Warehouse_block", "A", "0");
    obj.replace(df, "Warehouse_block", "B", "1");
    obj.replace(df, "Warehouse_block", "C", "2");
    obj.replace(df, "Warehouse_block", "D", "3");
    obj.replace(df, "Warehouse_block", "F", "4");

    obj.replace(df, "Mode_of_Shipment", "Flight", "0");
    obj.replace(df, "Mode_of_Shipment", "Road", "1");
    obj.replace(df, "Mode_of_Shipment", "Ship", "2");

    obj.replace(df, "Product_importance", "high", "0");
    obj.replace(df, "Product_importance", "medium", "1");
    obj.replace(df, "Product_importance", "low", "2");

    cout << "after replace : " << endl;
    obj.print(df);
    vector<vector<double>>dbData = obj.loadCSVAsFloatVector(df);

    cout << endl << "*****************************************************" << endl << endl;


    vector<double> mx = obj.MaxForColumn(dbData);

    vector<double> mn = obj.MinForColumn(dbData);

    vector<double> mean = obj.calculateMean(dbData);

    vector<double> median = obj.calculateMedian(dbData);

    vector<double> mode = obj.calculateMode(dbData);

    vector<double> stdd = obj.calculateStandardDeviations(dbData);


    obj.printTable(columns, { "Max","Min","Mean", "Median","Mode","StandardDeviations" }, { mx,mn,mean,median,mode,stdd });

    //cout << "\n";
    cout << endl << "***********************OUTLIERS***********************" << endl << endl;

    vector<vector<int>> outlier = obj.detectOutliersIQR(dbData);
    for (int j = 0; j < outlier.size(); ++j) {
        cout << "Column " << j << " , Name : " << df[0][j] << " , outliers: (size : " << outlier[j].size() << " ) " << (outlier[j].size() > 10 ? "Show 10 Elements : " : "");
        for (int i = 0; i < (outlier[j].size() > 10 ? 10 : outlier[j].size()); ++i) {
            cout << outlier[j][i] << " ";
        }
        cout << "\n";
    }

    cout << endl << "********************SCALER**************************" << endl << endl;

    vector<vector<double>> scaledData = obj.standardScaler(dbData, { 5,8 });
    obj.printof2D(scaledData, columns);


    cout << endl << "********************CURR**************************" << endl << endl;
    cout << "        ";
    for (int i = 0; i < columns.size(); ++i) {
        cout << columns[i] << " | ";
    }
    cout << endl << "-----------------------------------------------" << endl;

    for (int i = 0; i < scaledData[0].size(); ++i) {
        cout << columns[i] << " | ";
        for (int j = 0; j < scaledData[0].size(); ++j) {
            cout << obj.calculateCorrelation(scaledData, i, j) << " | ";
        }
        cout << endl;
    }
    cout << endl << "----------------Feature Selection----------------------" << endl;
    cout << endl << "--------------Way 1--------------------" << endl;

    obj.feature_selection(df, scaledData, 0.1, "curr");

    cout << endl << "--------------Way 2--------------------" << endl;

    vector<int>continousColumn = { 4,9 };
    obj.feature_selection(df, scaledData, 0.1, "Mutual_Information", continousColumn);




    cout << "\n //////////////////////////////MODELS\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n";
    cout << " 1 - SVM \n";
    vector<vector<double>>DtSVM = scaledData;

    vector<std::vector<double>> X;
    vector<int> y;
    int num_samples = DtSVM.size();

    SVM svm(0.001, 0.01, 1000);
    svm.splitFeaturesAndLabels(scaledData, X, y);
    int k = 5; // Number of folds
    std::vector<std::vector<int>> folds = svm.kFoldSplit(num_samples, k);
    double total_accuracy = 0.0;

    for (int i = 0; i < k; ++i) {
        std::vector<std::vector<double>> trainData, testData;
        std::vector<int> trainLabels, testLabels;

        for (int j = 0; j < k; ++j) {
            if (j == i) {
                for (int idx : folds[j]) {
                    testData.push_back(X[idx]);
                    testLabels.push_back(y[idx]);
                }
            }
            else {
                for (int idx : folds[j]) {
                    trainData.push_back(X[idx]);
                    trainLabels.push_back(y[idx]);
                }
            }
        }

        svm.fit(trainData, trainLabels);

        int correct = 0;
        for (size_t i = 0; i < testData.size(); ++i) {
            int prediction = svm.predict(testData[i]);
            if (prediction == testLabels[i]) {
                correct++;
            }
        }

        double accuracy = static_cast<double>(correct) / testData.size();
        std::cout << "Fold " << i + 1 << " Accuracy: " << accuracy * 100 << "%" << std::endl;
        total_accuracy += accuracy;
    }

    total_accuracy /= k;
    std::cout << "Average Accuracy: " << total_accuracy * 100 << "%" << std::endl;



    cout << "\n \n 2- Logistic Regression \n\n";
    LogisticRegression lr(0.1, 1000);
    //folds = lr.kFoldSplit(num_samples, k);

    for (int i = 0; i < k; ++i) {
        std::vector<std::vector<double>> trainData, testData;
        std::vector<int> trainLabels, testLabels;

        for (int j = 0; j < k; ++j) {
            if (j == i) {
                for (int idx : folds[j]) {
                    testData.push_back(X[idx]);
                    testLabels.push_back(y[idx]);
                }
            }
            else {
                for (int idx : folds[j]) {
                    trainData.push_back(X[idx]);
                    trainLabels.push_back(y[idx]);
                }
            }
        }

        lr.fit(trainData, trainLabels);

        int correct = 0;
        for (size_t i = 0; i < testData.size(); ++i) {
            int prediction = svm.predict(testData[i]);
            if (prediction == testLabels[i]) {
                correct++;
            }
        }

        double accuracy = static_cast<double>(correct) / testData.size();
        std::cout << "Fold " << i + 1 << " Accuracy: " << accuracy * 100 << "%" << std::endl;
        total_accuracy += accuracy;
    }

    total_accuracy /= k;
    std::cout << "Average Accuracy: " << total_accuracy * 100 << "%" << std::endl;


    return 0;

};
