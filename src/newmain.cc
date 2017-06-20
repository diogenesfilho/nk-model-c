//Implementation from: https://www.go4expert.com/articles/c-program-calculate-combinations-n-digit-t25380/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/******************************************************************************/
//This code below is used to get all possible binary combination for a k size array.
//Array is according K values, i.e. 2^K possible combinations.
#define ARRAY_SIZE 8

//NK default parameters.
#define N_ 6
//If changes K, changes the ARRAY_SIZE above too. This is equal to little or, whats means big K = k-1.
#define K_ 3

/* FUNCTIONS DECLARATIONS */
void find_all_possible_binary(int ,int );
void push(int );
void pop();

//SIMPLE LIFO STACK .YOU CAN ADJUST ARRAY_SIZE ACCORDING TO YOUR SYSTEM MEMORY
int stack[ARRAY_SIZE];

//Used to save the char[] combinations.
int comb_arr[ARRAY_SIZE][K_];
int count_arr = 0;
int count_temp = 0;

//Top is declared here, before main.
int top;

void push(int x){
	stack[++top]=x;
}

void pop(){
	stack[top--];
}

void find_all_possible_binary(int x,int temp)
{
	int i;
	if(temp!=-1){
		push(temp);
	}
	if(x==0){
		for( i=0;i<=top;++i){
			//printf("%d",stack[i]);
                        comb_arr[count_arr][count_temp] = stack[i];
                        count_temp++;
		}
		//printf("\n");
                count_temp = 0;
                count_arr++;
		pop();
	}
	else{
		find_all_possible_binary(x-1,0);
		find_all_possible_binary(x-1,1);
		pop();
	}
}

/******************************************************************************/
/*
 * Function: return an index of char[] (combination wanted).
 */
int seek_index(int combinations[][K_], char wanted[])
{

    //printf("\nSeeking..\n");

    int temp = 0;
    int index = 0;
    int teta = 0;

    int row, t;

    for (row = 0; row < ARRAY_SIZE; row++)
    {
        for (t = 0; t < K_; t++)
        {
            teta = wanted[t] - '0';
            //printf("%c\f", x);

            if (combinations[row][t] == teta)
            {
                //printf("true");
                temp++;
            }/*else
            {
                //printf("%d not equal to %c \n", combinations[row][t],x);
            }*/
        }
        if(temp == K_)
        {
            index = row;
        }else
        {
            temp = 0;
        }
    }

    return index;
}

/******************************************************************************/
//char *var, int position from element.
float calcDistribution (float distributions[][N_], int combinations[][K_], char epistasis[], int posi)
{

    int index = 0;

    index = seek_index(combinations,epistasis);

    //Return epistasis distribution at 'posi' position in individuals' genes.
    return distributions[index][posi];

}
/******************************************************************************/
float nkLandscape (float distributions[][N_], int combinations[][K_], char var[], int n, int k, int neighborhood)
{

    printf("Starting NK Landscape..\n");
    int s, t;

    //Final result that will be returned.
    float result = 0.0;

    if(n > k && k > 0)
    {
        //printf(" - n > k && k > 0 -> True! \n");

        if(neighborhood == 0)
        {
            //printf(" - neighborhood == 0 -> True too! \n");

            //Used to circular queue.
            int pointer = 0;

            //Used to save a char set of combination, for example 000, or 111 depends of k value.
            char chain[k];
            int count_chain = 0;

            //Inside individual
            for (s = 0; s < n; s++)
            {
                pointer = s;
                //inside epistasis.
                for (t = 0; t < k; t++)
                {
                    if(pointer >= n-1)
                    {
                        chain[count_chain] = var[pointer];
                        pointer = (pointer + 1) % n;
                        count_chain++;
                    }else
                    {
                        chain[count_chain] = var[pointer];
                        //printf("%c", var[pointer]);
                        count_chain++;
                        pointer++;
                    }
                }

                //Epistasis genes.
                /*printf("Epistasis genes \n");
                int y;
                for (y = 0; y <count_chain; y++){
                    printf("%c",chain[y]);
                }
                printf("\n");*/

                //Get the distribution of each k genes together.
                result += calcDistribution(distributions,combinations,chain,s);

                count_chain = 0;

                chain[k];

            }

        }
    }

    return (result/n);
}
/******************************************************************************/



int main(void)
{

    //Distribution Table
    float distributionTable[ARRAY_SIZE][N_];

    //Only call once.
    srand((unsigned int)time(NULL));

    //Limit between 0 and this var below.
    float limit_dist = 1.0;

    int w,j;
    float value = 0.0;
    /*
    * Just filling the distribution table.
    */
    //inside lines
    printf("Distribution Table\n");
    for (w = 0; w < ARRAY_SIZE; w++) {
            //Inside columns
            for (j = 0; j < N_; j++) {
            value = ((float)rand()/(float)(RAND_MAX)) * limit_dist;
            distributionTable[w][j] = value;
            printf("%f  ", value);
            }printf("\n");
    }

    //Used for stack combinations.
    top=-1;
    //printf("\nAll possible binary combinations below: \n");
    find_all_possible_binary(K_,top);

	//Just showing on console some logs about combination array.
    printf("\nInside array of combinations, just check. \n");
    int a,b;
    for (a = 0; a < ARRAY_SIZE; a++) {
        for(b = 0; b < K_; b++){
            printf("%d", comb_arr[a][b]);
        }printf("\n");
    }printf("\n");

    char watd[] = {'1', '1','0','\0'};
    printf("Index founded: %d (add +1 for position exactly)\n",seek_index(comb_arr,watd));

    printf("Distribution for index previously: %f \n", calcDistribution(distributionTable,comb_arr,watd,3));

    char individual[] = {'0','0','1','0','1','1','\0'};
    printf("NK Fitness for individual: %f \n", nkLandscape(distributionTable,comb_arr,individual,6,3,0));

}
