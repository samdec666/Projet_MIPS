#include "textToBin.h"
#include "operation_code_defines.h"

/*
On suppose :
	le texte instruction est valide
	la struct Instruction est initialisée
*/
void textInstructionToOpcode(char textInstruction, Instruction *instruction){
	char [8] opcode;
	getInstruction(textInstruction,opcode);

	if(opcode[1]=='\0' && opcode[0]=='j'){
		/* alors forcément instruction 'j' 
			j -> 6 premiers bits a 000010
			donc code[0] = 000010xx
		*/
		instruction->code[0] = (instruction->code[0]&0x03) + (J_CODE<<2);
		instruction->id = J_ID;
		setBlocksSize(instruction,6,26,0,0,0,0,0,0);
	}else if(opcode[2]=='\0'){
		/*
			or
			lw
			jr
			sw
		*/
	}else if(opcode[3]=='\0'){
		/*
		add
		and
		beq
		bne
		div		
		jal
		lui
		nop
		sll
		slt
		srl
		sub
		xor*/
	}else if(opcode[4]=='\0'){
		/*rotr
		addi
		bgtz
		blez
		mfhi
		mflo
		mult*/
	}else{
		/* syscall */
	}
}



void setBlocksSize(Instruction* instruction, char b0,char b1,char b2, char b3,char b4,char b5,char b6,char b7){
	instruction->b0=b0;
	instruction->b1=b1;
	instruction->b2=b2;
	instruction->b3=b3;
	instruction->b4=b4;
	instruction->b5=b5;
	instruction->b6=b6;
	instruction->b7=b7;
}