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
 
struct comp {
  short ac : 16;
  short ir : 16;
  short mbr : 16;
  short opcode;
  unsigned int pc : 12;
  unsigned int mar: 12;
  int input;
  int output;
  short mem[4096];
}comp;
