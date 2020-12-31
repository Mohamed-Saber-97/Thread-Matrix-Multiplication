#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <pthread.h>
#include <fstream>
#include <stdio.h>
using namespace std::chrono;
using namespace std;
fstream InputFile,OutputFile;
//Loop counters
int i=0,j=0,k=0;
//Reading and strong the matrix 1 and 2 from the input file
void ReadFromFile(vector<vector<int>>& Matrix1, vector<vector<int>>& Matrix2)
{
    InputFile.open("input.txt",ios::in);
    int Rows, Columns,Temp;
    //Reading first int to get number of rows and second to get number of columns for the first Matrix
    InputFile >> Rows;
    InputFile >> Columns;
    //Storing Data to Matrix1
    i=0;
    while(i<Rows)
    {
        vector<int> RowTemp;
        k=0;
        while(k<Columns)
        {
            InputFile >> Temp;
            RowTemp.push_back(Temp);
            k++;
        }
        Matrix1.push_back(RowTemp);
        i++;
    }
    //Reading first int to get number of rows and second to get number of columns for the Second Matrix
    InputFile >> Rows;
    InputFile >> Columns;
    //Storing Data to Matrix2
    i=0;
    while(i<Rows)
    {
        vector<int> RowTemp;
        k=0;
        while(k<Columns)
        {
            InputFile >> Temp;
            RowTemp.push_back(Temp);
            k++;
        }
        Matrix2.push_back(RowTemp);
        i++;
    }
    InputFile.close();
}


void ClearMatrix(vector<vector<int>>& Matrix, int Rows, int Columns)
{
    i=0;
    while(i<Rows)
    {
        vector<int> RowTemp;
        j=0;
        while(j<Columns)
        {
            RowTemp.push_back(0);
            j++;
        }
        Matrix.push_back(RowTemp);
        i++;
    }
}


void MatrixElementMultiplication(vector<vector<int>>& Rows, vector<vector<int>>& Columns, vector<vector<int>>& Matrix)
{
    //Clear Matrix values
    ClearMatrix(Matrix, Rows.size(), Columns[0].size());
    vector<thread> Threads(Rows.size() * Columns[0].size());
    int ThreadCounter=0,i=0;
    while(i<Rows.size())
    {
        j=0;
        while(j<Columns[0].size())
        {
            Threads[ThreadCounter] = thread{[&]()
            {
                k=0;
                while(k<Rows[0].size())
                {
                    Matrix[i][j] += Rows[i][k] * Columns[k][j];
                    k++;
                }
            }};
            Threads[ThreadCounter].join();
            ThreadCounter++;
            j++;
        }
        i++;
    }
}


void MatrixRowMultiplication(vector<vector<int>>& Rows, vector<vector<int>>& Columns, vector<vector<int>>& Matrix)
{
    //Initialize result with zeros
    ClearMatrix(Matrix, Rows.size(), Columns[0].size());
    vector<thread> Threads(Rows.size());
    int ThreadCounter=0,i=0;
    while(i<Rows.size())
    {
        Threads[ThreadCounter] = thread{[&]()
        {
            j=0;
            while(j<Columns[0].size())
            {
                k=0;
                while(k<Rows[0].size())
                {
                    Matrix[i][j] += Rows[i][k] * Columns[k][j];
                    k++;
                }
                j++;
            }
        }};
        Threads[ThreadCounter].join();
        ThreadCounter++;
        i++;
    }
}


void writeOutput(vector<vector<int>>& Matrix1, auto SpanTime1, vector<vector<int>>& Matrix2, auto SpanTime2)
{
    //Create file "output.txt" to print the results
    OutputFile.open("output.txt",ios::trunc|ios::out);
    i=0;
    while(i<Matrix1.size())
    {
        j=0;
        while(j<Matrix1[0].size())
        {
            OutputFile << Matrix1[i][j] << " ";
            j++;
        }
        OutputFile << "\n";
        i++;
    }
    OutputFile << "Span:" << SpanTime1 << " microseconds"<<endl;
    i=0;

    while(i<Matrix2.size())
    {
        j=0;
        while(j<Matrix2[0].size())
        {
            OutputFile << Matrix2[i][j] << " ";
            j++;
        }
        OutputFile << "\n";
        i++;
    }
    OutputFile << "Span:" << SpanTime2 << " microseconds"<<endl;
    OutputFile.close();
}

int main()
{
//Array for matrices input and output
    vector<vector<int>> Rows, Columns,OutputMatrix1,OutputMatrix2;
    //Reading the matrices 1 and 2
    ReadFromFile(Rows,Columns);
    //Starting the timer
    high_resolution_clock::time_point StartTime = high_resolution_clock::now();
    //Multiply Matrix by element
    MatrixElementMultiplication(Rows, Columns, OutputMatrix1);
    //Ending the timer
    high_resolution_clock::time_point EndTime = high_resolution_clock::now();
    //Span time
    auto SpanTime1 = duration_cast<microseconds>( EndTime - StartTime ).count();

    //Starting timer
    StartTime=high_resolution_clock::now();
    //Multiply Matrix by rows
    MatrixRowMultiplication(Rows, Columns, OutputMatrix2);
    //Ending of the timer
    EndTime=high_resolution_clock::now();
    auto SpanTime2 = duration_cast<microseconds>( EndTime - StartTime ).count();
    //Write Output
    writeOutput(OutputMatrix1, SpanTime1, OutputMatrix2, SpanTime2);
    return 0;
}
