#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/**************************************************************************
 * Assessment Title: Assessed Coursework Exercise # 3
 *
 *
 * Number of Submitted C Files: 2
 *
 *
 * Date: 25/11/18
 *
 *
 * Authors:
 *	1. Calum Todd, Reg no: 201707856
 *	2. Peter Spasov, Reg no: 201700387
 *	3. Liam Doolan, Reg no: 201725131
 *	4. David Caldwell, Reg no: 201707994
 *  5. Scott White, Reg no: 201717277
 *
 *	Statement: We confirm that this submission is all our own work.
 *
 *  (Signed)_____________________________________Calum Todd
 *
 * 	(Signed)_____________________________________Peter Spasov
 *
 *	(Signed)_____________________________________Liam Doolan
 *
 *	(Signed)_____________________________________David Caldwell
 *
 *  (Signed)_____________________________________Scott White
 **************************************************************************/

int binToDec (char* bin, int length){
	int dec = 0; // the decimal number to be returned
	int power = 1; // the power of 2 for each digit in the binary number
	char temp[length]; // a copy of bin to allow us to use read-only input
	for (int i = 0; i < length; i++)
	{
	    temp[i] = bin[i];
	}
	for (int i = length - 1; i > 0; i--)
	{
		if (bin[0] == '1') // if the most significant digit is 1, that means the number is negative in 2's complement
		{
			if (temp[i] == '0') // flip the digits
			    temp[i] = '1';
			else
			    temp[i] = '0';
		}

		dec += (temp[i] - '0')*power; // adds the appropriate power of 2 to the number
		power *= 2; // increments the power of 2
	}
	if (bin[0] == '1') // detects 2's complement
		dec = -1 - dec; // represents 2's complement
	return dec;
}


char *decToBin(int dec, int digits){
    char* bin; // start of array address
    bin = (char*)malloc(digits+1); // allow sufficient memory for the array to be returned
    int deccopy = dec; // copy of dec
    if (dec < 0) // detects negative
    {
        deccopy = -deccopy;
        deccopy -= 1;
    }
    for (int c = digits-1 ; c >= 0 ; c--)
    {
        if (deccopy%2 == 1) // detects and fulfills 2's complement
        {
            if (dec < 0)
                *(bin+c) = 0 + '0';
            else
                *(bin+c) = 1 + '0';
        }
        else
        {
            if (dec < 0)
                *(bin+c) = 1 + '0';
            else
                *(bin+c) = 0 + '0';
        }
        deccopy = deccopy/2; // changes deccopy appropriately
    }
    *(bin+digits) = '\0'; // finishes the string
    return bin; // returns the address of the string
}



void load_default()
{
	//populates memory by converting the following binary strings to decimal then storing them in the array
	 comp.mem[0] = binToDec("0101010111001010",16);
	 comp.mem[1] = binToDec("0010000000010100",16);
	 comp.mem[2] = binToDec("0101000000101010",16);
	 comp.mem[3] = binToDec("1010000000010100",16);
	 comp.mem[4] = binToDec("0010000000110010",16);
	 comp.mem[5] = binToDec("0101000101010100",16);
	 comp.mem[6] = binToDec("1001000000110010",16);
	 comp.mem[7] = binToDec("1011000010100101",16);
	 comp.mem[8] = binToDec("0000111010101010",16);
}

void display_memory(){
  short content;
  printf("\t\t Memory Address\t | Contents\n\n");
  for(int i = 0; i < 4096; i++){//checks every address in memory
		if(comp.mem[i] != 0){//if the memory location is not empty, print the address and contents in binary
    content = comp.mem[i];
    printf("\t %s\t |\t %s\n",decToBin(i, 16), decToBin(content,16));
	}
	}
}

void user_prompt()
{
  	int memory_pos = 0; // position in memory

		printf("\nThese are the opcodes for each of the instructions:\n0000 - Hault\t0110 - Output\n0001 - Load\t0111 - Skipcond\n0010 - Store\t1000 - Jump\n0011 - Subt\t1001 - Multiply\n0100 - Add\t1010 - Divide\n0101 - Input\t1011 - Flip\nIf you want to see this table again type 'Table'\n\n");
  	while (1==1)
  	{
  		char user_input[17] = {};

  		printf("Please enter a 16 bit binary value, enter stop when finished: "); // prompt user for input up to 16 chars
  		scanf(" %s17", user_input);

  		if(strcmp(user_input,"Stop") == 0) { // check for exit
  			break;
  		}
			if(strcmp(user_input,"Table") == 0){
				printf("\nThese are the opcodes for each of the instructions:\n0000 - Hault\t0110 - Output\n0001 - Load\t0111 - Skipcond\n0010 - Store\t1000 - Jump\n0011 - Subt\t1001 - Multiply\n0100 - Add\t1010 - Divide\n0101 - Input\t1011 - Flip\nIf you want to see this table again type 'Table'\n\n");
			}

		char opcode[5]; // check valid opcode
		int invalid = 0;
  		strncpy(opcode,user_input,4);
  		opcode[4] = '\0';
  		if(strcmp(opcode, "1100") == 0 || strcmp(opcode, "1101") == 0 || strcmp(opcode, "1110") == 0 || strcmp(opcode, "1111") == 0)
		{
			printf("Invalid opcode.\n\n");
			invalid = 1;
		}
		if((strlen(user_input) < 16 || strlen(user_input) > 16) && strcmp(user_input,"Table") != 0){ // checks if the length of the input is correct
        			printf("This input is not a 16 bit binary number\n\n");
							invalid = 1;
		}else if(strcmp(user_input, "Table") == 0){ // to make sure it you ask for the table it doesn't produce an error message
			invalid = 1;
		}
		if(invalid == 0)
		{
      			for(int i=0; i<16; i++) // for each bit in 16 bit string
  			{
  				char bit = user_input[i]; // get current bit
  				if(bit=='1')
  				{
  					comp.mem[memory_pos] <<=1; 	// left shift by 1
  					comp.mem[memory_pos] |=1; 	// flip 0 to 1
  				}
  				else if(bit=='0')
  				{
  					comp.mem[memory_pos] <<=1; // left shift by 1
  				}
  				else
  				{
  					printf("This input is not in binary form\n\n"); // invalid input, retry
  					memory_pos--;
  					break;
  				}
  			}
  			memory_pos++; // go to next position in memory
  			printf("Please enter the next line of memory.\n\n");
		}
    }
}

void hault(){
  printf("\nCheerio\n");
  display_memory();
	int i  = comp.ac;
	printf("\nAC(bin): %s\nAC(dec): %i\n",decToBin(i,16),comp.ac); // Displays the value of the ac in decimal and binary
  exit(0); // terminates the program
}

void load(){
  comp.ac = comp.mem[comp.mbr]; // loads the value which the operand points to into the AC
}

void store(){
  comp.mem[comp.mbr] = comp.ac; // stores the value of the AC to the address which the operand points to
}

void subt(){
  comp.ac = comp.ac - comp.mbr; // subtracts the value which the operand points to from the AC
}

void add(){
  comp.ac = comp.ac + comp.mbr; // adds the value which the operand points to, to the AC
}

void input(){
  printf("\nPlease enter a new value for the AC: ");
  scanf("%i",&comp.input); // asks the user for a value for the AC and uses the input register to get it
  comp.ac = comp.input;
}

void output(){
	comp.output = comp.ac; // copies the value of AC to the output register then outputs the contents to the user
  printf("%i",comp.output);
}

void skipcond(){
  if(comp.ac == 0){// checks if the AC is equal to 0, if so it proresses the pc on by 1
    comp.pc++;
  }
}

void jump(){
  comp.pc = comp.mbr; // sets the PC to the value of the operand
}

void multiply(){
  comp.ac = comp.ac * comp.mbr; // multiplies the AC by the value which the operand points to
}

void divide(){
	if(comp.mbr == 0){
		printf("\nDenomonator is equal to 0, cannot divide.");
	}else{ // floating point exception handling
  comp.ac = comp.ac / comp.mbr; // divides the AC by the value which is pointed to by the operand
}
}

void flip(){
/*convert the ac to binary, flip it then convert it back
to decimal and update ac
*/
short temp = comp.ac;
char *flipped = decToBin(temp, 16); // converts AC to binary

for(int i=0; i<16; i++){ // checks each bit of the AC and changes it to its opposite
  if(flipped[i] == '0'){
    flipped[i] = '1';
  }
  else{
    flipped[i] = '0';
  }
}

comp.ac = binToDec(flipped,16); // converts the flipped binary back to decimal and stores it in the AC
}

void find_instruction(){

int op = comp.mem[4096]; // copies the opcode from the specified memory location
switch(op){ // checks the value of the opcode to find the correct instruction and calls the corresponding instruction function
	//if the instruction requires the operand to be an address the MAR is copied to the MBR, if it requires a value then the MAR
	//finds the corresponding location in memory and sets the MBR to that value
  case 0:
  printf("\nHault");
  hault();
  break;

  case 1:
  printf("\nLoad");
  comp.mbr = comp.mar;
  load();
  break;

  case 2:
  printf("\nStore");
  comp.mbr = comp.mar;
  store();
  break;

  case 3:
  printf("\nSubt");
  comp.mbr = comp.mem[comp.mar];
  subt();
  break;

  case 4:
  printf("\nAdd");
  comp.mbr = comp.mem[comp.mar];
  add();
  break;

  case 5:
  printf("\nInput");
  input();
  break;

  case 6:
  printf("\nOutput");
  output();
  break;

  case 7:
  printf("\nSkipcond");
  skipcond();
  break;

  case -8:
  printf("\nJump");
  comp.mbr = comp.mem[comp.mar];
  jump();
  break;

  case -7:
  printf("\nMultiply");
  comp.mbr = comp.mem[comp.mar];
  multiply();
  break;

  case -6:
  printf("\nDivide");
  comp.mbr = comp.mem[comp.mar];
  divide();
  break;

  case -5:
  printf("\nFlip");
  flip();
  break;
}
}

void split(char* line){
  char* opcode;
  for(int i = 0; i < 4; i++){ // copies the first 4 bits of the 16 bit instruction to the opcode string
    opcode[i] = line[i];
  }
  opcode[4] = '\0';
  comp.mem[4096] = binToDec(opcode,4); // converts the opcode to decimal and stores it in a specified memory location
}

char* splitop(char *line){
  char* operand;
  int opcount = 0;

  for(int i = 4; i<16;i++){ // copies the last 12 bits of the 16 bit instruction to the operand string
    operand[opcount] = line[i];
    opcount++;
}
return operand;
}

void file_read(){
  char line[18];
  FILE *fptr;
  int i = 0;

  if ((fptr = fopen("Practice file.txt", "r")) == NULL){
    printf("Error opening file.");
    exit(1);
  }

  while(fgets(line,sizeof(line),fptr) != NULL){// when there exists a line of bits, read them into the line string
    line[strlen(line) - 1] = '\0';
    comp.mem[i] = binToDec(line,16); // converts the strings of binary to decimal and stores them in memory
    i++;
  }
  fclose(fptr);
}

void fetch_exec(){
  comp.ac = 0; // initialises the AC and the PC
  comp.pc = 0;

  while(comp.pc < 4096){
		if(comp.mem[comp.pc] != 0){
    comp.mar = comp.pc;
    comp.ir = comp.mem[comp.mar];
    comp.pc++; // loads the next instruction to be run into the ir and increments the pc
    int temp = comp.ir;
    char* tempstr = decToBin(temp,16); //converts the instruction to binary
    split(tempstr); //finds the opcode and stores it at a specified memory address
    char* operand = splitop(tempstr);
		comp.mar = binToDec(operand,12); // finds the operand and stores it to the MAR in case it's needed
    find_instruction();
	}
	else{
		comp.pc++;
	}
}

}

int main(int argc, char* argv[]){

if(argc != 2){
	printf("Invalid amount of arguments.\nIf you want to run this through a file, type -F as your argument.\nIf you want to run this through user input, type -C as your argument.\nIf you want to run the default program, type -D as your argument.");
	return 1; //if the wrong number of arguments are provided it prints this message and terminates
}
if(strcmp(argv[1], "-C") == 0){
  printf("You chose user input\n");
	for(int i = 0; i < 4096; i++ ){
		comp.mem[i] = 0;
	}
  user_prompt(); // if "-C" is typed it initilises memory and calls the user prompt function
  fetch_exec();
}

else if(strcmp(argv[1], "-D") == 0){
  printf("You chose the default program\n");
	for(int i = 0; i < 4096; i++ ){
		comp.mem[i] = 0;
	}
  load_default(); // if "-D" is typed it initilises memory and calls the load default function
  fetch_exec();
}
else if(strcmp(argv[1],"-F") == 0){
  printf("You chose file reading\n");
	for(int i = 0; i < 4096; i++ ){
		comp.mem[i] = 0;
	}
  file_read(); // if "-F" is typed it initilises memory and calls the file read function
  fetch_exec();
}
else{
  printf("Invalid arguments.\nIf you want to run this through a file, type -F as your argument.\nIf you want to run this through user input, type -C as your argument.\nIf you want to run the default program, type -D as your argument.");
  return 1; // if the right amount of arguments are entered but they are invalid it prints this message and terminates
}
display_memory();
int i = comp.ac;
printf("\nAC(bin): %s\nAC(dec): %i\n",decToBin(i,16),comp.ac);
return 0; //displays the contents of memory and prints the AC in binary and decimal form


}
