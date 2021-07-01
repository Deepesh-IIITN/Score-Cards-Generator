#include <bits/stdc++.h>
#include <fstream>
#include "TextTable.h"
using namespace std;

vector<string> createStrings(string s)
{
    int n = s.size();
    vector<string> vect;
    string str = "";
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ',')
        {
            vect.push_back(str);
            str = "";
        }
        else
        {
            str = str + s[i];
        }
    }
    vect.push_back(str);
    return vect;
}

vector<int> createIntegers(string s)
{
    int n = s.size();
    vector<int> vect;
    string str = "";
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ',')
        {
            int temp = stoi(str);
            vect.push_back(temp);
            str = "";
        }
        else
        {
            str = str + s[i];
        }
    }
    int temp = stoi(str);
    vect.push_back(temp);

    return vect;
}

vector<string> getData(string s)
{
    int n = s.size();
    vector<string> vect;
    string str = "";
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (cnt >= 2)
        {
            vect.push_back(s.substr(i, n - i));
            break;
        }
        if (s[i] == ',')
        {
            vect.push_back(str);
            cnt++;
            str = "";
        }
        else
        {
            str = str + s[i];
        }
    }
    return vect;
}
string calGrade(int n)
{
    if (n >= 90)
        return "A+";
    if (n >= 80)
        return "A";
    if (n >= 70)
        return "B";
    if (n >= 60)
        return "C";
    if (n >= 50)
        return "D";
    if (n >= 33)
        return "E";
    return "Fail";
}
void instructions()
{
    cout << "Steps for running this application:\n";
    cout << "1.Excel file name should be 'students' with extension '.csv'.Means files should be 'students.csv'.\n";
    cout << "2.formate of excel file should be student_Name, student_Roll_no., subject1, subject2, subject3 .......\n";
    cout << "3.There be a empty folder 'score_cards'\n";
    cout << "4.Generate_Score_Cards.exe , students.csv, 'score_cards' empty folder should be at same place\n";
    cout << "5.If you did not do all 3 steps then first complete all steps.\n\n";

    cout << "Enter q to 'quit' or enter any key to continue and press enter: ";
    char s;
    cin >> s;
    if (s == 'q')
        exit(0);
}
int main()
{
    instructions();
    fstream fio;
    string line;
    fio.open("students.csv", ios::app | ios::out | ios::in);
    int i = 0;

    vector<string> subjects;
    while (fio)
    {

        getline(fio, line);
        vector<string> vect = getData(line);
        if (i == 0)
        {
            subjects = createStrings(vect[2]);
        }
        else
        {
            fstream student;
            string status = "PASS";
            string pdffile = "score_cards/" + vect[1] + ".txt";
            student.open(pdffile, ios::trunc | ios::out | ios::in | ios::binary);
            student << "Name: " << vect[0] << "\n"
                    << "Roll No: " << vect[1] << "\n";

            vector<int> marks = createIntegers(vect[2]);

            int size = marks.size();
            int total = 0;
            TextTable t('-', '|', '+');

            t.add(" SUBJECTS ");
            t.add(" MARKS ");
            t.add(" GRADES ");
            t.endOfRow();
            for (int j = 0; j < size; j++)
            {
                t.add(subjects[j]);
                t.add(to_string(marks[j]));
                t.add(calGrade(marks[j]));
                if (calGrade(marks[j]) == "Fail")
                    status = "Fail";
                t.endOfRow();
                total += marks[j];
            }

            student << t;

            student << "Total"
                    << " : " << total << "\n";

            float percentage = float(total) / float(size);
            student << "Percentage"
                    << " : " << percentage << "\n";

            student << "Status"
                    << " : " << status << "\n";

            student.close();
        }
        i++;
    }
    cout << "\n\t\t\t....... All score_cards are created ...........\n\n";
    fio.close();

    return 0;
}