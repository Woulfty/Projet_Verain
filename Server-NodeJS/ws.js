//  Import
const WebSocketServer = require('ws').Server;
const mysql = require('mysql2/promise');
const mysqldump = require('mysqldump');
const fs = require('fs');

//  Déclaration BDD
const BDD_IP = "192.168.65.20";
const BDD_USER = "root";
const BDD_PWD = "root";
const BDD_BASE = "verain";

//  WebSocket
(async() => {
    // Création WebSocketServer
    const wss = new WebSocketServer({port: 40510});
    console.log("Serveur Lancé.");

    try{
        var con = await mysql.createConnection({
            host:       BDD_IP,
            user:       BDD_USER,
            password:   BDD_PWD,
            database:   BDD_BASE
        });
    }catch(error){
        console.log("Erreure de connexion à la base de données", error);
    }

    // Lancement WebSocketServer
    wss.on( 'connection', function (ws){
        // News Connexion
        console.log("Nouvelle connexion.");
        ws.send("Connexion établie.");
        // Lancement Date loop for 10 Secondes
        setInterval(() =>
            ws.send(`Temps : ${new Date()}`)
        ,30 * 1000)
        // Message Reçu Répo
        ws.on('message', async function(message){
            // Définition String Message
            message = String( message );
            // ListAffaire
            if(message.slice() == 'ListAffaire'){
                console.log('ListAffaire : %s', message);
                //const[rows, fields] = await con.execute('SELECT * FROM `Affaire`', []);
                //ws.send('RepListAffaire' + ';' + rows.length + ';' + JSON.stringify(rows)); //Liste des ID Uniquements
                const[rows, fields] = await con.execute('SELECT `idAffaire` FROM `Affaire`', []);
                ws.send('RepListAffaire' + ';' + JSON.stringify(rows));
            }
            // ListPV
            if(message.slice() == 'ListPV'){
                console.log('ListPV : %s', message);
                const[rows, fields] = await con.execute('SELECT * FROM `PV`', []);
                ws.send('RepListPV' + ';' + rows.length + ';' + JSON.stringify(rows));
            }
            // ListEssai
            if(message.slice() == 'ListEssai'){
                console.log('ListEssai : %s', message);
                const[rows, fields] = await con.execute('SELECT * FROM `Essai`', []);
                ws.send('RepListEssai' + ';' + rows.length + ';' + JSON.stringify(rows));
            }
            // ListUser
            if(message.slice() == 'ListUser'){
                console.log('ListUser : %s', message);
                const[rows, fields] = await con.execute('SELECT `idUser`, `Username`, `DateCreation` FROM `User`', []);
                ws.send('RepListUser' + ';' + rows.length + ';' + JSON.stringify(rows));
            }
            // UserConnexion
            if(message.split(';')[0] == 'UserConnexion'){
                console.log('UserConnexion : %s', message);
                Username    = message.split(';')[1];
                MdpUser     = message.split(';')[2];
                const[rows, fields] = await con.execute('SELECT `Username` FROM `User` WHERE `Username` = ? AND `Mdp` = ?', [Username,MdpUser]);
                console.log(rows)
                if(rows.length > 0){
                    console.log('RepUserConnexion' + ';' + Username + ';' + 'true');
                    ws.send('RepUserConnexion' + ';' + Username + ';' + 'true');
                }
                else{
                    console.log('RepUserConnexion' + ';' + Username + ';' + 'false');
                    ws.send('RepUserConnexion' + ';' + Username + ';' + 'false');
                }
            }
            // InfoAffaire
            if(message.split(';')[0] == 'InfoAffaire'){
                console.log('InfoAffaires : %s', message);
                idAffaire   = message.split(';')[1];
                const[rows, fields] = await con.execute('SELECT * FROM `Affaire` WHERE `idAffaire` = ?', [idAffaire]);
                ws.send('RepInfoAffaire' + ';' + idAffaire + ';' + JSON.stringify(rows));
            }
            // InfoEssai
            if(message.split(';')[0] == 'InfoEssai'){
                console.log('InfoEssai : %s', message);
                idEssai     = message.split(';')[1];
                const[rows, fields] = await con.execute('SELECT * FROM `Essai` WHERE `idEssai` = ?', [idEssai]);
                ws.send('RepInfoEssai' + ';' + idEssai + ';' + JSON.stringify(rows));
            }
            // InfoUser
            if(message.split(';')[0] == 'InfoUser'){
                console.log('InfoUser : %s', message);
                idUser      = message.split(';')[1];
                const[rows, fields] = await con.execute('SELECT * FROM `User` WHERE `idUser` = ?', [idUser]);
                ws.send('RepInfoUser' + ';' + idUser + ';' + JSON.stringify(rows));
            }
            // InfoPV
            if(message.split(';')[0] == 'InfoPV'){
                console.log('InfoPV : %s', message);
                idPV        = message.split(';')[1];
                const[rows, fields] = await con.execute('SELECT * FROM `PV` WHERE `idPV` = ?', [idPV]);
                ws.send('RepInfoPV' + ';' + idPV + ';' + JSON.stringify(rows));
            }
            // DelPV
            if(message.split(';')[0] == 'DelPV'){
                console.log('DelPV : %s', message);
                idPV = message.split(';')[1];
                con.execute('DELETE FROM `PV` WHERE `PV`.`idPV` = ?', [idPV]);
                ws.send('RepDelPV' + ';' + idPV + ';' + 'CONFIRM');
            }
            // AddPV
            if(message.split(';')[0] == 'AddPV'){
                console.log('AddPV : %s', message);
                idUser      = message.split(';')[1];
                idAffaire   = message.split(';')[2];
                Texte       = message.split(';')[3];
                con.execute('INSERT INTO `PV` (`idUser`, `idAffaire`, `Texte`) VALUES (?, ?, ?)', [idUser, idAffaire, Texte]);
                ws.send('RepAddPV' + ';' + 'CONFIRM');
            }
            // UpdPV
            if(message.split(';')[0] == 'UpdPV'){
                console.log('UpdPV : %s', message);
                idPV        = message.split(';')[1];
                Texte       = message.split(';')[2];
                con.execute('UPDATE `PV` SET `Texte` = ? WHERE `PV`.`idPV` = ?', [Texte, idPV]);
                ws.send('RepUpdPV' + ';' + idPV + ';' + 'CONFIRM');
            }
            // ExpBDD
            if(message.slice() == 'ExpBDD'){
                console.log('ExpBDD : %s', message);
                // Récupération de la BDD
                await mysqldump({
                    connection:{
                        host:       BDD_IP,
                        user:       BDD_USER,
                        password:   BDD_PWD,
                        database:   BDD_BASE
                    },
                    // Création du fichier
                    dumpToFile:'./BDD_files/dump.sql',
                });
                // Récupération du Fichier
                const BDD_Files = fs.readFileSync('./BDD_files/dump.sql','utf8');
                // Transformation et communication data
                String(BDD_Files);
                ws.send('RepExpBDD' + ';' + BDD_Files);
                console.log('RepExpBDD' + ';' + 'CONFIRM');
            }
            // ImpBDD
            if(message.slice() == 'ImpBDD'){
                console.log('ImpBDD : %s', message);
                ws.send('RepImpBDD' + ';' + 'CONFIRM');
            }
            // ResBDD
            if(message.slice() == 'ResBDD'){
                console.log('ResBDD : %s', message);
                ws.send('RepResBDD' + ';' + 'CONFIRM');
            }
            // Autres
            else if(message.slice() != 'connected'){
                console.log('Reçu : %s', message);
            }
        })
    });
})();