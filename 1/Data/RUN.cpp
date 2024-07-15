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
#include "OvRSVM.h"
#include "RandomForest.h"
using namespace std;
int main() {

    string filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/drug200.csv";
    Data obj(filepath);
    
    DataFrame df = obj.load(filepath);
    cout<<df[0][0];
    obj.print(df);            // Print the first 5 rows
    //    obj.print(df,df.size());   // Print all rows


    cout << endl << "*****************************************************" << endl;

    auto sh = obj.shape(df);             // found the shape
    cout << "shape: " << "ROWS : " << sh.first << " , COLUMNS : " << sh.second << endl;

    cout << endl << "*****************************************************" << endl;

    vector<string> columns = df[0];  // print name of columns
    cout << "Columns : ";
    for (string column : columns) {
        cout << column << " | ";
    }
    cout << endl << "*****************************************************" << endl;

    obj.info(df);

    cout << endl << "************************Unique*****************************" << endl;
    obj.unique(df, "Sex");
    cout << '/n';
    obj.unique(df, "Drug");
    cout << '/n';
    obj.unique(df, "Cholesterol");

    obj.unique(df, "BP");
    cout << endl << "*************************Value_counts*********************" << endl;
    obj.value_counts(df, "Sex");
    cout << endl;
    obj.value_counts(df, "Cholesterol");
    cout << endl;
    obj.value_counts(df, "BP");
    cout << endl;
    obj.value_counts(df, "Drug");
    cout << endl << "*****************************************************" << endl;

    std::cout << "REPLACE:\n"
        << "*Sex \nM -> 0 \nF -> 1 \n\n"
        << "*Drug \ndrugA -> 0\ndrugB -> 1\ndrugC -> 2\ndrugX -> 3\nDrugY -> 4\n\n"
        << "*Cholesterol \nHIGH -> 0\nNORMAL -> 1\n\n"
        << "*BP \nHIGH -> 0\nNORMAL -> 1\nLOW -> 2\n\n";

    obj.replace(df, "Sex", "M", "0");
    obj.replace(df, "Sex","F", "1");

    obj.replace(df, "Drug", "drugA", "0");
    obj.replace(df, "Drug", "drugB", "1");
    obj.replace(df, "Drug", "drugC", "2");
    obj.replace(df, "Drug", "drugX", "3");
    obj.replace(df, "Drug", "DrugY", "4");

    obj.replace(df, "Cholesterol", "HIGH", "0");
    obj.replace(df, "Cholesterol", "NORMAL", "1");

    obj.replace(df, "BP", "HIGH", "0");
    obj.replace(df, "BP", "NORMAL", "1");
    obj.replace(df, "BP", "LOW", "2");

    cout << "After Replace : " << endl;
    obj.print(df);
    vector<vector<double>>dbData=obj.loadCSVAsFloatVector(df);

    cout << endl << "*****************************************************" << endl << endl;
    cout << "     ";
   for (int i = 0; i < columns.size(); ++i) {
       cout << columns[i] << "|";
   }
   cout << endl << "-----------------------------------------------" << endl;

   vector<double> mx;
   mx = obj.MaxForColumn(dbData);
   cout << "Max  ";
   for (int i = 0; i < mx.size(); ++i) {
       cout << mx[i] << " | ";
   }
   cout << "\n";

    vector<double> mn;
    mn = obj.MinForColumn(dbData);
    cout << "Min  ";
    for (int i = 0; i < mn.size(); ++i) {
        cout << mn[i] << " | ";
    }
    cout << "\n";

    vector<double> mean;
    mean = obj.calculateMean(dbData);
    cout << "mean  ";
    for (int i = 0; i < mean.size(); ++i) {
        cout << mean[i] << " | ";
    }
    cout << "\n";

    cout << "median  ";
    vector<double> median;
    median = obj.calculateMedian(dbData);
    for (int i = 0; i < median.size(); ++i) {
        cout << median[i] << " | ";
    }
    cout << "\n";

    cout << "mode  ";
    vector<double> mode;
    mode = obj.calculateMode(dbData);
    for (int i = 0; i < mode.size(); ++i) {
        cout << mode[i] << " | ";
    }
    cout << "\n";

    cout << "std  ";
    vector<double> stdd;
    stdd = obj.calculateStandardDeviations(dbData);
    for (int i = 1; i < stdd.size(); ++i) {
        cout << stdd[i] << " | ";
    }
    cout << "\n";
    cout << endl << "***********************OUTLIERS***********************" << endl << endl;

    vector<vector<int>> outlier = obj.detectOutliersIQR(dbData);
    for (int j = 0; j < outlier.size(); ++j) {
        cout << "Column " << j << " outliers: (size : "<< outlier[j].size()<<" ) ";
        for (int i = 0; i < outlier[j].size(); ++i) {
            cout << outlier[j][i] << " ";
        }
        cout << "\n";
    }

   // cout << endl << "********************SCALER**************************" << endl << endl;
   // for (int i = 1; i < columns.size(); ++i) {
   //     cout << columns[i] << " | ";
   // }
   // cout << endl;
   // v = obj.standardScaler(v);
   // for (int i = 0; i < 5; ++i) {
   //     for (int j = 1; j < v[i].size(); ++j) {
   //         cout << v[i][j] << " ";
   //     }
   //     cout << "\n";
   // }

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
        cout << endl;
    }
    cout << endl << "----------------Feature Selection----------------------" << endl;
    cout << endl << "--------------Way 1--------------------" << endl;

    obj.feature_selection(df, dbData, 0.1, "curr");

    cout << endl << "--------------Way 2--------------------" << endl;

    vector<int>continousColumn = { 4 };
    obj.feature_selection(df,dbData, 0.1, "Mutual_Information", continousColumn);




    cout << "\n //////////////////////////////MODELS\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n";
    cout << " 1 - SVM \n";


    OvRSVM svm(0.001, 0.01, 1000);
    vector<std::vector<double>> X;
    vector<int> y;
    int num_samples = dbData.size();
    svm.splitFeaturesAndLabels(dbData, X, y);
    // Split the data into training and test sets
    int train_size = static_cast<int>(.5 * num_samples);
    std::vector<std::vector<double>> X_train(X.begin(), X.begin() + train_size);
    std::vector<int> y_train(y.begin(), y.begin() + train_size);
    std::vector<std::vector<double>> X_test(X.begin() + train_size, X.end());
    std::vector<int> y_test(y.begin() + train_size, y.end());

    //// Initialize and train the SVM
    svm.fit(X_train, y_train);

    // Predict and evaluate
    int correct = 0;
    for (size_t i = 0; i < X_test.size(); ++i) {
        int prediction = svm.predict(X_test[i]);
        if (prediction == y_test[i]) {
            correct++;
        }
    }

    double accuracy = static_cast<double>(correct) / X_test.size();
    std::cout << "Accuracy: " << accuracy * 100 << "%" << std::endl;
    for (size_t i = 0; i < X_test.size(); ++i) {
        int prediction = svm.predict(X_test[i]);
        std::cout << "True label: " << y_test[i] << ", Predicted label: " << prediction << std::endl;
    }

    cout << "\n \n 2 - Random Forest \n";


    RandomForest rf(10, 5); // 10 trees, max depth of 5
    rf.fit(X_train, y_train);


    correct = 0;
    for (size_t i = 0; i < X_test.size(); ++i) {
        int prediction = rf.predict(X_test[i]);
        std::cout << "True label: " << y_test[i] << ", Predicted label: " << prediction << std::endl;
    }
    for (size_t i = 0; i < X_test.size(); ++i) {
        int prediction = rf.predict(X_test[i]);
        if (prediction == y_test[i]) {
            correct++;
        }
    }

    accuracy = static_cast<double>(correct) / X_test.size();
    std::cout << "Accuracy: " << accuracy * 100 << "%" << std::endl;



    cout << "//////////////////////////////////////////////////////////////// \n";
    cout << "//////////////////////////////////////////////////////////////// \n";
    cout << "//////////////////////////////////////////////////////////////// \n";


    OvRSVM svm2(0.001, 0.01, 1000);
    int k = 5; // Number of folds
    std::vector<std::vector<int>> folds = svm2.kFoldSplit(num_samples, k);
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

        svm2.fit(trainData, trainLabels);

        int correct = 0;
        for (size_t i = 0; i < testData.size(); ++i) {
            int prediction = svm2.predict(testData[i]);
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







    cout << "//////////////////////////////////////////////////////////////// \n";
    RandomForest rf2(10, 5); // 10 trees, max depth of 5
         k = 5; // Number of folds
    //std::vector<std::vector<int>> folds = rf2.kFoldSplit(num_samples, k);
    total_accuracy = 0.0;

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

        rf2.fit(trainData, trainLabels);

        int correct = 0;
        for (size_t i = 0; i < testData.size(); ++i) {
            int prediction = rf2.predict(testData[i]);
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
