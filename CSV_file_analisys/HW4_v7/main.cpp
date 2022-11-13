#include <QFile>
#include <iostream>
#include <vector>

using namespace std;

int main(){

const int short sp = 55;

QFile file("data.csv");
QByteArray array;
QStringList list;
vector<float> vec;
vector<float> vec1;

// Prep: open file and transfer strings to initialize the Byte Array (stackoverflow.com›parsing-through-a-csv-file-in-qt)

file.open(QIODevice::ReadOnly);

while (!file.atEnd()) {
    array = file.readLine();
// Prep: split every string of Byte Array into two one using “;” and transfer first of them ("Temperature") to String List
    list.append(array.split(';').first());
    }
file.close();

// Prep: convert Strings List to Vector<float> (given on a forum)
for (int i = 0; i < list.size(); ++i) {
    vec.push_back(list[i].toDouble());
    }

// Prep: print vector
    for (int i = 0; i < vec.size(); i++) {
        cout << i << " = " << vec[i] << endl;
    }

// Prep: find first element greater than SetPoint
    auto overSP = find_if (vec.begin(), vec.end(),  // range
                  bind2nd (greater<float>(), sp));	// criterion
    float touch = distance(vec.begin(), overSP);    // index

// Prep: print its position
    cout << endl << "Task 1 solution:" << endl;
    cout << "The "
         << touch
         << ". element is the first greater than SetPoint" << endl;

// Task_1: find and print MAX and MIN elements after first SetPoint reaching
    cout << "MIN element after SetPoint reaching is " << *min_element(vec.begin()+touch, vec.end()) << '\n';
    cout << "MAX element after SetPoint reaching is " << *max_element(vec.begin()+touch, vec.end()) << '\n';

// Task_2: find "up" and "down" patterns (compare three consecutive vector elements) and count them
    int count = 0;
    for (int i = 2; i < vec.size(); i++) {
        if ((vec[i-2] <= vec[i-1] && vec[i-1] <= vec[i]) || (vec[i-2]>=vec[i-1] && vec[i-1]>=vec[i]))
            count = count;
            else {
            count ++;
            vec1.push_back(vec[i]); // push the values of turn points into new array for next task
            }
        }
    cout << endl << "Task 2 solution:" << endl;
    cout << "Trend has changed " << count << " times, which are:" << '\n'; // Since start, not since the SetPoint was reached
    for (int i = 0; i < vec1.size(); i++) {
        cout << i << " = " << vec1[i] << endl;
    }

// Task_3: find first smallest Temperature difference between the two nearest trend reversal points
    for (int i = 0; vec1.size(); i++) {
        if ((vec1[i+1] - vec1[i]) < 3){
            cout << endl << "Task 3 solution:" << endl;
            cout << "The first setpoint reach time is between Temperature reversals: " << vec1[i] << " and " << vec1[i+1] << endl;
            break;
        }
    }
    return 0;
}
