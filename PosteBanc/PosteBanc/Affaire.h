#pragma once
#include <qDebug>

#include "ui_PosteBanc.h"

class Affaire : public QObject
{
	int NumAffaire;
	int Capteur;
	int TempAcquisition;
	int Frequence;

	
public:
	Affaire(int, int, int, int);
	~Affaire();

	int getNumAffaire();
	int getCapteur();
	int getFrequence();
	int getTempAcquisition();

	void setValueAffaire(int, int, int, int);
	QString CreateJSON(int, float, float);
	QString JSONdelete(int);
	QString JSONupdate(int, int, int, int);

};

