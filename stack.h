// Manatuica Maria 313CA

#ifndef __STACK__H
#define __STACK__H

 
template<typename T>
class Stack {
	public:
		Stack();
		~Stack();
		void push(T x);
		T pop();
		T peek();
		bool isEmpty();
 
	private:
		// Lista folosita pentru stocarea elementelor stivei
		LinkedList<T> stackList;
 
};

template<typename T>
Stack<T>::Stack(){
}
 
template<typename T>
Stack<T>::~Stack(){
}

template<typename T>
void Stack<T>::push(T x){
	stackList.addLast(x);
}

template<typename T>
T Stack<T>::pop(){
	return stackList.removeLast();
}

template<typename T>
T Stack<T>::peek(){
	T x= stackList.removeLast();
	stackList.addLast(x);
	return x;
}

template<typename T>
bool Stack<T>::isEmpty(){

	return stackList.isEmpty();
 
}
#endif 
