// Manatuica Maria 313CA

#ifndef BACKEND_H_
#define BACKEND_H_
#include "List.h"
#include <string>
#include "stack.h"

// operatie este tipul de inregistrare folosit pentru
// stivele de undo si redo
struct operatie{
	// String-ul in care voi retine cuvintele modificate
	std::string words;
	// Tipul operatiei
	int op;
	// Indexul(indexii) de unde a fost sters/adaugat textul
	int index[2];
	
	// Supraincarcarea operatorului de atribuire
	void operator=(operatie b){
		words=b.words;
		op = b.op;
		index[0]=b.index[0];
		index[1] = b.index[1];
	}
		
};

class Backend {
	// Variabila care va intoarce textul in functia GetText
	char* getText;
	// Numarul de cuvinte din text
	int size;
	// Textul retinut sub forma unei liste
	LinkedList<std::string> text;
	// Clipboardul editorului reprezentat prin lista
	LinkedList<std::string> clipboard;
	// Stiva operatiei de undo
	Stack<operatie> undo;
	// Stiva operatiei redo
	Stack<operatie> redo;

public:
	// Constructor
	Backend();
	// Destructor
	~Backend();
	
	// Operatiile suportate de biblioteca Backend
	void Cut(const int start, const int stop);
	void Copy(const int start, const int stop);
	void Paste(const int start);
	void Undo(void);
	void Redo(void);
	void Add(const int index, const char *word);
	const char *GetText(void);
	
};

#endif
