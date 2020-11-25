#include "p4.h"

int main(){

	PlayerClass::AbilityArray abil = {1, 2, 3, 0, 0, 2};
	int dice[] = {1, 2, 3};

	cout << "============Start============" << endl << endl;

	cout << "----------Troll----------" << endl << endl;

	Troll troll1("Sally");
	troll1.Write(cout);

	cout << endl;

	cout << "----------Ogre----------" << endl << endl;

	Ogre ogre1("Bill");
	ogre1.Write(cout);

	cout << "----------Human----------" << endl << endl;

	Human human1("Ben");
	human1.Write(cout);

	cout << "----------Elf----------" << endl << endl;

	Elf elf1("Jess");
	elf1.Write(cout);

	cout << "----------Orc----------" << endl << endl;

	Orc orc1("Sarah");
	orc1.Write(cout);


	return 0;
}
