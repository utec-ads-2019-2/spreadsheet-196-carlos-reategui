#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

vector<string> splitCellFormula(string cell);
pair<int, int> cellPosition(const string& cell);
unsigned int getColumn(const string& column);
void enterSpreadSheet();
void printSpreadSheet();
int getCell(unsigned int column, unsigned int row);
int spreadSheetToInt(unsigned int column, unsigned int row);

unsigned int spreadSheetsToEvaluate, columnsOfSpreadSheet, rowsOfSpreadSheet;
vector<vector<int>> intSpreadSheet;
vector<vector<string>> spreadSheet;
auto minNumber = INT_MIN;

void enterSpreadSheet() {
    auto constructIntSpreadSheet = new vector<vector<int>>(rowsOfSpreadSheet, vector<int>(columnsOfSpreadSheet,
            minNumber));
    auto constructSpreadSheet = new vector<vector<string>>(rowsOfSpreadSheet, vector<string>(columnsOfSpreadSheet));
    intSpreadSheet = *constructIntSpreadSheet;
    spreadSheet = *constructSpreadSheet;
    delete constructIntSpreadSheet;
    delete constructSpreadSheet;
    for (unsigned int row = 0; row < rowsOfSpreadSheet; ++row)
        for (unsigned int column = 0; column < columnsOfSpreadSheet; ++column)
            cin >> spreadSheet[row][column];
}

void printSpreadSheet() {
    for (unsigned int row = 0; row < rowsOfSpreadSheet; ++row) {
        for (unsigned int column = 0; column < columnsOfSpreadSheet; ++column) {
            cout << (column > 0 ? " " : "");
            cout << getCell(column, row);
        }
        cout << '\n';
    }
}

int spreadSheetToInt(unsigned int column, unsigned int row) {
    return stoi(spreadSheet[row][column]);
}

pair<int, int> cellPosition(const string& cell) {
    string row, column;
    for (char c : cell) isalpha(c) ? column += c : row += c;
    return make_pair(stoi(row) - 1, getColumn(column));
}

vector<string> splitCellFormula(string cell) {
    cell.erase(remove(cell.begin(), cell.end(), '='), cell.end());
    stringstream ss(cell);
    string token;
    vector<string> splitCell;
    while(getline(ss, token, '+')) splitCell.push_back(token);
    return splitCell;
}

unsigned int getColumn(const string& column) {
    unsigned int columnToInt = 0;
    for (char c : column) columnToInt = 26 * columnToInt + c - 65 + 1;
    return columnToInt - 1;
}

int getCell(unsigned int column, unsigned int row) {
    if (isdigit(spreadSheet[row][column][0]) or spreadSheet[row][column][0] == '-') {
        intSpreadSheet[row][column] = spreadSheetToInt(column, row);
        return spreadSheetToInt(column, row);
    }
    if (intSpreadSheet[row][column] != minNumber) return intSpreadSheet[row][column];
    vector<string> cells = splitCellFormula(spreadSheet[row][column]);
    int cellResult = 0;
    for (const string& cell : cells) {
        pair<int, int> currentCellPosition = cellPosition(cell);
        cellResult += getCell(currentCellPosition.second, currentCellPosition.first);
    }
    intSpreadSheet[row][column] = cellResult;
    return cellResult;
}

int main() {
    cin >> spreadSheetsToEvaluate;
    for (unsigned int i = 0; i < spreadSheetsToEvaluate; ++i) {
        cin >> columnsOfSpreadSheet >> rowsOfSpreadSheet;
        enterSpreadSheet();
        printSpreadSheet();
    }
    return EXIT_SUCCESS;
}