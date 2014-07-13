#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cstdlib>
#include <sstream>
using namespace std;

class Partition
{
private:
    map<int, int> datas;
    vector<int> partitions;
    string propertyFile;
    string partitionFile;
    string resultFile;
public:
    Partition(string propertyFile, string partitionFile, string resultFile="result")
    {
        this->propertyFile = propertyFile;
        this->partitionFile = partitionFile;
        this->resultFile = resultFile;
        loadPropertyFile();
    }
    virtual ~Partition()
    {}

    void doPartition()
    {
        ifstream in(partitionFile.c_str());
        if (!in) {
            cerr << "load " << partitionFile << " error" << endl;
            exit(1);
        }
        string line;
        map<int, int>::iterator itr;
        while (getline(in, line)) {
            int data = atoi(line.c_str());
            int index = 0;
            if (!getIndex(data, index)) {
                cout << data << " out of range" << endl;
                continue;
            }
            itr = datas.find(index);
            if (itr == datas.end()) {
                datas[index] = 0;
            } else {
                datas[index]++;
            }
        }
        in.close();
        ofstream out(resultFile.c_str());
        if (!out) {
            cerr << "load " << resultFile << " error" << endl;
            exit(1);
        }
        for (itr = datas.begin(); itr != datas.end(); ++itr) {
            out << itr->first << "\t" << itr->second << "\t" << partitions[itr->first]
                << "\t" << partitions[itr->first + 1]<<endl;
        }
        out.close();
    }
private:
    bool getIndex(int key, int &index)
    {
        int size = partitions.size();
        for (int i = 0; i < size - 1; i++) {
            if (key < partitions[i] || key > partitions[size - 1]) {
                index = -1;
                return false;
            }
            if (key >= partitions[i] && key < partitions[i + 1]) {
                index = i;
                return true;
            }
            if (key == partitions[size-1]) {
                index = size - 2;
                return true;
            }
        }
        index = -1;
        return false;
    }

    void loadPropertyFile()
    {
        ifstream in(propertyFile.c_str());
        if (!in) {
            cerr << "load " << propertyFile << " error" << endl;
            exit(1);
        }
        string line;
        getline(in, line);
        istringstream iss(line);
        int data;
        while (iss >> data) {
            partitions.push_back(data);
        }
        in.close();
    }
};

int main(int argc, const char *argv[])
{
    if (argc != 3 && argc != 4) {
        cerr << "Usage: " << argv[0] << " propertyFile dataFile [resultFile]" << endl;
        exit(1);
    }

    string propertyFile = argv[1];
    string dataFile = argv[2];
    string resultFile = "result";

    if (argc == 4) {
        resultFile = argv[3];
    }
    Partition *p = new Partition(propertyFile, dataFile, resultFile);
    p->doPartition();
    delete p;
    return 0;
}


