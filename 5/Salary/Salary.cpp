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
#include "LinearRegression.h"
#include "RandomForest.h"
#include "PCA.h"
#include "KNN.h"
using namespace std;
int main() {
    string filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/Salary.csv";
    Data obj(filepath);

    DataFrame df = obj.load(filepath);
    obj.print(df);            // Print the first 5 rows
    for (int i = 20; i < 42; i++)
    {
    obj.dropColumnsFromIndices(df, { 20 });

    }
    //    obj.print(df,df.size());   // Print all rows


    cout << endl << "*****************************************************" << endl;

    auto sh = obj.shape(df);             // found the shape
    cout << "shape: " << "ROWS : " << sh.first << " , COLUMNS : " << sh.second << endl;

    cout << endl << "*****************************************************" << endl;
    df = obj.selectColumns(df, { "Lower Salary","Upper Salary","Avg Salary(K)" });
    vector<string> columns = df[0];  // print name of columns
    cout << "columns : ";
    int ind = 0;
    for (string column : columns) {
        cout << column <<" "<<obj.checkValueType(df[1][ind]) << " \n ";
        ind++;
    }

    obj.print(df);            // Print the first 5 rows

    //cout << endl << "*****************************************************" << endl;

    obj.info(df);

    cout << endl << "************************Unique*****************************" << endl;
    //Warehouse_block Mode_of_Shipment Customer_care_calls Customer_rating Cost_of_the_Product Prior_purchases Product_importance Gender Discount_offered Weight_in_gms Reached.on.Time_Y.N

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

    //cout << endl << "********************SCALER**************************" << endl << endl;

    //vector<vector<double>> scaledData = obj.standardScaler(dbData, { 0,4,5 });
    //obj.printof2D(scaledData, columns);


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

    vector<int>continousColumn = { 0,4,5,7 };
    obj.feature_selection(df, dbData, 0.1, "Mutual_Information", continousColumn);

    cout << "\n //////////////////////////////PCA\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n";

    vector<vector<double>> X;
    vector<double> y;
    obj.splitFeaturesAndLabels(dbData, X, y);

    PCA pca(1); // Reduce to 1 principal component
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



    cout << "\n //////////////////////////////MODELS\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n";
    cout << " 1 - LinearRegression \n";
    vector<vector<double>>DtLinear = dbData;


    int num_samples = DtLinear.size();

    LinearRegression lr;
    int k = 5; // Number of folds
    vector<vector<int>> folds = lr.kFoldSplit(num_samples, k);
    double total_accuracy = 0.0;

    for (int i = 0; i < k; ++i) {

        vector<vector<double>> trainData, testData;
        vector<double> trainLabels, testLabels;

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
        vector<double> predictions = lr.predict(testData);

        // Output the results
        cout << "Coefficients: ";
        for (const auto& coef : lr.getCoefficients()) {
            cout << coef << " ";
        }
        cout << endl;

        cout << "Predictions: ";
        int cnt = 0;
        //for (double pred : predictions) {
        //    cout << pred << " "<< testLabels[cnt++]<<endl;
        //}
        cout << endl;

        double mse = lr.calculateMSE(testLabels, predictions);
        double rmse = lr.calculateRMSE(testLabels, predictions);
        double rSquared = lr.calculateRSquared(testLabels, predictions);
        cout << "Fold " << i + 1 << endl;
        cout << "MSE: " << mse << endl;
        cout << "RMSE: " << rmse << endl;
        cout << "R-squared: " << rSquared << endl;

    }
    cout << "\n \n 2-KNNRegressor \n\n";
    KNNRegressor knn(2);
    k = 5; // Number of folds
    folds = knn.kFoldSplit(num_samples, k);
    total_accuracy = 0.0;

    for (int i = 0; i < k; ++i) {
        vector<vector<double>> trainData, testData;
        vector<double> trainLabels, testLabels;

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

        knn.fit(trainData, trainLabels);
        vector<double> predictions = knn.predict(testData);

        cout << "Predictions: ";
        int cnt = 0;

        cout << "\n";
        double mse = knn.calculateMSE(testLabels, predictions);
        double rmse = knn.calculateRMSE(testLabels, predictions);
        double rSquared = knn.calculateRSquared(testLabels, predictions);
        cout << "Fold " << i + 1 << endl;
        cout << "MSE: " << mse << endl;
        cout << "RMSE: " << rmse << endl;
        cout << "R-squared: " << rSquared << endl;
    }

    

    return 0;

};
