#pragma once
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
#include <iomanip>
#include <cstdlib>
using namespace std;

typedef vector<vector<string>> DataFrame;

//vector<vector<double>> v;
vector<string> dates;

class Data {
public:
    DataFrame df;

    Data(const string filepath) {
        DataFrame df = load(filepath);
        for (const auto& row : df) {
            dates.push_back(row[0]);  // Add the date to the vector
        }
    }

    DataFrame load(const string& filepath) {
        DataFrame df;
        ifstream file(filepath);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filepath << endl;
            return df;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string cell;
            vector<string> row;
            while (getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            df.push_back(row);
        }

        return df;
    }

    void print(const DataFrame& df, int numRows = 5) {
        if (df.empty()) return;

        vector<int> col_max_width(df[0].size(), 0); // Store max width per column
        for (const vector<string>& current_row : df) {
            for (int i = 0; i < current_row.size(); ++i) {
                if (current_row[i].size() > col_max_width[i]) {
                    col_max_width[i] = current_row[i].size();
                }
            }
        }

        int rowCount = 0;
        for (const vector<string>& row : df) {
            for (int i = 0; i < row.size(); ++i) {
                int padding = col_max_width[i] - row[i].size();
                int left = padding / 2;
                int right = padding - left;

                for (int j = 0; j < left; ++j) {
                    cout << " ";
                }

                cout << row[i];

                for (int j = 0; j < right; ++j) {
                    cout << " ";
                }

                cout << " ";
            }
            cout << endl;
            ++rowCount;
            if (rowCount >= numRows + 1) {
                break;
            }
        }
    }
    void printof2D(const vector<vector<double>>& data, const vector<string>& columnNames, int numRows = 5) {
        if (data.empty() || columnNames.empty()) return;

        vector<int> col_max_width(columnNames.size(), 0);

        // Update max width based on column names
        for (int i = 0; i < columnNames.size(); ++i) {
            if (columnNames[i].size() > col_max_width[i]) {
                col_max_width[i] = columnNames[i].size();
            }
        }

        // Calculate max width per column based on data
        for (const auto& current_row : data) {
            for (int i = 0; i < current_row.size(); ++i) {
                stringstream ss;
                ss << current_row[i];
                if (ss.str().size() > col_max_width[i]) {
                    col_max_width[i] = ss.str().size();
                }
            }
        }

        // Print column names
        for (int i = 0; i < columnNames.size(); ++i) {
            int padding = col_max_width[i] - columnNames[i].size();
            int left = padding / 2;
            int right = padding - left;

            for (int j = 0; j < left; ++j) {
                cout << " ";
            }

            cout << columnNames[i];

            for (int j = 0; j < right; ++j) {
                cout << " ";
            }

            cout << " ";
        }
        cout << endl;

        // Print data
        int rowCount = 0;
        for (const auto& row : data) {
            for (int i = 0; i < row.size(); ++i) {
                stringstream ss;
                ss << row[i];
                string cell = ss.str();

                int padding = col_max_width[i] - cell.size();
                int left = padding / 2;
                int right = padding - left;

                for (int j = 0; j < left; ++j) {
                    cout << " ";
                }

                cout << cell;

                for (int j = 0; j < right; ++j) {
                    cout << " ";
                }

                cout << " ";
            }
            cout << endl;
            ++rowCount;
            if (rowCount >= numRows + 1) {
                break;
            }
        }
    }
    vector<vector<double>> loadCSVAsFloatVector(const DataFrame& df) {
        if (df.empty() || df[0].empty()) {
            return {};
        }

        // Creating a 2D vector with dimensions adjusted for skipping the first row
        vector<vector<double>> data(df.size() - 1, vector<double>(df[0].size()));

        for (int i = 0; i < df[0].size(); i++) {
            for (int j = 1; j < df.size(); j++) { // Start from the second row (index 1)
                data[j - 1][i] = stod(df[j][i]); // Adjust the index in the data vector
            }
        }

        return data;
    }
    void dropColumnByIndex(vector<vector<string>>& dataframe, size_t columnIndex) {
        // Check if the columnIndex is valid

        if (columnIndex >= dataframe[0].size()) {
            cout << "Invalid column index." << endl;
            return;
        }
        cout << "Drop Column : " << dataframe[0][columnIndex] << endl;

        // Remove the column from each row
        for (auto& row : dataframe) {
            if (row.size() > columnIndex) {
                row.erase(row.begin() + columnIndex);
            }
        }
    }
    void dropColumnByIndexDouble(vector<vector<double>>& dataframe, size_t columnIndex) {
        // Check if the columnIndex is valid

        if (columnIndex >= dataframe[0].size()) {
            cout << "Invalid column index." << endl;
            return;
        }
        cout << "Drop Column : " << dataframe[0][columnIndex] << endl;

        // Remove the column from each row
        for (auto& row : dataframe) {
            if (row.size() > columnIndex) {
                row.erase(row.begin() + columnIndex);
            }
        }
    }
    string checkValueType(const std::string& value) {
        // Check if the value is an integer
        std::istringstream intStream(value);
        int intValue;
        if (intStream >> intValue && intStream.eof()) {
            return "Integer";
        }

        // Check if the value is a double
        std::istringstream doubleStream(value);
        double doubleValue;
        if (doubleStream >> doubleValue && doubleStream.eof()) {
            return "Double";
        }

        // Check if the value is a character
        if (value.length() == 1) {
            return "Character";
        }

        return "String";
    }
    void info(const DataFrame& df) {
        // Print basic info
        std::cout << "DataFrame info:\n";
        std::cout << "Number of rows: " << df.size() << "\n";
        std::cout << "Number of columns: " << df[0].size() << "\n\n";

        // Print column data types and non-null counts
        std::cout << "Column data types and non-null counts:\n";
        for (int i = 0; i < df[0].size(); ++i) {
            size_t non_null_count = 0;
            for (int j = 0; j < df.size(); ++j) {

                if (df[j][i] == "Nan" or df[j][i] == "nan" or df[j][i] == "NAN" or df[j][i].empty()) {
                    non_null_count++;
                }
            }
            cout << endl;
            string dtype;
            for (int j = 1; j < df.size(); ++j) {
                if (!(df[j][i] == "Nan" or df[j][i] == "nan" or df[j][i] == "NAN" or df[j][i].empty())) {
                    dtype = checkValueType(df[j][i]);
                    break;
                }

            }
            cout << "Column " << i + 1 << ": ";
            cout << "dtype: " << dtype << ", ";
            cout << "null count: " << non_null_count << "\n";
        }

        // Memory usage
        size_t memory_usage = df.size() * df[0].size() * sizeof(double); // Assuming double type elements
        std::cout << "\nMemory usage: " << memory_usage << " bytes\n";
    }


    vector<double> MaxForColumn(const vector<vector<double>>& data) {
        vector<double> ans;
        int numColumns = data[0].size();
        for (int col = 0; col < numColumns; ++col) {
            double mx = numeric_limits<double>::min();
            for (const auto& row : data) {
                if (mx < row[col]) {
                    mx = row[col];
                }
            }
            ans.push_back(mx);
        }
        return ans;
    }

    vector<double> MinForColumn(const vector<vector<double>>& data) {
        vector<double> ans;
        int numColumns = data[0].size();
        for (int col = 0; col < numColumns; ++col) {
            double mn = numeric_limits<double>::max();
            for (const auto& row : data) {
                if (mn > row[col]) {
                    mn = row[col];
                }
            }
            ans.push_back(mn);
        }
        return ans;
    }

    vector<double> calculateMean(const vector<vector<double>>& data) {
        vector<double> columnMeans;
        if (data.empty() || data[0].empty()) {
            return columnMeans;  // Return an empty vector
        }
        int numColumns = data[0].size();
        for (int col = 0; col < numColumns; ++col) {
            double sum = 0.0;
            int count = 0;

            for (const auto& row : data) {
                sum += row[col];
                count++;
            }
            double mean = sum / count;
            columnMeans.push_back(mean);
        }

        return columnMeans;
    }

    vector<double> calculateMedian(const vector<vector<double>>& data) {
        vector<double> columnMedians;
        if (data.empty() || data[0].empty()) {
            return columnMedians;
        }
        int numColumns = data[0].size();
        for (int col = 0; col < numColumns; ++col) {
            vector<double> columnValues;
            for (const auto& row : data) {
                columnValues.push_back(row[col]);
            }
            sort(columnValues.begin(), columnValues.end());
            double median;
            int n = columnValues.size();
            if (n % 2 == 0) {
                median = (columnValues[n / 2 - 1] + columnValues[n / 2]) / 2.0;
            }
            else {
                median = columnValues[n / 2];
            }
            columnMedians.push_back(median);
        }
        return columnMedians;
    }

    vector<double> calculateMode(const vector<vector<double>>& data) {
        vector<double> columnModes;
        if (data.empty() || data[0].empty()) {
            return columnModes;
        }
        int numColumns = data[0].size();
        for (int col = 0; col < numColumns; ++col) {
            map<double, int> freqMap;
            for (const auto& row : data) {
                freqMap[row[col]]++;
            }
            double mode = data[0][col];
            int maxFreq = freqMap[mode];
            for (const auto& pair : freqMap) {
                if (pair.second > maxFreq) {
                    mode = pair.first;
                    maxFreq = pair.second;
                }
            }
            columnModes.push_back(mode);
        }

        return columnModes;
    }

    vector<double> calculateVariances(const vector<vector<double>>& data) {
        vector<double> columnMeans = calculateMean(data);
        vector<double> columnVariances;
        if (data.empty() || data[0].empty()) {
            return columnVariances;
        }
        int numColumns = data[0].size();
        for (int col = 0; col < numColumns; ++col) {
            double sumSquaredDiff = 0.0;
            int count = 0;
            for (const auto& row : data) {
                double diff = row[col] - columnMeans[col];
                sumSquaredDiff += diff * diff;
                count++;
            }
            double variance = sumSquaredDiff / (count - 1);
            columnVariances.push_back(variance);
        }

        return columnVariances;
    }

    vector<double> calculateStandardDeviations(const vector<vector<double>>& data) {
        vector<double> columnVariances = calculateVariances(data);
        vector<double> standardDeviations;
        for (double variance : columnVariances) {
            double standardDeviation = sqrt(variance);
            standardDeviations.push_back(standardDeviation);
        }
        return standardDeviations;
    }

    void printTable(const vector<string>& columnNames, const vector<string>& titles, const vector<vector<double>>& values) {
        int numColumns = columnNames.size();
        int numRows = values.size();

        // Calculate column widths for padding
        vector<int> columnWidths(numColumns);
        for (int i = 0; i < numColumns; ++i) {
            columnWidths[i] = max(static_cast<int>(columnNames[i].size()), 10); // Minimum width 10 characters
        }

        // Print column names in the first row
        cout << setw(18) << "Column" << " | ";
        for (int i = 0; i < numColumns; ++i) {
            cout << left << setw(columnWidths[i]) << columnNames[i] << " | ";
        }
        cout << endl;

        // Print separator line
        cout << string(18, '-') << " | ";
        for (int i = 0; i < numColumns; ++i) {
            cout << string(columnWidths[i], '-') << " | ";
        }
        cout << endl;

        // Print titles in the first column and values in the table
        for (int i = 0; i < numRows; ++i) {
            cout << setw(18) << titles[i] << " | ";
            for (int j = 0; j < numColumns; ++j) {
                cout << setw(columnWidths[j]) << values[i][j] << " | ";
            }
            cout << endl;
        }
    }



    //void DataQuality(const vector<vector<double>>& data) {
    //    vector<double> means = calculateMean(data);

    //    // Calculate mean of means
    //    double overallMeanOfMeans = accumulate(means.begin(), means.end(), 0.0) / means.size();

    //    // Calculate column variances
    //    vector<double> variances = calculateVariances(data);

    //    // Calculate mean of variances
    //    double overallMeanOfVariances = accumulate(variances.begin(), variances.end(), 0.0) / variances.size();

    //    // Calculate standard deviation of column variances
    //    double varianceOfVariances = 0.0;
    //    for (double variance : variances) {
    //        varianceOfVariances += pow(variance - overallMeanOfVariances, 2);
    //    }
    //    varianceOfVariances /= variances.size();
    //    double stdDevOfVariances = sqrt(varianceOfVariances);

    //    // Print evaluation results
    //    cout << "Data Quality :\n";
    //    cout << "Means: " << overallMeanOfMeans << "\n";
    //    cout << "Variances: " << overallMeanOfVariances << "\n";
    //    cout << "Standard Deviation of Column Variances: " << stdDevOfVariances << "\n";
    //    if (overallMeanOfMeans > 0 && overallMeanOfVariances < 1.0) {
    //        cout << "Data quality is good. The means are consistent and variance is within an acceptable range.\n";
    //    }
    //    else {
    //        cout << "Data quality may need further investigation. Check for outliers or data distribution issues.\n";
    //    }
    //}

    vector<vector<int>> detectOutliersIQR(vector<vector<double>>& data) {
        vector<vector<int>> outliers;

        // Check if the input data is empty
        if (data.empty() || data[0].empty()) {
            return outliers;
        }

        // Get the number of columns and rows in the data
        int numColumns = data[0].size();
        int numRows = data.size();

        // Resize the outliers vector to hold results for each column
        outliers.resize(numColumns);

        // Iterate through each column
        for (int j = 0; j < numColumns; ++j) {
            // Create a temporary vector to store column data
            vector<double> columnData(numRows);

            // Extract the data from the column
            for (int i = 0; i < numRows; ++i) {
                columnData[i] = data[i][j];
            }

            // Sort the column data in ascending order
            sort(columnData.begin(), columnData.end());

            // Calculate the quartiles and the Interquartile Range (IQR)
            double Q1 = columnData[numRows / 4];
            double Q3 = columnData[3 * numRows / 4];
            double IQR = Q3 - Q1;

            // Calculate the lower and upper bounds for outliers
            double lowerBound = Q1 - 1.5 * IQR;
            double upperBound = Q3 + 1.5 * IQR;

            // Identify outliers and store their indices in the outliers vector
            for (int i = 0; i < numRows; ++i) {
                if (data[i][j] < lowerBound || data[i][j] > upperBound) {
                    outliers[j].push_back(i);
                }
            }
        }

        return outliers;
    }

    vector<vector<double>> standardScaler(vector<vector<double>>& data, const vector<int>& columnsToScale) {
        int numFeatures = data[0].size();
        int numSamples = data.size();
        vector<double> mean(numFeatures, 0.0);
        vector<double> stdDev(numFeatures, 0.0);

        // Calculate mean
        for (const auto& row : data) {
            for (int i = 0; i < numFeatures; ++i) {
                mean[i] += row[i];
            }
        }
        for (int i = 0; i < numFeatures; ++i) {
            mean[i] /= numSamples;
        }

        // Calculate standard deviation
        for (const auto& row : data) {
            for (int i = 0; i < numFeatures; ++i) {
                stdDev[i] += pow(row[i] - mean[i], 2);
            }
        }
        for (int i = 0; i < numFeatures; ++i) {
            stdDev[i] = sqrt(stdDev[i] / numSamples);
        }

        // Scale the specified columns
        vector<vector<double>> scaledData(numSamples, vector<double>(numFeatures));
        for (int i = 0; i < numSamples; ++i) {
            for (int j = 0; j < numFeatures; ++j) {
                if (find(columnsToScale.begin(), columnsToScale.end(), j) != columnsToScale.end() && stdDev[j] != 0) {
                    scaledData[i][j] = (data[i][j] - mean[j]) / stdDev[j];
                }
                else {
                    scaledData[i][j] = data[i][j];
                }
            }
        }

        return scaledData;
    }

    double calculateCorrelation(const vector<vector<double>>& data, int col1, int col2) {
        if (data.empty() || data[0].size() <= col1 || data[0].size() <= col2) {
            cerr << "DataFrame is empty or column index is out of range" << endl;
            return 0.0;
        }

        int n = data.size();
        vector<double> x, y;

        // Extracting the values from the specified columns
        for (const auto& row : data) {
            x.push_back(row[col1]);
            y.push_back(row[col2]);
        }

        double sum_x = accumulate(x.begin(), x.end(), 0.0);
        double sum_y = accumulate(y.begin(), y.end(), 0.0);
        double sum_xy = 0.0, sum_x2 = 0.0, sum_y2 = 0.0;

        for (int i = 0; i < n; ++i) {
            sum_xy += x[i] * y[i];
            sum_x2 += x[i] * x[i];
            sum_y2 += y[i] * y[i];
        }

        double numerator = n * sum_xy - sum_x * sum_y;
        double denominator = sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));

        if (denominator == 0) {
            cerr << "Denominator is zero, correlation cannot be calculated" << endl;
            return 0.0;
        }

        return numerator / denominator;
    }



    pair<int, int> shape(const DataFrame& df) {
        if (df.empty())
            return { 0, 0 };
        return { df.size() , df[0].size() }; // Exclude the header row
    }

    vector<int> count_missing_values(const DataFrame& df) {
        vector<int> missing(df[0].size());

        for (int col = 0; col < df[0].size(); col++) {
            for (int row = 0; row < df.size(); row++) {
                if (df[row][col].empty())
                    missing[col]++;
            }
        }

        return missing;
    }


    //int count_Duplicated(const DataFrame& df) {
    //    int duplicate = 0;
    //    set<string> seen;

    //    for (const auto& row : df) {
    //        string line = accumulate(row.begin(), row.end(), string()); // Concatenate
    //        if (seen.find(line) != seen.end()) {
    //            duplicate++;
    //        }
    //        else {
    //            seen.insert(line);
    //        }
    //    }

    //    return duplicate;
    //}

    //void remove_duplicated(DataFrame& df) {
    //    set<string> seen;
    //    df.erase(remove_if(df.begin(), df.end(), [&seen](const vector<string>& row) {
    //        string Row = accumulate(row.begin(), row.end(), string());
    //        return !seen.insert(Row).second;
    //        }), df.end()); // Using set auto
    //}

    map<string, int> value_counts(const DataFrame& df, const string& column_name) {
        map<string, int> counts;

        int columnIndex = 0;
        for (int i = 0; i < df[0].size(); i++) {
            if (df[0][i] == column_name) {
                columnIndex = i;
                break;
            }
        }

        for (int r = 1; r < df.size(); r++) { // Start from row 1 to skip header
            counts[df[r][columnIndex]]++;
        }

        cout << column_name << endl;

        for (const auto& pair : counts) {
            cout << pair.first << ": " << pair.second << endl;
        }
        return counts;
    }

    void unique(const DataFrame& df, const string& column_name) {
        set<string> unique_Val;

        int columnIndex = 0;
        for (int i = 0; i < df[0].size(); i++) {
            if (df[0][i] == column_name) {
                columnIndex = i;
                break;
            }
        }

        for (int row = 1; row < df.size(); row++) {
            if (df[row][columnIndex] == "121422")cout << row << '\n \n';
            unique_Val.insert(df[row][columnIndex]);
        }

        cout << '*' << column_name << endl;

        for (const auto& res : unique_Val) {
            cout << res << ", ";
        }
        cout << endl << endl;

    }

    //void renameColumn(DataFrame& df, const string& old_name, const string& new_name) {
    //    for (int i = 0; i < df[0].size(); i++) {
    //        if (df[0][i] == old_name) {
    //            df[0][i] = new_name;
    //            break;
    //        }
    //    }
    //}

    void replace(DataFrame& df, const string& columnName, const string& old_value, const string& new_value) {
        int col_index = 0;
        for (int i = 0; i < df[0].size(); i++) { // Find the index of the column
            if (df[0][i] == columnName) {
                col_index = i;
                break;
            }
        }

        for (int row = 1; row < df.size(); ++row) { // Start from row 1 to skip header
            if (df[row][col_index] == old_value)
                df[row][col_index] = new_value;
        }
    }


    ///////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


    double calculate_entropy(const vector<double>& values) {
        map<double, double> freq;
        for (double value : values) {
            freq[value]++;
        }
        double entropy = 0.0;
        double total = values.size();
        for (const auto& pair : freq) {
            double p = static_cast<double>(pair.second) / total;
            entropy -= p * log2(p);
        }
        return entropy;
    }

    // Function to calculate joint entropy
    double calculate_joint_entropy(const vector<double>& feature, const vector<double>& target) {
        map<double, map<double, double>> joint_freq;
        double total = feature.size();
        for (size_t i = 0; i < feature.size(); ++i) {
            joint_freq[feature[i]][target[i]]++;
        }
        double joint_entropy = 0.0;
        for (const auto& feature_pair : joint_freq) {
            for (const auto& target_pair : feature_pair.second) {
                double p = static_cast<double>(target_pair.second) / total;
                joint_entropy -= p * log2(p);
            }
        }
        return joint_entropy;
    }

    // Function to calculate mutual information
    double calculate_mutual_information(const vector<double>& feature, const vector<double>& target) {
        double H_X = calculate_entropy(feature);
        double H_Y = calculate_entropy(target);
        double H_XY = calculate_joint_entropy(feature, target);
        return H_X + H_Y - H_XY;
        //return 0.0;
    }

    // Function to discretize a vector of doubles into bins
    vector<double> discretize(const vector<double>& data, double num_bins) {
        vector<double> discretized_data(data.size());
        vector<double> sorted_data = data;
        sort(sorted_data.begin(), sorted_data.end());

        double bin_size = data.size() / static_cast<double>(num_bins);
        for (size_t i = 0; i < data.size(); ++i) {
            double bin = lower_bound(sorted_data.begin(), sorted_data.end(), data[i]) - sorted_data.begin();
            discretized_data[i] = static_cast<double>(bin / bin_size);
            //cout << discretized_data[i] << endl;
        }
        return discretized_data;
    }




    vector<vector<double>> feature_selection(DataFrame df, vector<vector<double>>& data, double threshold, string Way, vector<int>continousColumn = {}, double num_bins = 10) {
        if (Way == "curr") {
            vector<vector<double>>correlation_matrix(data[0].size(), vector<double>(data[0].size()));
            for (int i = 0; i < data[0].size(); ++i) {
                for (int j = 0; j < data[0].size(); ++j) {
                    correlation_matrix[i][j] = (calculateCorrelation(data, i, j));
                }
            }
            vector<int> index;
            cout << "Feature Selection by correlation \n";
            for (int i = 0; i < data[0].size() - 1; ++i) {
                if (abs(correlation_matrix[i][correlation_matrix.size() - 1]) >= threshold) {
                    cout << "Feature : " << df[0][i] << endl;
                    index.push_back(i);
                }


            }
            vector<vector<double>> feature(data.size(), vector<double>(data[0].size()));
            for (size_t i = 0; i < index.size(); i++)
            {
                for (int j = 0; j < df.size(); ++j) {

                    //   cout << df[j][index[i]] << " ";
                    if (j != df.size() - 1) {
                        feature[j][i] = data[j][index[i]];
                    }
                }
                cout << endl;
            }
            return feature;
        }
        else if (Way == "Mutual_Information") {
            vector<vector<double>> data_T;
            data_T = transposeMatrix(data);
            vector<double> target;
            for (int j = 0; j < data_T[0].size(); ++j) {
                target.push_back(data_T[data_T.size() - 1][j]);
            }
            vector<vector<double>> mi_scores(data_T.size(), vector<double>(data_T[0].size()));
            int j = 0;
            cout << "Mutual_Information of each Feature : ";
            for (int i = 0;i < data_T.size() - 1;i++) {
                if (find(continousColumn.begin(), continousColumn.end(), i) != continousColumn.end()) {
                    vector<double> discretized_feature = discretize(data_T[i], num_bins);
                    double mi = calculate_mutual_information(discretized_feature, target);
                    mi_scores[i].push_back(mi);
                    cout << mi << " ";
                }
                else {
                    double mi = calculate_mutual_information(data_T[i], target);
                    mi_scores[i].push_back(mi);
                    cout << mi << " ";
                }
            }
            return mi_scores;
        }
    }








    void show(const vector<vector<double>>& m, int size) {
        for (int i = 0; i < size && i < m.size(); ++i) {
            for (int j = 0; j < size && j < m[i].size(); ++j) {
                cout << m[i][j] << " ";
            }
            cout << "\n";
        }
    }

    //vector<vector<double>> select(int column, const vector<vector<double>>& v) {
    //    vector<vector<double>> ans(v.size(), vector<double>(1));
    //    for (int i = 0; i < v.size(); ++i) {
    //        ans[i][0] = v[i][column];
    //    }
    //    return ans;
    //}
    vector<vector<double>> transposeMatrix(const vector<vector<double>>& matrix) {
        if (matrix.empty()) return {};

        int rows = matrix.size();
        int cols = matrix[0].size();

        vector<vector<double>> transposed(cols, vector<double>(rows));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                transposed[j][i] = matrix[i][j];
            }
        }

        return transposed;
    }
};

