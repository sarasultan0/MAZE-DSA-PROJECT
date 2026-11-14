
#include <iostream>
#include "Maze.h"

using namespace std;

int main()
{
    int choice;
    int rows,cols;
    Maze* maze=NULL;
    do{
    	 cout<<"\n===== MAZE SOLVER ====="<<endl;
        cout<<"1. Generate Maze"<<endl;
        cout<<"2. Display Maze"<<endl;
        cout<<"3. Check Valid Path"<<endl;
        cout<<"4. Exit"<<endl;

        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
        	case 1:
        		cout<<"Enter number of rows: ";
        		cin>>rows;
        		cout<<"Enter number of columns: ";
        		cin>>cols;
        		if(rows<5||cols<5)
        		{
        		cout<<"Maze dimensions must be at least 5."<<endl;
                    break;
				}
				if(maze!=NULL)
				{
					delete maze;
				}
				maze=new Maze(rows,cols);
				maze->generateMaze();
				cout<<"\nMaze generated successfully!"<<endl;
				maze->displayMaze();
				break;
			case 2:
				if(maze==NULL)
                {
                    cout<<"Please generate a maze first."<<endl;
                }
                else
                {
                    maze->displayMaze();
                }
                break;
            case 3:
               if(maze==NULL)
                {
                    cout<<"Please generate a maze first."<<endl;
                }
                else if(maze->hasValidPath())
                {
                    cout<<"Valid path exists!"<<endl;
                }
                else
                {
                    cout<<"No valid path found!"<<endl;
                }
              break;
            case 4:

                cout<<"Exiting Maze Solver..."<<endl;
                break;

            default:

                cout<<"Invalid choice! Try again."<<endl;
        }

    }
    while(choice!=4);
   delete maze;

    return 0;
}

