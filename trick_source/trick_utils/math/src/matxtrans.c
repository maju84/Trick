/*******************************************************************************
*                                                                              *
* Trick Simulation Environment Software                                        *
*                                                                              *
* Copyright (c) 1996,1997 LinCom Corporation, Houston, TX                      *
* All rights reserved.                                                         *
*                                                                              *
* Copyrighted by LinCom Corporation and proprietary to it. Any unauthorized    *
* use of Trick Software including source code, object code or executables is   *
* strictly prohibited and LinCom assumes no liability for such actions or      *
* results thereof.                                                             *
*                                                                              *
* Trick Software has been developed under NASA Government Contracts and        *
* access to it may be granted for Government work by the following contact:    *
*                                                                              *
* Contact: Charles Gott, Branch Chief                                          *
*          Simulation and Graphics Branch                                      *
*          Automation, Robotics, & Simulation Division                         *
*          NASA, Johnson Space Center, Houston, TX                             *
*                                                                              *
*******************************************************************************/
/* 
   PURPOSE: (Matrix times Matrix transpose) ASSUMPTIONS AND LIMITATIONS: ((Square matrix)) PROGRAMMERS: (((Les Quiocho) 
   (NASA/JSC) (Jan 1993) (v1.0) (Init Release))) */

/* 
 * $Id: matxtrans.c 49 2009-02-02 22:37:59Z lin $
 */

#include "../include/trick_math.h"

void matxtrans(double **prod,   /* Out: product of the two matrices */
               double **mat1,   /* In: matrix 1 */
               double **mat2,   /* In: matrix 2 */
               int n)
{                                      /* In: array size */

    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            prod[i][j] = 0.0;
            for (k = 0; k < n; k++) {
                prod[i][j] += mat1[i][k] * mat2[j][k];
            }
        }
    }

    return;

}
