# include <iostream>
# include "maze.h"
#include "Position.h"
#include "solver.h"
#include "comparison.h"  
#include "analysis.h"     
using namespace std;

int main(){	
    int choice;
    int rows, cols;
    Maze* maze=NULL;
    do{
    	cout<<"\t MAZE SOLVER"<<endl;
        cout<<"1. Generate Maze"<<endl;
        cout<<"2. Display Maze"<<endl;
        cout<<"3. Check Valid Path"<<endl;
        cout<<"4. Solve using DFS"<<endl;
        cout<<"5. Solve using BFS"<<endl;
        cout<<"6. Compare DFS vs BFS"<<endl;
        cout<<"7. Exit"<<endl;

        cout<<"\nEnter your choice: ";
        cin>>choice;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            choice=0;
        }
        switch(choice){
        	case 1:
        		cout<<"Enter number of rows=>  ";
        		cin>>rows;
        		cout<<"Enter number of columns=>  ";
        		cin>>cols;
        		if(cin.fail()){
        			cin.clear();
        			cin.ignore(1000,'\n');
        			cout<<"Invalid input! Please enter numbers."<<endl;
        			break;
        		}
        		if(rows>100||cols>100){
        			cout<<"Maze dimensions must be smaller than 100."<<endl;
        			break;
        		}
        		if(rows<5||cols<5){
        		cout<<"Maze dimensions must be at least 5."<<endl;
                    break;
				}
				if(maze!=NULL){
					delete maze;
				}
				maze=new Maze(rows,cols);
				maze->generateMaze();
				int loops;   
				cout<<"Add extra routes (loops)? 1 = Yes, 0 = No: ";
				cin>>loops;
				if(cin.fail()){
					cin.clear();
					cin.ignore(1000,'\n');
					loops=0;
				}
				if(loops==1)
					maze->createLoops();
				cout<<"\nMaze generated successfully!"<<endl;
				maze->displayMaze();
				break;
				
			case 2:
				if(maze==NULL){
                    cout<<"Please generate a maze first."<<endl;
                }
                else{
                    maze->displayMaze();
                }
                break;
               
            case 3:
               if(maze==NULL){
                    cout<<"Please generate a maze first."<<endl;
                }
                else if(maze->hasValidPath()){
                    cout<<"Valid path exists!"<<endl;
                }
                else{
                    cout<<"No valid path found!"<<endl;
                }
              break;
              
            case 4:{
    			if (maze == NULL){
        			cout<< "Generate a maze first!"<<endl;
        			break;
    			}

    			SolveResult sol = Solver::dfs(*maze);

   				if (sol.found && sol.path != NULL){
        			cout<<"\nFound a path using DFS!"<<endl;

        		cout<<"Explored=\t "<<sol.exploredcells <<endl;

        		cout<< "Path length=\t "<< sol.pathlength<<endl;

        cout<<"Path verified=\t "<<(verifyPath(*maze,sol)?"Yes":"No")<<endl;   // NEW
        displaySolution(*maze,sol);   // NEW

        		for (int i = 0; i < sol.pathlength; i++){
            		cout<< "("<< sol.path[i].row<< "," << sol.path[i].col << ") ";
				}
    		}
    		else{
        		cout<<"DFS could not find a path!" <<endl;
    		}

    		delete[] sol.path;
    		delete[] sol.exploredList;   // NEW
    		break;
			}


			case 5:
				{
			    if (maze == NULL){
			        cout<< "Generate a maze first!" <<endl;
			        break;
			    }
			
			    SolveResult sol = Solver::bfs(*maze);
			
			    if (sol.found && sol.path != NULL){
			        cout<< "\nPath found using BFS!"<< endl;
			
			        cout<<"Explored=\t "<< sol.exploredcells<< endl;
			
			        cout<< "Path length=\t "<< sol.pathlength << endl;

			        cout<<"Path verified=\t "<<(verifyPath(*maze,sol)?"Yes":"No")<<endl;   
			        displaySolution(*maze,sol);   
			
			        for (int i=0; i< sol.pathlength; i++){
			            cout << "(" << sol.path[i].row<< "," << sol.path[i].col << ") ";
					 }
			    }
			    else{
			        cout<< "BFS could not find a path!"<< endl;
			    }
			
			    delete[] sol.path;
    		delete[] sol.exploredList;   
			    break;
			}
 		    case 6:   
                if(maze==NULL){
                    cout<<"Generate a maze first!"<<endl;
                }
                else{
                    Comparison::run(*maze);
                }
                break;

           case 7:  
                cout<<"Exiting. Thank you!"<<endl;
                break;

            default:
                cout<<"Invalid choice! Try again."<<endl;
    
			}
    }
    while(choice!=7);
   delete maze;

    return 0;
}

