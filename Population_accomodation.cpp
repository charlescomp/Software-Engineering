// Population_accomodation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
/*
	Abstract Class
	Used as parent for javatown family and py family classes.

*/
class family {
private:
	string lastname;
	int house_size;
	int family_members;
	double family_income;

public:

	//constructor
	family()
	{
		lastname = "Uninitialized";
		house_size = -1;
		family_members = -1;
		family_income = -1;
	}

	//parametrized constructor
	family(string _lastname, int _house_size, int _family_members, double _family_income)
	{
		lastname = _lastname;
		house_size = _house_size;
		family_members = _family_members;
		family_income = _family_income;
	}


	//virtual functions that must be overridden by child classes
	virtual void print_details() = 0;
	virtual bool assign_family(family*& fam) = 0;
	virtual bool get_accomodation_status() = 0;
	virtual void set_accomodation_status(bool status) = 0;
	virtual void set_id(int _id) = 0;
	virtual int get_id() = 0;

	/*
		getters and setters for all class members.
	*/

	string get_lastname()
	{
		return lastname;
	}
	int get_house_size()
	{
		return house_size;
	}
	int get_family_members()
	{
		return family_members;
	}
	double get_family_income()
	{
		return family_income;
	}

	void set_lastname(string name)
	{
		lastname = name;
	}
	void set_house_size(int land_area)
	{
		house_size = land_area;
	}
	void set_family_members(int members_count)
	{
		family_members = members_count;
	}
	void set_family_income(int income)
	{
		family_income = income;
	}
};

class java_family : public family {
private:
	int id;
public:

	//constructor
	java_family()
	{
		id = -1;
	}

	//parametrized constructor
	java_family(int _id, string lastname, int house_size, int family_members, double family_income) : family{ lastname,house_size,family_members,family_income }, id{ _id }
	{

	}

	//copy constructor
	java_family(java_family& f1) {
		set_lastname(f1.get_lastname());
		set_family_income(f1.get_family_income());
		set_family_members(f1.get_family_members());
		set_house_size(f1.get_house_size());
		set_id(f1.get_id());
	}

	//get the number of people which can be accomodated as per the 4 people per 1000sq ft guidelines
	int get_accomodation_capacity()
	{
		int total_members_capacity = get_house_size() / 250; // 4 people per 1000sq ft i.e. 1 per per 250sq ft
		total_members_capacity -= get_family_members();
		return total_members_capacity;
	}

	//assign a py village family to java town family
	bool assign_family(family*& fam)
	{
		if (fam->get_family_members() < get_accomodation_capacity())//check if java town family can acoomodate the family as per people:area ratio guidelines
		{
			cout <<"\n----------------------------------------------\n"<< get_lastname() << "s have accomodated " << fam->get_lastname() << "s";
			cout << "\n\n----------------------------------------------\nBEFORE:\nJT family: ";
			print_details();

			set_family_members(get_family_members() + fam->get_family_members());//add pyvillage's family members to javatown's family
			fam->set_id(get_id());//assigning javatown's family ID to the py village family.
			fam->set_accomodation_status(true);//updating py village family's accomodation status
			set_family_income(get_family_income() + 1000);//adding $1000 aid to Java family income
			
			cout << "\n\nAFTER: \n\nJT family: ";
			print_details();
			cout << "\n----------------------------------------------\n";
			return true;
		}
		return false;
	}


	void print_details()
	{
		cout << "\n" << id << "\t" << get_lastname() << "\t" << get_house_size() << "\t" << get_family_members() << "\t" << get_family_income();
	}

	//getters and setters for class's private members.

	bool get_accomodation_status() {
		return true;
	}

	void set_accomodation_status(bool status)
	{
		return;
	}

	int get_id()
	{
		return id;
	}

	void set_id(int _id)
	{
		id = _id;
	}
};


class py_family : public family {
private:
	int assigned_family_id;//ID of the javatown family assigned
	bool is_accomodated;
public:

	//constructor
	py_family()
	{
		assigned_family_id = -1;
		is_accomodated = false;
	}

	//parametrized constructor
	py_family(string lastname, int house_size, int family_members, double family_income):family{lastname,house_size,family_members,family_income}
	{
		assigned_family_id = -1;
		is_accomodated = false;
	}

	//copy constructor
	py_family(py_family& f1) {
		set_lastname(f1.get_lastname());
		set_family_income(f1.get_family_income());
		set_family_members(f1.get_family_members());
		set_house_size(f1.get_house_size());
		set_id(f1.get_id());
		set_accomodation_status(f1.get_accomodation_status());
	}


	bool assign_family(family*& fam)//can't assign a family to py village family as per assignment guidelines.
	{
		return false;
	}

	void print_details()
	{
		cout << "\n" << assigned_family_id << "\t" << get_lastname() << "\t" << get_house_size() << "\t" << get_family_members() << "\t" << get_family_income() << "\t" <<is_accomodated;
	}

	//getters and setters for class's private members.

	int get_id()
	{
		return assigned_family_id;
	}

	void set_id(int _id)
	{
		assigned_family_id = _id;
	}

	bool get_accomodation_status()
	{
		return is_accomodated;
	}

	void set_accomodation_status(bool status)
	{
		is_accomodated = status;
	}
};

/*
This class contains utility functions used throughout the main program.
Most of the functionality provided by the class is related to the 
filehandling part of the project.
*/
class utilities {
public:
	int get_countof_families(string filename)
	{
		int count = 0;
		fstream obj;
		obj.open(filename, ios::in); //open a file to perform read operation using file object
		if (obj.is_open()) {   //checking whether the file is open
			string record;
			while (getline(obj, record)) { //read data from file object and put it into string.
				//cout << record << endl;
				count++;
			}
			obj.close(); //close the file object.
		}
		return count;
	}

	//load data of a py family into program's memory
	py_family* load_py_family(string record)
	{
		string delimiter = ",";
		string ext_lastname, ext_house_size, ext_family_members, ext_family_income;
		ext_lastname = record.substr(0, record.find(delimiter));
		record = record.substr(ext_lastname.length() + 1);
		ext_house_size = record.substr(0, record.find(delimiter));
		record = record.substr(ext_house_size.length() + 1);
		ext_family_members = record.substr(0, record.find(delimiter));
		ext_family_income = record.substr(ext_family_members.length() + 1);
		py_family* fam = new py_family(ext_lastname, stoi(ext_house_size), stoi(ext_family_members), stod(ext_family_income));
		return fam;
	}

	//load data of a java family into program's memory
	java_family* load_java_family(string record)
	{
		string delimiter = ","; // delimiter used to separate out value in each column.
		string ext_id, ext_lastname, ext_house_size, ext_family_members, ext_family_income;

		/*
		* substr() function is used to extract a sub-string from a string by passing the position of sub-string 
		* i.e. starting index of sub-string and ending index of sub-string.
		* ---------------------------------------------------------------------------------------------------
		* find() function is used to find the index at which passed substring is found.
		* In our case we use it to find the position of delimiter and use this position to extact value of a 
		* column from a record.
		*/

		ext_id = record.substr(0, record.find(delimiter));
		record = record.substr(ext_id.length() + 1);
		ext_lastname = record.substr(0, record.find(delimiter));
		record = record.substr(ext_lastname.length() + 1);
		ext_house_size = record.substr(0, record.find(delimiter));
		record = record.substr(ext_house_size.length() + 1);
		ext_family_members = record.substr(0, record.find(delimiter));
		ext_family_income = record.substr(ext_family_members.length() + 1);

		/*
		* stoi() function is used to convert string to integer data type
		* stod() function is used to convert string to double data type
		*/

		java_family *fam = new java_family(stoi(ext_id), ext_lastname, stoi(ext_house_size), stoi(ext_family_members), stod(ext_family_income));
		return fam;
	}


	/*
	* loads data of java town families from txt file into program's memory
	*/
	family**load_javatown_data(family**& fams, string filename)
	{
		int count = 0;
		fstream obj;
		obj.open(filename, ios::in); //open a file to perform read operation using file object
		if (obj.is_open()) {   //checking whether the file is open
			string record;
			while (getline(obj, record)) { //read data from file object and put it into string.
				fams[count] = load_java_family(record);
				count++;
			}
			obj.close(); //close the file object.
		}
		return fams;
	}

	/*
	* loads data of py village families from txt file into program's memory
	*/
	family** load_pyvillage_data(family**& fams, int java_families_count, string filename)
	{
		int count = java_families_count;
		fstream obj;
		obj.open(filename, ios::in); //open a file to perform read operation using file object
		if (obj.is_open()) {   //checking whether the file is open
			string record;
			while (getline(obj, record)) { //read data from file object and put it into string.
				fams[count] = load_py_family(record);
				count++;
			}
			obj.close(); //close the file object.
		}
		return fams;
	}

	/*
	* find accomodation for py village family among the java town families.
	*/
	bool find_accomodation(family**& fams, int java_families_count, family* &py_fam)
	{
		bool _isassigned = false;
		for (int i = 0;i < java_families_count;i++)
		{
			if (py_fam->get_accomodation_status())//if already accomodated don't iterate the list.
			{
				break;
			}
			else
			{
				/*cout << "\n\nPy family: ";
				py_fam->print_details();*/

				_isassigned = fams[i]->assign_family(py_fam);
				if (_isassigned) //if family ias assigned we return true
				{
					return _isassigned;//isassigned would always have vaue "true" here
				}

				/*cout << "\n\nPy family: ";
				py_fam->print_details();*/
			}
		}
		return _isassigned;
	}
};

int main()
{

	// declaring list of families 
	family** families = NULL;

	//count of families from each village
    int java_families_count = 0;
	int py_families_count = 0;
	int unallocated_families_count = 0;

	//utilities class object to help with some basic data manipulations.
	utilities utils;
	
	//get count of families from each village
	java_families_count = utils.get_countof_families("javatown.txt");
	py_families_count = utils.get_countof_families("pyvillage.txt");
	
	//initializing list of families
	families = new family*[java_families_count+py_families_count];

	cout << "\n+===================================================================+";
	cout << "\nLoading data from text files...";
	cout << "\n+===================================================================+";
	//loading data from files into list of families
	families = utils.load_javatown_data(families, "javatown.txt");
	families = utils.load_pyvillage_data(families, java_families_count, "pyvillage.txt");
	
	cout << "\nNumber of javatown families: " << java_families_count;
	cout << "\nNumber of pyvillage families: " << py_families_count;

	cout << "\n+===================================================================+";
	cout << "\nAssigning dislocated Py Village families to Java Town families.";
	cout << "\n+===================================================================+";
	// find accomodation for each displaced py village family
	for (int i = java_families_count;i < (java_families_count + py_families_count);i++)
	{
		/*
		* finds accomodation for py village family in java town families.
		*/
		bool _isaccomodated = utils.find_accomodation(families, java_families_count, families[i]);
		if (_isaccomodated == false)
		{
			unallocated_families_count++;
		}
	}

	//prinitng report
	cout << "\n+===================================================================+";
	cout << "\nDETAILED REPORT OF FAMILIES AFTER REALLOCATION";
	cout << "\n+===================================================================+";
	cout << "\n----------------------------------\nJava Town's families record\n----------------------------------\n";
	cout << "\n" << "id" << "\t" << "lastname" << "\t" << "house_size" << "\t" << "family_members" << "\t" << "family_income";
	for (int i = 0;i < java_families_count;i++)
	{
		families[i]->print_details();
	}

	cout << "\n----------------------------------\nPy Village's families record\n----------------------------------\n";
	cout << "\n" << "assigned_family_id" << "\t" << "lastname" << "\t" << "house_size" << "\t" << "family_members" << "\t" << "family_income" << "\t" << "is_accomodated";
	for (int i = java_families_count;i < (java_families_count+py_families_count);i++)
	{
		families[i]->print_details();
	}

	cout << "\nNumber of unallocated Py village families: " << unallocated_families_count;
	cout << "\nNumber of accomodated Py Village families: " << py_families_count - unallocated_families_count;

	return 0;
}
