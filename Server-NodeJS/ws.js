const WebSocketServer = require('ws').Server;
const mysql = require('mysql2/promise');

(async() => {
    // Création WebSocketServer
    const wss = new WebSocketServer({port: 40510});
    console.log("Serveur Lancé.");

    try{
        var con = await mysql.createConnection({
            host:"192.168.65.20",
            user:"root",
            password:"root",
            database : "verain"
        });
    }catch(error){
        console.log("Erreure de connexion à la base de données", error);
    }

    // Lancement WebSocketServer
    wss.on( 'connection', function (ws){
        // News Connexion
        console.log("Nouvelle connexion");
        ws.send("Connexion établie.");
        // Lancement Date loop for 10 Secondes
        setInterval(() =>
            ws.send(`Temps : ${new Date()}`)
        ,30 * 1000)
        // Message Reçu Répo
        ws.on('message', async function(message){
            // ListeAffaires
            if(message.slice() == 'ListAffaires'){
                console.log('ListAffaires : %s', message);
                const[rows, fields] = await con.execute('SELECT `ID` FROM `Affaire`', []);
                ws.send(JSON.stringify(rows))
            }
            // Autres
            else{
                console.log('Reçu (Inconnu) : %s', message);
                ws.send('Erreur : reçu inconnu : ' + message)
            }
        })
    });
})();