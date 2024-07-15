//#include <iostream>
//#include "Data.h"
//using namespace std;
//
//int main() {
//    string filepath = "D:/Internship/DHub & ODC/Code/TASK/DataSet/Train.csv";
//    Data obj(filepath);
//    DataFrame df = obj.load(filepath);
//
//    // Open a file to write data for the bar chart
//    ofstream dataFile("Dat/BarPlot To Product_importance.dat");
//    map<string, int>m = obj.value_counts(df, "Product_importance");
//    for (auto pair : m) {
//        dataFile << pair.first << " " << pair.second << "\n";
//
//    }
//
//    // Close the data file
//    dataFile.close();
//
//    // Gnuplot commands
//    // Output to PNG file and plot bar chart
//    system("gnuplot -e \"set terminal pngcairo size 800,600; "
//        "set output 'Visualization/BarPlot_To_Product_importance.png'; "
//        "set style data histograms; "
//        "set style fill solid; "
//        "set boxwidth 0.8; "
//        "set title 'Bar Chart to Product_importance'; "
//        "set ylabel 'Values'; "
//        "set xlabel 'Categories'; "
//        "plot 'Dat/BarPlot To Product_importance.dat' using 2:xtic(1) title 'Bar Chart';\"");
//
//    cout << "Bar chart plotted as 'BarPlot To Product_importance" << endl;
//
//}
