//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_DEPRECATE
//#include <stdio.h>
//#include <iostream>
//#include "Data.h"
//using namespace std;
//
//int main() {
//    FILE* fp = NULL;
//    FILE* gnupipe = NULL;
//
//    // Commands to create a heatmap plot with labels
//    const char* GnuCommands[] = {
//        "set title \"Heatmap with Correlation Values\"",
//        "set xlabel \"Variable X\"",
//        "set ylabel \"Variable Y\"",
//        "unset key",
//        "set tic scale 0",
//        "set palette rgbformulae 33,13,10",
//        "set cbrange [-1:1]",
//        "set cblabel \"Correlation\"",
//        "set xtics out nomirror",
//        "set ytics out nomirror",
//        "set autoscale xfix",
//        "set autoscale yfix",
//        "set xrange [0:10]",
//        "set yrange [0.5:9.5]",
//        "set style fill solid 1.0 border -1"
//    };
//
//    // Example of a 5x5 correlation matrix
//    string filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/mushroom_cleaned.csv";
//    Data obj(filepath);
//    
//    DataFrame df = obj.load(filepath);
//
//
//
//    vector<vector<double>>dbData=obj.loadCSVAsFloatVector(df);
//    vector<vector<double>>correlation_matrix(dbData[0].size(), vector<double>(dbData[0].size()));
//    for (int i = 0; i < dbData[0].size(); ++i) {
//        for (int j = 0; j < dbData[0].size(); ++j) {
//            correlation_matrix[i][j] = (obj.calculateCorrelation(dbData, i, j));
//        }
//    }
//    for (int i = 0; i < correlation_matrix.size(); i++) {
//        for (int j = 0; j < correlation_matrix[i].size(); j++) {
//            cout << correlation_matrix[i][j];
//        }
//        cout << endl;
//    }
//    //double correlation_matrix[5][5] = {
//    //    {1.0, 0.1, 0.2, 0.3, 0.4},
//    //    {0.1, 1.0, 0.5, 0.6, 0.7},
//    //    {0.2, 0.5, 1.0, 0.8, 0.9},
//    //    {0.3, 0.6, 0.8, 1.0, 0.2},
//    //    {0.4, 0.7, 0.9, 0.2, 1.0}
//    //};
//
//    // Open data file for writing the correlation matrix
//    fp = fopen("data.tmp", "w");
//    if (fp == NULL) {
//        perror("Error opening data file");
//        return 1; // Exit if file opening failed
//    }
//
//    //// Write the correlation matrix to the file with x and y coordinates
//    for (int i = 0; i < correlation_matrix.size(); i++) {
//        for (int j = 0; j < correlation_matrix[i].size(); j++) {
//            fprintf(fp, "%d %d %f\n", i + 1, j + 1, correlation_matrix[i][j]);
//        }
//        fprintf(fp, "\n");
//    }
//    fclose(fp); // Close the file
//
//    ////// Open gnuplot pipe
//    gnupipe = _popen("gnuplot -persist", "w");
//    if (gnupipe == NULL) {
//        perror("Error opening gnuplot");
//        return 1; // Exit if gnuplot pipe opening failed
//    }
//
//    ////// Send the Gnuplot commands to create the heatmap
//    for (const char* command : GnuCommands) {
//        fprintf(gnupipe, "%s\n", command);
//    }
//
//    ////// Plot the heatmap with labels
//    fprintf(gnupipe, "plot 'data.tmp' using 1:2:3 with image, '' using 1:2:(sprintf(\"%.2f\", $3)) with labels font 'Arial,8' textcolor rgb 'black'\n");
//
//    _pclose(gnupipe); // Close the pipe
//    return 0;
//}
