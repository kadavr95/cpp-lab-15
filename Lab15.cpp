#include <fstream.h>
#include <iostream.h>
#include <conio.h>
#include <string>
#include <iomanip>

#include <clocale>    // может быть не обязательным - зависит от компилятора
#include <windows.h>

struct StudentData
{
   char Code[10];
   char FirstName[29];
   char MiddleName[29];
   char LastName[29];
   char Group[10];
   float Grades;
};

void OutputMainMenu();
void OutputSortMenu();
void OutputSearchMenu();
void AboutProgramme();
void InputTextFile(StudentData *DataArray, int *StudentsCount, char FileName[50]);
void InputBinaryFile(StudentData *DataArray, int *StudentsCount, char FileName[50]);
void OutputFile(StudentData *DataArray, int StudentsCount, char FileName[50]);
void DataSort(StudentData *DataArray, int StudentsCount);
void OutputConsole(StudentData *DataArray, int StudentsCount);
int CodeComparison( const void *a, const void *b);
int LastNameComparison( const void *a, const void *b);
int FirstNameComparison( const void *a, const void *b);
int MiddleNameComparison( const void *a, const void *b);
int GroupComparison( const void *a, const void *b);
int GradesComparison( const void *a, const void *b);
void BinarySearch(StudentData *DataArray, int StudentsCount);
void SearchResultCode(StudentData *DataArray, char SearchElement[29], int Index);
void SearchResultLastName(StudentData *DataArray, char SearchElement[29], int Index);
void SearchResultFirstName(StudentData *DataArray, char SearchElement[29], int Index);
void SearchResultMiddleName(StudentData *DataArray, char SearchElement[29], int Index);
void SearchResultGroup(StudentData *DataArray, char SearchElement[29], int Index);
void SearchResultGrades(StudentData *DataArray, float SearchElement, int Index);
int BinarySearchCode(StudentData *DataArray, int StudentsCount, char SearchElement[29]);
int BinarySearchLastName(StudentData *DataArray, int StudentsCount, char SearchElement[29]);
int BinarySearchFirstName(StudentData *DataArray, int StudentsCount, char SearchElement[29]);
int BinarySearchMiddleName(StudentData *DataArray, int StudentsCount, char SearchElement[29]);
int BinarySearchGroup(StudentData *DataArray, int StudentsCount, char SearchElement[29]);
int BinarySearchGrades(StudentData *DataArray, int StudentsCount, float SearchElement);

string RussianOutput(char TextChar[]); //перевод кодировки Windows в Dos

void output_file(char file_name[30]); //создание файла

const MaxElements=50;

void main()//main function
{
	char FileName[50];
	int StudentsCount;
	short OperationCode=0;//defining variables
	StudentData *DataArray = new StudentData [MaxElements];
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	OutputMainMenu();//show menu of available commands
	while(OperationCode!=48)//endless repeat
	{
		OperationCode=getch();//get command
		system("cls");//clear console screen
		switch (OperationCode)//command choice
		{
			case 49:
				cout<<"OPEN TEXT FILE\n";
				cout<<"Enter filename\n";
				cin>>FileName;
				InputTextFile(DataArray, &StudentsCount, FileName);
				cout<<"Done!\n";
				break;
			case 50:
				cout<<"OPEN BINARY FILE\n";
                cout<<"Enter filename\n";
				cin>>FileName;
				InputBinaryFile(DataArray, &StudentsCount, FileName);
				cout<<"Done!\n";
				break;
			case 51:
				DataSort(DataArray, StudentsCount);
				break;
			case 52:
				cout<<"   Code   |         Last Name           |          First Name         |         Middle Name         |  Group   |Grades\n";
				OutputConsole(DataArray, StudentsCount);
				break;
			case 53:
				BinarySearch(DataArray, StudentsCount);
				/*
				cout<<"SEARCH DATA\n";
				cout<<"Enter value to search\n";
				cin>>SearchElement;
				BinarySearchLastName(DataArray, StudentsCount, SearchElement);
				*/
				break;
			case 54:
				cout<<"SAVE BINARY FILE\n";
				cout<<"Enter filename\n";
				cin>>FileName;
				OutputFile(DataArray, StudentsCount, FileName);
				cout<<"Done!\n";
				break;
			case 57:
				AboutProgramme();
				break;
			case 48:
				exit;
				break;
			default://case of pressing button not assigned to commands
				OutputMainMenu();//show menu of available commands
		}
	}
}

void OutputMainMenu()//show menu of available commands
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

void OutputSortMenu()
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

void OutputSearchMenu()
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
	cout<<"Version 1.0.0.0 build 20160423201500\n\n";
	cout<<"Development and testing: Yaskovich Dmitry (ISBO-05-15)\n\n";
	cout<<"Dimini Inc, 2016";
}

void InputTextFile(StudentData *DataArray, int *StudentsCount, char FileName[50])
{
	ifstream FileStream;
	*StudentsCount=0;
	FileStream.open(FileName);
	while (FileStream.eof()!=1)
	{
		FileStream>>(DataArray)[*StudentsCount].Code;
		FileStream>>(DataArray)[*StudentsCount].LastName;
		FileStream>>(DataArray)[*StudentsCount].FirstName;
		FileStream>>(DataArray)[*StudentsCount].MiddleName;
		FileStream>>(DataArray)[*StudentsCount].Group;
		FileStream>>(DataArray)[*StudentsCount].Grades;
		(*StudentsCount)++;
	}
	(*StudentsCount)--;
	FileStream.close();
}

void InputBinaryFile(StudentData *DataArray, int *StudentsCount, char FileName[50])
{
	ifstream FileStream;
	streampos Size;
	char * MemoryBlock;

	FileStream.open(FileName, ios::binary);
	Size = FileStream.tellg();
	MemoryBlock = new char [Size];
	*StudentsCount=0;
	while (FileStream.eof()!=1)
	{
		FileStream.read((DataArray)[*StudentsCount].Code, sizeof(char[10]));
		FileStream.read((DataArray)[*StudentsCount].LastName, sizeof(char[29]));
		FileStream.read((DataArray)[*StudentsCount].FirstName, sizeof(char[29]));
		FileStream.read((DataArray)[*StudentsCount].MiddleName, sizeof(char[29]));
		FileStream.read((DataArray)[*StudentsCount].Group, sizeof(char[10]));

		FileStream.read(MemoryBlock, sizeof(float));
		(DataArray)[*StudentsCount].Grades=atof(MemoryBlock);
		(*StudentsCount)++;
	}
	(*StudentsCount)--;
	FileStream.close();
	delete[] MemoryBlock;

}

void OutputFile(StudentData *DataArray, int StudentsCount, char FileName[50])
{
	ofstream FileStream;
	int Counter;
	char MemoryBlock[30];
	FileStream.open(FileName, ios::binary | ios::trunc);
	for (Counter = 0; Counter < StudentsCount; Counter++)
	{
		FileStream.write((DataArray)[Counter].Code,sizeof(char[10]));
		FileStream.write((DataArray)[Counter].LastName,sizeof(char[29]));
		FileStream.write((DataArray)[Counter].FirstName,sizeof(char[29]));
		FileStream.write((DataArray)[Counter].MiddleName,sizeof(char[29]));
		FileStream.write((DataArray)[Counter].Group,sizeof(char[10]));
		snprintf(MemoryBlock, sizeof((DataArray)[Counter].Grades), "%f", (DataArray)[Counter].Grades);
		FileStream.write(MemoryBlock,sizeof(float));
	}
	FileStream.close();
}

void OutputConsole(StudentData *DataArray, int StudentsCount)
{
	int Counter;
	for (Counter = 0; Counter < StudentsCount; Counter++) 
	{
		cout<<setw(10)<<left<<(DataArray)[Counter].Code<<"|";
		cout<<setw(29)<<(DataArray)[Counter].LastName<<"|";
		cout<<setw(29)<<(DataArray)[Counter].FirstName<<"|";
		cout<<setw(29)<<(DataArray)[Counter].MiddleName<<"|";
		cout<<setw(10)<<(DataArray)[Counter].Group<<"|";
		cout<<setw(6)<<(DataArray)[Counter].Grades<<"\n";
	}
}

void DataSort(StudentData *DataArray, int StudentsCount)
{
	short OperationCode=0;//defining variables
	OutputSortMenu();//show menu of available commands
	while(OperationCode<48 || OperationCode>54)//endless repeat
	{
		OperationCode=getch();//get command
		system("cls");//clear console screen
		switch (OperationCode)//command choice
		{
			case 49:
				cout<<"SORT BY CODE\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),CodeComparison);
				cout<<"Done!";
				break;
			case 50:
				cout<<"SORT BY LAST NAME\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),LastNameComparison);
				cout<<"Done!";
				break;
			case 51:
				cout<<"SORT BY FIRST NAME\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),FirstNameComparison);
				cout<<"Done!";
				break;
			case 52:
				cout<<"SORT BY MIDDLE NAME\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),MiddleNameComparison);
				cout<<"Done!";
				break;
			case 53:
				cout<<"SORT BY GROUP\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),GroupComparison);
				cout<<"Done!";
				break;
			case 54:
				cout<<"SORT BY GRADES\n";
				qsort(DataArray, StudentsCount,sizeof(DataArray[0]),GradesComparison);
				cout<<"Done!";
				break;
			case 48:
				OutputMainMenu();
				exit;
				break;
			default://case of pressing button not assigned to commands
				OutputSortMenu();//show menu of available commands
		}
	}
}

int CodeComparison( const void *a, const void *b)
{
   return strcmp(((StudentData*)a)->Code, ((StudentData*)b)->Code);
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
   double Difference= ((StudentData*)a)->Grades - ((StudentData*)b)->Grades;
   return ( Difference < 0.0 ) ? -1 : ( Difference > 0.0 ) ? 1 : 0;
}

void BinarySearch(StudentData *DataArray, int StudentsCount)
{
	char SearchElement[29];
	float SearchElementFloat;
	short OperationCode=0;//defining variables
	int Index;
	OutputSearchMenu();//show menu of available commands
	while(OperationCode<48 || OperationCode>54)//endless repeat
	{
		OperationCode=getch();//get command
		system("cls");//clear console screen
		switch (OperationCode)//command choice
		{
			case 49:
				cout<<"SEARCH BY CODE\n";
                cout<<"Enter value to search\n";
				cin>>SearchElement;
				Index=BinarySearchCode(DataArray, StudentsCount, SearchElement);
				SearchResultCode(DataArray, SearchElement,Index);
				cout<<"Done!";
				break;
			case 50:
				cout<<"SEARCH BY LAST NAME\n";
                cout<<"Enter value to search\n";
				cin>>SearchElement;
				Index=BinarySearchLastName(DataArray, StudentsCount, SearchElement);
				SearchResultLastName(DataArray, SearchElement,Index);
				cout<<"Done!";
				break;
			case 51:
				cout<<"SEARCH BY FIRST NAME\n";
                cout<<"Enter value to search\n";
				cin>>SearchElement;
				Index=BinarySearchFirstName(DataArray, StudentsCount, SearchElement);
				SearchResultFirstName(DataArray, SearchElement,Index);
				cout<<"Done!";
				break;
			case 52:
				cout<<"SEARCH BY MIDDLE NAME\n";
                cout<<"Enter value to search\n";
				cin>>SearchElement;
				Index=BinarySearchMiddleName(DataArray, StudentsCount, SearchElement);
				SearchResultMiddleName(DataArray, SearchElement,Index);
				cout<<"Done!";
				break;
			case 53:
				cout<<"SEARCH BY GROUP\n";
				cout<<"Enter value to search\n";
				cin>>SearchElement;
				Index=BinarySearchGroup(DataArray, StudentsCount, SearchElement);
				SearchResultGroup(DataArray, SearchElement,Index);
				cout<<"Done!";
				break;
			case 54:
				cout<<"SEARCH BY GRADES\n";
                cout<<"Enter value to search\n";
				cin>>SearchElementFloat;
				Index=BinarySearchGrades(DataArray, StudentsCount, SearchElementFloat);
				SearchResultGrades(DataArray, SearchElementFloat,Index);
				cout<<"Done!";
				break;
			case 48:
				OutputMainMenu();
				exit;
				break;
			default://case of pressing button not assigned to commands
				OutputSortMenu();//show menu of available commands
		}
	}
}

void SearchResultCode(StudentData *DataArray, char SearchElement[29], int Index)
{
	if (strcmp(SearchElement, (DataArray[Index].Code))==0)
		cout<<"Value is found\n"<<"Index: "<<Index<<"\nCode: "<<DataArray[Index].Code<<"\nName: "<<DataArray[Index].LastName<<" "<<
			DataArray[Index].FirstName<<" "<<DataArray[Index].MiddleName<<"\nGroup: "<<DataArray[Index].Group<<"\nGrades: "<<DataArray[Index].Grades<<"\n";
	else
		cout << "Value is not found!\n";
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

int BinarySearchCode(StudentData *DataArray, int StudentsCount, char SearchElement[29])
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;
	while (FirstIndex < LastIndex)
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2; // меняем индекс среднего значения

		if (strcmp(SearchElement, (DataArray[AverageIndex].Code))<=0)
			LastIndex = AverageIndex;
		else
			FirstIndex = AverageIndex + 1;    // найден ключевой элемент или нет
	}
	return LastIndex;
}

int BinarySearchLastName(StudentData *DataArray, int StudentsCount, char SearchElement[29])
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;
	while (FirstIndex < LastIndex)
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2; // меняем индекс среднего значения

		if (strcmp(SearchElement, (DataArray[AverageIndex].LastName))<=0)
			LastIndex = AverageIndex;
		else
			FirstIndex = AverageIndex + 1;    // найден ключевой элемент или нет
	}
	return LastIndex;
}

int BinarySearchFirstName(StudentData *DataArray, int StudentsCount, char SearchElement[29])
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;
	while (FirstIndex < LastIndex)
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2; // меняем индекс среднего значения

		if (strcmp(SearchElement, (DataArray[AverageIndex].FirstName))<=0)
			LastIndex = AverageIndex;
		else
			FirstIndex = AverageIndex + 1;    // найден ключевой элемент или нет
	}
	return LastIndex;
}

int BinarySearchMiddleName(StudentData *DataArray, int StudentsCount, char SearchElement[29])
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;
	while (FirstIndex < LastIndex)
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2; // меняем индекс среднего значения

		if (strcmp(SearchElement, (DataArray[AverageIndex].MiddleName))<=0)
			LastIndex = AverageIndex;
		else
			FirstIndex = AverageIndex + 1;    // найден ключевой элемент или нет
	}
	return LastIndex;
}

int BinarySearchGroup(StudentData *DataArray, int StudentsCount, char SearchElement[29])
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;
	while (FirstIndex < LastIndex)
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2; // меняем индекс среднего значения

		if (strcmp(SearchElement, (DataArray[AverageIndex].Group))<=0)
			LastIndex = AverageIndex;
		else
			FirstIndex = AverageIndex + 1;    // найден ключевой элемент или нет
	}
	return LastIndex;
}

int BinarySearchGrades(StudentData *DataArray, int StudentsCount, float SearchElement)
{
	int AverageIndex = 0, FirstIndex   = 0,LastIndex    = StudentsCount -1;
	while (FirstIndex < LastIndex)
	{
		AverageIndex = FirstIndex + (LastIndex - FirstIndex) / 2; // меняем индекс среднего значения

		if ((SearchElement)<=(DataArray[AverageIndex].Grades))
			LastIndex = AverageIndex;
		else
			FirstIndex = AverageIndex + 1;    // найден ключевой элемент или нет
	}
	return LastIndex;
}

