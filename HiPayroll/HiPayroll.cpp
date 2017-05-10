#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
fstream empCasheFile;
struct empStruct {
	int id;
	string name;
	float hours;
	float pricePerHour;
};
/*
* initialization Function in globa
*/
int getEmpNumber();
int empLastId(int);
void getEmpFormfile(int, int, empStruct[]);
void getRefreshData();
void printAllEmp(int);
void deleteEmp(int, int);
void addEmp(string[], int);
float netSalary(float, float);
float getTax(float);
void exportDataTofile(int);
void computeTotal(int);
void computeGross(int);
void computeNet(int);
float getMaxMini(int, int);
/*
* Global @var
*/

int const MaxEmpNumber = 100;
string emp[MaxEmpNumber][3];
string const cacheFileName = "CacheFile.txt";
string empTrash[MaxEmpNumber][3];
string fdata;
string data;
empStruct employee[MaxEmpNumber];
int numOfEmp = getEmpNumber();
int lastEmpId = empLastId(numOfEmp);
int main()
{

	system("cls");
	cout << "\t" << " __    __   __     .______      ___   ____    ____ .______        ______    __       __      " << endl;
	cout << "\t" << "|  |  |  | |  |    |   _  \\    /   \\  \\   \\  /   / |   _  \\      /  __  \\  |  |     |  |     " << endl;
	cout << "\t" << "|  |__|  | |  |    |  |_)  |  /  ^  \\  \\   \\/   /  |  |_)  |    |  |  |  | |  |     |  |     " << endl;
	cout << "\t" << "|   __   | |  |    |   ___/  /  /_\\  \\  \\_    _/   |      /     |  |  |  | |  |     |  |     " << endl;
	cout << "\t" << "|  |  |  | |  |    |  |     /  _____  \\   |  |     |  |\\  \\----.|  `--'  | |  `----.|  `----." << endl;
	cout << "\t" << "|__|  |__| |__|    | _|    /__/     \\__\\  |__|     | _| `._____| \\______/  |_______||_______|" << endl;
	int operationNum = 0;
	char operation;
	cout << "\n\t\t\t\tSelect operation \n" << endl;
	cout << "A) Add new Employee \t  \t D) Delete Employee" << endl << endl;
	cout << "C) Compute \t \t \t P) Print " << endl << endl;
	cout << "E) Exprot data as Text file \t H) Help" << endl << endl;
	cout << "Q) Quit" << endl << endl;
	getRefreshData();


	while (operationNum != 7) {
		cout << "\n\t\t\t\Enter operation \n" << endl;
		cin >> operation;
		switch (operation)
		{
		case 'A':
		case 'a':
			operationNum = 1;
			break;
		case 'D':
		case 'd':
			operationNum = 2;
			break;
		case 'P':
		case 'p':
			operationNum = 3;
			break;
		case 'H':
		case 'h':
			operationNum = 4;
			break;
		case 'E':
		case 'e':
			operationNum = 5;
			break;
		case 'c':
		case 'C':
			operationNum = 6;
			break;
		case 'q':
		case 'Q':
			operationNum = 7;
			break;
		default:
			operationNum = 4;
			break;
		}

		if (operationNum == 1) {
			system("cls");
			getRefreshData();

			cout << "\t \t \t Add New Employee" << endl;
			string empData[3];
			cout << "Enter Employee Name " << endl;
			cin >> empData[0];
			cout << "Enter Work Hours in month " << endl;
			cin >> empData[1];
			cout << "Enter Employee Work Hour price " << endl;
			cin >> empData[2];
			addEmp(empData, lastEmpId);
			cout << "Employee Added!" << endl;
		}
		else if (operationNum == 2) {
			system("cls");
			getRefreshData();
			int id = 0;
			cout << "\t \t \t Delete Employee" << endl;
			cout << "Enter Employee ID" << endl;
			cin >> id;
			if (employee[id].name.empty() != 0) {
				cout << "Employee Not removed Please Enter exist Id" << endl;
			}
			else {
				deleteEmp(id, lastEmpId);
				cout << "Employee removed " << endl;
			}

		}
		else if (operationNum == 3) {
			system("cls");
			getRefreshData();
			printAllEmp(lastEmpId);
		}
		else if (operationNum == 4) {
			system("cls");
			cout << "\t \t \t \t Welcome to help panel \n";
			cout << "write 'a' or 'A' for adding new employee \n";
			cout << "write 'd' or 'D' for delete an employee \n";
			cout << "write 'c' or 'C' for Compute Total Salary for company , Max , Mini Salay \n";
			cout << "write 'p' or 'P' for print all employees data \n";
			cout << "write 'e' or 'E' for export data as Text File \n";
			cout << "write 'q' or 'Q' for exit \n";
		}

		else if (operationNum == 5) {
			system("cls");
			getRefreshData();
			cout << "\t \t \t \t Exporting... \n";
			exportDataTofile(lastEmpId);
			cout << "\t \t \t \t Export Done! \n";
		}
		else if (operationNum == 6) {
			system("cls");
			getRefreshData();
			char computeop;
			cout << "T  - Total Salary\n";
			cout << "G - Gross Salary \n";
			cout << "N - Net Salary \n";
			cout << "M - Max Salary \n";
			cout << "i - Mini Salary \n";
			cin >> computeop;
			switch (computeop)
			{
			case 't':
			case 'T':
				computeTotal(lastEmpId);
				break;
			case 'g':
			case 'G':

				computeGross(lastEmpId);
				break;
			case 'n':
			case 'N':
				computeNet(lastEmpId);
				break;
			case 'm':
			case 'M':
				cout << "Max Salary : " << getMaxMini(lastEmpId, 1) << endl;
				break;
			case 'i':
			case 'I':
				cout << "Mini Salary : " << getMaxMini(lastEmpId, 2) << endl;
				break;
			default:
				cout << "Error Enter Valid Numbers \n";
				break;
			}
		}

	}
	return 0;
}


int getEmpNumber() {

	string data;
	int numOfEmp = 0;
	int len = 0;
	empCasheFile.open(cacheFileName);
	empCasheFile.seekp(0, ios::end);
	len = empCasheFile.tellg();
	empCasheFile.close();
	if (len == 0 || !empCasheFile) {
		ofstream fristCasheFile;
		fristCasheFile.open(cacheFileName);

		cout << "add Any Employee to Start \n";
		string empOne[3];
		cout << "Enter Employee Name \n";
		cin >> empOne[0];
		cout << "Enter Employee Hours \n";
		cin >> empOne[1];
		cout << "Enter Employee price per Hours \n";
		cin >> empOne[2];
		fristCasheFile << endl << 1 << " " << empOne[0] << " " << empOne[1] << " " << empOne[2];
		fristCasheFile.close();
		return 1;
	}

	else
	{
		empCasheFile.open(cacheFileName);
		while (empCasheFile.good()) {
			empCasheFile >> data;
			++numOfEmp;
		}
		numOfEmp = numOfEmp / 4;
		empCasheFile.close();
		return numOfEmp;
	}


}

int empLastId(int numOfEmp) {
	int lastEmpId = 0;
	empCasheFile.open(cacheFileName);
	while (empCasheFile.good())
	{
		for (int i = 0; i < numOfEmp; i++) {
			empCasheFile >> lastEmpId;
			for (int z = 0; z < 3; z++) {
				//Trash data 
				empCasheFile >> fdata;
			}
		}
	}
	empCasheFile.close();
	return lastEmpId;
}


void getEmpFormfile(int numOfEmp, int lastEmpId, empStruct arr[]) {
	empCasheFile.open(cacheFileName);

	//Get data as array
	while (empCasheFile.good())
	{
		for (int i = 0; i < numOfEmp; i++) {
			empCasheFile >> lastEmpId;
			for (int z = 0; z < 3; z++) {
				empCasheFile >> fdata;
				if (fdata.empty() == 0) {
					emp[lastEmpId][z] = fdata;
				}
			}
		}
	}

	//Store array in Struct == Convert array to strcut 
	for (int x = 0; x <= lastEmpId; x++) {
		if (emp[x][0].empty() == 0) {
			arr[x].id = x;
			arr[x].name = emp[x][0];
			arr[x].hours = stof(emp[x][1]);
			arr[x].pricePerHour = stof(emp[x][2]);;
		}
	}
	empCasheFile.close();
}


void printAllEmp(int lastEmpid) {
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << "ID \t \t Name \t \t workHours \t \t Price/houre \t  salary " << endl;
	float companySalary = 0;
	for (int i = 0; i <= lastEmpid; i++) {
		// print while employee[i] have value
		if (employee[i].name.empty() == 0) {
			float hours = employee[i].hours;
			float hourPrice = employee[i].pricePerHour;
			float salary = netSalary(hours, hourPrice);
			cout << employee[i].id << "\t | \t" << employee[i].name << "\t | \t" << hours << "\t \t | \t"
				<< hourPrice << "\t | \t" << salary << endl;
			companySalary = companySalary + salary;
		}
	}
	cout << "------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t Total salary is : " << companySalary << endl;
}

void deleteEmp(int id, int lastEmpid) {
	ofstream deleteFile;
	deleteFile.open(cacheFileName);
	for (int i = 0; i <= lastEmpid; i++) {
		if (employee[i].name.empty() == 0 && i != id) {
			deleteFile << endl << employee[i].id << " " << employee[i].name << " " << employee[i].hours << " " << employee[i].pricePerHour;
		}
	}
	deleteFile.close();
}


void addEmp(string emp_arr[], int lastEmpid) {
	int id = lastEmpid + 1;
	ofstream addFile;
	addFile.open(cacheFileName, ios::app);
	addFile << endl << id << " " << emp_arr[0] << " " << emp_arr[1] << " " << emp_arr[2];
	addFile.close();
}

void exportDataTofile(int lastEmpid) {
	ofstream exportFile;
	exportFile.open("Export.txt");
	exportFile << "-----------------------------------------------------------------------------------" << endl;
	exportFile << "ID \t \t Name \t \t workHours \t \t Price/houre \t  salary " << endl;
	float companySalary = 0;
	for (int i = 0; i <= lastEmpid; i++) {
		// print while employee[i] have value
		if (employee[i].name.empty() == 0) {
			float hours = employee[i].hours;
			float hourPrice = employee[i].pricePerHour;
			float salary = netSalary(hours, hourPrice);
			exportFile << employee[i].id << "\t | \t" << employee[i].name << "\t | \t" << hours << "\t \t | \t"
				<< hourPrice << "\t | \t" << salary << endl;
			companySalary = companySalary + salary;
		}
	}
	exportFile << "------------------------------------------------------------------------------------" << endl;
	exportFile << "\t\t\t\t\t\t\t Total salary is : " << companySalary << endl;
}

void getRefreshData() {
	//empty array 
	memset(emp, 0, sizeof(emp));
	//empty Struct
	memset(employee, 0, sizeof(employee));
	numOfEmp = getEmpNumber();
	lastEmpId = empLastId(numOfEmp);
	getEmpFormfile(numOfEmp, lastEmpId, employee);
}

float netSalary(float hours, float pricePerHours) {
	float salary, tax, netSalary, incentives;
	salary = hours*pricePerHours;
	tax = getTax(salary);
	incentives = 0.52 * salary;
	netSalary = salary + incentives - tax;
	return netSalary;

}

float getTax(float salary) {
	float tax;
	if (salary < 0.00)
		tax = -1;
	else if (salary < 15000.00)
		tax = 0.15  * salary;
	else if (salary < 30000.00)
		tax = (salary - 15000.00) * 0.16 + 2250.00;
	else if (salary < 50000.00)
		tax = (salary - 30000.00) * 0.18 + 4650.00;
	else if (salary < 80000.00)
		tax = (salary - 50000.00) * 0.20 + 8250.00;
	else if (salary <= 150000.00)
		tax = (salary - 80000.00) * 0.25 + 14250.00;
	else
		tax = -1;
	return tax;
}



void computeTotal(int lastEmpid) {
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << "ID \t \t Name \t \t workHours \t \t Price/houre \t  Total salary " << endl;
	float companySalary = 0;
	float salary = 0;
	for (int i = 0; i <= lastEmpid; i++) {
		if (employee[i].name.empty() == 0) {
			salary = employee[i].hours * employee[i].pricePerHour;
			cout << employee[i].id << "\t | \t" << employee[i].name << "\t | \t" << employee[i].hours << "\t \t | \t"
				<< employee[i].pricePerHour << "\t | \t" << salary << endl;
			companySalary = salary + companySalary;
		}
	}
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t Total salary is : " << companySalary << endl;
}

void computeGross(int lastEmpid) {
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << "ID \t \t Name \t \t workHours \t \t Price/houre \t  Gross salary " << endl;
	float companySalary = 0;
	float salary = 0;
	float incentives = 0;
	for (int i = 0; i <= lastEmpid; i++) {
		if (employee[i].name.empty() == 0) {
			salary = employee[i].hours * employee[i].pricePerHour;
			incentives = 0.52 * salary;
			cout << employee[i].id << "\t | \t" << employee[i].name << "\t | \t" << employee[i].hours << "\t \t | \t"
				<< employee[i].pricePerHour << "\t | \t" << incentives << endl;
			companySalary = incentives + companySalary;
		}
	}
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t Gross salary is : " << companySalary << endl;
}

void computeNet(int lastEmpid) {
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << "ID \t \t Name \t \t workHours \t \t Price/houre \t  Gross salary " << endl;
	float companySalary = 0;
	float net = 0;
	for (int i = 0; i <= lastEmpid; i++) {
		if (employee[i].name.empty() == 0) {
			net = netSalary(employee[i].hours, employee[i].pricePerHour);
			cout << employee[i].id << "\t | \t" << employee[i].name << "\t | \t" << employee[i].hours << "\t \t | \t"
				<< employee[i].pricePerHour << "\t | \t" << net << endl;
			companySalary = companySalary + net;

		}
	}
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t\t Net salary is : " << companySalary << endl;
}

float getMaxMini(int lastEmpid, int op) {
	float  salary = 0, max, mini;
	max = mini = employee[lastEmpId].hours*employee[lastEmpId].pricePerHour;
	//Get max and mini
	for (int i = 0; i <= lastEmpId; i++) {
		if (employee[i].name.empty() == 0) {
			salary = employee[i].hours*employee[i].pricePerHour;

			if (salary > max) {
				max = salary;
			}
			else if (salary <  mini) {
				mini = salary;
			}
		}

	}

	if (op == 1) {
		return max;
	}
	else if (op == 2)
	{
		return mini;
	}
}