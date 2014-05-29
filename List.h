// Manatuica Maria 313CA

#ifndef LIST_H
#define LIST_H

template <typename T> struct Node {
	T value;
	Node <T> *next;
	Node <T> *prev;
};


template <typename T> class LinkedList {
	private:
		Node <T> *head,*tail;
	public:
		// Constructor si destructor
		LinkedList();
		~LinkedList();
		
		// Functiile specifice unei liste
		void addFirst( T value);
		void addLast( T value);
		T removeFirst();
		T removeLast();
		bool isEmpty();
		
		// Intoarce valoarea nodului aflat pe pozitia poz fata de head
		T get(int poz);
		
		// Adauga nodul cu valoarea value pe pozitia poz fata de head
		void insert(int poz, T value);
		
		// Elimina nodul de pe pozitia poz fata de head
		T remove( int poz);
		
		// Intoarce un pointer la nodul head (de unde se poate parcurga intreaga lista)
		Node<T>* iterator();
		
};

template <typename T>
LinkedList<T>::LinkedList(){
	head = tail = NULL;
}

template <typename T>
LinkedList<T>::~LinkedList(){
	if (! isEmpty()){
		Node<T> * it = head;
    	Node<T> *temp;
    	while(it !=NULL){
    		temp = it;
    		it = it->next;
    		delete temp;
   		}
    }
}


template <typename T>
void LinkedList<T>::addFirst(T value){
	// Daca lista este goala head si tail vor fi egale, si vor avea valoarea value
	if(isEmpty()){	
		head = new Node<T>;		
		head->value = value;	
		head->next = NULL;
		head->prev = NULL;
		tail = head;	
	} 
	// Altfel noul nod se insereaza pe prima pozitie, devenind noul head
	else {
		Node<T> *nod = new Node<T>;
		nod->value = value;
		nod->prev = NULL;
		nod->next = head;
		head->prev = nod;
		head = nod;
	}
}


template <typename T>
void LinkedList<T>::addLast(T value){
	// Daca lista este goala head si tail vor fi egale, si vor avea valoarea value
	if (isEmpty() ){
		head = new Node<T>;
		head->value = value;
		head->next = NULL;
		head->prev = NULL;
		tail = head;
	}
	// Altfel noul nod se insereaza pe ultima pozitie, devenind noul tail
	else{
		Node<T> *nod = new Node<T>;
		nod->value = value;
		nod->next = NULL;
		nod->prev = tail;
		tail->next = nod;
		tail = nod;
	
	}
}


template <typename T>
T LinkedList<T>::removeFirst(){
	// Daca lista are un singur nod, head si tail devin din nou NULL
	if (head == tail){
		T value= head->value;
		delete head;
		head= tail = NULL;
		return value;
	}
	
	Node <T> *temp = head;
	T value = head->value;
	head->next->prev = NULL;
	head = head->next;
	delete temp;
	return value;
}


template <typename T>
T LinkedList<T>::removeLast(){
	// Daca lista are un singur nod, head si tail devin din nou NULL
	if (head == tail){
		T value= head->value;
		delete head;
		head= tail = NULL;
		return value;
	}
	
	Node <T> *temp = tail;
	T value = tail->value;
	tail->prev->next = NULL;
	tail = tail->prev;
	delete temp;
	return value;
	
}

template <typename T>
bool LinkedList<T>::isEmpty(){
	return head==NULL;
}



template <typename T>
void LinkedList<T> :: insert(int poz, T value){
	// Daca pozitia este 0 insert este echivalent cu addFirst
	if (poz == 0) { 
		addFirst(value);
		return;
	}
	
	// Altfel parcurgem lista pana cand gasim elementul de pe pozitia poz
	// sau pana cand ajungem la capatul acesteia
	int i = 0;
	Node<T> *it = head;
	while (i != poz && it!=NULL){
		it = it->next;
		i++;
	}
	
	// Daca am ajuns la capatul listei rezulta ca insert este echivalent cu addLast
	if (it == NULL){
		addLast(value);
		return;
	}
	
	// Altfel adaugam elementul intre elementele de pozitia poz si poz-1 
	Node<T> * nod = new Node<T>;
	nod->value = value;
	nod->prev = it->prev;
	nod->next = it;
	it->prev->next = nod;
	it->prev = nod;
}

template <typename T>
T LinkedList<T> :: remove(int poz){ 
	// Daca poz == 0 remove este echivalent cu removeFirst 
	if (poz == 0){
		return removeFirst();
	}
	// Altfel cautam in lista elementul de pe pozitia poz
	Node<T> *it = head->next;
	int i = 1;
	while( i != poz){
		it = it->next;
		i++;
	}
	// Daca elementul de pe poz este tail remove este echivalent cu removeLast
	if(it == tail){
		return removeLast();
	}
	// Altfel stergem elementul modificand si elementele vecine
	T value = it->value;
	it->prev->next= it->next;
	it->next->prev = it->prev;
	delete it;
	return value;
}

template <typename T>
Node<T>* LinkedList<T>::iterator(){
	return head;
}

template <typename T>
T LinkedList<T>::get(int poz){
	// Intoarce valoarea de la pozitia poz fara sa o modifice
	if(poz==0){
		return head->value;
	}
	Node<T>* it = head->next;
	int i=1;
	while(i!=poz){
		it = it->next;
		i++;
	}
	return it->value;
}

#endif
