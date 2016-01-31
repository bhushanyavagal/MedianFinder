/* 
 * File:   main.cpp
 * Author: Bhushan
 *
 * Created on January 28, 2016, 6:14 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/*
 * 
 */


int kThSmallest(vector<int> &array, int s_index, int e_index);
int partition(vector<int> &input, int s_index, int e_index, int pivot);

int main(int argc, char** argv) {

    vector<int> Vect;

    cout << "\nEnter input array separated by spaces in a single line" << endl;
    string in_string;
    getline(cin, in_string);
    istringstream instr_stream(in_string);
    int temp;
    while (instr_stream >> temp) {
        Vect.push_back(temp);
    }

    cout << "\nInitial Array :" << endl;
    for (int i = 0; i < Vect.size(); i++)
        cout << Vect[i] << " ";


    int median = kThSmallest(Vect, 0, Vect.size() - 1);

    cout << "\n\nThe Median is :" << median << endl;

    return 0;
}

int kThSmallest(vector<int> &array, int s_index, int e_index) {
    int i = s_index, medianPos, chunkSize = 0, j = ceil((double) (e_index - s_index + 1) / 5);
    vector<int> medians;
    while (j > 0) { // iterate n/5 times
        if (i + 4 > e_index) { //chunk size smaller than 5
            chunkSize = e_index - i + 1;
            sort(array.begin() + i, array.begin() + i + chunkSize);
            medians.push_back(array[i + ceil((double) chunkSize / 2) - 1]);
        } else { // chunks of size 5
            chunkSize = 5;
            sort(array.begin() + i, array.begin() + i + chunkSize);
            medians.push_back(array[i + (chunkSize / 2)]);
        }
        i += 5;
        j--;
    }

    if (medians.size() == 1) //base case
        return medians[0];
    
    //Recursive call to get median of median
    int medianOfmedians = kThSmallest(medians, 0, medians.size() - 1);
    
    //partition array with MoM as pivot
    int momPosition = partition(array, s_index, e_index, medianOfmedians);

    if ((array.size() % 2) == 1)
        medianPos = (array.size() / 2);
    else
        medianPos = (array.size() / 2) - 1;


    if (momPosition == medianPos)
        return medianOfmedians;

    else if (momPosition > medianPos)
        return kThSmallest(array, s_index, momPosition);
    else
        return kThSmallest(array, momPosition, e_index);
}

int partition(vector<int> &input, int start, int end, int pivot) {
    int wall = start - 1, mmPos;

    for (int i = 0; i < input.size(); i++) {
        if (pivot == input[i])
            mmPos = i;
    }

    // Push pivot element to the last
    if (mmPos != end) {
        input[mmPos] = input[mmPos] + input[end];
        input[end] = input[mmPos] - input[end];
        input[mmPos] = input[mmPos] - input[end];
    }


    for (int i = start; i <= end - 1; i++) {

        if (input[i] < pivot) {
            // swap the element just next to wall with the smaller element
            if (wall + 1 != i) {
                input[wall + 1] = input[wall + 1] + input[i];
                input[i] = input[wall + 1] - input[i];
                input[wall + 1] = input[wall + 1] - input[i];
            }
            wall++;

        }

    }
    // swap pivot and element right next to wall
    if (pivot != input[wall + 1]) {
        input[wall + 1] = input[wall + 1] + input[end];
        input[end] = input[wall + 1] - input[end];
        input[wall + 1] = input[wall + 1] - input[end];
    }

    return wall + 1; // return pivot position

}
