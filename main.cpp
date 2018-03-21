
// PickingUpTheKit.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

#define SIZEOFHIST 100
unsigned int myHist[SIZEOFHIST]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// �������
class Envelope{
	unsigned short int numberOfLabelsInEnvelope;
	unsigned short int sizeOfCollection;
public:
	vector<int> elabel; // ������ �������
	Envelope(const Envelope &En); // ����������� ����������� �����, �.�. ������� ��������� ��� �������� �������.
	Envelope(unsigned short int InNumberOfLabelsInEnvelope, unsigned short int inSizeOfCollection);// ������������� ��������� �������
	//~Envelope();
	void fill(); // ��������� ������� ������
	void show(); // �������� ���������� ��������
};

// ������������� ��������� �������
Envelope::Envelope(unsigned short int InNumberOfLabelsInEnvelope, unsigned short int inSizeOfCollection){
	numberOfLabelsInEnvelope=InNumberOfLabelsInEnvelope;
	sizeOfCollection=inSizeOfCollection;
	//cout << "������� ������. �� ����. "<< endl;
}
//
Envelope::Envelope(const Envelope &En){
	elabel=En.elabel;
	numberOfLabelsInEnvelope=En.numberOfLabelsInEnvelope;
	sizeOfCollection=En.sizeOfCollection;
}

void Envelope::fill(){
	// ��������� �������
	for(int i=0; i<numberOfLabelsInEnvelope; i++){
		elabel.push_back( rand()%sizeOfCollection   ); // 0 ... (numberOfLabelsInEnvelope-1)
	}
	random_shuffle(elabel.begin(),elabel.end()); // �� ���� ����� ���� �� ������ ���������� �������� �������.
}

void Envelope::show(){
	cout << "���������� ��������: [ ";
	for(int i=0; i<elabel.size(); i++){
		cout << elabel[i];
		cout << "  ";
	}
	cout << "]  ";
}



// ���������
class Collection{
public:
	unsigned short int sizeOfCollection;
	//unsigned short int sizeOfCollection;
    vector<int> clabel; // ������ ����������� ������ �������
	Collection(unsigned short int InSizeOfCollection);
	Collection(const Collection &Coll );
	//~Collection();
	void replenishCollection(Envelope Envlp);  // ��������� ��������� (supplement)
	bool thereIsInTheCollection(int labeli); // ���������� ���� �� � ��������� �������� � ������� labeli?
	void show();
};
//
Collection::Collection(unsigned short int InSizeOfCollection){
	sizeOfCollection=InSizeOfCollection;
	//cout << "��������� �������."<< endl;
}
//
void Collection::replenishCollection(Envelope Envlp){
	for(int i=0; i<Envlp.elabel.size(); i++){
		if( !thereIsInTheCollection( Envlp.elabel[i] ) ){ // ���� ����� �������� ��� ��� � ���������, ��
			clabel.push_back(Envlp.elabel[i]);  // ��������� ����� �������� � ��������
		}// if
	}// for
}
//
Collection::Collection(const Collection &Coll){
	clabel=Coll.clabel;
	sizeOfCollection=Coll.sizeOfCollection;
}
//
bool Collection::thereIsInTheCollection(int labeli){
	for(int i=0; i<clabel.size(); i++){
		if(clabel[i]==labeli){
			return true;
		}
	}
	return false;
}

void Collection::show(){
	cout << "���������� ��������� ( ";
	for(int i=0; i<clabel.size(); i++){
		cout << clabel[i];
		cout << " ";
	}
	cout <<" )"<< endl;
}



unsigned short int carryOutExperiment( Collection &MyColl,  Envelope &Envl  ){
	unsigned short int n=0;
	//MyColl.show();
	while(MyColl.clabel.size() < MyColl.sizeOfCollection ){ // ���� ������ �������� �� ������
		n++;
		Envl.fill(); // ������ ����� �������
		//Envl.show(); // �������� �������. ��� �������
		MyColl.replenishCollection(Envl);// ������� ����� ��������
		//MyColl.show();    //��� �������
		Envl.elabel.clear();// ��������� �������
	}
	return n; // ��� ����, ����� ������� ������ �������� ����� ������ n ���������.
}

void findMax(unsigned int* inputArr,int size, unsigned int* maxEl,unsigned int* indexOfmaxEl ){
	unsigned int maxElelent;
	unsigned int indmaxEl;
	maxElelent=0;
	indmaxEl=0;

	for(int s=0; s<size; s++){
		if(inputArr[s]>maxElelent){
			maxElelent=inputArr[s];
			indmaxEl=s;
		}
	}
	*maxEl=maxElelent;
	*indexOfmaxEl=indmaxEl;
}

int main(){
	setlocale(LC_ALL, "Russian"); // ����������� ����������� ���������� ��������� �� �������.
	srand(time(NULL) ); // �������������� ��������� ��������� �����

	unsigned short int numberOfLabelsInEnvelope=0;  // ����� ������� � �������� (0 ... 65 000)
	unsigned int numberOfExperiments=0; // ����� ������������� (0 ... 65 000)
	unsigned short int numberOfEnvelopesYouNeedToBuy=0; // ���������� ���������, ������� ����� ������ ��� ����, ����� ������� ������ ��������.
	unsigned short int numberOfLabelsInSet=0; // ���������� ������� � ��������� (0....65 000)


	//cout << "������� ����� ������� � ��������  (E): "; cin >> numberOfLabelsInEnvelope; cout << endl;
	//cout << "������� ����� ������� � ��������� (L): "; cin >> numberOfLabelsInSet;     cout << endl;

	//cout << "������� ����� ������������� (N): "; cin >> numberOfExperiments; cout << endl;
	numberOfExperiments=3000;


    printf("\nStart\n");
for(numberOfLabelsInEnvelope=8; numberOfLabelsInEnvelope<=12; numberOfLabelsInEnvelope++){
	for(numberOfLabelsInSet=8; numberOfLabelsInSet<=12; numberOfLabelsInSet++){
		printf("\n numberOfLabelsInSet    (L): %d  \n",numberOfLabelsInSet);
		printf(" numberOfLabelsInEnvelope (E): %d  \n",numberOfLabelsInEnvelope);


			// clear hist
	    for(int k=0;k<SIZEOFHIST;k++){
	    	myHist[k]=0;
	    }

	    Collection MyColl(numberOfLabelsInSet); // create collection
	    MyColl.clabel.clear();

	    Envelope Envl(numberOfLabelsInEnvelope, numberOfLabelsInSet);
	    Envl.elabel.clear();

	    ofstream file("Result", ios::out | ios::binary);
	    if(!file){
	    	cout << "Cannot open file."<<  endl;
	        getchar();
	    	exit(1);
    	}

	    //file << numberOfLabelsInEnvelope << " ";
	    //cout << numberOfLabelsInEnvelope << ": ";
	    int percentageOfExecution=0;

	    //printf("\nthe percentage of execution:\n" );

	    for(int i=0; i<numberOfExperiments; i++){
		    numberOfEnvelopesYouNeedToBuy = carryOutExperiment( MyColl, Envl);// �������� �����������
		    file << numberOfEnvelopesYouNeedToBuy << " "; // ������� ���������� � ����
		    //cout<< endl <<"���� ������ " <<numberOfEnvelopesYouNeedToBuy <<" ���������"<< " ";

		    // build histogramm here
		    myHist[numberOfEnvelopesYouNeedToBuy]++;

		    MyColl.clabel.clear();  // ��������� ���������

		    if(i%50){
		        percentageOfExecution = (i*100/numberOfExperiments);
		    //printf("the percentage of execution: [%d  %%], \n\r",percentageOfExecution );
			//printf("\b\b\b\b\b\r");
			    printf("\r");
	    		printf("[%d%%]",percentageOfExecution );
	        }
	    }
	    file.close();

	//printf("\nDone! \a\n");

	/*
	for(int k=0; k<SIZEOFHIST; k++){
		printf("%d: \t %d \n\r",k, myHist[k]);
	}
	*/

	    unsigned int maxElem=0;
	    unsigned int indexOfmaxElem=0;

	    findMax(myHist, SIZEOFHIST, &maxElem , &indexOfmaxElem );

	    //printf("\nmax el: %d necc envel: %d \n\r", maxElem, indexOfmaxElem);
		printf("\n      the required number of envelopes: %d \n\r", indexOfmaxElem);
	}
}

	printf("\nDone! \a\n");

	getchar();
	return 0;
}

