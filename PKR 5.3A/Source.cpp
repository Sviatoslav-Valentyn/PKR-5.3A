#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <fstream>
using namespace std;

enum Spec { CS, IT, ME, PhIT, TR };

string strSpec[] = { "����'�����i �����", "I����������", "���������� �� ������i��", "�i���� �� i����������", "������� ��������" };

struct Student
{
    string surnamed;
    int kurs;
    Spec spec;
    int physics;
    int math;
    int informatik;
};

void Create(char* FileName, Student* s, int amSt) {
    ofstream f(FileName, ios::binary);
    if (!f)
    {
        cerr << "Error opening file '" << FileName << "'" << endl;
        exit(1);
    }
    int sp;
    for (int i = 0; i < amSt; i++) {
        cout << "��i�����: "; cin >> s[i].surnamed;
        cout << "����: "; cin >> s[i].kurs;
        cout << "����i����i��� (0 - ����'�����i �����; 1 - I����������; 2 - ���������� �� ������i��; 3 - �i���� �� i����������; 4 - ������� ��������;) ";
        cin >> sp;
        s[i].spec = (Spec)sp;
        cout << "��i��� � �i����: ";
        cin >> s[i].physics;
        cout << "��i��� � ����������: ";
        cin >> s[i].math;
        cout << "��i��� � �����������: ";
        cin >> s[i].informatik;
    }
}

void Print(char* FileName, Student* s, int amSt)
{
	ifstream f(FileName, ios::binary);
	if (!f)
	{
		cerr << "Error opening file" << endl;
		exit(1);
	}
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "|  �  | ���� |    �������    |       ������������     | ������ | ���������� |�����������|" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << left;
	for (int i = 0; i < amSt; i++) {

		cout << "|" << setw(3) << right << i + 1 << "  ";
		cout << "| " << setw(3) << right << s[i].kurs << "  "
			<< "|" << setw(16) << left << s[i].surnamed
			<< "| " << setw(24) << left << strSpec[s[i].spec]
			<< "| " << setw(3) << right << s[i].physics << "    "
			<< "| " << setw(6) << right << s[i].math << "     "
			<< "| " << setw(6) << right << s[i].informatik << "    " << "| ";
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------------"
		<< endl;
}


double avgGrade(Student* s, const int i)
{
    double m = (s[0].physics + s[0].math + s[0].informatik) / 3.;
    m = (s[i].physics + s[i].math + s[i].informatik) / 3.;
    return m;
}

void Sort(char* FileName, Student* p, const int N)
{
    ifstream f(FileName, ios::binary);
    if (!f)
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((avgGrade(p, i1) > avgGrade(p, i1 + 1)) ||
                (avgGrade(p, i1) == avgGrade(p, i1 + 1) && p[i1].math > p[i1 + 1].math)
                ||
                ((avgGrade(p, i1) == avgGrade(p, i1 + 1) && (p[i1].math == p[i1 + 1].math) &&
                    p[i1].surnamed > p[i1 + 1].surnamed)))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* indexSort(char* FileName, Student* s, int N)
{
    ifstream f(FileName, ios::binary);
    if (!f)
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    int* P = new int[N];

    for (int i = 0; i < N; i++)
    {
        P[i] = i;
    }
    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = P[i];
        for (j = i - 1; j >= 0 && ((avgGrade(s, P[j]) > avgGrade(s, value))
            ||
            (avgGrade(s, P[j]) == avgGrade(s, value) &&
                s[P[j]].math > s[value].math)
            ||
            ((avgGrade(s, P[j]) == avgGrade(s, value)) &&
                (s[P[j]].math == s[value].math))
            && (s[P[j]].surnamed > s[value].surnamed));
            j--)
        {
            P[j + 1] = P[j];
        }
        P[j + 1] = value;
    }
    return P;
}

int binSearch(char* FileName, Student* p, const int N, const string prizv, const int math)
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
    ifstream f(FileName, ios::binary);
    if (!f)
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].surnamed == prizv && avgGrade(p, m) == avgGrade(p, m) && p[m].math == math)
            return m;
        if ((avgGrade(p, m) > avgGrade(p, m + 1)) ||
            (avgGrade(p, m) == avgGrade(p, m + 1) && p[m].math > p[m + 1].math)
            ||
            ((avgGrade(p, m) == avgGrade(p, m + 1) && (p[m].math == p[m + 1].math) &&
                p[m].surnamed > p[m + 1].surnamed)))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int amSt;
    string lastName;
    int math;
    int avgGrade, found;
    cout << "ʳ������ ��������: ";
    cin >> amSt;
    Student* s = new Student[amSt];

    cin.get(); cin.sync();
    char FileName[81];
    cout << "������ ��'� �����:"; cin.getline(FileName, sizeof(FileName));

    int menuItem;
    do
    {
        cout << endl << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - �������� ����� � ��������� " << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ������� ������������� ����� " << endl;
        cout << " [4] - �������� ������������� �� ���� ����� " << endl;
        cout << " [5] - ������� ����� ��� ����������, �� ��������� ������� " << endl;
        cout << " �� �������� ������������ �������� �� ������� ������������ �� �������� ������� �����." << endl;
        cout << " [0] - ����� �� ���������� �������� " << endl;
        cout << "������ �������: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem) {
        case 1:
            Create(FileName,s, amSt);
            break;
        case 2:
            Print(FileName,s, amSt);
            break;
        case 3:
            Sort(FileName,s, amSt);
            break;
        case 4:
            indexSort(FileName,s, amSt);
            break;
        case 5:
            cout << "������ ����� ������:" << endl;
            cout << " �������: "; cin >> lastName;
            cout << endl;
            cout << " ������� ���: " << endl; cin >> avgGrade;
            cout << endl;
            cout << " ������ � ����������: " << endl; cin >> math;
            cout << endl;
            cin.get(); // ������� ����� ��������� � �� ����������� �������
            cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����


            if ((found = binSearch(FileName,s, amSt, lastName, math)) != -1)
                cout << "�������� �������� � ������� " << found + 1 << endl;
            else
                cout << "�������� �������� �� ��������" << endl;
            break;
        case 0:
            break;
        }
    } while (menuItem != 0);
    return 0;
}