#include "PosteBanc.h"

#include <qDebug>

PosteBanc::PosteBanc(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	socket = new QTcpSocket(this);

	QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));

}

void PosteBanc::ConnectServeur()
{
	QString ip = ui.AdresseServ->text();
	QString port = ui.PortServ->text();

	bool ok;
	int portAsInt = port.toInt(&ok);

	socket->connectToHost(ip, portAsInt);

	// Si le serveur ne r�pond pas on affiche un message d'�rreur
	if (!socket->waitForConnected(5000))
	{
		ui.ErreurServeur->setText("Can't connect to server");
	}
}

void PosteBanc::onSocketConnected()
{
	ui.ConnexionServeur->setEnabled(false);
	ui.InformationTest->setEnabled(true);
	ui.ErreurServeur->setText("");

	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDeconnected()));
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
}

void PosteBanc::onSocketDeconnected()
{
	ui.ConnexionServeur->setEnabled(true);
	ui.InformationTest->setEnabled(false);
}

void PosteBanc::onSocketReadyRead()
{
	// On lit le message re�ue et d�coupe les informations pour les exploiter
	QByteArray data = socket->read(socket->bytesAvailable());
	QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
	QJsonObject jsonObject = jsonResponse.object();

	// On extrait Les valeur et on les place dans variable
	int NumAffaire = jsonObject.value("affaire").toInt();
	int Capteur = jsonObject.value("capteur").toInt();
	int Frequence = jsonObject.value("frequence").toInt();
	int TempAcquisition = jsonObject.value("temp").toInt();

	//Creation du graph a l'aide du temp d'acquisition totale
	CreateGraph(TempAcquisition);


	// Utilisation d'un setteur pour stocker les param�tre
	affaire->setValueAffaire(NumAffaire, Capteur, Frequence, TempAcquisition);

	// Modification de l'IHM
	ChangeValueIHM();

	ui.CancelAffaire->setEnabled(true);
	ui.ChangeValueAffaire->setEnabled(true);
	ui.BouttonAffaire->setEnabled(true);

	ui.CapteurLine->setEnabled(false);
	ui.FrequenceLine->setEnabled(false);
	ui.tempAcquisitionLine->setEnabled(false);
}

/*---------------------------------------------------------------------------------------------------------------*/

void PosteBanc::EnableChangeValue()
{
	// Modification de l'ihm pour modifier les param�tres
	ui.CancelAffaire->setEnabled(false);
	ui.ChangeValueAffaire->setEnabled(false);
	ui.BouttonAffaire->setEnabled(false);
	ui.CapteurLine->setEnabled(true);
	ui.FrequenceLine->setEnabled(true);
	ui.tempAcquisitionLine->setEnabled(true);
	ui.ValideNewParemetre->setEnabled(true);
}

void PosteBanc::ChangeValueAffaire()
{
	int NewValueCapteur = ui.CapteurLine->text().toInt();
	int NewValueFrequence = ui.FrequenceLine->text().toInt();
	int NewValueTempAcquisition = ui.tempAcquisitionLine->text().toInt();

	int NumAffaire = affaire->getNumAffaire();

	//
	QString AffaireUpdateJSON = affaire->JSONupdate(NumAffaire, NewValueCapteur, NewValueFrequence, NewValueTempAcquisition);

	//Envoie nouveaux param�tre a BDD pour la modifier
	if (socket->state() == QTcpSocket::ConnectedState) {

		socket->write(AffaireUpdateJSON.toLatin1());

	}

	// Setteur pour changer les param�tre
	affaire->setValueAffaire(NumAffaire, NewValueCapteur, NewValueFrequence, NewValueTempAcquisition);
	ChangeValueIHM();

	ui.ValideNewParemetre->setEnabled(false);

	ui.CancelAffaire->setEnabled(true);
	ui.ChangeValueAffaire->setEnabled(true);
	ui.BouttonAffaire->setEnabled(true);
	ui.CapteurLine->setEnabled(false);
	ui.FrequenceLine->setEnabled(false);
	ui.tempAcquisitionLine->setEnabled(false);

}

void PosteBanc::ChangeValueIHM()
{
	// Modification IHM pour nouveaux param�tre
	int Affaire = this->affaire->getNumAffaire();
	int Capteur = this->affaire->getCapteur();
	int Frequence = this->affaire->getFrequence();
	int TempAcquisition = this->affaire->getTempAcquisition();

	ui.LabelAffaire->setText(QString::number(Affaire));
	ui.LabelCapteur->setText(QString::number(Capteur));
	ui.LabelFrequence->setText(QString::number(Frequence));
	ui.LabelAcquisition->setText(QString::number(TempAcquisition));

}

void PosteBanc::DeleteAffaire()
{
	int NumAffaireDelete = affaire->getNumAffaire();
	QString AffaireDeleteJSON = affaire->JSONdelete(NumAffaireDelete);

	// Envoie a la BDD pour supression de l'affaire
	if (socket->state() == QTcpSocket::ConnectedState) {

		socket->write(AffaireDeleteJSON.toLatin1());

	}

	this->affaire = new Affaire(0, 0, 0, 0);

	ChangeValueIHM();

	ui.CancelAffaire->setEnabled(false);
	ui.ChangeValueAffaire->setEnabled(false);
	ui.BouttonAffaire->setEnabled(false);
}

/*---------------------------------------------------------------------------------------------------------------*/



void PosteBanc::StartRead()
{
	ui.ConnexionServeur->setEnabled(false);
	ui.InformationTest->setEnabled(false);

	//R�cup�ration param�tres
	int FrequenceLecture = this->affaire->getFrequence();
	int TempAcquisitionLecture = this->affaire->getTempAcquisition();
	int TempAcquisitionLectureSecond = TempAcquisitionLecture * 1000 + FrequenceLecture;

	arduino.ArduinoConnexion();

	//Timer de Fr�quence
	Frequence = new QTimer(this);
	QObject::connect(Frequence, SIGNAL(timeout()), this, SLOT(Mesure()));
	Frequence->start(FrequenceLecture);

	//Timer temp total
	TempAcquisition = new QTimer(this);
	QObject::connect(TempAcquisition, SIGNAL(timeout()), this, SLOT(StopTimer()));
	TempAcquisition->start(TempAcquisitionLectureSecond);

}

void PosteBanc::Mesure()
{
	arduino.ArduinoSendRequest();
}



void PosteBanc::SendData()
{
	int TempAcquisition = affaire->getTempAcquisition();
	CreateGraph(TempAcquisition);

	// Boucle qui parcourt le tableaux de donn�e pour tous les envoyer
	int TailleTableau = arduino.getListSize();

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	//Cr�ation premi�re ligne
	QLineSeries *LigneValueEntre = new QLineSeries(chart);
	//Param�tre du pinceaux
	QPen penEntre = LigneValueEntre->pen();
	penEntre.setWidth(3);
	penEntre.setBrush(QBrush("orange"));
	LigneValueEntre->setPen(penEntre);

	LigneValueEntre->setPointsVisible();
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	//Cr�ation premi�re ligne
	QLineSeries *LigneValueSortie = new QLineSeries(chart);
	//Param�tre du pinceaux
	QPen penSortie = LigneValueSortie->pen();
	penSortie.setWidth(3);
	penSortie.setBrush(QBrush("green"));
	LigneValueSortie->setPen(penSortie);

	LigneValueSortie->setPointsVisible();
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


	*LigneValueEntre << QPointF(0, 600) << QPointF(1, 100) << QPointF(2, 200) << QPointF(3, 50) << QPointF(4, 500);
	chart->addSeries(LigneValueEntre);

	for (int i = 1; i < TailleTableau; i++)
	{
		float	ValueEntre = arduino.getValueEntre(i);
		float	ValueSortie = arduino.getValueSortie(i);
		float	ValueDebit = arduino.getDebit(i);



		*LigneValueSortie << QPointF(i, ValueSortie);
		//chart->addSeries(LigneValueSortie);

		int NumeroEssaieBase = i;
		QString Affaire = affaire->CreateJSON(NumeroEssaieBase, ValueEntre, ValueSortie, ValueDebit);

		if (socket->state() == QTcpSocket::ConnectedState) {

			socket->write(Affaire.toLatin1());

		}

	}

}

void PosteBanc::StopTimer()
{
	//Fin des timers
	Frequence->stop();
	TempAcquisition->stop();
	qDebug() << "End Timer";

	// Arr�t de la connection arduino et envoie des donn�e au serveur
	arduino.StopConnection();
	SendData();



	this->affaire = new Affaire(0, 0, 0, 0);
	ChangeValueIHM();

	ui.InformationTest->setEnabled(true);

	ui.CancelAffaire->setEnabled(false);
	ui.ChangeValueAffaire->setEnabled(false);
	ui.BouttonAffaire->setEnabled(false);


}

void PosteBanc::CreateGraph(int TempAcquisition)
{

	//Creation Axe Y
	axisY = new QCategoryAxis();
	axisY->setRange(0, 700);
	axisY->setTickCount(50);
	axisY->append("0", 0);
	axisY->append("50 kPa", 50);
	axisY->append("100 kPa", 100);
	axisY->append("150 kPa", 150);
	axisY->append("200 kPa", 200);
	axisY->append("250 kPa", 250);
	axisY->append("300 kPa", 300);
	axisY->append("350 kPa", 350);
	axisY->append("400 kPa", 400);
	axisY->append("450 kPa", 450);
	axisY->append("500 kPa", 500);
	axisY->append("550 kPa", 550);
	axisY->append("600 kPa", 600);
	axisY->append("650 kPa", 650);
	axisY->append("700 kPa", 700);

	//Creation Axe X en fonction du temp d'aquisition totale
	axisX = new QCategoryAxis();
	axisX->setRange(0, TempAcquisition);
	for (int x = 0; x <= TempAcquisition; x++)
	{
		qDebug() << x;
		axisX->append(QString::number(x), x);
	}

	//Cre�ation du graph
	chart = new QChart();

	//Parametrage du graphiques
	chart->layout()->setContentsMargins(0, 0, 0, 0);
	chart->setBackgroundRoundness(0);

	chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);

	//Titre du graph
	chart->setTitle("Graphique de la Pression en fonction du temps");



	//Cr�er l'affichage du graphique et ses parametrages
	Graph = new QChartView(chart);
	Graph->setRenderHint(QPainter::Antialiasing);
	Graph->resize(70 * TempAcquisition, 400);
	Graph->show();
	//ui.gridLayout->addWidget(Graph, 0, 0);
}
