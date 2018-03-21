
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

// Конверт
class Envelope{
	unsigned short int numberOfLabelsInEnvelope;
	unsigned short int sizeOfCollection;
public:
	vector<int> elabel; // массив наклеек
	Envelope(const Envelope &En); // Конструктор копирования нужет, т.к. конверт передаётся как параметр функции.
	Envelope(unsigned short int InNumberOfLabelsInEnvelope, unsigned short int inSizeOfCollection);// Сгенерировать случайный конверт
	//~Envelope();
	void fill(); // Заполнить конверт заново
	void show(); // Показать содкржимое конверта
};

// Сгенерировать случайный конверт
Envelope::Envelope(unsigned short int InNumberOfLabelsInEnvelope, unsigned short int inSizeOfCollection){
	numberOfLabelsInEnvelope=InNumberOfLabelsInEnvelope;
	sizeOfCollection=inSizeOfCollection;
	//cout << "Конверт создан. Он пуст. "<< endl;
}
//
Envelope::Envelope(const Envelope &En){
	elabel=En.elabel;
	numberOfLabelsInEnvelope=En.numberOfLabelsInEnvelope;
	sizeOfCollection=En.sizeOfCollection;
}

void Envelope::fill(){
	// Заполнить конверт
	for(int i=0; i<numberOfLabelsInEnvelope; i++){
		elabel.push_back( rand()%sizeOfCollection   ); // 0 ... (numberOfLabelsInEnvelope-1)
	}
	random_shuffle(elabel.begin(),elabel.end()); // На этом этапе было бы хорошо перемешать элементы массива.
}

void Envelope::show(){
	cout << "Содержимое конверта: [ ";
	for(int i=0; i<elabel.size(); i++){
		cout << elabel[i];
		cout << "  ";
	}
	cout << "]  ";
}



// Коллекция
class Collection{
public:
	unsigned short int sizeOfCollection;
	//unsigned short int sizeOfCollection;
    vector<int> clabel; // массив нокопленных разных наклеек
	Collection(unsigned short int InSizeOfCollection);
	Collection(const Collection &Coll );
	//~Collection();
	void replenishCollection(Envelope Envlp);  // Пополнить коллекцию (supplement)
	bool thereIsInTheCollection(int labeli); // Определить есть ли в коллекции наклейка с номаром labeli?
	void show();
};
//
Collection::Collection(unsigned short int InSizeOfCollection){
	sizeOfCollection=InSizeOfCollection;
	//cout << "Коллекция создана."<< endl;
}
//
void Collection::replenishCollection(Envelope Envlp){
	for(int i=0; i<Envlp.elabel.size(); i++){
		if( !thereIsInTheCollection( Envlp.elabel[i] ) ){ // Если такой наклейки ещё нет в коллекции, то
			clabel.push_back(Envlp.elabel[i]);  // Добавляем новую наклейку в коллецию
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
	cout << "Содержимое коллекции ( ";
	for(int i=0; i<clabel.size(); i++){
		cout << clabel[i];
		cout << " ";
	}
	cout <<" )"<< endl;
}



unsigned short int carryOutExperiment( Collection &MyColl,  Envelope &Envl  ){
	unsigned short int n=0;
	//MyColl.show();
	while(MyColl.clabel.size() < MyColl.sizeOfCollection ){ // Пока полный комплект не собран
		n++;
		Envl.fill(); // Купить новый нокверт
		//Envl.show(); // Раскрыть конверт. Для отладки
		MyColl.replenishCollection(Envl);// Выбрать новые наклейки
		//MyColl.show();    //Для отладки
		Envl.elabel.clear();// Выбросить остатки
	}
	return n; // Для того, чтобы собрать полный комплект нужно купить n конвертов.
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
	setlocale(LC_ALL, "Russian"); // Подключение возможности отображать кириллицу на консоль.
	srand(time(NULL) ); // Иницмализируем генератор случайных чисел

	unsigned short int numberOfLabelsInEnvelope=0;  // число наклеек в конверте (0 ... 65 000)
	unsigned int numberOfExperiments=0; // Число экспериментов (0 ... 65 000)
	unsigned short int numberOfEnvelopesYouNeedToBuy=0; // Количество конвертов, которые нужно купить для того, чтобы собрать полный комплект.
	unsigned short int numberOfLabelsInSet=0; // Количество наклеек в комплекте (0....65 000)


	//cout << "Введите число наклеек в конверте  (E): "; cin >> numberOfLabelsInEnvelope; cout << endl;
	//cout << "Введите число наклеек в комплекте (L): "; cin >> numberOfLabelsInSet;     cout << endl;

	//cout << "Введите число экспериментов (N): "; cin >> numberOfExperiments; cout << endl;
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
		    numberOfEnvelopesYouNeedToBuy = carryOutExperiment( MyColl, Envl);// Провести эксперимент
		    file << numberOfEnvelopesYouNeedToBuy << " "; // Занести результаты в файл
		    //cout<< endl <<"Надо купить " <<numberOfEnvelopesYouNeedToBuy <<" конвертов"<< " ";

		    // build histogramm here
		    myHist[numberOfEnvelopesYouNeedToBuy]++;

		    MyColl.clabel.clear();  // Отчистить коллекцию

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

