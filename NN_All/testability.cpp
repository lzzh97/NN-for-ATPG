
/***********************************************************************

		Copyright (C) 1991,
		Virginia Polytechnic Institute & State University

		This program was originally written by Mr. Hyung K. Lee
		under the supervision of Dr. Dong S. Ha, in the Bradley
		Department of Electrical Engineering, VPI&SU, in 1991.

		This program is released for research use only. This program,
		or any derivative thereof, may not be reproduced nor used
		for any commercial product without the written permission
		of the authors.

		For detailed information, please contact to

		Dr. Dong S. Ha
		Bradley Department of Electrical Engineering
		Virginia Polytechnic Institute & State University
		Blacksburg, VA 24061

		Ph.: (540) 231-4942
		Fax: (540) 231-3362
		E-Mail: ha@vt.edu
		Web: http://www.ee.vt.edu/ha

		REFERENCE:
		   H. K. Lee and D. S. Ha, "On the Generation of Test Patterns
		   for Combinational Circuits," Technical Report No. 12_93,
		   Dep't of Electrical Eng., Virginia Polytechnic Institute
		   and State University.

***********************************************************************/

/**************************** HISTORY **********************************
 
		atalanta: version 1.0   	 H. K. Lee, 8/15/1991
		atalanta: version 1.1   	 H. K. Lee, 10/5/1992
		atalanta: version 2.0   	 H. K. Lee, 6/30/1997
 
***********************************************************************/

/*---------------------------------------------------------------------- 
	testability.c
	Assign controllibility and observability.

	Uses depth of the gate as parameter.
-----------------------------------------------------------------------*/
#include "stdafx.h"
#include <stdio.h>
#include<limits.h>

#include "testability.h"

#include "parameter.h" 
#include "define.h"    
#include "macro.h"

extern GATEPTR *g_net;



#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

void preOrder(GATEPTR pGate){
	if(pGate->type!=PO){
		if(pGate->related_flag == FALSE){
			pGate->related_num += 1;
			pGate->related_flag = TRUE;
			for (int i = 0; i < pGate->outCount; i++){
				preOrder(pGate->outList[i]);
			}

		}
		
	}
}

void setGateTestability(int iNoGate) //set_testability
{
	register int i, j, iDepth;

	// int maxdpi2 = 0;

	for (int i = 0; i < iNoGate; i++)
	{
		GATEPTR pGate;
		pGate = g_net[i]; 
		if(pGate->type == PI) {
			for (int j = 0; j < iNoGate; j++)
				g_net[j]->related_flag = FALSE;
			preOrder(pGate);
		}
		
	}

	/* cont0 and cont1 */
	//cont0 & cont1 small is better!!


	for (i = 0; i < iNoGate; i++)
	{
		g_net[i]->ml_flag = 0;
		float cop = 1;
		switch (g_net[i]->type)
		{
		
		case 4:
			g_net[i]->cop = 0.5;
			break;
		case 0: 
			for (int j=0;j<g_net[i]->inCount;j++)
			{
				cop = cop*g_net[i]->inList[j]->cop;
			}
			g_net[i]->cop = cop;
			break;
		case 1: 
			for (int j=0;j<g_net[i]->inCount;j++)
			{
				cop = cop*g_net[i]->inList[j]->cop;
			}
			g_net[i]->cop = 1-cop;
			break;
		case 2: 
			for (int j=0;j<g_net[i]->inCount;j++)
			{
				cop = cop*(1-g_net[i]->inList[j]->cop);
			}
			g_net[i]->cop = 1-cop;
			break;
		case 3: 
			for (int j=0;j<g_net[i]->inCount;j++)
			{
				cop = cop*(1-g_net[i]->inList[j]->cop);
			}
			g_net[i]->cop = cop;
			break;
		
		
		default:
			g_net[i]->cop = g_net[i]->inList[0]->cop;
			break;
		}
		//printf("symbol:%s, cop:%f\n",g_net[i]->hash->symbol, g_net[i]->cop);



		if (g_net[i]->type==4)
		{
			g_net[i]->dpi2 = 0;
		}
		else
		{
			short minDpi=INFINITY;
			for (j = 0; j< g_net[i]->inCount; j++)
			{
				if (g_net[i]->inList[j]->dpi2<minDpi)
				{
					minDpi = g_net[i]->inList[j]->dpi2;
				}
			} 
			g_net[i]->dpi2 = minDpi+1;
		}

		

		if (is_free(g_net[i])|| is_head(g_net[i]))
		{
			g_net[i]->cont0 = 1;
			g_net[i]->cont1 = 1;
		}
		else
		{
			g_net[i]->cont1 = 0;
			iDepth = (-1);
			int cc0[g_net[i]->inCount];
			int cc1[g_net[i]->inCount];
			for (j = 0; j< g_net[i]->inCount; j++)
			{
				cc0[j] = g_net[i]->inList[j]->cont0;
				cc1[j] = g_net[i]->inList[j]->cont1;
				//fprintf(stderr,"inList: %c %c, type: %d\n", g_net[i]->inList[j]->hash->symbol[0], g_net[i]->inList[j]->hash->symbol[1], g_net[i]->type);

			}
			if (g_net[i]->type == 4)//PI
			{
				g_net[i]->cont0 = 1;
				g_net[i]->cont1 = 1;
			}
			if (g_net[i]->type == 0)// AND
			{	
				int cc0_min = INT_MAX;
				int cc1_sum = 0;
				for (j = 0; j< g_net[i]->inCount; j++)
				{
					cc0_min = min(cc0_min, cc0[j]);
					cc1_sum += cc1[j];
				}
				g_net[i]->cont0 = cc0_min+1;
				g_net[i]->cont1 = cc1_sum+1;
			}
			if (g_net[i]->type == 1)// NAND
			{
				int cc0_min = INT_MAX;
				int cc1_sum = 0;
				for (j = 0; j< g_net[i]->inCount; j++)
				{
					cc0_min = min(cc0_min, cc0[j]);
					cc1_sum += cc1[j];
				}
				g_net[i]->cont1 = cc0_min+1;
				g_net[i]->cont0 = cc1_sum+1;
			}

			if (g_net[i]->type == 2)// OR
			{
				int cc1_min = INT_MAX;
				int cc0_sum = 0;
				for (j = 0; j< g_net[i]->inCount; j++)
				{
					cc1_min = min(cc1_min, cc1[j]);
					cc0_sum += cc0[j];
				}
				g_net[i]->cont0 = cc0_sum+1;
				g_net[i]->cont1 = cc1_min+1;
			}

			if (g_net[i]->type == 3)// NOR
			{
				int cc1_min = INT_MAX;
				int cc0_sum = 0;
				for (j = 0; j< g_net[i]->inCount; j++)
				{
					cc1_min = min(cc1_min, cc1[j]);
					cc0_sum += cc0[j];
				}
				g_net[i]->cont1 = cc0_sum+1;
				g_net[i]->cont0 = cc1_min+1;
			}

			if (g_net[i]->type == 10)// NOT
			{
				g_net[i]->cont0 = cc1[0]+1;
				g_net[i]->cont1 = cc0[0]+1;
			}

			if (g_net[i]->type == 9)// BUFFER
			{
				g_net[i]->cont0 = cc0[0]+1;
				g_net[i]->cont1 = cc1[0]+1;
			}

			if (g_net[i]->type == 5)// XOR
			{
				int cc1_sum = 0;
				int cc0_sum = 0;
				int cc01_sum = 0;
				int cc10_sum = 0;
				cc1_sum = cc1[0]+cc1[1];
				cc0_sum = cc0[0]+cc0[1];
				cc01_sum = cc0[0]+cc1[1];
				cc10_sum = cc1[0]+cc0[1];
				g_net[i]->cont0 = min(cc1_sum, cc0_sum)+1;
				g_net[i]->cont1 = min(cc01_sum, cc10_sum)+1;
			}

			if (g_net[i]->type == 6)// XNOR
			{
				int cc1_sum = 0;
				int cc0_sum = 0;
				int cc01_sum = 0;
				int cc10_sum = 0;
				cc1_sum = cc1[0]+cc1[1];
				cc0_sum = cc0[0]+cc0[1];
				cc01_sum = cc0[0]+cc1[1];
				cc10_sum = cc1[0]+cc0[1];
				g_net[i]->cont1 = min(cc1_sum, cc0_sum)+1;
				g_net[i]->cont0 = min(cc01_sum, cc10_sum)+1;
			}

			if (g_net[i]->type == 20)// PO
			{
				
				g_net[i]->cont1 = g_net[i]->inList[0]->cont1;
				g_net[i]->cont0 = g_net[i]->inList[0]->cont0;
				//fprintf(stderr,"symbol:%s, dpi2:%i, dpi:%i\n", g_net[i]->hash->symbol, g_net[i]->dpi2, g_net[i]->dpi);
			}
			//g_net[i]->cont0 = iDepth + 1; //cont0 = max{pGate->inList[j]->cont0} + 1
			//g_net[i]->cont1 = g_net[i]->cont1 +1;
		}
		//g_net[i]->cont1 = g_net[i]->cont0;
		//fprintf(stderr,"symbol:%s, dpi:%i\n", g_net[i]->hash->symbol, g_net[i]->dpi2);
		// if (g_net[i]->dpi2>maxdpi2){
		// 	maxdpi2 = g_net[i]->dpi2;
		// }
	}
	// printf("maxdpi2:%i\n", maxdpi2);

	/* iDepth from output */
	//dpo small is better!!
	for (i = iNoGate - 1; i >= 0; i--)
	{
		if (g_net[i]->type == PO)
		{
			g_net[i]->dpo = 0;
		}
		else
		{
			iDepth = (-1);
			for (j = 0; j< g_net[i]->outCount; j++)
			{
				iDepth = max(iDepth, g_net[i]->outList[j]->dpo);
			}
			g_net[i]->dpo = iDepth + 1;  //dpo = max{pGate->outList[j]->dpo} + 1
		}
	}
}
