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
		{
			cout<<"The line you entered exceeds the existing number of lines..."<<endl;
		}
		else if (ind == 0)
		{
			cout<<"There's no line 0, did you mean 1 (cough...Google suggestions...cough)"<<endl;
		}
		else if (numOfLines >= ind )
		{
			node *temp = head;
			int goToLine = 1;
			while(goToLine < ind)
			{
				temp = temp->next;
				goToLine++;
			} cout<<temp->data;
        }
}



void addToHead(string dataGiven){		//this function will add to Head
		if (head == NULL)					//no node, empty linked list
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;
		}
		else 								//one or more than one node
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			temp->next = head;
			head = temp;
			numOfLines++;
		}
		undoCmd adddedToHead;
		adddedToHead.lineNumber = 1;
		adddedToHead.commandNumber = 1;
		undoStack.push(adddedToHead);
	}

	void whateverAddToTail(string dataGiven){		//an extra function used to add to tail, had to implement to make Undo function work, ignore this one please
		if (head == NULL)					//no node, empty linked list
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;
		}
		else 								//one or more than one node
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
			numOfLines++;
		}
	}

	void whateverDeleteTail(){						//an extra function used to delete from tail, had to implement to make Undo function work,ignore this one please
		node *temp = head;
		if (head == NULL)
		{
			cout<<"Nothing to be deleted."<<endl;
		}
		else if (head == tail)
		{
			temp = head;
			string backup = temp->data;
			delete(temp);
			head = NULL;
			tail = NULL;
			numOfLines--;
		}
		else
		{
			while (temp->next != NULL && temp->next->next != NULL)
			{
				temp = temp->next;
			}
			tail = temp;
			delete temp->next;
			temp->next = NULL;
			numOfLines--;
		}
	}

	void addToTail(string dataGiven){		//this function will add to Tail
		if (head == NULL)					//no node, empty linked list
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;
		}
		else 								//one or more than one node
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
			numOfLines++;
		}
		undoCmd addedToTail;
		addedToTail.lineNumber = 1;
		addedToTail.commandNumber = 8;
		undoStack.push(addedToTail);
	}

	void deleteHead(){						//function used to delete the very first element, and update the head
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
		undoStack.push(deletedHead);
	}

	void deleteTail(){						//function used to delete the very last element, and update the tail
		node *temp = head;
		if (head == NULL)
		{
			cout<<"Nothing to be deleted."<<endl;
		}
		else if (head == tail)
		{
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
			undoStack.push(deletedTail);
		}
		else
		{
			while (temp->next != NULL && temp->next->next != NULL)
			{
				temp = temp->next;
			}
			tail = temp;
			string backup = temp->next->data;
			delete temp->next;
			temp->next = NULL;
			numOfLines--;
			undoCmd deletedTail;
			deletedTail.text = backup;
			deletedTail.lineNumber = 1;
			deletedTail.commandNumber = 7;
			undoStack.push(deletedTail);
		}
	}

	void insertTextInBetween(string dataGiven, int ind){		//this function will insert text in the given line, and will push all the other lines
		if (ind == 0)
		{
			cout<<"There's no line 0, did you mean 1 (cough...Google suggestions...cough)"<<endl;
		}
		else if (ind == 1)
		{
			if (head == NULL)					//no node, empty linked list
			{
				node *temp;
				temp = new node;
				temp->data = dataGiven;
				temp->next = NULL;
				head = temp;
				tail = head;
				numOfLines++;
			}
			else 								//one or more than one node
			{
				node *temp;
				temp = new node;
				temp->data = dataGiven;
				temp->next = NULL;
				temp->next = head;
				head = temp;
				numOfLines++;
			}
			//May be unnecessary, dunno
			undoCmd insertedToHead;
			insertedToHead.lineNumber = 1;
			insertedToHead.commandNumber = 5;
			undoStack.push(insertedToHead);
			// addToHead(dataGiven);
			// numOfLines++;
		}
		else{
			node *prevNode = head;
			node *nextNode = head;
			node *temp = new node();
			temp->data = dataGiven;
			temp->next = NULL;
			int iterator = 2;
			while(iterator < ind)
			{
				prevNode = prevNode->next;
				nextNode = nextNode->next;
				iterator++;
			}
			nextNode = nextNode->next;
			prevNode->next = temp;
			temp->next = nextNode;
			numOfLines++;
			undoCmd insertedInBetween;
			insertedInBetween.lineNumber = ind;
			insertedInBetween.commandNumber = 6;
			undoStack.push(insertedInBetween);
		}
	}

	void replaceTextInLine(string dataGiven,int ind){		//this function will overwrite anything written in the given line
		undoCmd replacedLine;
		if (numOfLines < ind)
		{
			cout<<"The line you entered exceeds the existing number of lines..."<<endl;
		}
		else if (ind == 0)
		{
			cout<<"There's no line 0, did you mean 1 (cough...Google suggestions...cough)"<<endl;
		}
		else if (numOfLines >= ind )
		{
			node *temp = head;
			int goToLine = 1;
			while(goToLine < ind)
			{
				temp = temp->next;
				goToLine++;
			}
			string backup = temp->data;
			temp->data = dataGiven;		//change what is inside the node number that has been given as line parameter
			replacedLine.lineNumber = ind;
			replacedLine.text = backup;
			replacedLine.commandNumber = 4;
			undoStack.push(replacedLine);
		}
	}

	void deleteLine(int ind){							//this function should delete anything in the given line, also decreases the numOfLines
		if (head == NULL)
		{
			cout<<"There is no line to be deleted/removed."<<endl;
		}
		else if(head == tail){
			node *temp = head;
			delete(temp);
			head = NULL;
			tail = NULL;
			numOfLines--;
		}
		else if(ind == 0){
			cout<<"There's no line 0, did you mean 1 (cough...Google suggestions...cough)"<<endl;
		}
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
			undoStack.push(headRemoved);
		}
		else if(ind == numOfLines){
			node *temp = head;
			undoCmd deletedLine;
			deletedLine.commandNumber = 11;
			while (temp->next != NULL && temp->next->next != NULL)
			{
				temp = temp->next;
			}
			tail = temp;
			string backup = temp->next->data;
			delete temp->next;
			temp->next = NULL;
			numOfLines--;
			deletedLine.text = backup;
			deletedLine.lineNumber = ind;
			undoStack.push(deletedLine);

		}
		else if (ind > numOfLines)
		{
			cout<<"Entered line is larger than existing lines..."<<endl;
		}
		else if (ind < numOfLines)
		{
			undoCmd deletedLine;
			deletedLine.commandNumber = 10;
			node *prevNode = head;
			node *nextNode = head;
			node *temp = head;
			int iterator = 2;
			while(iterator < ind)
			{
				prevNode = prevNode->next;
				nextNode = nextNode->next;
				iterator++;
			}
			nextNode = nextNode->next;
			temp = nextNode;
			nextNode = nextNode->next;
			prevNode->next = nextNode;
			string backup = temp->data;
			delete(temp);
			numOfLines--;
			deletedLine.text = backup;
			deletedLine.lineNumber = ind;
			undoStack.push(deletedLine);
		}
	}

	void insertFurtherAway(string dataGiven, int ind){		//will print /n lines if given line is larger than numOfLines
		undoCmd insertedFurtherAway;
		insertedFurtherAway.lineNumber = 0;
		insertedFurtherAway.commandNumber = 9;
		if (head == NULL)
		{
			while(numOfLines < ind-1)
			{
				whateverAddToTail("\n");
				insertedFurtherAway.lineNumber++;
			}
			// insertedFurtherAway.lineNumber++;
			whateverAddToTail(dataGiven);
		}
		else{
			while(numOfLines < ind-1)
			{
				whateverAddToTail("\n");
				insertedFurtherAway.lineNumber++;
			}
			whateverAddToTail(dataGiven);
		}
		undoStack.push(insertedFurtherAway);
	}
    void undo(){						//function used to undo the last action taken
		undoCmd temp = undoStack.top();
		if (temp.commandNumber == 1)
		{
			cout<<"Added To head, removing from head..."<<endl;
			deleteHead();
			undoStack.pop();
		}
		else if (temp.commandNumber == 3)
		{
			cout<<"Deleted head, replacing head..."<<endl;;
			addToHead(temp.text);
			undoStack.pop();
		}
		else if (temp.commandNumber == 4)
		{
			cout<<"Replaced line, replacing again..."<<endl;
			replaceTextInLine(temp.text,temp.lineNumber);
			undoStack.pop();
		}
		else if (temp.commandNumber == 5)
		{
			cout<<"Inserted to Head, removing from head..."<<endl;
			deleteHead();
			undoStack.pop();
		}
		else if (temp.commandNumber == 6)
		{
			cout<<"Inserted in between, removing that line..."<<endl;
			deleteLine(temp.lineNumber);
			undoStack.pop();
		}
		else if (temp.commandNumber == 7)
		{
			cout<<"Deleted Tail, inserting again..."<<endl;
			addToTail(temp.text);
			undoStack.pop();
		}
		else if (temp.commandNumber == 8)
		{
			cout<<"Added to tail, removing from tail..."<<endl;
			deleteTail();
			undoStack.pop();
		}
		else if (temp.commandNumber == 9)
		{
			int whatever = temp.lineNumber;
			while(whatever >= 0){
				whateverDeleteTail();
				whatever--;
			}
			undoStack.pop();
		}
		else if (temp.commandNumber == 10)
		{
			cout<<"Line deleted, inserting again..."<<endl;
			insertTextInBetween(temp.text, temp.lineNumber);
			undoStack.pop();
		}
		else if (temp.commandNumber == 11)
		{
			cout<<"Last line deleted, inserting again..."<<endl;
			addToTail(temp.text);
			undoStack.pop();
		}
		else if (temp.commandNumber == 12)
		{
			cout<<"First line deleted, inserting again..."<<endl;
			addToHead(temp.text);
			undoStack.pop();
		}
	}

	void printall(){						//function used to print the whole linked list
		node *temp = head;
		int linePrinted = 1;
		int pagePrinted = 2;
		int choice;
		if (head == NULL)
		{
			cout<<"no elements here, yay!"<<endl;
		}
		else{
			while(temp!=NULL)
			{
				if (linePrinted == 1)
				{
					cout<<"-------------------Page "<<"1"<<"-------------------\n";
				}
				else if ((linePrinted-1) % 10 == 0)
				{
					cout<<"-------------------Page "<<pagePrinted<<"-------------------\n";
					pagePrinted++;

				}
				cout<<linePrinted<<") "<<temp->data<<endl;
				temp = temp->next;
				linePrinted++;
			}
		}
	}
int main(){      
    cout<<"\t\t\tTEXT EDITOR USING ROPE ";
	int i, tmp; char c[100];
    		string dataGiven;
    int ind ,choice,choice1;
    do{
        cout<<"\n\t\t\t\tMENU";
        cout<<"\n\t\t\t1. FIND STRING BY INDEX  \n\t\t\t2. FIND AND REPLACE \n\t\t\t3. DELETE \n\t\t\t4. PRINT \n\nEnter your choice: ";
        cin>>choice;
        switch( choice ){
        case 1:
     
		
				cout<<"Enter line you want the text to be placed into : ";
				cin >> ind;
				cout<<"Enter text : ";
				cin>>dataGiven;
				dataGiven+="\n";
				if (ind == 1)
				{
					addToHead(dataGiven);
				}
				else if (ind > numOfLines)
				{
					insertFurtherAway(dataGiven,ind);
				}
				else if (ind < numOfLines)
				{
					insertTextInBetween(dataGiven,ind);
				}
				else if (ind == numOfLines)
				{
					int selection;
					cout<<"Enter 1 to replace the last line, enter 2 to insert a new line";
					cin>>selection;
					if (selection == 1)
					{
						replaceTextInLine(dataGiven,ind);
					}
					else if (selection == 2)
					{
						addToTail(dataGiven);
					}
				}
                    break;

        case 2:
                   
				cout<<"Enter the line you want to delete : ";
				cin>>ind;
				deleteLine(ind);
                    break;

        case 3:
				cout<<"Enter line you want to change the content of : ";
				cin>>ind;
				if (ind > numOfLines)
				{
					cout<<"The line you entered exceeds the existing number of lines..."<<endl;
				}
				else{
					cout<<"Enter the new text : ";
					cin>>dataGiven;
					dataGiven+="\n";
					replaceTextInLine(dataGiven, ind);}

        case 4:
                cin>>ind;
                get_line(ind);
           break;
        case 5:    
                   if (undoStack.empty())
				{
					cout<<"No command."<<endl;
			
				}
				else{
					//cout<<"under construction..."<<endl;
					undo();
				
				}
                break;

        default:
                    cout<<"\nINVALID OPTION";}
                    printall();
        cout<<"\n \n 1 - CONTINUE \n 0 - EXIT";
        cin>>choice1;
    }while( choice1 );
return 0;}