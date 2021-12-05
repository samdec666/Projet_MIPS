#include "InstructionCompiler.h"


/*
On suppose :
	le texte instruction est valide
	la struct Instruction est initialisée
*/
void textInstructionToOpcode(char* textInstruction, Instruction *instruction){
	char opcode[8];
	getOperationCodeText(textInstruction,opcode);

	if(opcode[1]=='\0' && opcode[0]=='j'){
		/* alors forcément instruction 'j' 
			j -> 6 premiers bits a 000010
			donc code[0] = 000010xx
		*/
		/*instruction->code[0] = (instruction->code[0]&0x03) + (J_CODE<<2);*/
		setNormalOpCode(instruction, J_CODE);
		instruction->id = J_ID;

		setBlocksSize(instruction,6,26,0,0,0,0,0,0);
	}else if(opcode[2]=='\0'){
		/*
			or
			lw
			jr
			sw
		*/

		if (!strcmp("or",opcode)){
			setSpecialOpCode(instruction, OR_CODE);
			instruction->id = OR_ID;
			setBlocksSize(instruction,6,5,5,5,5,6,0,0);
		}
		else if (!strcmp("lw",opcode)){
			setNormalOpCode(instruction, LW_CODE);
			instruction->id = LW_ID;
			setBlocksSize(instruction,6,5,5,16,0,0,0,0);
		}
		else if (!strcmp("jr",opcode)){
			setSpecialOpCode(instruction, JR_CODE);
			instruction->id = JR_ID;
			setBlocksSize(instruction,6,5,10,5,6,0,0,0);
		}
		else if (!strcmp("sw",opcode)){
			setNormalOpCode(instruction, SW_CODE);
			instruction->id = SW_ID;
			setBlocksSize(instruction,6,5,5,16,0,0,0,0);
		}
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

		if (!strcmp("add",opcode)){
			setSpecialOpCode(instruction, ADD_CODE);
			instruction->id = ADD_ID;
			setBlocksSize(instruction,6,5,5,5,5,6,0,0);
		}
		else if (!strcmp("and",opcode)){
			setSpecialOpCode(instruction, AND_CODE);
			instruction->id = AND_ID;
			setBlocksSize(instruction,6,5,5,5,5,6,0,0);
		}
		else if (!strcmp("beq",opcode)){
			setNormalOpCode(instruction, BEQ_CODE);
			instruction->id = BEQ_ID;
			setBlocksSize(instruction,6,5,5,16,0,0,0,0);
		}
		else if (!strcmp("bne",opcode)){
			setNormalOpCode(instruction, BNE_CODE);
			instruction->id = BNE_ID;
			setBlocksSize(instruction,6,5,5,16,0,0,0,0);
		}
		else if (!strcmp("div",opcode)){
			setSpecialOpCode(instruction, DIV_CODE);
			instruction->id = DIV_ID;
			setBlocksSize(instruction,6,5,5,10,6,0,0,0);
		}
		else if (!strcmp("jal",opcode)){
			setNormalOpCode(instruction, JAL_CODE);
			instruction->id = JAL_ID;
			setBlocksSize(instruction,6,26,0,0,0,0,0,0);
		}
		else if (!strcmp("lui",opcode)){
			setNormalOpCode(instruction, LUI_CODE);
			instruction->id = LUI_ID;
			setBlocksSize(instruction,6,5,5,16,0,0,0,0);
		}
		else if (!strcmp("nop",opcode)){
			setSpecialOpCode(instruction, NOP_CODE);
			instruction->id = NOP_ID;
			setBlocksSize(instruction,6,5,5,5,5,6,0,0);
		}
		else if (!strcmp("sll",opcode)){
			setSpecialOpCode(instruction, SLL_CODE);
			instruction->id = SLL_ID;
			setBlocksSize(instruction,6,5,5,5,5,6,0,0);
		}
		else if (!strcmp("slt",opcode)){
			setSpecialOpCode(instruction, SLT_CODE);
			instruction->id = SLT_ID;
			setBlocksSize(instruction,6,5,5,5,5,6,0,0);
		}
		else if (!strcmp("srl",opcode)){
			setSpecialOpCode(instruction, SRL_CODE);
			instruction->id = SRL_ID;
			setBlocksSize(instruction,6,4,1,5,5,5,6,0);
		}
		else if (!strcmp("sub",opcode)){
			setSpecialOpCode(instruction, SUB_CODE);
			instruction->id = SUB_ID;
			setBlocksSize(instruction,6,5,5,5,5,6,0,0);
		}
		else if (!strcmp("xor",opcode)){
			setSpecialOpCode(instruction, XOR_CODE);
			instruction->id = XOR_ID;
			setBlocksSize(instruction,6,5,5,5,5,6,0,0);
		}
	}else if(opcode[4]=='\0'){
		/*rotr
		addi
		bgtz
		blez
		mfhi
		mflo
		mult*/

		if (!strcmp("rotr",opcode)){
			setSpecialOpCode(instruction, ROTR_CODE);
			instruction->id = ROTR_ID;
			setBlocksSize(instruction,6,4,1,5,5,5,6,0);
		}
		else if (!strcmp("addi",opcode)){
			setNormalOpCode(instruction, ADDI_CODE);
			instruction->id = ADDI_ID;
			setBlocksSize(instruction,6,5,5,16,0,0,0,0);
		}
		else if (!strcmp("bgtz",opcode)){
			setNormalOpCode(instruction, BGTZ_CODE);
			instruction->id = BGTZ_ID;
			setBlocksSize(instruction,6,5,5,16,0,0,0,0);
		}
		else if (!strcmp("blez",opcode)){
			setNormalOpCode(instruction, BLEZ_CODE);
			instruction->id = BLEZ_ID;
			setBlocksSize(instruction,6,5,5,16,0,0,0,0);
		}
		else if (!strcmp("mfhi",opcode)){
			setSpecialOpCode(instruction, MFHI_CODE);
			instruction->id = MFHI_ID;
			setBlocksSize(instruction,6,10,5,5,6,0,0,0);
		}
		else if (!strcmp("mflo",opcode)){
			setSpecialOpCode(instruction, MFLO_CODE);
			instruction->id = MFLO_ID;
			setBlocksSize(instruction,6,10,5,5,6,0,0,0);
		}
		else if (!strcmp("mult",opcode)){
			setSpecialOpCode(instruction, MULT_CODE);
			instruction->id = MULT_ID;
			setBlocksSize(instruction,6,5,5,10,6,0,0,0);
		}
	}else{
		/* syscall */
		if (!strcmp("syscall",opcode)){
			setSpecialOpCode(instruction, SYSCALL_CODE);
			instruction->id = SYSCALL_ID;
			setBlocksSize(instruction,6,20,6,0,0,0,0,0);
		}
	}
}

void writeInstructionOperands(Instruction *inst, char *isnt_str){
	/*pasteValue(Instruction* instruction, int field,Byte* value,int dim) */
	char operandes[8][16];
	Byte imm[2];
	Byte reg;

	param_to_tab(operandes,isnt_str);
	switch(inst->id){
		case ADD_ID:
			/*ADD rd(0), rs(1), rt(2)*/
			/*SPECIAL | rs(1) | rt(2) | rd(0) | 0 | ADD*/

			reg = registerToByte(operandes[1]);
			pasteValue(inst,1,&reg,1);
						
			reg = registerToByte(operandes[2]);
			pasteValue(inst,2,&reg,1);

			reg = registerToByte(operandes[0]);
			pasteValue(inst,3,&reg,1);
			break;

		case ADDI_ID:
			/*ADDI rt(0), rs(1), imm(2)*/
			/*ADDI | rs(1) | rt(0) | imm(2)*/

			reg = registerToByte(operandes[1]);
			pasteValue(inst,1,&reg,1);
						
			reg = registerToByte(operandes[0]);
			pasteValue(inst,2,&reg,1);

			/* write imm */

			break;
	}
}

/*
Description:
	met les 6 premiers bits de l'instruction avec opCode en conservant les valeurs d'origine pour le reste
parametre:
	instruction - l'instruction en paramtre a changer
	opCode - le code instruction a insérer en début
return:
	void
error :
	si instruction pas initialiser
*/
void setNormalOpCode(Instruction *instruction, Byte opCode){
	instruction->code[0] = (instruction->code[0]&0x03) + (opCode<<2);
}

/*
Description:
	met les 6 premiers bits de l'instruction a 0 et les 6 derniers avec opCode en conservant les valeurs d'origine pour le reste
parametre:
	instruction - l'instruction en paramtre a changer
	opCode - le code instruction a insérer en fin
return:
	void
error :
	si instruction pas initialiser
*/
void setSpecialOpCode(Instruction *instruction, Byte opCode){
	instruction->code[3] = (instruction->code[0]&0xC0) + opCode;
	setNormalOpCode(instruction,0);
}

/*
Description:
	Récupere tout les char jusqu'au premier espace dan l'instruction en  parametre
et les mets dans res. exemple pour 'addiu $val, $res, 10' va donner 'addiu\0' 
parametre:
	textInstruction - l'instruction complete dans un tableau de char (fin \0)
	res - tableau de char qui va stocker l'instruction au moin de taille 8 (fin \0)
return:
	void
erreur:
	si res est trop petit ou textInstruction n'est pas valide
*/
void getOperationCodeText(char* textInstruction, char* res){
	int i=0;
	while(textInstruction[i]!=' '){
		res[i]=textInstruction[i];
		i++;
	}
	res[i]='\0';
	toLowerCase(res); /* instruction en lower case */
}

/*
Description:
	transforme une chaine de caractères en lower case
parametre:
	text - chaine de caractère se finissant par \0
return:
	void
erreur:
	si la chaine n'est pas terminée par \0
*/
void toLowerCase(char *text){
	char *cp = text;
	while((*cp)!='\0'){
		if((*cp)>= 'A' && (*cp)<='Z'){
			(*cp)=(*cp)+32;
		}

		cp++;
	}
}


/*
Description:
	remplie les paramètres block de l'instruction
parametre:
	Instruction* instruction - l'instruction qui va etre modifiée
	char bn - les tailles des blocks
return: 
	void
erreur:
	si l'instruction pas initialisée
*/
void setBlocksSize(Instruction* instruction, Byte b0,Byte b1,Byte b2, Byte b3,Byte b4,Byte b5,Byte b6,Byte b7){
	instruction->b[0]=b0;
	instruction->b[1]=b1;
	instruction->b[2]=b2;
	instruction->b[3]=b3;
	instruction->b[4]=b4;
	instruction->b[5]=b5;
	instruction->b[6]=b6;
	instruction->b[7]=b7;
}

/*
Description:
	prend en parametre une instruction dont les tailles b[n] sont initialisées, et un numéro de block
	la valeur value de dim octet sera écrite dans le code de la struct Instruction dans zone qui luis est associée
	avec la taille correspondante dans b[n].
parametre:
	instruction - l'insqtruction dont les valeurs b[n] sont intialisée ainsi que le code ou la zone dédiée
	a la valeur qu'on veut écrire soit vide de données
	field - le numéro de block qu'on souhaite remplire
	value - la valeur que le block va prendre tableau de 8*dim bit soit dim char tell que 8*dim > b[field]
	dim - taille du tableau value en octet
erreurs:
	si instruction n'est pas initialisée, alors il y a risque de crash aussi la zone dans le code de 
	l'instruction ou l'on veut écrire doit nécéssairement etre vide en risque de corrompre tout le code.
	la taille de value ne provoquera pas d'exeption, la fonction tronquera le nombre automatiquement.
*/
void pasteValue(Instruction* instruction, int field,Byte* value,int dim){
	/* size in bit of the value not necessarly a multiple of 8 */
	int size=instruction->b[field];
	/* position wanted on the instruction code */
	int pos = 0,i=0;

	/* temp values */
	Byte val[4];
	Byte mask1[4];
	Byte mask2[4];

	/* calculate position in bit in the 32bit code */
	for(i=0;i<field;i++){
		pos += instruction->b[i];
	}

	/* init mask at 0xFFFFFFFF and val at 0x00000000 */
	for(i=0;i<4;i++){
		mask1[i] = 0xFF;
		mask2[i] = 0xFF;
		val[i]=0;
	}

	/* met value dans val (taille value =< 4) */
	for(i=0;i<dim;i++){
		printf("%02x\n", value[i]);
		/* on doit écrire a la fin car les shift sont appliqués dans le sens 
		inverse aux indices des tableaux */
		val[i+(4-dim)]=value[i];
	}

	/* positionne la valeur a la fin tel que le bit de poid fort soit le premier dans la chaine */
	shiftLNBit(val, 32-size, 4);
	/* décale val pour etre a la bonne position dans le code */
	shiftRNBit(val, pos,4);

	/* calcul les mask pour l'insertion dans le code */
	shiftRNBit(mask1, pos,4);
	shiftLNBit(mask2, 32-(pos+size), 4);

	/* insertion dans le code */
	for(i=0;i<4;i++){
		instruction->code[i] += mask1[i] &mask2[i]&val[i];
	}
}
/*
Description:
	place les arguments dans une matrice de caracteres
parametre:
	tab - tableu bidimensionnel de char
	instruction - pointeur vers char
return:
	void
*/
void param_to_tab(char tab[8][16],char *instruction){
	int index = 0;
	int i =0;
	int j=0;
	int taille = strlen(instruction);
	while(index < taille && instruction[index] != ','){
	    index++;  /* on passe l'instruction pour aller aux parametres */
	} 
	index++;
	/*tant qu'on est pas à la fin de l'instruction alors il reste des paramètres*/
	while(index<taille){  
		j=0;
		/*on récupère le paramètre jusqu'au prochain ','*/
		while(index < taille && instruction[index] != ','){   
			tab[i][j] = instruction[index];
			j++;
			index++;
		}
		tab[i][j] ='\0';
		/*on saute la virgule*/
		if (instruction[index]==',')
			index++;
		i++;
	}
	/*on definit le reste des lignes avec une simple '\0' */
	while(i<8){
		tab[i][0]='\0';
		i++;
	}
}
/*
Description:
	transforme une chaine de caractere en binaire  -> "11" = 11
parametre:
	val - chaine de caractere
return:
	Byte
*/
Byte registerToByte(char *val){

	int taille =strlen(val);
    int dizaine = 1;
    int index =0;
    Byte resultat =0;
    if (val[0] == '$')
    	index++;
    /*tant qu'on à pas finit de lire le nombre*/
    while(index<taille && val[index] != ')'){
    	/*on ajoute au résultat la valeur décimale correspondante au caractere fois la bonne dizaine*/
        resultat+=dizaine*(val[taille -1 -index]-48);

        dizaine *=10;
        index++;
    }
    return resultat;
}



/*
Description:
  retourne la valeur du registre et met dans offset la valeur de l'offset.
  example si on a "200($1)" => offset=200 et return = 1
parametre:
	str - chaine de caractere
	offset - chaine de caractere
return:
	Byte
*/
Byte indirectRegisterToByte(char *str, int *offset){
	/*on recupère l'offset*/
	int taille =strlen(str);
	int pos =0;


    int dizaine = 1;
    int index =0;
    *offset = 0;

    while(pos<taille & str[pos] != '(')
    	pos++;

    /*tant qu'on à pas finit de lire le nombre*/
    while(index<pos){
  
        *offset+=dizaine*(str[pos -1 -index]-48);

        dizaine *=10;
        index++;
    }
    index++;
    Byte *ptr = str + index;

    return (registerToByte(ptr));
}