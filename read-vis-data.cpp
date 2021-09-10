#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>

using namespace std;

/*
* This function takes in a file for the school years from applicants and calculates the number of applicants per year
* Parameters: string fileName
* Return: none
*/
void readSchoolYear(string fileName){
    //array to store data values
    string schoolyearArr[14150];
    int idx = 0;
    
    //variables for counting value of each
    double alumni = 0.0;
    double masters = 0.0;
    double senior = 0.0;
    double junior = 0.0;
    double sophomore = 0.0;
    double freshman = 0.0;

    //open a stream to read data from data set
    ifstream fileStream;
    fileStream.open(fileName);

    //read the file
    if(fileStream.fail()){
        cout << "Failed to open the file " << endl;
    } else {
        string schoolyear;
        //While there are still values in the file, read them 
        while(!fileStream.eof()){
            //read the line and store in a temporary variable
            getline(fileStream,schoolyear);

            //calculate values of each year in school
            if(schoolyear == "Alumni"){
                alumni++;
            }

            if(schoolyear == "Masters"){
                masters++;
            }

            if(schoolyear == "Senior"){
                senior++;
            }

            if(schoolyear == "Junior"){
                junior++;
            }
            
            if(schoolyear == "Sophomore"){
                sophomore++;
            }

            if(schoolyear == "Freshman"){
                freshman++;
            }

            //add to array
            schoolyearArr[idx] = schoolyear;
            idx++;
        }
    }
    fileStream.close();

    cout << "======== SCHOOL YEAR TOTALS =========" << endl;
    cout << "Freshman: " << freshman << ", Percentage: " << (freshman/idx)*100.0 << endl;
    cout << "Sophmores: " << sophomore << ", Percentage: " << (sophomore/idx)*100.0 << endl;
    cout << "Juniors: " << junior << ", Percentage: " << (junior/idx)*100.0 << endl;
    cout << "Seniors: " << senior << ", Percentage: " << (senior/idx)*100.0 << endl;
    cout << "Masters: " << masters << ", Percentage: " << (masters/idx)*100.0 << endl;
    cout << "Alumni: " << alumni << ", Percentage: " << (alumni/idx)*100.0 << endl;
}

struct schoolData{
    string name = "";
    int numApplicantsFrom = 0;
};

/*
* This function returns the number of distinct elements in an array
* Parameters: 
* Return: int value for distinct elements
*/
int distinct_elements(string arr[], int size, schoolData uniqueArr[]){
    //sort the array
    sort(arr,arr+size);

    //traverse the sorted array
    int count = 0;
    int numDuplicates;
    int uniqueIdx = 0;
    for(int i=0; i < size; i++){
        //moving the index when duplicate is found
        numDuplicates = 1;
        while(i < size-1 && arr[i] == arr[i+1]){
            i++;
            //add to the number of duplicates per school
            numDuplicates++;
        }
        //add data to unique schools array
        schoolData s;
        s.name = arr[i];
        s.numApplicantsFrom = numDuplicates;
        uniqueArr[uniqueIdx] = s;
        uniqueIdx++;

        //increase the number of unique schools
        count++;
    }
    return count;
}

/*
* This function takes in a file of school names and counts how many of each
* Parameters: string fileName
* Return: none
*/
void readSchoolName(string fileName){
    //array to store data values
    string schools[14150];
    schoolData unique[14150];
    int idx = 0;

    //open a stream to read data from data set
    ifstream fileStream;
    fileStream.open(fileName);

    //read the file
    if(fileStream.fail()){
        cout << "Failed to open the file " << endl;
    } else {
        string schoolName;
        //While there are still values in the file, read them 
        while(!fileStream.eof()){
            //read the line and store in a temporary variable
            getline(fileStream,schoolName);
            schools[idx] = schoolName;
            idx++;
        }
    }
    fileStream.close();

    //count distinct elements
    int totalDistinctSchools = distinct_elements(schools,14150,unique);

    cout << "==================" << endl;
    cout << "Total Unique Schools: " << totalDistinctSchools << endl;


    //add distinct elements and number from each school to csv
    //record data into an external file
    ofstream outStream;
    outStream.open("schoolsData.csv");

    //Write to the file
    if(outStream.fail()){
        cout << "Out file failed to open" << endl;
    } else {
        //output data into two columns for LL
        outStream << "SCHOOL, NUMAPPLICANTS" << endl;
        for(int y=0; y < totalDistinctSchools; y++){
            outStream << unique[y].name << "," << unique[y].numApplicantsFrom << endl;
        }
    }
    outStream.close();
}



/*
* This function takes in a file of majors and counts how many of each
* Parameters: string fileName
* Return: none
*/
void readMajors(string fileName){
    //array to store data values
    string majors[14150];
    schoolData uniqueMajors[14150];
    int idx = 0;

    //open a stream to read data from data set
    ifstream fileStream;
    fileStream.open(fileName);

    //read the file
    if(fileStream.fail()){
        cout << "Failed to open the file " << endl;
    } else {
        string majorName;
        //While there are still values in the file, read them 
        while(!fileStream.eof()){
            //read the line and store in a temporary variable
            getline(fileStream,majorName);
            majors[idx] = majorName;
            idx++;
        }
    }
    fileStream.close();

    //count distinct elements
    int totalDistinctMajors = distinct_elements(majors,14150,uniqueMajors);

    cout << "==================" << endl;
    cout << "Total Unique Majors: " << totalDistinctMajors << endl;


    //add distinct elements and number from each school to csv
    //record data into an external file
    ofstream outStream;
    outStream.open("majorDataOrganized.csv");

    int totalStud = 0;
    for(int m=0; m < totalDistinctMajors; m++){
        totalStud += uniqueMajors[m].numApplicantsFrom;
    }

    cout << "TOTAL STUDENTS: " << totalStud << endl;


    //Write to the file
    if(outStream.fail()){
        cout << "Out file failed to open" << endl;
    } else {
        //output data into two columns for LL
        outStream << "Major" << endl;
        for(int y=0; y < totalDistinctMajors; y++){
            outStream << uniqueMajors[y].name << endl;
        }
    }
    outStream.close();


    //ofstream outStream;
    outStream.open("majorDataOrganizedNUMS.csv");

    if(outStream.fail()){
        cout << "Out file failed to open" << endl;
    } else {
        //output data into two columns for LL
        outStream << "NUM" << endl;
        for(int y=0; y < totalDistinctMajors; y++){
            outStream << uniqueMajors[y].numApplicantsFrom << endl;
        }
    }
    outStream.close();
}


int main(){
    //readSchoolYear("schoolyear.csv");
    //readSchoolName("schoolsAttended.csv");
    readMajors("majorData.csv");

    return 0;
}