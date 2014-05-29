Manatuica Maria 313CA

	Pentru realizarea functiilor bibliotecii de backend am folosit mai multe tipuri de date studiate pana in prezent: pentru retinerea textului din editor am folosit o lista dublu inlantuita cu elemente de tip string (string-ul din STL), pentru clipboard-ul editorului la fel, iar pentru operatiile de undo si redo am folosit doua stive implementate cu lista dublu inlantuita (pentru a nu fi nevoie de dimensiuni pentru stiva). 
	
	Functia GetText intoarce textul aflat in editor. Pentru a putea elibera memoria folosita pentru variabila in care se va incarca textul am folosit atributul getText, asigurandu-ma ca eliberez memoria folosita de acesta la final in destructorul clasei Backend. Detalii despre functia GetText se gasesc in fisierul backend.cpp.
	
	Functia Add adauga un element in memoria editorului la indexul primit ca parametru. Pentru a insera elementul pe un index valid, caut primul index la care se poate adauga un cuvant, mai mare sau egal decat cel primit, sau sfarsitul textului, in cazul in care indexul dat ca parametru este mai mare decat lungimea textului. Odata gasit aceasta pozitie inserez cuvantul cu ajutorul functiei insert a listei.
	
	Functia Copy copiaza in memoria clipboard-ului cuvintele aflate integral intre indicii start si stop primiti ca parametru. Pentru a determina cuvintele ce respecta aceasta conditie calculez pentru fiecare cuvant indicele de start si stop, iar apoi verific care dintre ele au indicele de start mai mare sau egal cu parametrul start si indexul de stop mai mic decat stop, si le copiez in clipboard, a carui memorie a fost stearsa la inceputul functiei.
	
	Functia Cut sterge cuvintele din text aflate integral intre start si stop si le adauga in clipboard. Functia functioneaza la fel ca si Copy, cu exceptia ca odata gasite cuvintele ce indeplinesc conditia, ele sunt sterse din text.
	
	Pentru operatiile de Cut si Copy aveam nevoie de numarul de cuvinte (size-ul textului), motiv pentru care am creat atributul size, pe care il modific de cate ori se adauga sau se sterge un element, si il initializez in constructor.
	
	Functia Paste insereaza textul retinut in clipboard incepand cu indexul start primit ca parametru. La fel ca la functia Add, caut primul index valid si incepand cu acel indice inserez cuvintele cu ajutorul functiei insert a listei.
	
	Pentru functiile Undo si Redo am creat structura operatie ce are ca si atribute un string in care se va retine stringul modificat intr-o operatie efectuata pe text, un intreg op ce determina tipul operatiei (0-pentru o operatie de Cut, 1-pentru Paste, 2-pentru Add), si un vector de 2 elemente intregi index, in care se gaseste indexul de start (pentru Paste,Add si Cut) si indexul de stop (doar Cut). In functie de tipul operatiei aplic modificarile aferente asupra textului. 
	
	In cadrul functiilor reversibile (Paste,Add,Cut) creez un obiect operatie pe care il initializez cu elementele aferente dupa care il bag in stiva de undo. Atunci cand se apeleaza functia de undo scot din stiva operatia, aplic modificarile asupra textului, dupa care bag operatia in stiva de redo.
	
	Mentionez ca lista dublu inlantuita implementata de mine lucreaza cu index pe element, astfel pentru fiecare functie determin pozitia cuvantului in text, pentru a putea apela functiile listei.
