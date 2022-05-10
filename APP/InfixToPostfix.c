/*
 * infixToPostfix.c
 *
 *  Created on: Apr 27, 2022
 *      Author: taqwa
 */



#include "stdlib.h"
#include"../Services/STD_TYPES.h"
#include"InfixToPostfix.h"



struct stack
{
	s8 top;
	u8 capacity;
	s32* array;
};

struct stack* CreatStack(u8 capacity)
{

	struct stack* st= (struct stack*) malloc (sizeof(struct stack));

	if(!st)
	{
		return NULL;
	}

	else
	{
		st->top = -1;
		st->capacity =capacity;
		st->array = (s32*) malloc( sizeof(s32)* st->capacity );

		if(!st->array)
			return NULL;

	}

	return st;

}

u8 IsStackEmpty (struct stack* st)
{
	if(st->top == -1 )
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


s32 Currently (struct stack* st)
{
	return(st->array[st->top]);

}

u8 pop(struct stack* st , s32 *popedValue)
{
	if(st!= NULL)
	{

		if(!IsStackEmpty(st))

		{
			*popedValue=(st->array[st->top--]);
		}
		else
		{
			return 0;
		}

	}
	else
	{
		return 0;
	}

}
void push(struct stack* st , s32 op)
{
	st->array[++st->top] = op;

}

u8 IsOperand(u16 copy_u16Value)
{
	if((copy_u16Value>>15)!=1)
	{
		return 1;
	}

	else
	{
		return 0;
	}

}
s8 Periority(u8 operation)
{
	switch (operation)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	default :
		return -1;
	}


}


u8 infixToPostfix(u16 * exp, u8 Copy_u8ExpLength)
{
	s8 LOC_S8Exp_ArrIterator, LOC_S8Infix_ArrIndex;

	struct stack*st = CreatStack(Copy_u8ExpLength);
	if(!st)
	{
		return NULL;
	}
	for(LOC_S8Exp_ArrIterator=0, LOC_S8Infix_ArrIndex=-1 ;LOC_S8Exp_ArrIterator<=Copy_u8ExpLength; LOC_S8Exp_ArrIterator++ )
	{
		if(IsOperand(exp[LOC_S8Exp_ArrIterator]))
		{
			exp[++LOC_S8Infix_ArrIndex]=exp[LOC_S8Exp_ArrIterator];
		}
		else
		{
			while(!IsStackEmpty(st) && Periority(exp[LOC_S8Exp_ArrIterator]) <= Periority(Currently(st)))
			{
				s32 LOC_s32Temp=0;
				pop(st, &LOC_s32Temp);
				exp[++LOC_S8Infix_ArrIndex]=LOC_s32Temp;
			}

			push(st,exp[LOC_S8Exp_ArrIterator]);
		}


	}


	while(!IsStackEmpty(st))
	{
		s32 LOC_s32Temp=0;
		pop(st,&LOC_s32Temp);
		exp[++LOC_S8Infix_ArrIndex]=LOC_s32Temp;
	}


}


s32 CalcPostfix(u16 *exp , u8 Copy_u8ExpLength)
{
	s32 LOC_s32Result=0;
	u8 LOC_u8PostfixIterator=0;
	struct stack* st= CreatStack(Copy_u8ExpLength);
	if(!st)
	{
		return NULL;
	}

	for(LOC_u8PostfixIterator=0; LOC_u8PostfixIterator<=Copy_u8ExpLength;++LOC_u8PostfixIterator)
	{
		if(IsOperand(exp[LOC_u8PostfixIterator]))
		{
			push(st,exp[LOC_u8PostfixIterator]);
		}
		else
		{
			s32 LOC_s32Value1=0;
			s32 LOC_s32Value2=0;
			pop(st,&LOC_s32Value1);
			pop(st,&LOC_s32Value2);

			switch((u8)exp[LOC_u8PostfixIterator])
			{
			case '+' : push(st,LOC_s32Value2+LOC_s32Value1); break;
			case '-' : push(st,LOC_s32Value2-LOC_s32Value1); break;
			case '*' : push(st,LOC_s32Value2*LOC_s32Value1); break;
			case '/' : push(st,LOC_s32Value2/LOC_s32Value1); break;
			}


		}


	}

	pop(st,&LOC_s32Result);
	return LOC_s32Result;

}


s32 CALCEquation(u16 *exp , u8 Copy_u8ExpLength)
{
	infixToPostfix(exp, Copy_u8ExpLength);
	return CalcPostfix(exp , Copy_u8ExpLength);

}



