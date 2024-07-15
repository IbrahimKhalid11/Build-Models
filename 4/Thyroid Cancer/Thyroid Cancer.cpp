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
using namespace std;
int main() {

    string filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/Thyroid_Diff.csv";
    Data obj(filepath);

    DataFrame df = obj.load(filepath);
    obj.print(df);            // Print the first 5 rows
    //    obj.print(df,df.size());   // Print all rows


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

    cout << endl << "*****************************************************" << endl;

    obj.info(df);

    cout << endl << "************************Unique*****************************" << endl;
    obj.unique(df, "Thyroid Function");
    obj.unique(df, "Physical Examination");
    obj.unique(df, "Adenopathy");
    obj.unique(df, "Pathology");
    obj.unique(df, "Risk");
    obj.unique(df, "T");
    obj.unique(df, "N");
    obj.unique(df, "Stage");
    obj.unique(df, "Response");
    cout << endl << "*************************Value_counts*********************" << endl;
    obj.value_counts(df, "Thyroid Function");
    cout << endl;
    obj.value_counts(df, "Physical Examination");
    cout << endl;
    obj.value_counts(df, "Adenopathy");
    cout << endl;
    obj.value_counts(df, "Pathology");
    cout << endl;
    obj.value_counts(df, "Risk");
    cout << endl;
    obj.value_counts(df, "T");
    cout << endl;
    obj.value_counts(df, "Stage");
    cout << endl;
    obj.value_counts(df, "Response");
    cout << endl;
    cout << endl << "*****************************************************" << endl;



    obj.replace(df, "Pathology", "Follicular", "0");
    obj.replace(df, "Pathology", "Hurthel cell", "1");
    obj.replace(df, "Pathology", "Micropapillary", "2");
    obj.replace(df, "Pathology", "Papillary", "3");

    obj.replace(df, "Risk", "High", "0");
    obj.replace(df, "Risk", "Intermediate", "1");
    obj.replace(df, "Risk", "Low", "2");

    obj.replace(df, "T", "T1a", "0");
    obj.replace(df, "T", "T1b", "1");
    obj.replace(df, "T", "T2", "2");
    obj.replace(df, "T", "T3a", "3");
    obj.replace(df, "T", "T3b", "4");
    obj.replace(df, "T", "T4a", "5");
    obj.replace(df, "T", "T4b", "6");

    obj.replace(df, "Stage", "I", "0");
    obj.replace(df, "Stage", "II", "1");
    obj.replace(df, "Stage", "III", "2");
    obj.replace(df, "Stage", "IVA", "3");
    obj.replace(df, "Stage", "IVB", "4");


    obj.replace(df, "Response", "Biochemical Incomplete", "0");
    obj.replace(df, "Response", "Excellent", "1");
    obj.replace(df, "Response", "Indeterminate", "2");
    obj.replace(df, "Response", "Structural Incomplete", "3");

    obj.replace(df, "Gender", "M", "0");
    obj.replace(df, "Gender", "F", "1");

    obj.replace(df, "Smoking", "Yes", "0");
    obj.replace(df, "Smoking", "No", "1");

    obj.replace(df, "Hx Smoking", "Yes", "0");
    obj.replace(df, "Hx Smoking", "No", "1");

    obj.replace(df, "Hx Radiothreapy", "Yes", "0");
    obj.replace(df, "Hx Radiothreapy", "No", "1");

    obj.replace(df, "Focality", "Uni-Focal", "0");
    obj.replace(df, "Focality", "Multi-Focal", "1");

    obj.replace(df, "N", "N0", "0");
    obj.replace(df, "N", "N1a", "1");
    obj.replace(df, "N", "N1b", "2");

    obj.replace(df, "M", "M0", "0");
    obj.replace(df, "M", "M1", "1");

    obj.replace(df, "Recurred", "Yes", "0");
    obj.replace(df, "Recurred", "No", "1");

    obj.replace(df, "Thyroid Function", "Euthyroid", "0");
    obj.replace(df, "Thyroid Function", "Clinical Hyperthyroidism", "1");
    obj.replace(df, "Thyroid Function", "Clinical Hypothyroidism", "2");
    obj.replace(df, "Thyroid Function", "Subclinical Hyperthyroidism", "3");
    obj.replace(df, "Thyroid Function", "Subclinical Hypothyroidism", "4");

    obj.replace(df, "Physical Examination", "Multinodular goiter", "0");
    obj.replace(df, "Physical Examination", "Diffuse goiter", "1");
    obj.replace(df, "Physical Examination", "Normal", "2");
    obj.replace(df, "Physical Examination", "Single nodular goiter-left", "3");
    obj.replace(df, "Physical Examination", "Single nodular goiter-right", "4");

    obj.replace(df, "Adenopathy", "Bilateral", "0");
    obj.replace(df, "Adenopathy", "Left", "1");
    obj.replace(df, "Adenopathy", "No", "2");
    obj.replace(df, "Adenopathy", "Extensive", "3");
    obj.replace(df, "Adenopathy", "Right", "4");
    obj.replace(df, "Adenopathy", "Posterior", "5");


    cout << "After Replace : " << endl;
    obj.print(df);
    
    vector<vector<double>>dbData = obj.loadCSVAsFloatVector(df);

    cout << endl << "*****************************************************" << endl << endl;


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

    //cout << endl << "--------------Way 2--------------------" << endl;

    vector<int>continousColumn = { 0,4,5,7 };
    obj.feature_selection(df, dbData, 0.1, "Mutual_Information", continousColumn);




    cout << "\n //////////////////////////////MODELS\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n";
    cout << " 1 - SVM \n";
    vector<vector<double>>DtSVM = dbData;
    obj.dropColumnByIndexDouble(DtSVM, 0);
    obj.dropColumnByIndexDouble(DtSVM, 6);
    vector<std::vector<double>> X;
    vector<int> y;
    int num_samples = DtSVM.size();

    SVM svm(0.001, 0.01, 1000);
    svm.splitFeaturesAndLabels(DtSVM, X, y);
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
