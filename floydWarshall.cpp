#include <cstring>
#include <unistd.h>
#include <ios>
#include <stdio.h>
#include <fstream>
#include <string>
#include<stdio.h>
#include<cstdlib>
#include<vector>
#include<iostream>
#include <climits>
#include <exception>
#include <set>
#include <limits>
#include <ctime>
#include<random>
#include "sys/types.h"
#include "sys/sysinfo.h"
/* Define Infinite as a large enough value. This value will be used
  for vertices not connected to each other */
#define INF 9999
#define N 100
using namespace std;
/*
 * Graph is the graph representation in adjacency matrix
*/
//vector< vector<int> > Graph;
int inputSize = 0;
bool denseTrue;
float  rawSum = 0 ;
float rawSumOptimal = 0;
int minWeightVal = 0;
int maxWeightVal = 0;
long edgeCounter = 0 ; //When number is not infinity
//TAKE 0 OUT OF RANDOMNUMBER
int RandomNumberNegative(int Min, int Max);
void InputGraph(float min, float max);
void printGraph();





//////////////////////////////////////////////////////////////////////////////
//
// process_mem_usage(double &, double &) - takes two doubles by reference,
// attempts to read the system-dependent data for a process' virtual memory
// size and resident set size, and return the results in KB.
//
// On failure, returns 0.0, 0.0

void process_mem_usage(double& vm_usage, double& resident_set)
{
 using std::ios_base;
 using std::ifstream;
 using std::string;

 vm_usage     = 0.0;
 resident_set = 0.0;

   // 'file' stat seems to give the most reliable results
   //
 ifstream stat_stream("/proc/self/stat",ios_base::in);

   // dummy vars for leading entries in stat that we don't care about
   //
 string pid, comm, state, ppid, pgrp, session, tty_nr;
 string tpgid, flags, minflt, cminflt, majflt, cmajflt;
 string utime, stime, cutime, cstime, priority, nice;
 string O, itrealvalue, starttime;

   // the two fields we want
   //
 unsigned long vsize;
 long rss;

 stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
 >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
 >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

               stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   vm_usage     = vsize / 1024.0;
   resident_set = rss * page_size_kb;
 }



















 int RandomNumberNegative(int Min, int Max){
	int finalNum;
	do{
  		 finalNum = rand()%(maxWeightVal-minWeightVal+1)+minWeightVal; // Generate the number, assign to variable.
	}while(finalNum==0);
	//cout<<"finalNum IS "<<finalNum<<endl;
	return finalNum;
}

/*Use infinity 25% of the time so the graph is not a mess */
bool useInfinity(){
 /*For dense we use 25% chance to get an infinite value (more likely to produce edges)
   For sparse we use 75% chance to get an infinite value */
  bool retVal;
  int val = rand()%4+1; //value from 1-4 If 1 then use value inf (25%) of the time
  if(denseTrue){
    if(val==1){
      retVal = true;
    }else{
      retVal = false;
    }
  }else{
    if(val==1 || val==2 || val==3){
      retVal= true;
    }else{
      retVal = false;
    }
  }
  return retVal;
}


void InputGraph(float min, float max,vector<vector<int>> &Graph){
  for(int i = 0; i < Graph.size(); ++i){
   for(int j=0; j<Graph.size();j++){
     if(i==j){
      Graph[i][j]=0;
    }else{
      if(useInfinity()){
        Graph[i][j] =  INF;
      }else{
       Graph[i][j]= RandomNumberNegative(min, max);
     }
   }
 }
}
}

void PrintGraph(vector<vector<int>> &Graph ){
    // Print the current Graph
  printf("\n");
  printf("Graph:\n");
  for(int i = 0; i < Graph.size(); ++i){
    for(int j = 0; j < Graph.size(); ++j){
     if(Graph[i][j]==INF){
      printf("INF ");
    }else{
      printf("%d ", Graph[i][j]);
    }
  }
  printf("\n");
}
printf("\n");
}



void printSolution(int &Graph);
// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
bool containsNegativeCycle (vector<vector<int>> &Graph)
{
    /* dist[][] will be the output matrix that will finally have the shortest 
      distances between every pair of vertices */
  int dist[inputSize][inputSize], i, j, k;

    /* Initialize the solution matrix same as input graph matrix. Or 
       we can say the initial values of shortest distances are based
       on shortest paths considering no intermediate vertex. */
  for (i = 0; i < inputSize; i++)
    for (j = 0; j < inputSize; j++)
      dist[i][j] = Graph[i][j];

    /* Add all vertices one by one to the set of intermediate vertices.
      ---> Before start of a iteration, we have shortest distances between all
      pairs of vertices such that the shortest distances consider only the
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
      ----> After the end of a iteration, vertex no. k is added to the set of
      intermediate vertices and the set becomes {0, 1, 2, .. k} */
    for (k = 0; k < inputSize; k++)
    {
      for (int i=0; i<inputSize; i++){
        if (dist[i,i] < 0 ){
          //printf("NEGATIVE CYCLE DETECTED OMITTING FROM RESULTS");
          return true;
        }
      }


        // Pick all vertices as source one by one
      for (i = 0; i < inputSize; i++)
      {
            // Pick all vertices as destination for the
            // above picked source
        for (j = 0; j < inputSize; j++)
        {
              // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
          if (dist[i][k] + dist[k][j] < dist[i][j])
            dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }

    // No negative cycles
    return false;
  }



  void floydWarshallOptimized (vector<vector<int>> &Graph) {
    int dist[inputSize][inputSize], i, j, k;
    for (i = 0; i < inputSize; i++)
      for (j = 0; j < inputSize; j++)
        dist[i][j] = Graph[i][j];
      for ( k = 0; k < inputSize; k++){
        for ( i = 0; i < inputSize; i++ ) {
     	if( dist[i][k] != INF ){ //IGNORE
      for ( j =  0; j < inputSize; j++ ) {
        /*Diagnol will always be 0,0 */
        if ( dist[k][j] != INF ||j==i) { //IGNORE
          int temp = dist[i][k] + dist[k][j];     //SAVE RECALCULATION
          if (dist[i][j] == INF || temp < dist[i][j]) {
            dist[i][j] = temp;
          }
        }
      }
    }
  }
}
}












/*
void printSolution(int Graph[inputSize][inputSize])
{
  printf ("Following matrix shows the shortest distances"
    " between every pair of vertices \n");
  for (int i = 0; i < inputSize; i++)
  {
    for (int j = 0; j < inputSize; j++)
    {
      if (Graph[i][j] == INF)
        printf("%7s", "INF");
      else
        printf ("%7d", Graph[i][j]);
    }
    printf("\n");
  }
}
*/

void resetVector(vector<vector<int>> &Graph){
  for(int i = 0; i < Graph.size(); ++i){
   for(int j=0; j<Graph.size();j++){   
    Graph[i][j]=0;
  }
}
}


/***********************MAIN FW IMPLEMENTATION****************************************/
void floydWarshall (vector<vector<int>> &Graph)
{
  int dist[inputSize][inputSize];
  int  i, j, k;


  for (i = 0; i < inputSize; i++){
    for (j = 0; j < inputSize; j++){
      dist[i][j] = Graph[i][j];
	//cout<<"DIST VAL: "<<dist[i][j]<<endl;
      }
    }
	for ( k = 0; k < inputSize; k++) {
	for (i = 0; i < inputSize; i++) 
	{
		for (j =  0; j < inputSize; j++) 
		{
			if (dist[i][k] != INF && dist[k][j] != INF) 
			{
			   int temp = dist[i][k] + dist[k][j];     
		           if (dist[i][j] == INF || temp < dist[i][j]) 
			   {
				dist[i][j] = temp;
			   }
			}
		}
	}
}
 
	for(int i =0; i<inputSize ; i++){
		for(int j=0; j<inputSize ; j++){
			if(dist[i][j] == INF){
				cout<<"INF ";
			}else{
				cout<<dist[i][j]<<" ";
			}
		}
					cout<<endl;
	}
  }













// driver program to test above function
  int main(int argc, char const *argv[])
  {
     if ( argc != 3 ){ // argc should be 2 for correct execution
      cout<<"Usage: "<< argv[0]<<" <# OF VERTEXES> <true if Graphs are sparse, false if Graphs are dense>"<<endl;
      exit(0);
    }
    srand(time(NULL));
    inputSize = atoi(argv[1]);
    string temp = argv[2];
    if( temp.compare("true")==0){
      denseTrue = true;
    }else{
      denseTrue = false;
    }

  /*CHANGE HERE */
    int numIterations = 1;
     minWeightVal = -10;
     maxWeightVal = 50;
    //mt19937 rng(seed);
    //uniform_int_distribution<int> gen(minWeightVal, maxWeightVal); 
    cout<<"denseTrue Value is "<<denseTrue<<endl;
    vector<vector<int>> myGraph(inputSize, std::vector<int>(inputSize, 0));
  //  printf("Directed Weighted Graph:\n");
   printf("============================\n\n");
    int counter = 0 ;
    float average =0;
    float averageOptimal =0;

    do{
      InputGraph(minWeightVal,maxWeightVal,myGraph);
      counter++;
      if(containsNegativeCycle(myGraph)){
    //Retry the graph genator
        resetVector(myGraph);
        InputGraph(minWeightVal,maxWeightVal,myGraph);
      }else{
       PrintGraph(myGraph);
       clock_t begin = clock();
       floydWarshall(myGraph);
       clock_t end = clock();
       float elapsed_secs = float(end - begin) / CLOCKS_PER_SEC;
       //cout<<"ELSAPSED SECS: "<<elapsed_secs<<endl;
       rawSum +=elapsed_secs;


      /*floydWarshallOptimized */
//       PrintGraph(myGraph);
  //     clock_t begin2 = clock();
    //   floydWarshallOptimized(myGraph);
      // clock_t end2 = clock();
      // float elapsed_secs2 = float(end2 - begin2) / CLOCKS_PER_SEC;
       //cout<<"ELSAPSED SECS OPTIMIZED: "<<elapsed_secs2<<endl;
      // rawSumOptimal +=elapsed_secs2;
     }
   }while(counter < numIterations );

//   cout<<"RAW SUM: "<<rawSum<<endl;
  // cout<<"RAW SUM OPTIMAL: "<<rawSumOptimal<<endl;

//   double vm, rss;
//   process_mem_usage(vm, rss);
 //  cout << "VM: " << vm << "; RSS: " << rss << endl;
   average = (rawSum / numIterations);
   averageOptimal = (rawSumOptimal / numIterations);

   printf("Average Time elapsed [STANDARD] %.7f\n",average);
   printf("Average Time elapsed [OPTIMAL] %.7f\n",averageOptimal);
//	printSolution(myGraph);
   return 0;
 }































