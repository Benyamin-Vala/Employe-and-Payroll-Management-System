#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <json.hpp>
using namespace std;
using json = nlohmann::json;
int MainMenu();
int ListingEmployers();
int AddingEmployer();
int RemovingEmployer();
int ShowEmployerInformations(int empID);

int lineCount = 0;
int main() {
	MainMenu();
	return 0;
	
}
int MainMenu() {
	ifstream f("database.json");
	string databaseLine;
	json data;
	try {
		data = json::parse(f);
		lineCount = data["employes"].size();
		f.close();
	}
	catch (exception ex){
		f.close();
	}
	
	cout << "Payroll Management System v1, Coded By SeyyedBenyamin Valaei" << endl << endl << "Welcome to payroll management system." << endl;
	cout << "1-Listing employers" << "\t\t 2-Adding employer\t\t 3-Removing employer from list"<<endl;
	cout << "employer counts : " << lineCount<<endl<<endl<<"Please enter your task number : ";
	int inputTaskNumber;
	cin >> inputTaskNumber;
	if (inputTaskNumber == 1)
		ListingEmployers();
	else if (inputTaskNumber == 2)
		AddingEmployer();
	else if (inputTaskNumber == 3)
		RemovingEmployer();
	else
	{
		cout << "You Entered Wrong Number !";
		system("pause > nul");
		system("cls");
		MainMenu();
		return 0;

	}
		

	return 0;
}
int ListingEmployers() {
	string databaseLine;
	ifstream f("database.json");
	json data;
	int counter = 1;
	if (lineCount == 0)
	{
		cout << "Not any employer in list for showing !"<<endl;
		f.close();
		return 0;
	}
	else {
		data = json::parse(f);
		for (int i = 0; i < data["employes"].size(); i++)
		{
			cout << counter << "-" << data["employes"][i]["employerName"] << endl;
			counter += 1;
		}

	}
	f.close();
	cout << "Please enter Employer number for showing more information : " << endl;
	int employerNumber;
	cin >> employerNumber;
	ShowEmployerInformations(employerNumber-1);
	return 0;
}
int AddingEmployer() {

	ifstream existingFile("database.json");
	string employerName = "";
	int employerAge = 0;
	string employerJobName = "";
	float employerSalary = 0.00;
	int TaxPercentage = 20;
	string startedJobTime = "";
	string employerIdinityNumber = "";
	string employerAddress = "";
	
	json jsonData ;
	json TempData ;
	if(lineCount != 0)
		TempData = json::parse(existingFile);
	cout << "Please Enter Employer Name : " << endl;
	cin >> employerName;
	cout << "Please Enter Employer Age : " << endl;
	cin >> employerAge;
	cout << "Please Enter Employer Job Title : " << endl;
	cin >> employerJobName;
	cout << "Please Enter Salary :" << endl;
	cin >> employerSalary;
	cout << "Please Enter Started Job Date : "<<endl;
	cin >> startedJobTime;
	cout << "Please Enter Employer Idinity Number : " << endl;
	cin >> employerIdinityNumber;
	cout << "Please Enter Employer Adress : " << endl;
	cin >> employerAddress;
	jsonData["employerName"] = employerName;
	jsonData["employerAge"] = employerAge;
	jsonData["employerJobName"] = employerJobName;
	jsonData["employerSalary"] = employerSalary;
	jsonData["startedJobTime"] = startedJobTime;
	jsonData["employerIdinityNumber"] = employerIdinityNumber;
	jsonData["employerAddress"] = employerAddress;
	ofstream file("database.json");
	if (!file.is_open()) {
		cerr << "Failed to open the file for writing !" << endl;
		MainMenu();
		return 0;
	}
	if (TempData["employes"].size() != 0)
	{
		TempData["employes"].push_back(jsonData);

	
		file << setw(4) << TempData << endl;
		file.close();
		lineCount+=1;
	}
	else {
		TempData["employes"] = { jsonData };
		file << setw(4) << TempData << endl;
		file.close();
		lineCount+=1;
	}
	
	
	MainMenu();
	return 0;
}
int RemovingEmployer() {
	ifstream f("database.json");
	json data = json::parse(f);
	cout << "Please Enter Employer List Number for Removing : " << endl;
	int employNum;
	cin >> employNum;

	data["employes"].erase(employNum-1);
	f.close();
	ofstream file("database.json");
	file << setw(4) << data << endl;
	file.close();
	MainMenu();
	return 0;
}
int ShowEmployerInformations(int empID) {
	ifstream f("database.json");
	json data = json::parse(f);
	cout << "EmployerName : " << data["employes"][empID]["employerName"] << "\t\t EmployerAge : " << data["employes"][empID]["employerAge"] << "\nEmployer Job Title : " << data["employes"][empID]["employerJobName"] << "\t\tEmployer Salary : " << data["employes"][empID]["employerSalary"] << "\nEmployer Started Job Date : " << data["employes"][empID]["startedJobTime"] << "\t\tEmployer Idinity Number : " << data["employes"][empID]["employerIdinityNumber"] << "\nEmployer Address : " << data["employes"][empID]["employerAddress"] << endl;
	f.close();
	MainMenu();
	return 0;
}