//used libraries
#include <fstream.h>//file stream
#include <iostream.h>//input, output stream
#include <conio.h>//getch
#include <iomanip>//string comparison
#include <windows.h>//localization

struct StudentData//student structure
{
   char Code[10];
   char FirstName[29];
   char MiddleName[29];
   char LastName[29];
   char Group[10];
   float Grades;
};

//functions prototypes
void OutputMainMenu();//menu and info
void OutputSortMenu();
void OutputSearchMenu();
void AboutProgramme();
void InputTextFile(StudentData *DataArray, int *StudentsCount, char FileName[50]);//open files
void InputBinaryFile(StudentData *DataArray, int *StudentsCount, char FileName[50]);
void OutputFile(StudentData *DataArray, int StudentsCount, char FileName[50]);//save file
void DataSort(StudentData *DataArray, int StudentsCount);//sorting data
void OutputConsole(StudentData *DataArray, int StudentsCount);//output to console
int CodeComparison( const void *a, const void *b);//comparison of structure elements
int LastNameComparison( const void *a, const void *b);
int FirstNameComparison( const void *a, const void *b);
int MiddleNameComparison( const void *a, const void *b);
int GroupComparison( const void *a, const void *b);
int GradesComparison( const void *a, const void *b);
void BinarySearch(StudentData *DataArray, int StudentsCount);//element search
void SearchResultCode(StudentData *DataArray, char SearchElement[29], int Index);//structure element search result output
void SearchResultLastName(StudentData *DataArray, char SearchElement[29], int Index);
void SearchResultFirstName(StudentData *DataArray, char SearchElement[29], int Index);
void SearchResultMiddleName(StudentData *DataArray, char SearchElement[29], int Index);
void SearchResultGroup(StudentData *DataArray, char SearchElement[29], int Index);
void SearchResultGrades(StudentData *DataArray, float SearchElement, int Index);
int BinarySearchCode(StudentData *DataArray, int StudentsCount, char SearchElement[29]);//search structure element
int BinarySearchLastName(StudentData *DataArray, int StudentsCount, char SearchElement[29]);
int BinarySearchFirstName(StudentData *DataArray, int StudentsCount, char SearchElement[29]);
int BinarySearchMiddleName(StudentData *DataArray, int StudentsCount, char SearchElement[29]);
int BinarySearchGroup(StudentData *DataArray, int StudentsCount, char SearchElement[29]);
int BinarySearchGrades(StudentData *DataArray, int StudentsCount, float SearchElement);

const MaxElements=50;//maximum available quantity of elements in structure

void main()//main function
{
	char FileName[50];//defining variables
	int StudentsCount;
	short OperationCode=0;
	StudentData *DataArray = new StudentData [MaxElements];//structure array creation
	SetConsoleOutputCP(1251);//console localization
	SetConsoleCP(1251);
	OutputMainMenu();//show menu of available commands
	while(OperationCode!=48)//repeat untin exit
	{
		OperationCode=getch();//get command
		system("cls");//clear console screen
		switch (OperationCode)//command choice
		{
			case 49://open text file
				cout<<"OPEN TEXT FILE\n";
				cout<<"Enter filename\n";//filename assignmnent
				cin>>FileName;
				InputTextFile(DataArray, &StudentsCount, FileName);
				cout<<"Done!\n";
				break;
			case 50://open binary file
				cout<<"OPEN BINARY FILE\n";
				cout<<"Enter filename\n";//filename assignmnent
				cin>>FileName;
				InputBinaryFile(DataArray, &StudentsCount, FileName);
				cout<<"Done!\n";
				break;
			case 51://sort data
				DataSort(DataArray, StudentsCount);
				break;
			case 52://show data in console
				cout<<"   Code   |         Last Name           |          First Name         |         Middle Name         |  Group   |Grades\n";
				OutputConsole(DataArray, StudentsCount);
				break;
			case 53://data search
				BinarySearch(DataArray, StudentsCount);
				break;
			case 54://save binary file
				cout<<"SAVE BINARY FILE\n";
				cout<<"Enter filename\n";//filename assignmnent
				cin>>FileName;
				OutputFile(DataArray, StudentsCount, FileName);
				cout<<"Done!\n";
				break;
			case 57://show info about programme
				AboutProgramme();
				break;
			case 48://programme shut down
				exit;
				break;
			default://case of pressing button not assigned to commands
				OutputMainMenu();//show menu of available commands
		}
	}
}

void OutputMainMenu()//show menu of available commands in main menu
{
	cout<<"MAIN MENU\n";
	cout<<"Choose operation:\n";
	cout<<"Press 1 to open text file\n";
	cout<<"Press 2 to open binary file\n";
	cout<<"Press 3 to sort data\n";
	cout<<"Press 4 to show data\n";
	cout<<"Press 5 to search data\n";
	cout<<"Press 6 to save data to binary file\n";
	cout<<"Press 9 to get info about the programme\n";
	cout<<"Press 0 to exit";
}

void OutputSortMenu()//show menu of available commands in sort menu
{
	cout<<"SORT DATA\n";
	cout<<"Choose value to sort:\n";
	cout<<"Press 1 to sort by code\n";
	cout<<"Press 2 to sort by last name\n";
	cout<<"Press 3 to sort by first name\n";
	cout<<"Press 4 to sort by middle name\n";
	cout<<"Press 5 to sort by group\n";
	cout<<"Press 6 to sort by grades\n";
	cout<<"Press 0 to return to main menu";
}

void OutputSearchMenu()//show menu of available commands in search menu
{
	cout<<"SEARCH DATA\n";
	cout<<"Choose value to search:\n";
	cout<<"Press 1 to search by code\n";
	cout<<"Press 2 to search by last name\n";
	cout<<"Press 3 to search by first name\n";
	cout<<"Press 4 to search by middle name\n";
	cout<<"Press 5 to search by group\n";
	cout<<"Press 6 to search by grades\n";
	cout<<"Press 0 to return to main menu";
}

void AboutProgramme()//show info about the programme
{
	cout<<"ABOUT PROGRAMME\n\n";
	cout<<"Lab 15: Files\n";
	cout<<"Variant 4\n\n";
	cout<<"Version 1.0.0.0 build 20160427180000\n\n";
	cout<<"Development and testing: Yaskovich Dmitry (ISBO-05-15)\n\n";
	cout<<"Dimini Inc, 2016";
}

void InputTextFile(StudentData *DataArray, int *StudentsCount, char FileName[50])//open text file
{
	ifstream FileStream;//defining variables
	*StudentsCount=0;
	FileStream.open(FileName);//open file
	while (FileStream.eof()!=1)//repeat until file ends
	{
		FileStream>>(DataArray)[*StudentsCount].Code;//fill structure for one student
		FileStream>>(DataArray)[*StudentsCount].LastName;
		FileStream>>(DataArray)[*StudentsCount].FirstName;
		FileStream>>(DataArray)[*StudentsCount].MiddleName;
		FileStream>>(DataArray)[*StudentsCount].Group;
		FileStream>>(DataArray)[*StudentsCount].Grades;
		(*StudentsCount)++;//go to next student
	}
	(*StudentsCount)--;//correcting number of students
	FileStream.close();//close file
}

void InputBinaryFile(StudentData *DataArray, int *StudentsCount, char FileName[50])//open binary file
{
	ifstream FileStream; //defining variables
	streampos Size;
	char * MemoryBlock;
	FileStream.open(FileName, ios::binary);//open file
	Size = FileStream.tellg();//preparing big enough memory block for later
	MemoryBlock = new char [Size];
	*StudentsCount=0;
	while (FileStream.eof()!=1)//repeat until file ends
	{
		FileStream.read((DataArray)[*StudentsCount].Code, sizeof(char[10]));//fill structure for one student
		FileStream.read((DataArray)[*StudentsCount].LastName, sizeof(char[29]));
		FileStream.read((DataArray)[*StudentsCount].FirstName, sizeof(char[29]));
		FileStream.read((DataArray)[*StudentsCount].MiddleName, sizeof(char[29]));
		FileStream.read((DataArray)[*StudentsCount].Group, sizeof(char[10]));
		FileStream.read(MemoryBlock, sizeof(float));//float type data filling
		(DataArray)[*StudentsCount].Grades=atof(MemoryBlock);
		(*StudentsCount)++;//go to next student
	}
	(*StudentsCount)--;//correcting number of students
	FileStream.close();//close file
	delete[] MemoryBlock;//free memory

}

void OutputFile(StudentData *DataArray, int StudentsCount, char FileName[50])//save binary file
{
	ofstream FileStream;//defining variables
	int Counter;
	char MemoryBlock[30];
	FileStream.open(FileName, ios::binary | ios::trunc);//open file
	for (Counter = 0; Counter < StudentsCount; Counter++)//repeat for all students
	{
		FileStream.write((DataArray)[Counter].Code,sizeof(char[10]));//save structure of one student
		FileStream.write((DataArray)[Counter].LastName,sizeof(char[29]));
		FileStream.write((DataArray)[Counter].FirstName,sizeof(char[29]));
		FileStream.write((DataArray)[Counter].MiddleName,sizeof(char[29]));
		FileStream.write((DataArray)[Counter].Group,sizeof(char[10]));
		snprintf(MemoryBlock, sizeof((DataArray)[Counter].Grades), "%f", (DataArray)[Counter].Grades);//float type data saving
		FileStream.write(MemoryBlock,sizeof(float));
	}
	FileStream.close();//close file
}

void OutputConsole(StudentData *DataArray, int StudentsCount)//output data to console
{
	int Counter;
	for (Counter = 0; Counter < StudentsCount; Counter++)//repeat for all students
	{
		cout<<setw(10)<<left<<(DataArray)[Counter].Code<<"|";//formatted output
		cout<<setw(29)<<(DataArray)[Counter].LastName<<"|";
		cout<<setw(29)<<(DataArray)[Counter].FirstName<<"|";
		cout<<setw(29)<<(DataArray)[Counter].MiddleName<<"|";
		cout<<setw(10)<<(DataArray)[Counter].Group<<"|";
		cout<<setw(6)<<(DataArray)[Counter].Grades<<"\n";
	}
}

void DataSort(StudentData *DataArray, int StudentsCount)//sorting data
{
	short OperationCode=0;//defining variables
	OutputSortMenu();//show menu of available commands
	while(OperationCode<48 || OperationCode>54)//repeat until exit
	{
		OperationCode=getch();//get command
		system("cls");//clear console screen
		switch (OperationCode)//command choice
		{
			case 49://sort by code
				cout<<"SORT BY CODE\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),CodeComparison);
				cout<<"Done!";
				break;
			case 50://sort by last name
				cout<<"SORT BY LAST NAME\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),LastNameComparison);
				cout<<"Done!";
				break;
			case 51://sort by first name
				cout<<"SORT BY FIRST NAME\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),FirstNameComparison);
				cout<<"Done!";
				break;
			case 52://sort by middle name
				cout<<"SORT BY MIDDLE NAME\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),MiddleNameComparison);
				cout<<"Done!";
				break;
			case 53://sort by group
				cout<<"SORT BY GROUP\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),GroupComparison);
				cout<<"Done!";
				break;
			case 54://sort by grades
				cout<<"SORT BY GRADES\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),GradesComparison);
				cout<<"Done!";
				break;
			case 48://exit submenu
				OutputMainMenu();
				exit;
				break;
			default://case of pressing button not assigned to commands
				OutputSortMenu();//show menu of available commands
		}
	}
}

//Elements comparison functions
/*----------------------------------------------------------------------------*/

int CodeComparison( const void *a, const void *b)
{
   return strcmp(((StudentData*)a)->Code, ((StudentData*)b)->Code);//compare char fields
}

int LastNameComparison( const void *a, const void *b)
{
   return strcmp(((StudentData*)a)->LastName, ((StudentData*)b)->LastName);
}

int FirstNameComparison( const void *a, const void *b)
{
   return strcmp(((StudentData*)a)->FirstName, ((StudentData*)b)->FirstName);
}

int MiddleNameComparison( const void *a, const void *b)
{
   return strcmp(((StudentData*)a)->MiddleName, ((StudentData*)b)->MiddleName);
}

int GroupComparison( const void *a, const void *b)
{
   return strcmp(((StudentData*)a)->Group, ((StudentData*)b)->Group);
}

int GradesComparison( const void *a, const void *b)
{
   double Difference= ((StudentData*)a)->Grades - ((StudentData*)b)->Grades;//compare float fields
   return ( Difference < 0.0 ) ? -1 : ( Difference > 0.0 ) ? 1 : 0;
}

/*----------------------------------------------------------------------------*/

void BinarySearch(StudentData *DataArray, int StudentsCount)
{
	char SearchElement[29];//defining variables
	float SearchElementFloat;
	short OperationCode=0;
	int Index;
	OutputSearchMenu();//show menu of available commands
	while(OperationCode<48 || OperationCode>54)//repeat until exit
	{
		OperationCode=getch();//get command
		system("cls");//clear console screen
		switch (OperationCode)//command choice
		{
			case 49://search by code
				cout<<"SEARCH BY CODE\n";
                cout<<"Enter value to search\n";
				cin>>SearchElement;
				Index=BinarySearchCode(DataArray, StudentsCount, SearchElement);
				SearchResultCode(DataArray, SearchElement,Index);
				cout<<"Done!";
				break;
			case 50://search by last name
				cout<<"SEARCH BY LAST NAME\n";
                cout<<"Enter value to search\n";
				cin>>SearchElement;
				Index=BinarySearchLastName(DataArray, StudentsCount, SearchElement);
				SearchResultLastName(DataArray, SearchElement,Index);
				cout<<"Done!";
				break;
			case 51://search by first name
				cout<<"SEARCH BY FIRST NAME\n";
                cout<<"Enter value to search\n";
				cin>>SearchElement;
				Index=BinarySearchFirstName(DataArray, StudentsCount, SearchElement);
				SearchResultFirstName(DataArray, SearchElement,Index);
				cout<<"Done!";
				break;
			case 52://search by middle name
				cout<<"SEARCH BY MIDDLE NAME\n";
                cout<<"Enter value to search\n";
				cin>>SearchElement;
				Index=BinarySearchMiddleName(DataArray, StudentsCount, SearchElement);
				SearchResultMiddleName(DataArray, SearchElement,Index);
				cout<<"Done!";
				break;
			case 53://search by group
				cout<<"SEARCH BY GROUP\n";
				cout<<"Enter value to search\n";
				cin>>SearchElement;
				Index=BinarySearchGroup(DataArray, StudentsCount, SearchElement);
				SearchResultGroup(DataArray, SearchElement,Index);
				cout<<"Done!";
				break;
			case 54://search by grades
				cout<<"SEARCH BY GRADES\n";
                cout<<"Enter value to search\n";
				cin>>SearchElementFloat;
				Index=BinarySearchGrades(DataArray, StudentsCount, SearchElementFloat);
				SearchResultGrades(DataArray, SearchElementFloat,Index);
				cout<<"Done!";
				break;
			case 48://exit submenu
				OutputMainMenu();
				exit;
				break;
			default://case of pressing button not assigned to commands
				OutputSortMenu();//show menu of available commands
		}
	}
}

//Search results console output
/*----------------------------------------------------------------------------*/

void SearchResultCode(StudentData *DataArray, char SearchElement[29], int Index)
{
	if (strcmp(SearchElement, (DataArray[Index].Code))==0)//if element was found
		cout<<"Value is found\n"<<"Index: "<<Index<<"\nCode: "<<DataArray[Index].Code<<"\nName: "<<DataArray[Index].LastName<<" "<<
			DataArray[Index].FirstName<<" "<<DataArray[Index].MiddleName<<"\nGroup: "<<DataArray[Index].Group<<"\nGrades: "<<DataArray[Index].Grades<<"\n";//output info about elememnt
	else
		cout << "Value is not found!\n";//element not found
}

void SearchResultLastName(StudentData *DataArray, char SearchElement[29], int Index)
{
	if (strcmp(SearchElement, (DataArray[Index].LastName))==0)
		cout<<"Value is found\n"<<"Index: "<<Index<<"\nCode: "<<DataArray[Index].Code<<"\nName: "<<DataArray[Index].LastName<<" "<<
			DataArray[Index].FirstName<<" "<<DataArray[Index].MiddleName<<"\nGroup: "<<DataArray[Index].Group<<"\nGrades: "<<DataArray[Index].Grades<<"\n";
	else
		cout << "Value is not found!\n";
}

void SearchResultFirstName(StudentData *DataArray, char SearchElement[29], int Index)
{
	if (strcmp(SearchElement, (DataArray[Index].FirstName))==0)
		cout<<"Value is found\n"<<"Index: "<<Index<<"\nCode: "<<DataArray[Index].Code<<"\nName: "<<DataArray[Index].LastName<<" "<<
			DataArray[Index].FirstName<<" "<<DataArray[Index].MiddleName<<"\nGroup: "<<DataArray[Index].Group<<"\nGrades: "<<DataArray[Index].Grades<<"\n";
	else
		cout << "Value is not found!\n";
}

void SearchResultMiddleName(StudentData *DataArray, char SearchElement[29], int Index)
{
	if (strcmp(SearchElement, (DataArray[Index].MiddleName))==0)
		cout<<"Value is found\n"<<"Index: "<<Index<<"\nCode: "<<DataArray[Index].Code<<"\nName: "<<DataArray[Index].LastName<<" "<<
			DataArray[Index].FirstName<<" "<<DataArray[Index].MiddleName<<"\nGroup: "<<DataArray[Index].Group<<"\nGrades: "<<DataArray[Index].Grades<<"\n";
	else
		cout << "Value is not found!\n";
}

void SearchResultGroup(StudentData *DataArray, char SearchElement[29], int Index)
{
	if (strcmp(SearchElement, (DataArray[Index].Group))==0)
		cout<<"Value is found\n"<<"Index: "<<Index<<"\nCode: "<<DataArray[Index].Code<<"\nName: "<<DataArray[Index].LastName<<" "<<
			DataArray[Index].FirstName<<" "<<DataArray[Index].MiddleName<<"\nGroup: "<<DataArray[Index].Group<<"\nGrades: "<<DataArray[Index].Grades<<"\n";
	else
		cout << "Value is not found!\n";
}

void SearchResultGrades(StudentData *DataArray, float SearchElement, int Index)
{
	if ((SearchElement)==(DataArray[Index].Grades))
		cout<<"Value is found\n"<<"Index: "<<Index<<"\nCode: "<<DataArray[Index].Code<<"\nName: "<<DataArray[Index].LastName<<" "<<
			DataArray[Index].FirstName<<" "<<DataArray[Index].MiddleName<<"\nGroup: "<<DataArray[Index].Group<<"\nGrades: "<<DataArray[Index].Grades<<"\n";
	else
		cout << "Value is not found!\n";
}

/*----------------------------------------------------------------------------*/

//Binary search of elements
/*----------------------------------------------------------------------------*/

int BinarySearchCode(StudentData *DataArray, int StudentsCount, char SearchElement[29])
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;//defining variables
	while (FirstIndex < LastIndex)//while interval is big
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2; //average value on interval
		if (strcmp(SearchElement, (DataArray[AverageIndex].Code))<=0)//if element is less than average
			LastIndex = AverageIndex;//shrink right interval border
		else
			FirstIndex = AverageIndex + 1;    // shrink left interval border
	}
	return LastIndex;
}

int BinarySearchLastName(StudentData *DataArray, int StudentsCount, char SearchElement[29])
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;
	while (FirstIndex < LastIndex)
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2;
		if (strcmp(SearchElement, (DataArray[AverageIndex].LastName))<=0)
			LastIndex = AverageIndex;
		else
			FirstIndex = AverageIndex + 1;
	}
	return LastIndex;
}

int BinarySearchFirstName(StudentData *DataArray, int StudentsCount, char SearchElement[29])
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;
	while (FirstIndex < LastIndex)
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2;
		if (strcmp(SearchElement, (DataArray[AverageIndex].FirstName))<=0)
			LastIndex = AverageIndex;
		else
			FirstIndex = AverageIndex + 1;
	}
	return LastIndex;
}

int BinarySearchMiddleName(StudentData *DataArray, int StudentsCount, char SearchElement[29])
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;
	while (FirstIndex < LastIndex)
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2;
		if (strcmp(SearchElement, (DataArray[AverageIndex].MiddleName))<=0)
			LastIndex = AverageIndex;
		else
			FirstIndex = AverageIndex + 1;
	}
	return LastIndex;
}

int BinarySearchGroup(StudentData *DataArray, int StudentsCount, char SearchElement[29])
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;
	while (FirstIndex < LastIndex)
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2;
		if (strcmp(SearchElement, (DataArray[AverageIndex].Group))<=0)
			LastIndex = AverageIndex;
		else
			FirstIndex = AverageIndex + 1;
	}
	return LastIndex;
}

int BinarySearchGrades(StudentData *DataArray, int StudentsCount, float SearchElement)
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;
	while (FirstIndex < LastIndex)
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2;
		if ((SearchElement)<=(DataArray[AverageIndex].Grades))
			LastIndex = AverageIndex;
		else
			FirstIndex = AverageIndex + 1;
	}
	return LastIndex;
}

/*----------------------------------------------------------------------------*/
