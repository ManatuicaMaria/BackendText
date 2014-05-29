// Manatuica Maria 313CA

#include <iostream>
#include "backend.h"
#include <string>
#include <string.h>

Backend::Backend()
{
	// Initializarile necesare
	getText = NULL;		
	size = 0;
}

Backend::~Backend()
{
	// Eliberarea memoriei, daca nu a fost deja eliberata
	if (getText!= NULL){
		delete [] getText;
	}
}

void Backend::Cut(const int start, const int stop)
{
	// Sterg cuvintele din clipboard
	while(!clipboard.isEmpty()){
		clipboard.removeLast();
	}
	
	// Daca textul este gol ies din functie
	if (text.isEmpty()){
		return;
	}
	
	// Cu it voi itera prin lista de cuvinte a textului incepand cu primul nod
	Node <std::string>* it = text.iterator();
	
	// Pentru fiecare element determin pozitia de inceput si de sfarsit
	int indexstart[size];
	int indexstop[size];
	
	// Vectorul del va retine pozitiile cuvintelor ce vor fi sterse si adaugate in clipboard
	int del[size];
	int i,j;
	
	// Pentru primul cuvant indexul de start este 0
	indexstart[0] = 0;
	indexstop[0] = it->value.length();
	it = it->next;
	
	// Determin indecsii pentru celelalte elemente
	for(i=1;i<size;i++){
		indexstart[i] = indexstop[i-1]+1;
		indexstop[i] = indexstart[i]+it->value.length();
		it=it->next;
	}
	
	// j va reprezinta numarul elementelor selectate
	j =0;
	
	// Aflu ce elemente sunt cuprinse integral intre start si stop
	for(i=0;i<size;i++){
		if(indexstart[i]>=start && indexstop[i]<stop){
			del[j] = i;
			j++;
		}
	}
	
	// Cu ajutorul lui j le scot din text si le adaug in clipboard
	for(i=0;i<j;i++){
		clipboard.addLast(text.remove(del[0]));
		// Decrementez numarul de cuvinte 
		size--;
	}
	
	// Construiesc elementul de tip operatie cut, si il introduc in stiva
	operatie cut;
	cut.op=0;
	
	// Indecsii sunt indecsi de cuvinte, nu caractere
	cut.index[0]=del[0];
	cut.index[1] = del[j-1];
	undo.push(cut);
	
	// Am facut o modificare asupra textului, deci golesc stiva de redo
	while(!redo.isEmpty()){
		redo.pop();
	}
} 


void Backend::Copy(const int start, const int stop)
{
	// Sterg cuvintele din clipboard
	while(!clipboard.isEmpty()){
		clipboard.removeLast();
	}
	
	// Daca textul este gol ies din functie
	if (text.isEmpty()){
		return;
	}
	
	// Cu it voi itera prin text incepand cu primul cuvant
	Node<std::string>* it = text.iterator();
	
	// Am nevoie din nou de indecsii de start si stop ai cuvintelor
	int indexstart[size];
	int indexstop[size];
	int i;
	
	// Ii calculez
	indexstart[0] = 0;
	indexstop[0] = it->value.length();
	it = it->next;
	for(i=1;i<size;i++){
		indexstart[i]=indexstop[i-1]+1;
		indexstop[i] = indexstart[i] +it->value.length();
		it=it->next; 
	}
	
	// Apoi copiez in clipboard doar cuvintele care sunt cuprinse integral intre start si stop
	for(i=0;i<size;i++){
		if(indexstart[i]>=start && indexstop[i]<stop){
			clipboard.addLast(text.get(i));
		}
	}
	
	// Operatiile care nu afecteaza continutul textului nu sunt reversibile
}

void Backend::Paste(const int start)
{
	Node <std::string>* it=text.iterator();
	
	// Daca clipboard-ul este gol => nu exista elemente de adaugat => ies din functie
	if(clipboard.isEmpty()){
		return;
	}
	
	// nrcuv va reprezenta indexul in cadrul listei de cuvinte a primului el din clipboard
	// nrch (nr caractere) va retine indicele de start al introducerii textului
	int nrcuv=0, nrch=0;
	
	// Caut in text primul indice valid pentru indexul de start cerut, calculand nr de caractere al cuvintelor
	while((it !=NULL) && (nrch<start)){
		nrcuv++;
		nrch+=(it->value.length() + 1);
		it=it->next;
	}
	
	// Bag in stiva de undo operatia paste
	operatie paste;
	paste.op=1;
	paste.index[0]=nrcuv;
	undo.push(paste);
	it=clipboard.iterator();
	
	// Iterand prin clipboard introduc in text cuvintele din el
	while(it != NULL){
		text.insert(nrcuv,it->value);
		nrcuv++;
		it=it->next;
		size++;
	}
	
	// Am facut o modificare asupra textului, deci golesc stiva de redo
	while(!redo.isEmpty()){
		redo.pop();
	}
	
}

void Backend::Undo(void)
{
	int i;
	operatie old;
	Node<std::string>* it=clipboard.iterator();
	
	// Daca stiva de undo este goala ies din functie, altfel extrag ultima operatie efectuata
	if (!undo.isEmpty()){
		old = undo.pop();
	}else{
		return;
	}
	
	// In functie de operatie efectuez modificarile aferente
	switch (old.op){
		// 0-Cut
		case 0:
			// Reintroduc cuvintele extrase in text 
			for(i=old.index[0];i<=old.index[1];i++){
				text.insert(i,clipboard.get(i-old.index[0]));
				size++;
			}
			break;
		// 1-Paste
		case 1:
			// Sterg cuvintele adaugate prin comanda Paste
			while(it!=NULL){
				text.remove(old.index[0]);
				it=it->next;
				size--;
			}
			break;
		// 2-Add
		case 2:
			// Sterg cuvantul adaugat
			text.remove(old.index[0]);
			size--;
			break;
	}
	
	// Introduc in stiva de redo operatia 
	redo.push(old);

}

void Backend::Redo(void)
{
	int i;
	Node<std::string>* it;
	operatie old;
	
	// Daca stiva de redo este goala ies din functie
	if(redo.isEmpty()){
		return;
	}
	
	//  Extrag operatia ce trebuie refacuta
	old = redo.pop();
	
	// In functie de operatie efectuez modificarile aferente
	switch (old.op){
		// 0-Cut
		case 0:
			// Reextrag elementele adaugate prin undo
			for(i =old.index[0]; i<=old.index[1];i++){
				text.remove(old.index[0]);
				size--;
			}
			break;
		// 1-Paste
		case 1:
			it = clipboard.iterator();
			i=0;
			// Reintroduc elementele sterse prin undo
			while(it!=NULL){
				text.insert(old.index[0]+i,it->value);
				it=it->next;
				i++;
				size++;
			}
			break;
		// 2-Add
		case 2:
			// Reintroduc cuvantul sters prin undo
			text.insert(old.index[0],old.words);
			size++;
			break;
	}	
		
	
}

void Backend::Add(const int index, const char *word)
{
	std::string newWord (word);
	Node <std::string>* it=text.iterator();
	int start=0,poz=0;
	
	// Caut primul indice valid pentru indexul cerut prin calcularea nr de caractere al cuvintelor din text
	while(start<index && it!=NULL){
		start+=(it->value.length()+1);
		// poz va fi pozitia noului cuvant in cadrul listei
		poz++;
		it=it->next;
	}
	
	// Inserez cuvantul in text
	text.insert(poz,newWord);
	size++;
	
	// Introduc operatia add in stiva de undo
	operatie add;
	add.op = 2;
	add.words=newWord;
	add.index[0] = poz;
	undo.push(add);
	
	// Am facut o modificare asupra textului, deci golesc stiva de redo
	while(!redo.isEmpty()){
		redo.pop();
	}

}

const char *Backend::GetText(void)
{
	Node<std::string>* it = text.iterator();
	int n = 0;
	// Calculez nr de caractere din text si il retin in variabila n
	while (it != NULL){
		n+=(it->value.length()+1);
		it= it->next;
	}
	
	// Sterg textul retinut anterior
	if (getText!= NULL){
		delete [] getText;
	}
	
	// Aloc memoria necesara
	getText =new char[n+1];
	
	// Construiesc textul in variabila getText folosind functia memcpy
	it = text.iterator();
	n=0;
	while(it!=NULL){
		memcpy(&getText[n],it->value.c_str(),it->value.length());
		getText[n+it->value.length()] = ' ';
		n+=(it->value.length()+1);
		it=it->next;
	}
	getText[n]='\0';
	
	// Intorc variabila in care am copiat textul
	return getText;
}

