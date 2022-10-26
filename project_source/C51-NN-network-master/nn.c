#include <math.h>
#include "HC89F0541.h"
#include <stdio.h>
#include <stdlib.h>

/******************************************************************
 * Network Configuration - customized per network 
 ******************************************************************/
#define PatternCount	10
#define InputNodes		7
#define HiddenNodes		8
#define OutputNodes		4

//const int PatternCount = Pattern_Count;
//const int InputNodes = Input_Nodes;
//const int HiddenNodes = Hidden_Nodes;
//const int OutputNodes = Output_Nodes;
const float LearningRate = 0.3;
const float Momentum = 0.9;
const float InitialWeightMax = 0.5;
const float Success = 0.1;//0.0004;

typedef ux8 byte;

const byte Input[PatternCount][InputNodes] = {
  { 1, 1, 1, 1, 1, 1, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1 },  // 2
  { 1, 1, 1, 1, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 1 },  // 4
  { 1, 0, 1, 1, 0, 1, 1 },  // 5
  { 0, 0, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 0, 0, 0, 0 },  // 7 
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 0, 0, 1, 1 }   // 9
}; 

const byte Target[PatternCount][OutputNodes] = {
  { 0, 0, 0, 0 },  
  { 0, 0, 0, 1 }, 
  { 0, 0, 1, 0 }, 
  { 0, 0, 1, 1 }, 
  { 0, 1, 0, 0 }, 
  { 0, 1, 0, 1 }, 
  { 0, 1, 1, 0 }, 
  { 0, 1, 1, 1 }, 
  { 1, 0, 0, 0 }, 
  { 1, 0, 0, 1 } 
};

typedef int (*func1)(int);
typedef int (*func2)(const char*, int) reentrant;
typedef int (*func3)(const char*, float) reentrant;

typedef struct S {
	func1	begin;
	func2	println;// = printf;
	func2	print;// = printf;
	func3	printf;// = printf;
	
}s_t;

s_t Serial;

void Uart_SendByte(unsigned char buf)
{
	SCON &=~ 0x10;				//失能UART1接收
	SBUF = buf;					//发送8位串口数据
 	while(!(SCON & 0x02));
	SCON &=~ 0x02;				//清除发送中断标志位
	SCON |= 0x10;				//UART1接收使能
}

char putchar(char c)
{
 	Uart_SendByte(c);
	return c;
}

int sendmsg(const char* str, float d){
	printf(str, d);

	return 1;
}

/******************************************************************
 * End Network Configuration
 ******************************************************************/


xdata int i, j, p, q, r;
xdata int ReportEvery1000;
xdata int RandomizedIndex[PatternCount];
xdata long  TrainingCycle;
xdata float Rando;
xdata float Error;
xdata float Accum;


xdata float Hidden[HiddenNodes];
xdata float Output[OutputNodes];
xdata float HiddenWeights[InputNodes+1][HiddenNodes];
xdata float OutputWeights[HiddenNodes+1][OutputNodes];
xdata float HiddenDelta[HiddenNodes];
xdata float OutputDelta[OutputNodes];
xdata float ChangeHiddenWeights[InputNodes+1][HiddenNodes];
xdata float ChangeOutputWeights[HiddenNodes+1][OutputNodes];


int random(int r){
  return rand() % r;
}
void toTerminal()
{

  for( p = 0 ; p < PatternCount ; p++ ) { 
    Serial.println("\n"); 
    Serial.print ("  Training Pattern: %d ", p);
    //Serial.println (p);      
    Serial.print ("  Input ");
    for( i = 0 ; i < InputNodes ; i++ ) {
      Serial.print ("%d", Input[p][i]);
      Serial.print (" ");
    }
    Serial.print ("  Target ");
    for( i = 0 ; i < OutputNodes ; i++ ) {
      Serial.print ("%d", Target[p][i]);
      Serial.print (" ");
    }
/******************************************************************
* Compute hidden layer activations
******************************************************************/

    for( i = 0 ; i < HiddenNodes ; i++ ) {    
      Accum = HiddenWeights[InputNodes][i] ;
      for( j = 0 ; j < InputNodes ; j++ ) {
        Accum += Input[p][j] * HiddenWeights[j][i] ;
      }
      Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
    }

/******************************************************************
* Compute output layer activations and calculate errors
******************************************************************/

    for( i = 0 ; i < OutputNodes ; i++ ) {    
      Accum = OutputWeights[HiddenNodes][i] ;
      for( j = 0 ; j < HiddenNodes ; j++ ) {
        Accum += Hidden[j] * OutputWeights[j][i] ;
      }
      Output[i] = 1.0/(1.0 + exp(-Accum)) ; 
    }
    Serial.print ("  Output ");
    for( i = 0 ; i < OutputNodes ; i++ ) {       
      Serial.printf ("%f", Output[i]);
      Serial.print (" ");
    }
  }


}

void predict(u8 *input)
{
/******************************************************************
* Compute hidden layer activations
******************************************************************/

    for( i = 0 ; i < HiddenNodes ; i++ ) {    
      Accum = HiddenWeights[InputNodes][i] ;
      for( j = 0 ; j < InputNodes ; j++ ) {
        Accum += input[j] * HiddenWeights[j][i] ;
      }
      Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
    }

/******************************************************************
* Compute output layer activations and calculate errors
******************************************************************/

    for( i = 0 ; i < OutputNodes ; i++ ) {    
      Accum = OutputWeights[HiddenNodes][i] ;
      for( j = 0 ; j < HiddenNodes ; j++ ) {
        Accum += Hidden[j] * OutputWeights[j][i] ;
      }
      Output[i] = 1.0/(1.0 + exp(-Accum)) ; 
	  Output[i] = Output[i] > 0.8 ? 1:0;
    }
    Serial.print ("result: ");
    for( i = 0 ; i < OutputNodes ; i++ ) {       
      Serial.printf ("%f", Output[i]);
      Serial.print (" ");
    }
    Serial.print ("\n");
}

void setup(){

  Serial.begin = (9600);
  Serial.println = sendmsg;
  Serial.print = sendmsg;
  Serial.printf = sendmsg;
  //randomSeed(analogRead(3));
  ReportEvery1000 = 1;
  for( p = 0 ; p < PatternCount ; p++ ) {    
    RandomizedIndex[p] = p ;
  }
}  

void main(){

	setup();

/******************************************************************
* Initialize HiddenWeights and ChangeHiddenWeights 
******************************************************************/

  for( i = 0 ; i < HiddenNodes ; i++ ) {    
    for( j = 0 ; j <= InputNodes ; j++ ) { 
      ChangeHiddenWeights[j][i] = 0.0 ;
      Rando = (float)(random(100))/100;
      HiddenWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;
    }
  }
/******************************************************************
* Initialize OutputWeights and ChangeOutputWeights
******************************************************************/

  for( i = 0 ; i < OutputNodes ; i ++ ) {    
    for( j = 0 ; j <= HiddenNodes ; j++ ) {
      ChangeOutputWeights[j][i] = 0.0 ;  
      Rando = (float)(random(100))/100;        
      OutputWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;
    }
  }
  Serial.println("Initial/Untrained Outputs: ");
  toTerminal();
/******************************************************************
* Begin training 
******************************************************************/

  for( TrainingCycle = 1 ; TrainingCycle < 2147483647 ; TrainingCycle++) {    

/******************************************************************
* Randomize order of training patterns
******************************************************************/

    for( p = 0 ; p < PatternCount ; p++) {
      q = random(PatternCount);
      r = RandomizedIndex[p] ; 
      RandomizedIndex[p] = RandomizedIndex[q] ; 
      RandomizedIndex[q] = r ;
    }
    Error = 0.0 ;
/******************************************************************
* Cycle through each training pattern in the randomized order
******************************************************************/
    for( q = 0 ; q < PatternCount ; q++ ) {    
      p = RandomizedIndex[q];

/******************************************************************
* Compute hidden layer activations
******************************************************************/

      for( i = 0 ; i < HiddenNodes ; i++ ) {    
        Accum = HiddenWeights[InputNodes][i] ;
        for( j = 0 ; j < InputNodes ; j++ ) {
          Accum += Input[p][j] * HiddenWeights[j][i] ;
        }
        Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
      }

/******************************************************************
* Compute output layer activations and calculate errors
******************************************************************/

      for( i = 0 ; i < OutputNodes ; i++ ) {    
        Accum = OutputWeights[HiddenNodes][i] ;
        for( j = 0 ; j < HiddenNodes ; j++ ) {
          Accum += Hidden[j] * OutputWeights[j][i] ;
        }
        Output[i] = 1.0/(1.0 + exp(-Accum)) ;   
        OutputDelta[i] = (Target[p][i] - Output[i]) * Output[i] * (1.0 - Output[i]) ;   
        Error += 0.5 * (Target[p][i] - Output[i]) * (Target[p][i] - Output[i]) ;
      }

/******************************************************************
* Backpropagate errors to hidden layer
******************************************************************/

      for( i = 0 ; i < HiddenNodes ; i++ ) {    
        Accum = 0.0 ;
        for( j = 0 ; j < OutputNodes ; j++ ) {
          Accum += OutputWeights[i][j] * OutputDelta[j] ;
        }
        HiddenDelta[i] = Accum * Hidden[i] * (1.0 - Hidden[i]) ;
      }


/******************************************************************
* Update Inner-->Hidden Weights
******************************************************************/


      for( i = 0 ; i < HiddenNodes ; i++ ) {     
        ChangeHiddenWeights[InputNodes][i] = LearningRate * HiddenDelta[i] + Momentum * ChangeHiddenWeights[InputNodes][i] ;
        HiddenWeights[InputNodes][i] += ChangeHiddenWeights[InputNodes][i] ;
        for( j = 0 ; j < InputNodes ; j++ ) { 
          ChangeHiddenWeights[j][i] = LearningRate * Input[p][j] * HiddenDelta[i] + Momentum * ChangeHiddenWeights[j][i];
          HiddenWeights[j][i] += ChangeHiddenWeights[j][i] ;
        }
      }

/******************************************************************
* Update Hidden-->Output Weights
******************************************************************/

      for( i = 0 ; i < OutputNodes ; i ++ ) {    
        ChangeOutputWeights[HiddenNodes][i] = LearningRate * OutputDelta[i] + Momentum * ChangeOutputWeights[HiddenNodes][i] ;
        OutputWeights[HiddenNodes][i] += ChangeOutputWeights[HiddenNodes][i] ;
        for( j = 0 ; j < HiddenNodes ; j++ ) {
          ChangeOutputWeights[j][i] = LearningRate * Hidden[j] * OutputDelta[i] + Momentum * ChangeOutputWeights[j][i] ;
          OutputWeights[j][i] += ChangeOutputWeights[j][i] ;
        }
      }
    }

/******************************************************************
* Every 1000 cycles send data to terminal for display
******************************************************************/
    ReportEvery1000 = ReportEvery1000 - 1;
    if (ReportEvery1000 == 0)
    {
      Serial.println("\n"); 
      Serial.println("\n"); 
      Serial.print ("TrainingCycle: %d",TrainingCycle );
      //Serial.print (TrainingCycle);
      Serial.printf ("  Error = %f", Error);
      //Serial.println (Error, 5);

      toTerminal();

      if (TrainingCycle==1)
      {
        ReportEvery1000 = 999;
      }
      else
      {
        ReportEvery1000 = 1000;
      }
    }    


/******************************************************************
* If error rate is less than pre-determined threshold then end
******************************************************************/

    if( Error < Success ) break ;  
  }
  Serial.println("\n");
  Serial.println("\n"); 
  Serial.print ("TrainingCycle: %d", TrainingCycle);
  //Serial.print (TrainingCycle);
  Serial.printf ("  Error = %f", Error);
 // Serial.println (Error, 5);

  toTerminal();

  Serial.println ("\n");  
  Serial.println ("\n");
  Serial.println ("Training Set Solved! ");
  Serial.println ("--------"); 
  Serial.println ("\n");
  Serial.println ("\n");  
  ReportEvery1000 = 1;
  
  
/******************************************************************
* from a 7 segments input data predict the value
******************************************************************/
  predict(&Input[3]);
}

