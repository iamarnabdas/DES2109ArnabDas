/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
unsigned char masterkey[8] = "abcdefgh";
unsigned char roundkey[16][6];

int PC1[7][8] =  {
                { 57, 49, 41, 33, 25, 17, 9, 1   },
                { 58, 50, 42, 34, 26, 18, 10, 2  },
                { 59, 51, 43, 35, 27, 19, 11, 3  },
                { 60, 52, 44, 36, 63, 55, 47, 39 },
                { 31, 23, 15, 7, 62, 54, 46, 38  }, 
                { 30, 22, 14, 6, 61, 53, 45, 37  },
                { 29, 21, 13, 5, 28, 20, 12, 4   }
                };
int PC2[6][8] =  {
                 { 14, 17, 11, 24, 1, 5, 3, 28   },
                 { 15, 6, 21, 10, 23, 19, 12, 4  },
                 { 26, 8, 16, 7, 27, 20, 13, 2    },
                 { 41, 52, 31, 37, 47, 55, 30, 40 },
                 { 51, 45, 33, 48, 44, 49, 39, 56 },
                 { 34, 53, 46, 42, 50, 36, 29, 32 }
                 }; 

  int  s_box[8][4][16] = {{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		      {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		      {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
		      {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
		     {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		      {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		      {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		      {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
		     {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		      {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		      {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		      {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
		     {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		      {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		      {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		      {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
		     {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		      {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
	          {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		      {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
		     {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		      {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		      {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		      {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
		     {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		      {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		      {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		      {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
		     {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		      {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		      {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		      {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}};
		      
		      
int ip[8][8]=  {{58 ,	50 ,	42 ,	34 ,	26 ,	18 ,	10 ,	2},
	 		{60 ,	52 ,	44 ,	36 ,	28 ,	20 ,	12 ,	4},
			{62 ,	54 ,	46 ,	38 ,	30 ,	22 ,	14 ,	6},
			{64 ,	56 ,	48 ,	40 ,	32 ,	24 ,	16 ,	8},
			{57 ,	49 ,	41 ,	33 ,	25 ,	17 ,	9  ,	1},
			{59 ,	51 ,	43 ,	35 ,	27 ,	19 ,	11 ,	3},
			{61 ,	53 ,	45 ,	37 ,	29 ,	21 ,	13 ,	5},
			{63 ,	55 ,	47 ,	39 ,	31 ,	23 ,	15 ,    7}}, 
			
			
 ip1[8][8]={{ 40 ,	8 ,	48 ,	16 ,	56 ,	24 ,	64 ,	32},
			{39 , 	7 ,	47 ,	15 ,	55 ,	23 ,	63 ,	31},
			{38 ,	6 ,	46 ,	14 ,	54 ,	22 ,	62 ,	30},
			{37 ,	5 ,	45 ,	13 ,	53 ,	21 ,	61 ,	29},
			{36 ,	4 ,	44 ,	12 ,	52 ,	20 ,	60 ,	28},
			{35 ,	3 ,	43 ,	11 ,	51 ,	19 ,	59 ,	27},
			{34 ,	2 ,	42 ,	10 ,	50 ,	18 ,	58 ,	26},
			{33 ,	1 ,	41 ,	9  , 	49 ,	17 ,	57 ,	25}};		      

unsigned char ex[6][8]={{32 ,  1 ,   2 ,   3 ,  4 ,	5 ,	4 ,	5},
			{6 ,	7 ,	8 ,	9 ,	8 ,	9 ,	10 ,	11},
			{12 ,	13 ,	12 ,	13 ,	14 ,	15 ,	16 ,	17},
			{16 ,	17 ,	18 ,	19 ,	20 ,	21 ,	20 ,	21},
			{22 ,	23 ,	24 ,	25 ,	24 ,	25 ,	26 ,	27},
			{28 ,	29 ,	28 ,	29 ,	30 ,	31 ,	32 ,	1 }};



int get_bit(unsigned char* arr, int i)
{
	int x = i/8;
	int y = i%8;
	return !!(arr[x] & (1<<(7 - y)));
} 
void set_bit(unsigned char* arr, int i, int b)
{
	int x = i/8;
	int y = i%8;
	arr[x] = arr[x] | (b << (7 - y));
}

void key_schedule()
{
	unsigned char tmp_key_1[7];
	for(int i=0; i<7; i++) 
	tmp_key_1[i] = 0;
	unsigned char tmp_key_2[7];

	// PC-1
	for(int i=0; i<56; i++)
		set_bit(tmp_key_1, i, get_bit(masterkey, PC1[i/8][i%8] - 1));
		// tmp_key_1[i] <- key[PC_1[i] - 1]

	

    for(int round = 0; round < 16; round++)
    {

    	int shift = 2;
    	if(round == 0 || round == 1 || round == 8 || round == 15)
    	     shift = 1;
    
	for(int i=0; i<7; i++) 
	     tmp_key_2[i] = 0;
    	// rotate first half
    	for(int i=0; i<28; i++)
    	     set_bit(tmp_key_2, i, get_bit(tmp_key_1, (i+shift) % 28));
    		// tmp_key_2[i] <- tmp_key_1[ (i+shift) % 28]
    
    	// rotate second half
    	for(int i=28; i<56; i++)
    	{
    		int a = i + shift;
    		if(a >= 56) a = 28 + a - 56; 
    		set_bit(tmp_key_2, i, get_bit(tmp_key_1, a));
    		// a = i + shift 
    		// if( a >= 56) a = 28 + a - 56;
    		// tmp_key_2[i] <- tmp_key_1[ a ]
    	}
	for(int i=0; i<7; i++)
	 tmp_key_1[i] = tmp_key_2[i];

	    for(int j=0; j<7; j++)
		    printf("%02x ", tmp_key_1[j]);
            printf("\n");


	// PC-2
	for(int i=0; i<48; i++)
		set_bit(roundkey[round], i, get_bit(tmp_key_1, PC2[i/8][i%8] - 1));
		// roundkey[round][i] <- tmp_key[PC_2[i] - 1]
	
    }
    printf("round keys:\n");
    for(int i=0; i<16; i++)
	    for(int j=0; j<6; j++)
		    printf("%02x ", roundkey[i][j]);
    printf("\n\n");
}			

void fiestel ( unsigned char l0[], unsigned char r0[], int round ) 	
{
	unsigned char l1[4], r1[4], expan[6] ={0} , c[8] , row, col, s_value[8] , s_output[4]={0}, s[4] ,getbit[8];
	int i,j;
	
	//***** BEFORE ENCRYPTING L0 AND R0****  //    

	// EXPANSION FUNCTION//
	
	for(i=0;i<6;i++)
		for(j=0;j<8;j++)
			{
				
			getbit[i] = (r0[(ex[i][j]-1)/8]>>((ex[i][j]-1)%8))&1;
		        expan[i] = expan[i] | (getbit[i]<<j);
			}
        for(i=0; i<6; i++)
             expan[i] = expan[i] ^ roundkey[round][i];
	
	// APPLYING S-BOX //
	//PREPARING INPUTS FOR S-BOX//
	
	c[0] = (expan[0] & 0x3F);
	c[1] = (expan[0] >> 6);//getting last two bits and placing them to first two positions//
	c[1] = c[1] |( (expan[1] & 0x0F) << 2);// getting first four bits and placing them//
	c[2] = (expan[1] >> 4);//getting last four bits and placing them//
	c[2] = c[2] | ((expan[2] & 0x03) << 4);//getting first two bits and placing them//
	c[3] = (expan[2]  >> 2); //getting last six bits//
	
	c[4] = (expan[3] & 0x3F);
	c[5] = (expan[3] >> 6);//getting last two bits and placing them to first two positions//
	c[5] = c[5] |( (expan[4] & 0x0F) << 2);// getting first four bits and placing them//
	c[6] = (expan[4] >> 4);//getting last four bits and placing them//
	c[6] = c[6] | ((expan[5] & 0x03) << 4);//getting first two bits and placing them//
	c[7] = (expan[5]  >> 2); //getting last six bits//
	
	//PREPARING ROWS AND COLUMNS OF S-BOX//
	 
      
         // OUTPUT OF S-BOXES //
         for ( i=0;i<8;i++)
         {
           row = ((c[i] & 1) |( (c[i] >> 4) & 0x02));
           col = (( c[i] >> 1) & 0x0F) ;		       
	       s_value[i] = s_box[i][row][col];
	   }
	   
	//ADDING TWO FOUR BITS TO MAKE 8 BITS (1CHAR = 8BITS)// 
	 for ( i=0; i<4; i++)
	   s[i] = ((s_value[2*i] & 0x0F) | ((s_value[(2*i)+1] & 0x0F) << 4));
	   
	//PERMUTING S-BOX OUTPUTS //
	 int per[4][8] = {{16,  7,  20,   21,   29, 	12, 	28, 	17},
		{1, 	15, 	23, 	26, 	5, 	18, 	31, 	10},
		{2, 	8, 	24, 	14, 	32, 	27, 	3, 	9},
		{19, 	13, 	30, 	6, 	22, 	11, 	4, 	25}};    
	 
	 for(i=0;i<4;i++)
		for(j=0;j<8;j++)
			{	
			getbit[i] = (s[(per[i][j]-1)/8]>>((per[i][j]-1)%8))&1;
		    s_output[i] = s_output[i] | (getbit[i]<<j);
			}     
	 for( i=0;i< 4;i++)
	   {
	    r1[i] = s_output[i] ^ l0[i];
	    l1[i] = r0[i];
	    }
    	
	//***ATER 1ST ROUND ENCRYPTION , L1 AND R1***   // 
	for(i =0;i< 4;i++)
	  {
	    l0[i]=l1[i];
	    r0[i] = r1[i];
	    }  
	
}	  


#include<stdio.h>
void main()
{
    unsigned char i,j,a[8]={'a','r','n','a','b','d','a','s'},b[8]={0},c[8]={0},l0[4],r0[4],expan[6]={0},s_value[8],s_output[4]={0},l1[4],r1[4], s[4] ;
    unsigned char getbit[8], swap[4] , cipher[8]={0} , plaintext[8]={0};


	

    printf("***********INITIAL MESSAGE*********\n");
	for(i=0;i<8;i++)
		printf("%c\t",a[i]);
	

	
	for(i=0;i<8;i++)
		{
		    for(j=0;j<8;j++)
		    {
		        getbit[i] = (a[(ip[i][j]-1)/8]>>(((ip[i][j]-1)%8)))&1;
		        b[i] = b[i] | (getbit[i]<<j);
		    }
		    
		}
    
	//DIVIDING 32 BITS;
	for(i=0;i<4;i++)
	   {
	     l0[i]= b[i+4];
	   }
	for(i=0;i<4;i++)
	   {
	     r0[i]= b[i];
	   }
	 // SENDING L0 AND R0 TO FIESTEL FUNCTION//
	 
	 
	for(i =0 ; i<16;i++)
	  fiestel (l0,r0,i);
	  
	//AFTER APPLYING 16 ROUND FIESTEL
	
	printf("\n1st 32 bits l16\n");    
	for(i =0;i< 4;i++)
	  {
	    printf("%c ",l0[i]);
	    }  
	  printf("\nlast 32 bits r16\n");    
	 for(i =0;i< 4;i++)
	  {
	    printf("%c ",r0[i]);
	    }
	  // *******SWAPPING L16 AND R16******///
	  
	  for( i=0; i< 4; i++)
	   {
	       swap[i] = l0[i];
	       l0[i] = r0[i];
	       r0[i] = swap[i];
	   }
	   
	   //////****** APPLYING IP INVERSE ******////
	   for( i = 0; i<4; i++)
	   {
	       b[i]= r0[i];
	       b[i+4] =l0[i];
	   }
	   for(i=0;i<8;i++)
		{
		    for(j=0;j<8;j++)
		    {
		        getbit[i] = (b[(ip1[i][j]-1)/8]>>(((ip1[i][j]-1)%8)))&1;
		        cipher[i] = cipher[i] | (getbit[i]<<j);
		    }
		    
		}
		 
	//// ********----------- FINAL CIPHER TEXT -----------**********/////
	printf("\n\n\n*******_____FINAL CIPHER TEXT______******\n");
	for(i =0;i< 8;i++)
	  {
	    printf("%c\t ",cipher[i]);
	    }
	   
	
	//////___________________ ***************DECRYPTION PROCEDURE*********_____________________________ ////////////  
	
	///APPLYING IP ON CIPHER ////
	
	
	for(i=0;i<8;i++)
	   {
	    for(j=0;j<8;j++)
		  {
		      getbit[i] = (cipher[(ip[i][j]-1)/8]>>(((ip[i][j]-1)%8)))&1;
		      b[i] = b[i] | (getbit[i]<<j);
		   }
		}
		//DIVIDING 32 BITS;
	for(i=0;i<4;i++)
	   {
	     l0[i]= b[i+4];
	   }
	for(i=0;i<4;i++)
	   {
	     r0[i]= b[i];
	   }
	 // SENDING L0 AND R0 TO FIESTEL FUNCTION//
	 
	 
	for(i =0 ; i<16;i++)
	  fiestel (l0,r0, 16-i);
	  
	  
	//AFTER APPLYING 16 ROUND FIESTEL
	
	printf("\n1st 32 bits l16\n");    
	for(i =0;i< 4;i++)
	  {
	    printf("%c ",l0[i]);
	    }  
	  printf("\nlast 32 bits r16\n");    
	 for(i =0;i< 4;i++)
	  {
	    printf("%c ",r0[i]);
	    }
	  // *******SWAPPING L16 AND R16******///
	  
	  for( i=0; i< 4; i++)
	   {
	       swap[i] = l0[i];
	       l0[i] = r0[i];
	       r0[i] = swap[i];
	   }
	   
	   //////****** APPLYING IP INVERSE ******////
	   for( i = 0; i<4; i++)
	   {
	       b[i]= r0[i];
	       b[i+4] =l0[i];
	   }
	   for(i=0;i<8;i++)
		{
		    for(j=0;j<8;j++)
		    {
		        getbit[i] = (b[(ip1[i][j]-1)/8]>>(((ip1[i][j]-1)%8)))&1;
		        plaintext[i] = plaintext[i] | (getbit[i]<<j);
		    }
		    
		}
		
		
	//// ********----------- FINAL CIPHER TEXT -----------**********/////
	printf("\n\n\n*******_____FINAL PLAINTEXT______******\n");
	for(i =0;i< 8;i++)
	  {
	    printf("%c\t ",plaintext[i]);
	    }
		
		

}
