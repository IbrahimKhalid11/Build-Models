//#include <iostream>
//#include "Data.h"
//using namespace std;
//
//int main() {
//    string filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/drug200.csv";
//    Data obj(filepath);
//    DataFrame df = obj.load(filepath);
//
//    // Open a file to write data for the bar chart
//    ofstream dataFile("Dat/BarPlot Between Drug and Cholesterol.dat");
//    map<string, map<string, int>>m;
//
//    for (int j = 1; j < df.size(); j++) {
//        string cholesterolType = df[j][3];
//        string gender = df[j][5];
//        m[cholesterolType][gender]++;
//    }
//
//    for (const auto& outerPair : m) {
//        for (const auto& innerPair : outerPair.second) {
//            dataFile << outerPair.first << "_" << innerPair.first << " " << innerPair.second << "\n";
//        }
//    }
//
//    // Close the data file
//    dataFile.close();
//
//    // Gnuplot command
//    // Output to PNG file and plot bar chart
//    system("gnuplot -e \"set terminal pngcairo size 1200,600; "
//        "set output 'Visualization/BarPlot_To_Drug_and_Cholesterol.png'; "
//        "set style data histograms; "
//        "set style fill solid; "
//        "set boxwidth 0.8; "
//        "set title 'Bar Chart Example'; "
//        "set ylabel 'Values'; "
//        "set xlabel 'Drug Type and Cholesterol'; "
//        "plot 'Dat/BarPlot Between Drug and Cholesterol.dat' using 2:xtic(1) title 'Bar Chart';\"");
//
//    cout << "Bar chart plotted as 'BarPlot To Drug and Cholesterol'" << endl;
//
//}
