#include <stdio.h>
#include <assert.h>
#define INFINITY 9999
#define MAX 12
#define MAX_BALL 4

int dijkstra(int begin, int index, int* next_move, size_t size);
int checkpos(int position[], int* round_position, size_t size);
int check_finished(int check_array[]);
int array_to_zero(int* array, size_t size);

int main()
{
	int temp[MAX_BALL],next[MAX_BALL],i,k, check, round=0, pos_check =0, check1;

	int begin[MAX_BALL] = {1,2,3,4};
    /*
	printf("\nEnter the begin 1 position:");
	scanf("%d",&begin[0]);

	printf("\nEnter the begin 2 position:");
	scanf("%d",&begin[1]);

	printf("\nEnter the begin 3 position:");
	scanf("%d",&begin[2]);

	printf("\nEnter the begin 4 position:");
	scanf("%d",&begin[3]);
     */
	do
    {
        printf("-----------------------------------------This is round: %d----------------------------------------------\n", round);
	    check = check_finished(begin);
	    pos_check = checkpos(begin, temp, sizeof(temp) / sizeof(temp[0]));
        if(pos_check == 1) {
            for (i = 0; i < MAX_BALL; i++) {
                check1 = dijkstra(begin[i], i, next, sizeof(next) / sizeof(next[0]));
                if(check1 != 100)
                    begin[i] = check1;
            }
        }
        else if(pos_check== 0)
        {
            for (i = 0; i < MAX_BALL; i++) {
                //printf("temp[%d] is: %d\n", i, temp[i]);
                check1 = dijkstra(temp[i], i, next, sizeof(next) / sizeof(next[0]));
                if(check1 == 99)
                    begin[i] = check1;
            }
        }
        round++;
        array_to_zero(next, sizeof(next) / sizeof(next[0]));
    }while(check != 1);

	return 0;
}

int array_to_zero(int* array, size_t size)
{
    int i;
    assert(size >= 4);
    for(i=0;i<MAX_BALL;i++)
    {
        array[i] = 0;
    }

}

int check_finished(int check_array[])
{
    int checked=0,i;
    for(i=0;i<MAX_BALL; i++)
    {
        if(check_array[i] == 99)
            checked = 1;
        else
            return 0;
    }
    return checked;
}

int checkpos(int position[], int* round_position, size_t size)
{
    int i,k, temp, check=1;
    assert(size >= 4);
    for(i=0; i<MAX_BALL; i++)
    {
        temp = position[i];
        //printf("temp =%d\n",temp);
        for(k=0;k<MAX_BALL;k++)
        {
            if(temp==position[k] &&! k == i && temp != 99)
            {
                round_position[k] = position[k];
               // printf("temp is %d, position = %d, k = %d, i = %d\n", temp, position[k], k, i);
                check = 0;
            }
            else if(temp != position[k] &&! k == i && temp != 99)
                round_position[k] = 100;
        }
    }
    return check;
}

int dijkstra(int begin, int index, int* next_move, size_t size)
{
    assert(size >= 4);
    if(begin == 100)
        return 0;
    int G[MAX][MAX] =  { {0, 2, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0},
                        {2, 0, 2, 0, 0, 0, 0, 0, 1, 1, 0, 0},
                        {0, 2, 0, 2, 0, 0, 0, 0, 0, 3, 0, 0},
                        {0, 0, 2, 0, 2, 0, 0, 0, 0, 1, 1, 0},
                        {0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 3, 0},
                        {0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 1, 1},
                        {0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 3},
                        {2, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1},
                        {3, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                        {0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0}};

	int cost[MAX][MAX],distance[MAX],pred[MAX], end[MAX_BALL]={8,9,10,11},n = MAX;
	int visited[MAX],count,mindistance,nextnode,i,j,k, previous, begin_value, end_value, returnvalue;
    /*for(k=0;k<MAX_BALL;k++)
	{
	    end_value=end[k];
	    begin_value=begin[k];

    */
    end_value = end[index];
    begin_value = begin;
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];


	    //initialize pred[],distance[] and visited[]
	    for(i=0;i<n;i++)
	    {
		    distance[i]=cost[end_value][i];
		    pred[i]= end_value;
		    visited[i]=0;
	    }

	    distance[end_value]=0;
	    visited[end_value]=1;
	    count=1;

	    while(count<n-1)
	    {
		    mindistance=INFINITY;

		    //nextnode gives the node at minimum distance
	    	for(i=0;i<n;i++)
		    	if(distance[i]<mindistance&&!visited[i])
			    {
				    mindistance=distance[i];
				    nextnode=i;
			    }

			    //check if a better path exists through nextnode
			    visited[nextnode]=1;
			    for(i=0;i<n;i++)
				    if(!visited[i])
					    if(mindistance+cost[nextnode][i]<distance[i])
					    {
						    distance[i]=mindistance+cost[nextnode][i];
						    pred[i]=nextnode;
					    }
    		count++;
	    }

	    //print the path and distance of each node

        for(i=0;i<n;i++)
	        if(i!=end_value)
	        {
	            if(i == begin_value)
	            {
	                previous = i;
	                if(i>=8)
	                    printf("\nDistance of node f%d to f%d = %d\n",i-7, end_value-7,distance[i]);
		            else
		                printf("\nDistance of node t%d to f%d = %d\n",i+1, end_value-7,distance[i]);
		            j=i;
			            j=pred[j];

                    next_move[index] = j;
                    for(k=0; k<MAX_BALL; k++)
                    {
                        //printf("nextmove [%d] is: %d, nextmove k: %d is: %d\n",index, next_move[index], k, next_move[k]);
                        if (j == next_move[k] && k != index) {
                            return 100;
                        }
                    }
                    printf("\nPath =");
			            if(j >= 8 && j < 12)
			            {
			                if(previous >= 8 && previous < 12)
			                {
			                    printf(" f%df%d\n",previous-7, j-7);

			                }
			                else
			                {
			                    printf(" t%df%d\n",previous+1, j-7);
			                }
			            }
			            else if(previous >= 8 && previous < 12)
			            {
			                printf(" f%dt%d\n",previous-7, j+1);
			            }
			            else
			            {
			                printf("t%dt%d\n", previous+1, j+1);
			            }
			        //begin[k]=j;
			        //dijkstra(G,n,end, begin);
		           //}
	               //while(j!=end_value);
	              if(j!=end_value)
	               {
	                    return j;
	                    //dijkstra(begin, index);
	               }
	                else return 99;
	        }

	}
	return 99;
}