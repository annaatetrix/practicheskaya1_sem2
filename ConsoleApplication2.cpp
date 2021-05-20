#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


using namespace std;

struct Profile
{
	string full_name;
	char sex;
	int group;
	int id;
	int grades[8];
	string depart;
	string date;
};



struct tm* timeinfo;
time_t tstamp;

void creatingRecord()
{
	Profile student;
	cout << "Full name: ";
	getline(std::cin, student.full_name);
	cout << "Group: ";
	cin >> student.group;
	cout << "Index: ";
	cin >> student.id;
	cout << "Sex (F/M): ";
	cin >> student.sex;
	cout << "Department (day/evening/distance): ";
	cin >> student.depart;
	cout << "Term grades: ";
	for (int i = 0; i < 8; i++)
		cin >> student.grades[i];

	time(&tstamp);
	timeinfo = localtime(&tstamp);
	student.date = asctime(timeinfo);

	int temp = 0;
	for (int i = 0; i < 8; i++) 
	{
		if (student.grades[i] == 2)
			temp++; 
	}
	if (temp == 0)
	{
		ofstream file;
		file.open("students.txt", ios::app);
		if (!file.is_open())
			cout << "Saving error!";
		else {
			file << student.full_name << "\n";
			file << student.group << "\n";
			file << student.id << "\n";
			file << student.sex << "\n";
			file << student.depart << "\n";
			for (int i = 0; i < 8; i++)
				file << student.grades[i] << " ";
			file << "\n";
			file << student.date;
			file.close();


			cout << "\nProfile is saved in the file\n";
		}
	}

	else
		cout << "\nThis student will be expelled. The profile will not be saved to the file.\n";
}

void editStudent()
{

}

int countStudents() 
{
	ifstream file("students.txt");
	if (file.is_open())
	{
		int temp = 0;
		string data;
		while (!file.eof())
		{
			getline(file, data);
			temp++;
		}
		file.close();
		int n;
		n = temp / 7;
		return n;
	}
	else return 0;
}

void showData()
{
	ifstream file("students.txt"); 
	if (!file.is_open())
		cout << "File opening error";
	else
	{
		int temp;
		temp = countStudents();
		if (temp == 0)
			cout << "The File is empty";
		else
		{
			string data;
			while (!file.eof())
			{
				getline(file, data); 
				cout << data << '\n';    
			}
		}
		file.close();
	}
}

void groupNum()
	{
		int n;
		cout << "Enter the group number:" << endl;
		cin >> n;
		ifstream file("students.txt");
		if (!file.is_open())
			cout << "Error!";
		else
		{
			int size;
			size = countStudents();
			if (size == 0)
				cout << "The database is empty." << endl;
			else
			{
				Profile* student = new Profile[size];
				for (int i = 0; i < size; i++)
				{
					getline(file, student[i].full_name);
					file >> student[i].group;
					file >> student[i].id;
					file >> student[i].sex;
					file >> student[i].depart;
					for (int j = 0; j < 8; j++)
						file >> student[i].grades[j];
					file.ignore();
					file.ignore();
					getline(file, student[i].date);
				}
				file.close();
				int temp = 0;
				for (int i = 0; i < size; i++)
				{
					if (student[i].group == n)
					{
						cout << student[i].id << " " << student[i].full_name << '\n';
						cout << student[i].sex << '\n';
						cout << "Term grades: ";
						for (int j = 0; j < 8; j++)
							cout << student[i].grades[j] << " ";
						cout << "\n\n";
						temp++;
					}
				}
				if (temp == 0)
					cout << "No records were found" << endl;
				delete[] student;
			}
		}
	}

void topStudents()
{
	float max1 = 0;
	float max2 = 0;
	float max3 = 0;
	string top_1;
	string top_2;
	string top_3;
	float tempAverage;

	ifstream file("students.txt");
	if (!file.is_open())
		cout << "Error!";
	else
	{
		int size;
		size = countStudents();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			Profile* student = new Profile[size];
			for (int i = 0; i < size; i++)
			{
				getline(file, student[i].full_name);
				file >> student[i].group;
				file >> student[i].id;
				file >> student[i].sex;
				file >> student[i].depart;
				for (int j = 0; j < 8; j++)
					file >> student[i].grades[j];
				file.ignore();
				file.ignore();
				getline(file, student[i].date);
			}
			file.close();
			top_1 = top_2 = top_3 = student[0].full_name;
			for (int i = 0; i < size; i++)
			{
				{
					tempAverage = 0;
					for (int j = 0; j < 8; j++)

					{
						tempAverage = tempAverage + student[i].grades[j];
					}
					tempAverage = tempAverage / 8;
					if (tempAverage > max1)
					{
						max3 = max2;
						max2 = max1;
						max1 = tempAverage;

						top_3 = top_2;
						top_2 = top_1;
						top_1 = student[i].full_name;
					}

					else if (tempAverage > max2)
					{
						max3 = max2;
						max2 = tempAverage;

						top_3 = top_2;
						top_2 = student[i].full_name;
					}

					else if (tempAverage > max3)
					{
						max3 = tempAverage;
						top_3 = student[i].full_name;
					}

				}

			}
		}

		cout << "Top 1 student: " << top_1 << "\n";
		cout << "Top 2 student: " << top_2 << "\n";
		cout << "Top 3 student: " << top_3 << "\n\n\n\n";
	}
}

void genders()
{
	int females = 0;
	int males = 0;
	ifstream file("students.txt");
	if (!file.is_open())
		cout << "Error!";
	else
	{
		int size;
		size = countStudents();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			Profile* student = new Profile[size];
			for (int i = 0; i < size; i++)
			{
				getline(file, student[i].full_name);
				file >> student[i].group;
				file >> student[i].id;
				file >> student[i].sex;
				file >> student[i].depart;
				for (int j = 0; j < 8; j++)
					file >> student[i].grades[j];
				file.ignore();
				file.ignore();
				getline(file, student[i].date);
			}
			file.close();
			for (int i = 0; i < size; i++)
				if (student[i].sex == 70)
					females++;
				else
					males++;
		}
		cout << "The number of females is: " << females << "\n";
		cout << "The number of males is: " << males << "\n\n\n";
	}
}

void grantStudents()
{
	int grade_3 = 0;
	int temp = 0;
	ifstream file("students.txt");
	if (!file.is_open())
		cout << "Error!";
	else
	{
		int size;
		size = countStudents();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			Profile* student = new Profile[size];
			for (int i = 0; i < size; i++)
			{
				getline(file, student[i].full_name);
				file >> student[i].group;
				file >> student[i].id;
				file >> student[i].sex;
				file.ignore();
				getline(file, student[i].depart);
				for (int j = 0; j < 8; j++)
					file >> student[i].grades[j];
				file.ignore();
				file.ignore();
				getline(file, student[i].date);
			}
			file.close();
			for (int i = 0; i < size; i++)
			{
				grade_3 = 0;
				for (int j = 0; j < 8; j++)
				{
					if (student[i].grades[j] == 3)
						grade_3++;
				}
					if ((student[i].depart == "day") && (grade_3==0))
						temp++;

				
			}
		}

		cout << "Number of students with grant is: " << temp << "\n\n\n";
	}
	
	
}

void noGrantStudents()
	{
		int grades_3;
		ifstream file("students.txt");
		if (!file.is_open())
			cout << "Error!";
		else
		{
			int size;
			size = countStudents();
			if (size == 0)
				cout << "The database is empty." << endl;
			else
			{
				Profile* student = new Profile[size];
				for (int i = 0; i < size; i++)
				{
					getline(file, student[i].full_name);
					file >> student[i].group;
					file >> student[i].id;
					file >> student[i].sex;
					file >> student[i].depart;
					for (int j = 0; j < 8; j++)
						file >> student[i].grades[j];
					file.ignore();
					file.ignore();
					getline(file, student[i].date);
				}
				file.close();
				int temp = 0;
				for (int i = 0; i < size; i++)
				{
					grades_3 = 0;
					for (int j = 0; j < 8; j++)
					{
						if (student[i].grades[j] == 3)


							grades_3++;
					}
							
						if (grades_3 > 0)
						{
							cout << student[i].id << " " << student[i].full_name << '\n';
							cout << student[i].sex << '\n';
							cout << "Term grades: ";
							for (int j = 0; j < 8; j++)
								cout << student[i].grades[j] << " ";
							cout << "\n\n";
							temp++;
						}
					
				}
				if (temp == 0)
					cout << "No records were found" << endl;
				delete[] student;
			}
		}
	}

void goodGradesOnly()
{
	int grades_3;
	ifstream file("students.txt");
	if (!file.is_open())
		cout << "Error!";
	else
	{
		int size;
		size = countStudents();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			Profile* student = new Profile[size];
			for (int i = 0; i < size; i++)
			{
				getline(file, student[i].full_name);
				file >> student[i].group;
				file >> student[i].id;
				file >> student[i].sex;
				file >> student[i].depart;
				for (int j = 0; j < 8; j++)
					file >> student[i].grades[j];
				file.ignore();
				file.ignore();
				getline(file, student[i].date);
			}
			file.close();
			int temp = 0;
			for (int i = 0; i < size; i++)
			{
				grades_3 = 0;
				for (int j = 0; j < 8; j++)
				{
					if (student[i].grades[j] == 3)


						grades_3++;
				}

				if (grades_3 == 0)
				{
					cout << student[i].id << " " << student[i].full_name << '\n';
					cout << student[i].sex << '\n';
					cout << "Term grades: ";
					for (int j = 0; j < 8; j++)
						cout << student[i].grades[j] << " ";
					cout << "\n\n";
					temp++;
				}

			}
			if (temp == 0)
				cout << "No records were found" << endl;
			delete[] student;
		}
	}
}

void excellentGradesOnly()
{
	int grades;
	ifstream file("students.txt");
	if (!file.is_open())
		cout << "Error!";
	else
	{
		int size;
		size = countStudents();
		if (size == 0)
			cout << "The database is empty." << endl;
		else
		{
			Profile* student = new Profile[size];
			for (int i = 0; i < size; i++)
			{
				getline(file, student[i].full_name);
				file >> student[i].group;
				file >> student[i].id;
				file >> student[i].sex;
				file >> student[i].depart;
				for (int j = 0; j < 8; j++)
					file >> student[i].grades[j];
				file.ignore();
				file.ignore();
				getline(file, student[i].date);
			}
			file.close();
			int temp = 0;
			for (int i = 0; i < size; i++)
			{
				grades = 0;
				for (int j = 0; j < 8; j++)
				{
					if ((student[i].grades[j] == 3) ||(student[i].grades[j] == 4) )


						grades++;
				}

				if (grades == 0)
				{
					cout << student[i].id << " " << student[i].full_name << '\n';
					cout << student[i].sex << '\n';
					cout << "Term grades: ";
					for (int j = 0; j < 8; j++)
						cout << student[i].grades[j] << " ";
					cout << "\n\n";
					temp++;
				}

			}
			if (temp == 0)
				cout << "No records were found" << endl;
			delete[] student;
		}
	}
}

void showByNumber()

	{
		int n;
		cout << "Enter the id:" << endl;
		cin >> n;
		ifstream file("students.txt");
		if (!file.is_open())
			cout << "Error!";
		else
		{
			int size;
			size = countStudents();
			if (size == 0)
				cout << "The database is empty." << endl;
			else
			{
				Profile* student = new Profile[size];
				for (int i = 0; i < size; i++)
				{
					getline(file, student[i].full_name);
					file >> student[i].group;
					file >> student[i].id;
					file >> student[i].sex;
					file >> student[i].depart;
					for (int j = 0; j < 8; j++)
						file >> student[i].grades[j];
					file.ignore();
					file.ignore();
					getline(file, student[i].date);
				}
				file.close();
				int temp = 0;
				for (int i = 0; i < size; i++)
				{
					if (student[i].id == n)
					{
						cout << student[i].full_name << " " << student[i].group << '\n';
						cout << student[i].sex << '\n';
						cout << "Term grades: ";
						for (int j = 0; j < 8; j++)
							cout << student[i].grades[j] << " ";
						cout << "\n\n";
						temp++;
					}
				}
				if (temp == 0)
					cout << "No records were found" << endl;
				delete[] student;
			}
		}
	}

void printMenu() {

	std::cout
		<< "1 - Create new student record\n"
		<< "2 - Edit student record\n"
		<< "3 - Print all students\n"
		<< "4 - Print all students of group\n"
		<< "5 - Print top students\n"
		<< "6 - Print students by gender\n"
		<< "7 - Print number of students with grant\n"
		<< "8 - Print students without grant\n"
		<< "9 - Print students with Good & Excellent grades only\n"
		<< "10 - Print students with Excellent grades only\n"
		<< "11 - Print students with specific number in group\n"
		<< "0 - Exit\n"
		<< "Select option: ";

}


int main()
{

	int choice = -1;
	int back;
	while (choice != 0) {
		printMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			creatingRecord();
			system("pause");
			system("cls");
			break;
		
		case 2:
			system("cls");
			editStudent();
			system("pause");
			system("cls");
			break;
		
		case 3:
			system("cls");
			showData();
			system("pause");
			system("cls");
			break;

		case 4:
			system("cls");
			groupNum();
			system("pause");
			system("cls");
			break;

		case 5:
			system("cls");
			topStudents();
			system("pause");
			system("cls");
			break;

		case 6:
			system("cls");
			genders();
			system("pause");
			system("cls");
			break;
			
		case 7:
			system("cls");
			grantStudents();
			system("pause");
			system("cls");
			break;
		
		case 8:
			system("cls");
			noGrantStudents();
			system("pause");
			system("cls");
			break;

		case 9:
			system("cls");
			goodGradesOnly();
			system("pause");
			system("cls");
			break;

		case 10:
			system("cls");
			excellentGradesOnly();
			system("pause");
			system("cls");
			break;

		case 11:
			system("cls");
			showByNumber();
			system("pause");
			system("cls");
			break;

		}

	}
	return 0;

}





