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
#include "LogisticRegression.h"
#include "SVM.h"
#include "PCA.h"
/// <summary>
///    /* Random subset to dataset */
/// </summary>
using namespace std;
int main() {

    string base_filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/IoT_Intrusion.csv";
    Data obj;
    DataFrame df=obj.load(base_filepath);
    //map<int, vector<vector<string>>> all_data;

    //// number of subset of dataset 15 can change in loop
    //for (int i = 1; i <= 1; ++i) {
    //    string filepath = base_filepath + to_string(i) + ".csv";
    //    DataFrame df = obj.load(filepath);
    //    all_data[1] = df;
    //    cout << "ok" << " " << i << endl;
    //    //all_data.push_back(data);
    //    //cout << "Loaded " << filepath << " with " << data.size() << " rows." << endl;
    //}
    ////DataFrame df = obj.load(filepath);
    //obj.print(all_data[1]);            // Print the first 5 rows
    //    obj.print(df,df.size());   // Print all rows
    cout << "ok";
    obj.print(df);
    cout << endl << "*****************************************************" << endl;

    obj.dropColumnByIndex(df, 12);
    obj.dropColumnByIndex(df, 12);
    obj.dropColumnByIndex(df, 20);
    obj.dropColumnByIndex(df, 20);
    obj.dropColumnByIndex(df, 21);
    cout << endl << "*****************************************************" << endl;

    auto sh = obj.shape(df);             // found the shape
    cout << "shape: " << "ROWS : " << sh.first << " , COLUMNS : " << sh.second << endl;

    cout << endl << "*****************************************************" << endl;
    //obj.dropColumnByIndex(df, 0);

    vector<string> columns = df[0];  // print name of columns
    cout << "Columns : ";
    for (string column : columns) {
        cout << column << " | ";
    }

    
    vector<vector<double>>dbData = obj.loadCSVAsFloatVector(df);

    //cout << endl << "**********************info to chunk 1**************************" << endl << endl;


    vector<double> mx = obj.MaxForColumn(dbData);

    vector<double> mn = obj.MinForColumn(dbData);

    vector<double> mean = obj.calculateMean(dbData);

    vector<double> median = obj.calculateMedian(dbData);

    vector<double> mode = obj.calculateMode(dbData);

    vector<double> stdd = obj.calculateStandardDeviations(dbData);


    obj.printTable(columns, { "Max","Min","Mean", "Median","Mode","Std" }, { mx,mn,mean,median,mode,stdd });

    cout << "\n";
    cout << endl << "***********************OUTLIERS***********************" << endl << endl;

    vector<vector<int>> outlier = obj.detectOutliersIQR(dbData);
    for (int j = 0; j < outlier.size(); ++j) {
        cout << "Column " << j << " , Name : " << df[0][j] << " , outliers: (size : " << outlier[j].size() << " ) " << (outlier[j].size() > 10 ? "Show 10 IndexElements : " : "");
        for (int i = 0; i < (outlier[j].size() > 10 ? 10 : outlier[j].size()); ++i) {
            cout << outlier[j][i] << " ";
        }
        cout << "\n";
    }


    cout << endl << "********************CURR**************************" << endl << endl;
    cout << "        ";
    for (int i = 0; i < columns.size(); ++i) {
        cout << columns[i] << " | ";
    }
    cout << endl << "-----------------------------------------------" << endl;

    for (int i = 0; i < dbData[0].size(); ++i) {
        cout << columns[i] << " | ";
        for (int j = 0; j < dbData[0].size(); ++j) {
            cout << obj.calculateCorrelation(dbData, i, j) << " | ";
        }
        cout << "\n";
    }
    cout << endl << "----------------Feature Selection----------------------" << endl;
    cout << endl << "--------------Way 1--------------------" << endl;

    obj.feature_selection(df, dbData, 0.1, "curr");

    cout << endl << "--------------Way 2--------------------" << endl;

    vector<int>continousColumn = { 0,1,2,3,4,5,15,16,17,30,31,32,33,34,35,36,37,38,39,40,41,42 };
    obj.feature_selection(df, dbData, 0.1, "Mutual_Information", continousColumn);

    cout << "\n //////////////////////////////PCA\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n";
    
        vector<vector<double>> X;
        vector<int> y;
        obj.splitFeaturesAndLabels(dbData, X, y);
    
        PCA pca(10); // Reduce to 1 principal component
        pca.fit(X);
    
        // Transform the data
        vector<vector<double>> transformed_data = pca.transform(X);
    
        // Output the transformed data
        //cout << "Transformed data:" << endl;
        //for (const auto& row : transformed_data) {
        //    for (double val : row) {
        //        cout << val << " ";
        //    }
        //    cout << endl;
        //}
    
    //


    //cout << "\n //////////////////////////////MODELS\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n";
    cout << " 1 - SVM \n";
    vector<vector<double>>DtSVM = dbData;

    int num_samples = DtSVM.size();

    SVM svm(0.001, 0.01, 1000);
    int k = 5; // Number of folds
    vector<vector<int>> folds = svm.kFoldSplit(num_samples, k);
    double total_accuracy = 0.0;

    for (int i = 0; i < k; ++i) {
        vector<vector<double>> trainData, testData;
        vector<int> trainLabels, testLabels;

        for (int j = 0; j < k; ++j) {
            if (j == i) {
                for (int idx : folds[j]) {
                    testData.push_back(transformed_data[idx]);
                    testLabels.push_back(y[idx]);
                }
            }
            else {
                for (int idx : folds[j]) {
                    trainData.push_back(transformed_data[idx]);
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
        cout << "Fold " << i + 1 << " Accuracy: " << accuracy * 100 << "%" << endl;
        total_accuracy += accuracy;
    }

    total_accuracy /= k;
    cout << "Average Accuracy: " << total_accuracy * 100 << "%" << endl;



    cout << "\n \n 2- Logistic Regression \n\n";
    LogisticRegression lr(0.1, 1000);
    //folds = lr.kFoldSplit(num_samples, k);

    for (int i = 0; i < k; ++i) {
        vector<vector<double>> trainData, testData;
        vector<int> trainLabels, testLabels;

        for (int j = 0; j < k; ++j) {
            if (j == i) {
                for (int idx : folds[j]) {
                    testData.push_back(transformed_data[idx]);
                    testLabels.push_back(y[idx]);
                }
            }
            else {
                for (int idx : folds[j]) {
                    trainData.push_back(transformed_data[idx]);
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
        cout << "Fold " << i + 1 << " Accuracy: " << accuracy * 100 << "%" << endl;
        total_accuracy += accuracy;
    }

    total_accuracy /= k;
    cout << "Average Accuracy: " << total_accuracy * 100 << "%" << endl;


    return 0;

};
