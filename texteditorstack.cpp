#include<bits/stdc++.h>
using namespace std;

struct undoCmd{
	int lineNumber;
	string text;
	int commandNumber;
	int mLine;
	int nLine;
};

struct node{
	string data;
	struct node *next;
};
	node *head;
	node *tail;
	int numOfLines = 0;
	int next = 1;
	stack<undoCmd> undoStack;

void get_line(int ind){
    	undoCmd replacedLine;
		if (numOfLines < ind)
			cout<<"The line you entered exceeds the existing number of lines"<<endl;
		else if (ind == 0)

			cout<<"There's no line 0, did you mean 1 (coughGoogle suggestionscough)"<<endl;
		else if (numOfLines >= ind ){
			node *temp = head;
			int goToLine = 1;
			while(goToLine < ind){
				temp = temp->next;
				goToLine++;
			} cout<<temp->data;}}

void addToHead(string c){		
		if (head == NULL){
			node *temp;
			temp = new node;
			temp->data = c;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;}
		else{
			node *temp;
			temp = new node;
			temp->data = c;
			temp->next = NULL;
			temp->next = head;
			head = temp;
			numOfLines++;}
		undoCmd adddedToHead;
		adddedToHead.lineNumber = 1;
		adddedToHead.commandNumber = 1;
		undoStack.push(adddedToHead);}

	void whateverAddToTail(string c){
		if (head == NULL)					{
			node *temp;
			temp = new node;
			temp->data = c;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;}
		else{
			node *temp;
			temp = new node;
			temp->data = c;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
			numOfLines++;}}

	void whateverDeleteTail(){						
		node *temp = head;
		if (head == NULL){
			cout<<"Nothing to be deleted."<<endl;}
		else if (head == tail){
			temp = head;
			string backup = temp->data;
			delete(temp);
			head = NULL;
			tail = NULL;
			numOfLines--;}
		else{
			while (temp->next != NULL && temp->next->next != NULL){
				temp = temp->next;}
			tail = temp;
			delete temp->next;
			temp->next = NULL;
			numOfLines--;}}

	void addToTail(string c){
		if (head == NULL){
			node *temp;
			temp = new node;
			temp->data = c;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;}
		else{
			node *temp;
			temp = new node;
			temp->data = c;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
			numOfLines++;}
		undoCmd addedToTail;
		addedToTail.lineNumber = 1;
		addedToTail.commandNumber = 8;
		undoStack.push(addedToTail);}

	void deleteHead(){
		string backup = head->data;
		node *temp = head;
		node *nextNode = head->next;
		head = nextNode;
		delete(temp);
		numOfLines--;
		undoCmd deletedHead;
		deletedHead.text = backup;
		deletedHead.lineNumber = 1;
		deletedHead.commandNumber = 3;
		undoStack.push(deletedHead);}

	void deleteTail(){
		node *temp = head;
		if (head == NULL){
			cout<<"Nothing to be deleted."<<endl;}
		else if (head == tail){
			temp = head;
			string backup = temp->data;
			delete(temp);
			head = NULL;
			tail = NULL;
			numOfLines--;
			undoCmd deletedTail;
			deletedTail.text = backup;
			deletedTail.lineNumber = 1;
			deletedTail.commandNumber = 7;
			undoStack.push(deletedTail);}
		else{
			while (temp->next != NULL && temp->next->next != NULL){
				temp = temp->next;}
			tail = temp;
			string backup = temp->next->data;
			delete temp->next;
			temp->next = NULL;
			numOfLines--;
			undoCmd deletedTail;
			deletedTail.text = backup;
			deletedTail.lineNumber = 1;
			deletedTail.commandNumber = 7;
			undoStack.push(deletedTail);}}

	void insertTextInBetween(string c, int ind){
		if (ind == 0){
			cout<<"INCORRECT INDEX"<<endl;}
		else if (ind == 1){
			if (head == NULL){
				node *temp;
				temp = new node;
				temp->data = c;
				temp->next = NULL;
				head = temp;
				tail = head;
				numOfLines++;}
			else{
				node *temp;
				temp = new node;
				temp->data = c;
				temp->next = NULL;
				temp->next = head;
				head = temp;
				numOfLines++;}
			undoCmd insertedToHead;
			insertedToHead.lineNumber = 1;
			insertedToHead.commandNumber = 5;
			undoStack.push(insertedToHead);}
		else{
			node *prevNode = head;
			node *nextNode = head;
			node *temp = new node();
			temp->data = c;
			temp->next = NULL;
			int iterator = 2;
			while(iterator < ind){
				prevNode = prevNode->next;
				nextNode = nextNode->next;
				iterator++;}
			nextNode = nextNode->next;
			prevNode->next = temp;
			temp->next = nextNode;
			numOfLines++;
			undoCmd insertedInBetween;
			insertedInBetween.lineNumber = ind;
			insertedInBetween.commandNumber = 6;
			undoStack.push(insertedInBetween);}}

	void set_line(string c,int ind){
		undoCmd replacedLine;
		if (numOfLines < ind){
			cout<<"INCOREECT INDEX"<<endl;}
		else if (ind == 0){
			cout<<"INCORRECT INDEX"<<endl;}
		else if (numOfLines >= ind ){
			node *temp = head;
			int goToLine = 1;
			while(goToLine < ind){
				temp = temp->next;
				goToLine++;}
			string backup = temp->data;
			temp->data = c;		
			replacedLine.lineNumber = ind;
			replacedLine.text = backup;
			replacedLine.commandNumber = 4;
			undoStack.push(replacedLine);}}

	void delete_line(int ind){
		if (head == NULL){
			cout<<"ALREADY EMPTY"<<endl;}
		else if(head == tail){
			node *temp = head;
			delete(temp);
			head = NULL;
			tail = NULL;
			numOfLines--;}
		else if(ind == 0){
			cout<<"INCORRECT INDEX"<<endl;}
		else if(ind == 1){
			string backup = head->data;
			node *temp = head;
			node *nextNode = head->next;
			head = nextNode;
			delete(temp);
			numOfLines--;
			undoCmd headRemoved;
			headRemoved.text = backup;
			headRemoved.lineNumber = 1;
			headRemoved.commandNumber = 12;
			undoStack.push(headRemoved);}
		else if(ind == numOfLines){
			node *temp = head;
			undoCmd deletedLine;
			deletedLine.commandNumber = 11;
			while (temp->next != NULL && temp->next->next != NULL){
				temp = temp->next;}
			tail = temp;
			string backup = temp->next->data;
			delete temp->next;
			temp->next = NULL;
			numOfLines--;
			deletedLine.text = backup;
			deletedLine.lineNumber = ind;
			undoStack.push(deletedLine);}
		else if (ind > numOfLines){
			cout<<"INCORRECT INDEX"<<endl;}
		else if (ind < numOfLines){
			undoCmd deletedLine;
			deletedLine.commandNumber = 10;
			node *prevNode = head;
			node *nextNode = head;
			node *temp = head;
			int iterator = 2;
			while(iterator < ind){
				prevNode = prevNode->next;
				nextNode = nextNode->next;
				iterator++;}
			nextNode = nextNode->next;
			temp = nextNode;
			nextNode = nextNode->next;
			prevNode->next = nextNode;
			string backup = temp->data;
			delete(temp);
			numOfLines--;
			deletedLine.text = backup;
			deletedLine.lineNumber = ind;
			undoStack.push(deletedLine);}}

	void insertFurtherAway(string c, int ind){
		undoCmd insertedFurtherAway;
		insertedFurtherAway.lineNumber = 0;
		insertedFurtherAway.commandNumber = 9;
		if (head == NULL){
			while(numOfLines < ind-1){
				whateverAddToTail("\n");
				insertedFurtherAway.lineNumber++;}
			whateverAddToTail(c);}
		else{
			while(numOfLines < ind-1){
				whateverAddToTail("\n");
				insertedFurtherAway.lineNumber++;}
			whateverAddToTail(c);}
		undoStack.push(insertedFurtherAway);}

    void undo(){					
		undoCmd temp = undoStack.top();
		if (temp.commandNumber == 1){
			cout<<"Added To head, removing from head"<<endl;
			deleteHead();
			undoStack.pop();}
		else if (temp.commandNumber == 3){
			cout<<"Deleted head, replacing head"<<endl;;
			addToHead(temp.text);
			undoStack.pop();}
		else if (temp.commandNumber == 4){
			cout<<"Replaced line, replacing again"<<endl;
			set_line(temp.text,temp.lineNumber);
			undoStack.pop();}
		else if (temp.commandNumber == 5){
			cout<<"Inserted to Head, removing from head"<<endl;
			deleteHead();
			undoStack.pop();}
		else if (temp.commandNumber == 6){
			cout<<"Inserted in between, removing that line"<<endl;
			delete_line(temp.lineNumber);
			undoStack.pop();}
		else if (temp.commandNumber == 7){
			cout<<"Deleted Tail, inserting again"<<endl;
			addToTail(temp.text);
			undoStack.pop();}
		else if (temp.commandNumber == 8){
			cout<<"Added to tail, removing from tail"<<endl;
			deleteTail();
			undoStack.pop();}
		else if (temp.commandNumber == 9){
			int whatever = temp.lineNumber;
			while(whatever >= 0){
				whateverDeleteTail();
				whatever--;}
			undoStack.pop();}
		else if (temp.commandNumber == 10){
			cout<<"Line deleted, inserting again"<<endl;
			insertTextInBetween(temp.text, temp.lineNumber);
			undoStack.pop();}
		else if (temp.commandNumber == 11){
			cout<<"Last line deleted, inserting again"<<endl;
			addToTail(temp.text);
			undoStack.pop();}
		else if (temp.commandNumber == 12){
			cout<<"First line deleted, inserting again"<<endl;
			addToHead(temp.text);
			undoStack.pop();}}

	void printall(){						
		node *temp = head;
		int linePrinted = 1;
		int choice;
		if (head == NULL)
		{cout<<"EMPTY"<<endl;}
		else{
			while(temp!=NULL){
				cout<<linePrinted<<"."<<temp->data<<endl;
				temp = temp->next;
				linePrinted++;}}}

int main(){      
    cout<<"\t\t\tTEXT EDITOR USING STACK\n";
	int i, tmp; 
    		string c;
    int ind ,choice,choice1;
	addToHead("ADVANCED DATA STRUCTURES");
	addToTail("PROJECT DEMO");
	addToTail("TEXT EDITOR");
	addToTail("USING STACK");
	printall();
    do{
        cout<<"\n\t\t\t\tMENU";
        cout<<"\n\t\t\t1.INSERT  \n\t\t\t2.DELETE \n\t\t\t3. FIND  \n\t\t\t4. UNDO \n\nEnter your choice: ";
        cin>>choice;
        switch( choice ){
        case 1:
				cout<<"ENTER THE INDEX : ";
				cin >> ind;
				cout<<"ENTER THE TEXT : ";
				cin>>c;
				c+="\n";
				if (ind == 1){
					addToHead(c);}
				else if (ind > numOfLines){
					insertFurtherAway(c,ind);}
				else if (ind < numOfLines){
					insertTextInBetween(c,ind);}
				else if (ind == numOfLines){
					int selection;
					cout<<"Enter 1 to, enter 2 to insert";
					cin>>selection;
					if (selection == 1){
						set_line(c,ind);}
					else if (selection == 2){
						addToTail(c);}}
                    break;

        case 2:
                   
				cout<<"ENTER THE INDEX : ";
				cin>>ind;
				delete_line(ind);
                    break;
        case 3:
		        cout<<"ENTER THE INDEX : ";
                cin>>ind;
                get_line(ind);cout<<endl;
           break;
        case 4:    
                   if (undoStack.empty()){
					cout<<"No command."<<endl;}
				else{
					undo();}
                break;

        default:
                    cout<<"\nINVALID OPTION";}
                    printall();
        cout<<"\n \n 1 - CONTINUE \n 0 - EXIT";
        cin>>choice1;
    }while( choice1 );
return 0;}