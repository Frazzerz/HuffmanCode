//Michele Frattini S4878744

#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <fstream>

using namespace std;

//////////////////////////////// S T R U C T /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct codifica {
  char simbolo;
  string bit;
};


struct tree {
  char simbolo;
  int frequenza;		//Quante volte c'è un carattere (numero totale carattere) per ogni carattere presente nel file
  tree* figldes = nullptr;
  tree* figlsin = nullptr;
};



extern int c;  //Numero totale simboli nel file


/////////////////////////////// F U N C T I O N ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ordina( vector<tree>& a, tree* e );	//Funzione ausiliaria di codhuffman

tree* codhuffman( vector<tree> a );		//Funzione che esegue effettivamente la codifica di huffman

void sortfreq( vector<tree>& a );		//Una funzione di sort (per mettere in ordine decrescente le frequenze , fondamentale successivamente per Huffman)

void printBT( const string& prefix, const tree* node, bool isLeft );			//Funzione per stampare l'albero a schermo

void printBTaux( const tree* node );							// "	ausiliaria	"		"
	
void probab( double* tutsimb );		//Funzione che stampa a schermo le probabilità di ogni simbolo 

bool cercapath( tree* r, vector<int>& ar, char x, string i );	//Funzione ricorsiva ausiliaria di creacod, crea lista codifica

void comprex( vector<codifica>& codice );				//Funzione comprimi

void creacod( vector<tree> alfab, tree* alb, vector<codifica>& codice );	//Funzione che prima chima funzione cercapath,
										//poi stampa a schermo lista codifica di ogni carattere in bit,
										//e infine chiama funzione comprex

int cerca( char a, vector<codifica> b );	//Funzione di ricerca di un elemente usata nella determinazione della lunghezza attesa	

void huff();	//Funzione princiapale che richimana tutte le altre funzioni precedenti






