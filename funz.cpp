//Michele Frattini S4878744

#include "funz.h"



void ordina( vector<tree>& a, tree* e ){

	tree tmp = *e;
	for(int i=0;i<a.size();i++){
		if(a.at(i).frequenza<tmp.frequenza){
			a.insert(a.begin()+i,tmp);
			return;
        	}
	}

	a.push_back(tmp);

}


tree* codhuffman( vector<tree> a ) {

	tree* node;

	if(a.size()<=0)
		return nullptr;

	if(a.size()==1)
		node=&a[0];

	while(a.size()>1){

		tree* tmp = new tree();

		tree* tmps = new tree();	//sinistra
       		*tmps = a.at(a.size()-1);
		tmp->figlsin= tmps;
		a.pop_back();

		tree* tmpd = new tree();	//destra
		*tmpd = a.at(a.size()-1);
		tmp->figldes= tmpd;
		a.pop_back();

		tmp->frequenza=tmp->figlsin->frequenza + tmp->figldes->frequenza;

		ordina(a,tmp);

		node = tmp;

	}

	return node;

}


void sortfreq( vector<tree>& a ) {

	int n=a.size();	//Variabile d'appoggio
	int x,y;	// "	  i	"   

	do{
		x=0;
		for(int i=0;i<n-1;i++)
			if(a.at(i).frequenza<a.at(i+1).frequenza){
				tree temp=a.at(i);
				a.at(i)=a.at(i+1);
				a.at(i+1)=temp;
				x=1;
				y=i+1;
			}
		n=y;
	}while(x==1);

}


void printBT( const string& prefix, const tree* node, bool isLeft ) {

    if( node != nullptr || node != NULL){
        cout << prefix;

        cout << (isLeft ? "├──" : "└──" );

        cout <<"'"<<node->simbolo <<"'"<< endl;

        printBT( prefix + (isLeft ? "│   " : "    "), node->figlsin, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->figldes, false);

    }

}


void printBTaux( const tree* node) {

    printBT("", node, false); 
   
}


void probab( double* tutsimb ) {

	cout<<"Vuoi vedere le probabilità qui sotto di ogni simbolo del file 'text.txt' ?\n";
	string Yes;
	cin>>Yes;
	if (Yes == "si" || Yes == "Si" || Yes == "s" || Yes == "S" || Yes == "Yes" || Yes == "yes" || Yes == "y"){	
		for(int i=0;i<256;i++){
			tutsimb[i]/=c;
			cout<<" "<< (char) i <<" = "<<tutsimb[i]<<"\n";
		}
	}

}


bool cercapath( tree* r, vector<int>& ar, char x, string i ){
    
	if (!r)
		return false;


	if(i=="DX")		//destra codifica -> 1
		ar.push_back(1);
	else if(i=="SN")	//sinistra codifica -> 0
			ar.push_back(0);


	if (r->simbolo == x)    
		return true;

	if (cercapath(r->figlsin, ar, x,"SN") || cercapath(r->figldes, ar, x,"DX"))
		return true;
		
	ar.pop_back();

	return false;   
         
}


void comprex( vector<codifica>& codice ){

	string linea;		// Preparazione apertura/creazione dei due file
	ofstream zip ("comprex.txt");
	if(zip.is_open()){
		ifstream myfile ("text.txt");
		if(myfile.is_open()){
			while(getline(myfile,linea)){
				char lineax[linea.size()+1];
				strcpy(reinterpret_cast<char*>(lineax), linea.c_str());

				for(int i=0; i < linea.length(); i++){			// Codifica vera e propria
					for(int j=0;j<codice.size();j++)
						if(codice[j].simbolo == lineax[i])
							zip << codice[j].bit;
                    		}
              		}
            	}else cout <<"Impossibile aprire il file 'text.txt' :(\n";
        }else cout <<"Impossibile aprire il file 'comprex.txt' :(\n";

	if(zip.is_open())
        	zip.close();

}


void creacod( vector<tree> alfab, tree* alb, vector<codifica>& codice ){

	for(int i=0;i<alfab.size();i++){
		vector<int> path;

		cercapath(alb,path,alfab.at(i).simbolo,"0");

		codifica tmp;
		tmp.simbolo = alfab.at(i).simbolo;
		for(int j=0;j<path.size();j++)
			tmp.bit += (path.at(j) +'0');
		codice.push_back(tmp);
		cout << alfab.at(i).simbolo <<" : ";
		for(int j=0;j<path.size();j++)
		        cout<<path.at(j);
	
 		cout<<endl;
	}

	comprex(codice);

}


int cerca( char a, vector<codifica> b ){

	for(int i=0;i<b.size();i++){
		if(b.at(i).simbolo==a)
			return b.at(i).bit.size();
	}
	return -1;

}


void huff() {
	
   	double tuttisimboli[256];	//Lista tutti i simboli possibili
	string linea;

	for(int i=0;i<256;i++)		//Inizializziamo l'array
        tuttisimboli[i]=0;

	//apertura del file

	cout<<"Il testo che si vuole comprimere deve essere dentro il file 'text.txt' che a sua volta deve essere all'interno della cartella di lavoro."<<endl;
	ifstream myfile ("text.txt");


	string Yes;	
	cout<<"Vuoi vedere il contenuto del file 'text.txt'?\n";
	bool Check=false;
	cin>>Yes;
	if (Yes == "si" || Yes == "Si" || Yes == "s" || Yes == "S" || Yes == "Yes" || Yes == "yes" || Yes == "y"){
		Check=true;
		cout<<"Apertura del file 'text.txt' in corso ...\nTesto da comprimere: \n";
	}


	if(myfile.is_open()){

		while(getline(myfile,linea)){
			if(Check){
				cout<<linea<<endl;
			}
			char lineax[linea.size()+1];		//Estrapola le linee che ci sono nel file
			strcpy(reinterpret_cast<char*>(lineax), linea.c_str());	 
			for(int i=0; i< linea.length(); i++){
				int l=(int)lineax[i];			
				tuttisimboli[l]++;	//per poi aumentare di + 1 i simboli che compaiono nella lista di tutti i possibili simboli
				c++;
			}

		}

        myfile.close();

	vector<tree> albero;
		for(int i=0;i<256;i++){
		    if(tuttisimboli[i]!=0){
		        tree aux;
		        aux.simbolo = (char) i;
		        aux.frequenza = tuttisimboli[i];
		        aux.figldes = nullptr;
			aux.figlsin = nullptr;
		        albero.push_back(aux);
		    }

		}
	

        cout<<"\nIl testo ha "<<c<<" simboli."<<endl;

        probab(tuttisimboli);
	
	sortfreq(albero);


	cout<<"\nQueste sone la frequenze dei caratteri nel file :\n"<<endl;
	for(int i=0;i<albero.size();i++)
		cout<<" '"<<albero.at(i).simbolo<<"' : "<< albero.at(i).frequenza <<"\n";
	

        tree* arbol = codhuffman(albero);
	cout<<"\nL'albero della codifica di Huffman :\n\n";
        printBTaux(arbol);
        cout<<"\n";
	

	vector<codifica> listacodifica;	// Lista codifica delle lettere + propria rappresentazione in bit
	cout<<"Questa è la lista della codifica di ogni carattere in bit : \n\n";
	creacod(albero,arbol,listacodifica);

        cout<<"\nE'stato correttamente creato il file 'comprex.txt', ovvero il file compresso del file 'text.txt'.\n\n";

	double LungAtt=0.0;		//Lunghezza Attesa
        for(int i=0;i<albero.size();i++){
            LungAtt+= ((double)albero.at(i).frequenza/(double)c)*(double)cerca(albero.at(i).simbolo,listacodifica);	//Formula calcolo lunghezza attesa
        }
        cout<<"Lunghezza attesa L(C,X) della codifica : "<<LungAtt<<"\n\n";


        double EntrSh=0;
        for(int i=0;i<albero.size();i++){
            EntrSh+= ((double)albero.at(i).frequenza/(double)c)*log2(1/((double)albero.at(i).frequenza/(double)c));	//Formula calcolo entropia di sharron
        }

        cout<<"L’entropia di Shannon H(X) associata con X = {x1,...,xm} è : "<<EntrSh<<"\n\n";


	}else cout<<"Impossibile aprire il file 'text.txt' :(\n";

}




