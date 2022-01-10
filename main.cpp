#include <iostream>
#include <stack>

using namespace std;

class textEditor {

    public:
        stack<char> leftStack;
        stack<char> rightStack;

        void insertWord(char word[]);
        void insertCharacter(char character);
        bool deleteCharacter();
        bool backSpaceCharacter();
        void moveCursor(int position);
        void moveLeft(int position);
        void moveRight(int position);
        void findAndReplaceChar(char findWhat, char replaceWith);
        void examineTop();
};

void textEditor::examineTop(){
    if(leftStack.empty())
        cout << "leftStack: empty\t";
    else
        cout << "leftStack: " << leftStack.top() << "," << leftStack.size() << "\t\t";
    if(rightStack.empty())
        cout << "rightStack: empty\n";
    else
        cout << "rightStack: " << rightStack.top() << "," << rightStack.size() << endl;
}

void textEditor::insertCharacter(char character){
    
    leftStack.push(character);
}

void textEditor::insertWord(char word[]) {
    int i=0;

    while(word[i]!='\0') {
        insertCharacter(word[i]);
        i++;
    }
}

bool textEditor::deleteCharacter(){

    if (rightStack.empty())
        return false;
    else
        rightStack.pop();
    return true;
}

bool textEditor::backSpaceCharacter(){

    if (leftStack.empty())
        return false;
    else
        leftStack.pop();
    return true;
}

void textEditor::moveLeft(int position){
    int leftSize;
    leftSize = leftStack.size();
    while(position!=leftSize) {
        rightStack.push(leftStack.top());
        leftStack.pop();
        leftSize = leftStack.size();
    }
}

void textEditor::moveRight(int count){
    int rightSize, i=1;
    
    rightSize = rightStack.size();
    
    if (count > rightSize){
        cout << "Cannot move the cursor, right, to the specified position";
    }
    else {
        while(i<=count) {
            leftStack.push(rightStack.top());
            rightStack.pop();
            i++;
        }
    }
}

void textEditor::moveCursor(int position){

    int leftSize, rightSize, count;
    leftSize = leftStack.size();
    rightSize = rightStack.size();
    if (position < leftSize)
        moveLeft(position);
    else {
        count = position - leftSize;
        moveRight(count);
    }
}

void textEditor::findAndReplaceChar(char findWhat, char replaceWith){

    int count=1, originalCursorPoistion = leftStack.size();
    moveCursor(0);
    
    while(!rightStack.empty()) {
        if(rightStack.top()==findWhat) {
        deleteCharacter();
        insertCharacter(replaceWith);
        }
        else
            moveCursor(count);
            count++;
    }
    moveCursor(originalCursorPoistion);
}

int main() {
    int i=0; 
    char text[80],character;
    textEditor txt;
    char o,n;
    int post1,post2,post3,choice=1;
    
    cout << "Firstly enter text: \t";
    cin.getline(text,80);
    txt.insertWord(text);
    cout<<endl;
    cout << ".............Inserting the word.................";
    cout<<endl;
    txt.examineTop();
    
    while(choice != 0){
      cout<<endl<<"====TEXT EDITOR====\n"<<endl;
      cout<<"Select an Action.\n0 - To Exit \n1 - Insert word into Line."<<endl;
      cout<<"2 - Insert a character into Line\n3 - Backspace a Character\n4 - Delete a Character"<<endl;
      cout<<"5 - Move cursor to Left \n6 - Move cursor to Right\n7 - Move cursor at a specific position\n8 - Find a character and replace them all"<<endl;
      cout<<"Your Action :";
      cin>>choice;
      cout<<endl;
      if(choice==0){
          break;
      }
      else if (choice == 1)      
      {
        cout << "Enter the word to be inserted: ";
        // cin.getline(text,80);
        cin>>text;
        txt.insertWord(text);
        cout<<endl<<"Saving text....\n"<<endl;
        cout<<"..................Word added..............."<<endl;
        txt.examineTop();
      }
      else if (choice == 2)    
      {
        cout<<"Enter character: ";
        cin>>character;
        txt.insertCharacter(character);
        cout<<endl<<"Saving text....\n"<<endl;
        cout<<"..................Character added..............."<<endl;
        txt.examineTop();
      }
      else if (choice == 3)    
      {
        for(i=0;i<1;i++){
            if(txt.backSpaceCharacter()!=0){
                cout << "Delete characters using Backspace: "<<endl;
                txt.examineTop();
            }    
            else{
                cout << "Nothing to Backspace ";
            }
        }
        cout<<endl<<"Saving changes....\n"<<endl;
        cout<<"..................Char Backspaced..............."<<endl;
      }
      else if (choice == 4)
      {
        for(i=0;i<1;i++){
            if(txt.deleteCharacter()!=0){
                cout << "Delete characters using DEL: ";
                txt.examineTop();            
            }
            else{
                cout << "There is nothing to delete. Move your cursor accordingly to delete the character";
            }
        }
        cout<<endl<<"Saving changes....\n"<<endl;
        cout<<"..................Char Backspaced..............."<<endl;
      }
      else if (choice == 5)  
      {
        cout<<"Move cursor to left to by position: ";
        cin>>post1;
        cout<<endl;
        txt.moveLeft(post1);
        txt.examineTop();
        cout<<endl;
        cout<<"............Done..........."<<endl;
      }
      else if (choice == 6)    
      {
        cout<<"Move cursor to right to by postion: ";
        cin>>post2;
        cout<<endl;
        txt.moveRight(post2);
        txt.examineTop();
        cout<<endl;
        cout<<".............Done.........."<<endl;
      }
      else if (choice == 7)
      {
        cout<<"Enter specific position where cursor should be: ";
        cin>>post3;
        txt.moveCursor(post3);
        txt.examineTop();
        cout<<endl;
        cout<<"............Done..........."<<endl;
      }
      else if (choice == 8)
      {
        cout<<"Enter which character you wanted to replace from text: ";
        cin>>o;
        cout<<endl;
        cout<<"Enter new character:";
        cin>>n;
        cout<<endl;
        cout<<endl;
        txt.findAndReplaceChar(o,n);
        cout << "Replace occurrences of "<<o<<" with "<<n;
        cout<<endl;
        cout<<endl;
        txt.examineTop();
        cout<<".............Replaced Sucessfully................"<<endl;
        }
        else{
        cout<<"Please enter valid action"<<endl;
        }
    }
}