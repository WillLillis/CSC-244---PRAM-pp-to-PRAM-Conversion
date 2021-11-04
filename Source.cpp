//Going to establish my own convention here and say that each instruction gets its own
//set of temporary register(s)/ memory cell(s) at the start of the RAM tape
//thus to convert our PRAM++ code to PRAM, we'll have to adjust each cell number reference by
//the number of temporary cells we have up front, as well as the z register that is always 0
//Let's say:
	//z: Cell 1
	//Increment: No temporary registers needed
	//Decrement: No temporary registers needed
	//Branch: No temporary registers needed
	//Copy: 1 temporary register needed->Cell 2
	//Addition: 1 temporary register needed->Cell 3
	//Monus: 1 temporary register needed->Cell 4
	//Multiplication: 2 temporary registers needed->Cell 5, Cell 6
	//Division: 3 temporary registers needed->Cell 7, Cell 8, Cell 9
	//Unconditional Jump: No temporary registers needed
	//Zero: No temporary registers needed

#include <iostream>
#include <string>
#include <vector>

/*
constexpr auto ZCELL = 1;
constexpr auto COPYCELL = 2;
constexpr auto ADDCELL = 3;
constexpr auto MONUSCELL = 4;
constexpr auto MULCELL1 = 5;
constexpr auto MULCELL2 = 6;
constexpr auto DIVCELL1 = 7;
constexpr auto DIVCELL2 = 8;
constexpr auto DIVCELL3 = 9;
constexpr auto OFFSET = 10;
constexpr auto BADINPUT = "ERROR: Invalid Input String\n";
*/

#define ZCELL 1
#define COPYCELL 2
#define ADDCELL 3
#define MONUSCELL 4
#define MULCELL1 5
#define MULCELL2 6
#define DIVCELL1 7
#define DIVCELL2 8
#define DIVCELL3 9
#define OFFSET 10
#define BADINPUT "ERROR: Invalid Input String\n"

class returnTuple
{
	public: 
		std::string getString();
		unsigned getnuminstructs();

		returnTuple()
		{
			converted = "";
			numinstructs = 0;
		}
		returnTuple(std::string words, unsigned number)
		{
			converted = words;
			numinstructs = number;
		}

	private:
		std::string converted;
		unsigned numinstructs;

};

std::string returnTuple::getString()
{
	return converted;
}

unsigned returnTuple::getnuminstructs()
{
	return numinstructs;
}

returnTuple ZeroConvert(unsigned convertedpos, unsigned x)
{
	unsigned numinstructs = 0;
	std::string converted = "#D";
	numinstructs++;

	for (unsigned i = 0; i < x + OFFSET; i++)
	{
		converted += "1";
	}

	converted += "#B";
	numinstructs++;
	
	for (unsigned i = 0; i < x + OFFSET; i++)
	{
		converted += "1";
	}
	
	converted += ",";

	for (unsigned i = 0; i < convertedpos + 3; i++)
	{
		converted += "1";
	}


	converted += "#B";
	numinstructs++;
	
	for (unsigned i = 0; i < ZCELL; i++)
	{
		converted += "1";
	}
	
	converted += ",";

	for (unsigned i = 0; i < convertedpos; i++)
	{
		converted += "1";
	}

	return  returnTuple(converted, numinstructs);
}

returnTuple CopyConvert(unsigned convertedpos, unsigned x, unsigned y)
{
	unsigned numinstructs = 0;
	std::string converted;
	returnTuple temp;
	
	temp = ZeroConvert(convertedpos + numinstructs, x);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();

	temp = ZeroConvert(convertedpos + numinstructs, COPYCELL);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < y + OFFSET; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 7; i++)
	{
		converted += "1";
	}

	converted += "#I";
	numinstructs++;

	for (unsigned i = 0; i < x + OFFSET; i++)
	{
		converted += "1";
	}

	converted += "#I";
	numinstructs++;

	for (unsigned i = 0; i < COPYCELL; i++)
	{
		converted += "1";
	}

	converted += "#D";
	numinstructs++;

	for (unsigned i = 0; i < y + OFFSET; i++)
	{
		converted += "1";
	}

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < ZCELL; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 2; i++)
	{
		converted += "1";
	}

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < COPYCELL; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 11; i++)
	{
		converted += "1";
	}

	converted += "#I";
	numinstructs++;

	for (unsigned i = 0; i < y + OFFSET; i++)
	{
		converted += "1";
	}

	converted += "#D";
	numinstructs++;

	for (unsigned i = 0; i < COPYCELL; i++)
	{
		converted += "1";
	}

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < ZCELL; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 7; i++)
	{
		converted += "1";
	}

	return returnTuple(converted, numinstructs);
}

std::string IncrementConvert(unsigned x)
{
	std::string converted = "#I";
	
	for (unsigned i = 0; i < x + OFFSET; i++)
	{
		converted += "1";
	}

	return converted;

}

std::string DecrementConvert(unsigned x)
{
	std::string converted = "#D";

	for (unsigned i = 0; i < x + OFFSET; i++)
	{
		converted += "1";
	}

	return converted;

}

std::string BranchConvert(unsigned convertedpos, unsigned x, unsigned c, bool originalcheck)
{
	std::string converted = "#B";

	for (unsigned i = 0; i < x + OFFSET; i++)
	{
		converted += "1";
	}

	converted += ",";
	if (originalcheck == true)
	{
		converted += "$";
		for (unsigned i = 0; i < c; i++)
		{
			converted += "1";
		}
	}
	else
	{
		for (unsigned i = 0; i < convertedpos + c; i++)
		{
			converted += "1";
		}
	}

	

	return converted;
}

returnTuple AdditionConvert(unsigned convertedpos, unsigned x, unsigned y)
{
	unsigned numinstructs = 0;
	std::string converted;
	returnTuple temp;

	temp = CopyConvert(convertedpos + numinstructs, ADDCELL, y);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();
	
	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < ADDCELL; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 5; i++)
	{
		converted += "1";
	}

	converted += "#D";
	numinstructs++;

	for (unsigned i = 0; i < ADDCELL; i++)
	{
		converted += "1";
	}

	converted += "#I";
	numinstructs++;

	for (unsigned i = 0; i < x + OFFSET; i++)
	{
		converted += "1";
	}

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < ZCELL; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 1; i++)
	{
		converted += "1";
	}

	return returnTuple(converted, numinstructs);

}

returnTuple MonusConvert(unsigned convertedpos, unsigned x, unsigned y)
{
	unsigned numinstructs = 0;
	std::string converted;
	returnTuple temp;

	temp = CopyConvert(convertedpos + numinstructs, MONUSCELL, y);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < MONUSCELL; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 5; i++)
	{
		converted += "1";
	}

	converted += "#D";
	numinstructs++;
	 
	for (unsigned i = 0; i < MONUSCELL; i++)
	{
		converted += "1";
	}

	converted += "#D";
	numinstructs++;

	for (unsigned i = 0; i < x + OFFSET; i++)
	{
		converted += "1";
	}

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < ZCELL; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 1; i++)
	{
		converted += "1";
	}

	return returnTuple(converted, numinstructs);
}

returnTuple MultiplicationConvert(unsigned convertedpos, unsigned x, unsigned y)
{
	unsigned numinstructs = 0;
	std::string converted;
	returnTuple temp;

	temp = CopyConvert(convertedpos + numinstructs, MULCELL1, x);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();

	temp = CopyConvert(convertedpos + numinstructs, MULCELL2, y);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < MULCELL2; i++)
	{
		converted += "1";
	}
	
	converted += ",";

	for (unsigned i = 0; i < convertedpos + 6; i++)
	{
		converted += "1";
	}

	converted += "#D";
	numinstructs++;

	for (unsigned i = 0; i < MULCELL2; i++)
	{
		converted += "1";
	}

	temp = AdditionConvert(convertedpos + numinstructs, x, MULCELL1);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < ZCELL; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 2; i++)
	{
		converted += "1";
	}

	return returnTuple(converted, numinstructs);
}

returnTuple DivisionConvert(unsigned convertedpos, unsigned x, unsigned y)
{
	unsigned numinstructs = 0;
	std::string converted;
	returnTuple temp;

	temp = CopyConvert(convertedpos + numinstructs, DIVCELL1, x);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();

	temp = CopyConvert(convertedpos + numinstructs, DIVCELL2, y);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();

	temp = ZeroConvert(convertedpos + numinstructs, x);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < DIVCELL1; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 14; i++)
	{
		converted += "1";
	}

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < DIVCELL2; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 14; i++)
	{
		converted += "1";
	}

	temp = CopyConvert(convertedpos + numinstructs, DIVCELL3, DIVCELL2);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();

	converted += "#D";
	numinstructs++;

	for (unsigned i = 0; i < DIVCELL2; i++)
	{
		converted += "1";
	}

	converted += "#D";
	numinstructs++;

	for (unsigned i = 0; i < DIVCELL1; i++)
	{
		converted += "1";
	}

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < DIVCELL2; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 11; i++)
	{
		converted += "1";
	}

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < DIVCELL1; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 14; i++)
	{
		converted += "1";
	}

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < ZCELL; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 6; i++)
	{
		converted += "1";
	}

	converted += "I";
	numinstructs++;

	for (unsigned i = 0; i < x + OFFSET; i++)
	{
		converted += "1";
	}

	temp = CopyConvert(convertedpos + numinstructs, DIVCELL2, DIVCELL3);
	converted += temp.getString();
	numinstructs += temp.getnuminstructs();

	converted += "#B";
	numinstructs++;

	for (unsigned i = 0; i < ZCELL; i++)
	{
		converted += "1";
	}

	converted += ",";

	for (unsigned i = 0; i < convertedpos + 6; i++)
	{
		converted += "1";	
	}

	return returnTuple(converted, numinstructs);
}

std::string JumpConvert(unsigned convertedpos, unsigned c)
{
	std::string converted = "#B";

	for (unsigned i = 0; i < ZCELL; i++)
	{
		converted += "1";
	}

	converted += ",";
	converted += "$";

	for (unsigned i = 0; i < c; i++)
	{
		converted += "1";
	}

	return converted;
}

unsigned PRAMppInstructionCounter(const char inputcode[])
{
	unsigned instructioncounter = 0;
	unsigned i = 0;

	while (inputcode[i] != '\0')
	{
		if (inputcode[i] == '#')
		{
			instructioncounter++;
		}
		i++;
	}

	return instructioncounter;
}

std::string PRAMpptoPRAM(const char inputcode[])
{
	std::string outputcode;
	unsigned arg1 = 0;
	unsigned arg2 = 0;

	//ith entry in the translation vector holds the # instruction in the converted string
	//for the ith entry in the unconverted string
	std::vector<unsigned> translation(PRAMppInstructionCounter(inputcode)+1);
	translation[0] = 0; //first instruction will start with the first instruction in the converted string 
	returnTuple temp;

	unsigned i = 0;
	unsigned j = 0;
	while (inputcode[i] != '\0')
	{
		arg1 = arg2 = 0;
		if (inputcode[i] == '#')
		{
			i++; //do nothing, go to next character to read instruction label if it's there
		}

		//All the possible instructions
		//Increment
		else if (inputcode[i] == 'I')
		{
			i++;
			while (inputcode[i] == '1')
			{
				arg1++;
				i++;
			}
			outputcode += IncrementConvert(arg1);
			translation[j+1] = translation[j] + 1;
			j++;
		}
		//Decrement OR Division
		else if (inputcode[i] == 'D')
		{
			//Division
			if (inputcode[i + 1] == 'I' && inputcode[i + 2] == 'V')
			{
				i += 3;
				while (inputcode[i] == '1')
				{
					arg1++;
					i++;
				}
				if (inputcode[i] == ',')
				{
					i++;
					while (inputcode[i] == '1')
					{
						arg2++;
						i++;
					}
				}
				else
				{
					return BADINPUT;
				}
				temp = DivisionConvert(translation[j], arg1, arg2);
				outputcode += temp.getString();
				translation[j + 1] = translation[j] + temp.getnuminstructs();
				j++;
			}
			//Decrement
			else
			{
				i++;
				while (inputcode[i] == '1')
				{
					arg1++;
					i++;
				}
				outputcode += DecrementConvert(arg1);
				translation[j + 1] = translation[j] + 1;
				j++;
			}
		}
		//Branch
		// the way I wrote this you can check against/ branch to the "0th instruction"
		else if (inputcode[i] == 'B')
		{
			i++;
			while (inputcode[i] == '1')
			{
				arg1++;
				i++;
			}
			if (inputcode[i] == ',')
			{
				i++;
				while (inputcode[i] == '1')
				{
					arg2++;
					i++;
				}
			}
			else
			{
				return BADINPUT;
			}
			outputcode += BranchConvert(translation[j], arg1, arg2, true);
			translation[j+1] = translation[j] + 1;
			j++;
		}
		//Zero
		else if (inputcode[i] == 'Z')
		{
			if (inputcode[i + 1] == 'R' && inputcode[i + 2] == 'O')
			{
				i += 3;
				while (inputcode[i] == '1')
				{
					arg1++;
					i++;
				}
			}
			else
			{
				return BADINPUT;
			}
			temp = ZeroConvert(translation[j], arg1);
			outputcode += temp.getString();
			translation[j + 1] = translation[j] + temp.getnuminstructs();
		}
		//Copy
		else if (inputcode[i] == 'C')
		{
			if (inputcode[i + 1] == 'P' && inputcode[i + 2] == 'Y')
			{
				i += 3;
				while (inputcode[i] == '1')
				{
					arg1++;
					i++;
				}
				if (inputcode[i] == ',')
				{
					i++;
					while (inputcode[i] == '1')
					{
						arg2++;
						i++;
					}
				}
			}
			else
			{
				return BADINPUT;
			}
			temp = CopyConvert(translation[j], arg1, arg2);
			outputcode += temp.getString();
			translation[j + 1] = translation[j] + temp.getnuminstructs();
			j++;
		}
		//Addition
		else if (inputcode[i] == 'A')
		{
			if (inputcode[i + 1] == 'D' && inputcode[i + 2] == 'D')
			{
				i += 3;
				while (inputcode[i] == '1')
				{
					arg1++;
					i++;
				}
				if (inputcode[i] == ',')
				{
					i++;
					while (inputcode[i] == '1')
					{
						arg2++;
						i++;
					}
				}
				else
				{
					return BADINPUT;
				}
			}
			else
			{
				return BADINPUT;
			}
			temp = AdditionConvert(translation[j], arg1, arg2);
			outputcode += temp.getString();
			translation[j + 1] = translation[j] + temp.getnuminstructs();
			j++;
		}
		//Monus OR Multiplication
		else if (inputcode[i] == 'M')
		{
			//Monus
			if (inputcode[i+1] == 'O' && inputcode[i + 2] == 'N')
			{
				i += 3;
				while (inputcode[i] == '1')
				{
					arg1++;
					i++;
				}
				if (inputcode[i] == ',')
				{
					i++;
					while (inputcode[i] == '1')
					{
						arg2++;
						i++;
					}
				}
				else
				{
					return BADINPUT;
				}
				temp = MonusConvert(translation[j], arg1, arg2);
				outputcode += temp.getString();
				translation[j + 1] = translation[j] + temp.getnuminstructs();
				j++;
			}
			//Multiplication
			else if (inputcode[i+1] == 'U' && inputcode[i+2] == 'L')
			{
				i += 3;
				while (inputcode[i] == '1')
				{
					arg1++;
					i++;
				}
				if (inputcode[i] == ',')
				{
					i++;
					while (inputcode[i] == '1')
					{
						arg2++;
						i++;
					}
				}
				else
				{
					return BADINPUT;
				}
				temp = MultiplicationConvert(translation[j], arg1, arg2);
				outputcode += temp.getString();
				translation[j + 1] = translation[j] + temp.getnuminstructs();
				j++;
			}
			//Other input
			else
			{
				return BADINPUT;
			}
		}
		//Jump
		else if (inputcode[i] == 'J')
		{
			if (inputcode[i + 1] == 'M' && inputcode[i + 2] == 'P')
			{
				i += 3;
				while (inputcode[i] == '1')
				{
					arg1++;
					i++;
				}
				outputcode += JumpConvert(translation[j], arg1);
				translation[j + 1] = translation[j] + 1;
				j++;
			}
		}
		//Bad Input
		else
		{
			return BADINPUT;
		}
	}

	outputcode += '\0';

	//std::cout << "Output: " << outputcode << std::endl;



	//Now for the second pass to fix args for jump commands
	//go through, if you encounter a $, count the number of ones after it, say x
	//take out $, make it so translation[x] 1's are there (insert difference?)
	//and we're done?
	i = j = 0;

	while (outputcode[i] != '\0')
	{
		arg1 = arg2 = 0;
		if (outputcode[i] == '$')
		{
			i++;
			//loop through the 1's
			while (outputcode[i] == '1')
			{
				arg1++;
				i++;
			}
			//go back to the $
			while (outputcode[i] != '$')
			{
				i--;
			}
			outputcode.erase(i, 1); //take the $ out
			outputcode.insert(i, translation[arg1]-arg1, '1');
		}
		else
		{
			i++;
		}
	}

	return outputcode;
}


int main()
{
	//std::string testin = "#I1#I11#I11111#I11#D1";
	//std::string testin = "#MUL1,1";
	//std::string testin = "#I1#B11,1";
	std::string testin = "#B11#D1";
	std::string testout;

	testout = PRAMpptoPRAM(testin.c_str());

	std::cout << "Input String (PRAM++): " << std::endl << testin << std::endl;
	std::cout << "Output String (PRAM++): " << std::endl << testout << std::endl;

	return 0;
}