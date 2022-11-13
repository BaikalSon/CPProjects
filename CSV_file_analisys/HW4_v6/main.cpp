#include <QFile>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(){

const int short sp = 55;

QFile file("data.csv");
QByteArray array;
QStringList list;
vector<float> vec;

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
    float touch = distance(vec.begin(), overSP);   // index

// Prep: print its position
    cout << "The "
         << touch
         << ". element is the first greater than SetPoint" << endl;

// Task_1: find and print MAX and MIN elements after first SetPoint reaching
    cout << "MIN element after SetPoint reaching is " << *min_element(vec.begin()+touch, vec.end()) << '\n';
    cout << "MAX element after SetPoint reaching is " << *max_element(vec.begin()+touch, vec.end()) << '\n';

// Task_2: find "up" and "down" patterns (compare three consecutive vector elements) and count them
    int count = 0;
    for (int i = 0; i < vec.size(); i++) {
        if ((vec[i-2] <= vec[i-1] && vec[i-1] <= vec[i]) || (vec[i-2]>=vec[i-1] && vec[i-1]>=vec[i]))
            count = count;
            else count ++;
        }
    cout << "Since SetPoint was reached trend has changed " << count << " times" << '\n';

// Task_3: find first smallest then 3 degrees Celsius difference between the two nearest trend reversal points

    // so far no idea

return 0;

}
