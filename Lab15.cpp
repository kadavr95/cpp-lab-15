#include <fstream.h>
#include <iostream.h>
#include <conio.h>
#include <string>
#include <iomanip>

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
void AboutProgramme();
void InputTextFile(StudentData *DataArray, int *StudentsCount, char FileName[50]);
void InputBinaryFile(StudentData *DataArray, int *StudentsCount, char FileName[50]);
void OutputFile(StudentData *DataArray, int StudentsCount, char FileName[50]);
void DataSort(StudentData *DataArray, int StudentsCount);
void OutputConsole(StudentData *DataArray, int StudentsCount);

int CharComparison( const void *a, const void *b);

string RussianOutput(char TextChar[]); //перевод кодировки Windows в Dos

void output_file(char file_name[30]); //создание файла

const MaxElements=50;

void main()//main function
{
	char FileName[50];
	int StudentsCount;
	short OperationCode;//defining variables
	StudentData *DataArray = new StudentData [MaxElements];
	OutputMainMenu();//show menu of available commands
	while(OperationCode!=48)//endless repeat
	{
		OperationCode=getch();//get command
		system("cls");//clear console screen
		switch (OperationCode)//command choice
		{
			case 49:
				cout<<"Enter filename\n";
				cin>>FileName;
				InputTextFile(DataArray, &StudentsCount, FileName);
				break;
			case 50:
                cout<<"Enter filename\n";
				cin>>FileName;
				InputBinaryFile(DataArray, &StudentsCount, FileName);
				break;
			case 51:
				DataSort(DataArray, StudentsCount);

				break;
			case 52:
				cout<<"   Code   |         Last Name           |          First Name         |         Middle Name         |  Group   |Grades\n";
				OutputConsole(DataArray, StudentsCount);
				break;
			case 53:

				break;
			case 54:
				cout<<"Enter filename\n";
				cin>>FileName;
				OutputFile(DataArray, StudentsCount, FileName);
				break;
			case 55:

				break;
			case 56:

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
		cout<<setw(10)<<left<<RussianOutput((DataArray)[Counter].Code)<<"|";
		cout<<setw(29)<<RussianOutput((DataArray)[Counter].LastName)<<"|";
		cout<<setw(29)<<RussianOutput((DataArray)[Counter].FirstName)<<"|";
		cout<<setw(29)<<RussianOutput((DataArray)[Counter].MiddleName)<<"|";
		cout<<setw(10)<<RussianOutput((DataArray)[Counter].Group)<<"|";
		cout<<setw(6)<<(DataArray)[Counter].Grades<<"\n";    
	}
}

void DataSort(StudentData *DataArray, int StudentsCount)
{
	//qsort(DataArray[0].LastName, StudentsCount,sizeof(DataArray[0]),CharComparison);
	qsort(DataArray[0].Grades, StudentsCount,sizeof(DataArray[0]),FloatComparison);
}

int CharComparison( const void *a, const void *b)
{
   return( strcmp((char *)a,(char *)b) );
}

/*
void MatrixQuickSort(int FirstElement, int LastElement, VariableClassType** DataMatrix, int RowNumber)//matrix sort
{
	VariableClassType Pivot, TemporaryVariable; //defining variables
	int FirstSubarrayElement,LastSubarrayElement,Counter;
	FirstSubarrayElement=FirstElement;//assign data from external variables to internal counters
	LastSubarrayElement=LastElement;
	Pivot=DataMatrix[(FirstSubarrayElement+LastSubarrayElement)/2][0];//defining pivot element
	while (FirstSubarrayElement<=LastSubarrayElement)//checking counters intersection
	{
		while (DataMatrix[FirstSubarrayElement][0]<Pivot)//while element is smaller than pivot
		{
			FirstSubarrayElement++;//left counter increment
		}
		while (DataMatrix[LastSubarrayElement][0]>Pivot)//while element is bigger than pivot
		{
			LastSubarrayElement--;//right counter decrement
		}
		if (FirstSubarrayElement<=LastSubarrayElement)//in case of left counter is less than right counter
		{
			for (Counter = 0; Counter < RowNumber; Counter++)//replacement of all elements in column through temporary variable
			{
				TemporaryVariable=DataMatrix[FirstSubarrayElement][Counter];
				DataMatrix[FirstSubarrayElement][Counter]=DataMatrix[LastSubarrayElement][Counter];
				DataMatrix[LastSubarrayElement][Counter]=TemporaryVariable;
			}
			FirstSubarrayElement++;//left counter increment
			LastSubarrayElement--;//right counter decrement
		}
	}
	if (FirstElement<LastSubarrayElement)//sorting of left part of matrix
		MatrixQuickSort(FirstElement,LastSubarrayElement,DataMatrix, RowNumber);
	if (FirstSubarrayElement<LastElement)//sorting of right part of matrix
		MatrixQuickSort(FirstSubarrayElement,LastElement,DataMatrix, RowNumber);
}
*/



/*
void output_file(char file_name[30])
{
	worker r; //работник
	ofstream f; //файлова€ переменна€
	f.open(name); //открытие текстового файла
	// «апись в файл данных о 3 работниках
	for(int i=1;i<=3;i++)
	{
	   cout<<"number? ";
	   cin>>r.nom;
	   cout<<Фfam? У;
	   cin>>r.fam;
	   cout<<Фname? У;
	   cin>>r.name;
	   cout<<Фsalary? У;
	   cin>>r.salary;
	   f<<r.number<<" "<<r.fam<<" "<<r.name<<" "<<r.salary<<endl;
	}
	f.close( ); //закрытие файла
}
*/

/*
void main( )
{
	char file_name[30]; //им€ файла
	cout<<"file_name_file? ";
	cin>>file_name;
	output_file(file_name);
}
*/

string RussianOutput(char TextChar[])
{
	string TextString;
	TextString=TextChar;
	int Counter=0;
	while (TextChar[Counter]!=0)
	{
	   if(TextChar[Counter]>='ј'&& TextChar[Counter]<='п' ) TextString[Counter]-=64;
	   if(TextChar[Counter]>='р'&& TextChar[Counter]<='€' ) TextString[Counter]-=16;
	   if(TextChar[Counter]=='®' ) TextString[Counter]=240;
	   if(TextChar[Counter]=='Є' ) TextString[Counter]=241;
		  Counter++;
	}
	return TextString;
}

