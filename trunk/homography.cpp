//========================================================================
//  This software is free: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License Version 3,
//  as published by the Free Software Foundation.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  Version 3 in the file COPYING that came with this distribution.
//  If not, see <http://www.gnu.org/licenses/>.
//========================================================================
/*!
  \file    homography.cpp
  \brief   C++ Implementation: Homography
  \author  Guillermo Eduardo Torres, (C) 2012
*/
//========================================================================

#include "homography.h"

Homography::Homography() {
	// TODO Auto-generated constructor stub
}

Homography::~Homography() {
	// TODO Auto-generated destructor stub
}

void Homography::setImagePoints(CvPoint _p1, CvPoint _p2, CvPoint _p3, CvPoint _p4) {
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
	p4 = _p4;
}

void Homography::setRealPoints(CvPoint _u1, CvPoint _u2, CvPoint _u3, CvPoint _u4) {
	u1 = _u1;
	u2 = _u2;
	u3 = _u3;
	u4 = _u4;
}

void Homography::calcMH() {
	double A[]={
	   		p1.x,	p1.y,	1,	0,	0,	0,	-u1.x*p1.x,	-u1.x*p1.y,
			0,	0,	0,	p1.x,	p1.y,	1,	-p1.x*u1.y,	-p1.y*u1.y,
			p2.x,	p2.y,	1,	0,	0,	0,	-u2.x*p2.x,	-u2.x*p2.y,
			0,	0,	0,	p2.x,	p2.y,	1,	-p2.x*u2.y,	-p2.y*u2.y,
			p3.x,	p3.y,	1,	0,	0,	0,	-u3.x*p3.x,	-u3.x*p3.y,
			0,	0,	0,	p3.x,	p3.y,	1,	-p3.x*u3.y,	-p3.y*u3.y,
			p4.x,	p4.y,	1,	0,	0,	0,	-u4.x*p4.x,	-u4.x*p4.y,
			0,	0,	0,	p4.x,	p4.y,	1,	-p4.x*u4.y,	-p4.y*u4.y
			};
	//Definicion de la matriz U
	double U[8]={u1.x,u1.y,u2.x,u2.y,u3.x,u3.y,u4.x,u4.y};

	//Inicializamos las matrizes de OpenCV donde trabajaremos
	CvMat MA,MU;

	//Funcion que inicializa una matriz y asigna un Array a dicha matriz
	cvInitMatHeader( &MA, 8, 8, CV_64FC1, A,CV_AUTOSTEP );
	cvInitMatHeader( &MU, 8, 1, CV_64FC1, U,CV_AUTOSTEP );

	//creamos matriz inversa de A;
	CvMat MAinv;
	double Ainv[64];
	cvInitMatHeader( &MAinv, 8, 8, CV_64FC1, Ainv,CV_AUTOSTEP );
	cvInvert(&MA,&MAinv,CV_SVD);//cvmInvert(&MA,&MAinv);

	//obtenemos la matriz h
	CvMat Mh;
	double h[8];
	cvInitMatHeader( &Mh, 8, 1, CV_64FC1, h ,CV_AUTOSTEP);
	cvmMul(&MAinv,&MU,&Mh);

	//Creamos la matriz H;
	//double H[9];
	int i=0;
	for(i=0;i<8;i++)
		H[i]=h[i];
	H[8]=1.0;

	//Almacenamos la matriz H
	cvInitMatHeader(&MH,3,3,CV_64FC1,H,CV_AUTOSTEP);

	/*
	for (i=0; i<9; ++i)
		printf("H[%d] = %d\n", i, (int)H[i]);
	*/

}

CvPoint Homography::transPoint(CvPoint pixel) {
	//CvPoint2D32f aux;
	CvPoint aux;
	CvMat Maux,Maux1;

	//Creamos los arrays necesarios para almacenar los puntos
	double mp[]={pixel.x, pixel.y, 1};//Punto dado
	double mp1[3];//punto resultado de la equación p'=H·p

	//Inicializamos las estructuras de matrices de openCV
	cvInitMatHeader( &Maux, 3, 1, CV_64FC1, mp); //,CV_AUTOSTEP);
	cvInitMatHeader( &Maux1, 3, 1, CV_64FC1, mp1); //,CV_AUTOSTEP);

	//Realizamos la operación MH·Mp=Mp'
	cvmMul(&MH,&Maux,&Maux1);

	//El resultado devuelto será una matriz p1 de 3 filas y una columna, de donde el punto equvalente x'=p1[0]/p1[2] y'=p1[1]/p1[2]
	//p1[2] es el factor escala o como se definia en la funcion lambda

	//printf("mp[0]=%d, mp[1]=%d, mp[2]=%d\n", (int) mp[0], (int) mp[1], (int) mp[2]);
	//printf("Detectado mp1[0]=%d, mp1[1]=%d, mp1[2]=%d\n", (int) mp1[0], (int) mp1[1], (int) mp1[2]);

	aux.x=cvRound(mp1[0]/mp1[2]);
	aux.y=cvRound((mp1[1]/mp1[2])); //aux.y=(int)(480-(mp1[1]/mp1[2]));

	//printf("Detectado x=%d y=%d f=%d\n",aux.x,aux.y, (int) mp1[2]);
	//Devolvemos el punto obtenido
	return (aux);
}
