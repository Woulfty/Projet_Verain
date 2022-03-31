//connexion du socket au serveur
const ws = new WebSocket("ws://192.168.65.44:40510");

//récupération de la barre de navigation
navigation = document.getElementById('navigation');

//récupération du loarder
dloader = document.getElementById('dloader');
    
//boutton de la barre
var toggle = document.getElementById('toggle');
   
//affichage de la page de connexion
dconnexion = document.getElementById('dconnexion');

dloader.style.display = "block"
toggle.style.display = "none"
dconnexion.style.display = "none"
navigation.style.display = "none"

ws.addEventListener("message", async (event, isBinary ) => {
    console.log( event.data )
})

//Erreur du socket
ws.addEventListener('error', function (event) {
    navigation.style.display = "none";
    dloader.style.display = "block";
    console.log('WebSocket error: ', event);
});
//Quand le socket c'est connecter
ws.onopen = function () {

    console.log('websocket is connected ...');

    ws.send('connected');
    //loader
    dloader = document.getElementById('dloader');
    dloader.style.display = "none";
    //barre de navigation
    //navigation = document.getElementById('navigation');
    navigation.style.display = "block";
    //boutton de la barre
    toggle = document.getElementById('toggle');
    toggle.style.display = "block";
    //affichage de la page de connexion
    dconnexion = document.getElementById('dconnexion');
    dconnexion.style.display = "block";

    //réception de messages
    ws.onmessage = async function (message) {
        // Définition String Message
        message = String( message );
        //récéption de la connexion
        if(message.split(';')[0] == 'RepUserConnexion'){
            var idUser = message.split(';')[1];
            var registerRep = message.split(';')[2];

            if(registerRep == "false"){
                alert("Identifiants incorectes");
            }
            else if(registerRep == "true"){
                //création du cookie
                document.cookie = idUser;'path=/; expires=' + date;

                //on cache la div de connexion
                dconnexion = document.getElementById('dconnexion');
                dconnexion.style.display = "none";
                //apparition de la div de déconnexion
                var bdeco = document.getElementById('bdeco');
                bdeco.style.display = "block";
                //apparition de la div de visualisation des Affaires
                var bpv = document.getElementById('bpv');
                bpv.style.display = "block";    
                //apparition de la div de téléverement de fichier
                var ddoc = document.getElementById('ddoc');
                ddoc.style.display = "block";

                //demande des affaires au serveur
                ws.send('ListAffaires');
            }
        }
        //récéption des infos affaires
        if(message.split(';')[0] == 'RepListAffaire'){

        }
        //récéption des information de l'affaire
        if(message.split(';')[0] == 'RepInfoAffaire'){
            
        }
        //récéption des Pv de l'affaire
        if(message.split(';')[0] == 'RepListPV'){
            
        }
        //récéption des essais de l'affaire
        if(message.split(';')[0] == 'RepListEssai'){
            
        }
        //récéption des information de l'essais
        if(message.split(';')[0] == 'RepInfoEssai'){
            
        }
        //récéption des information du Pv
        if(message.split(';')[0] == 'RepInfoPV'){
            
        }
    }

    //récupération des valeurs dans les champs de connexion
    var form = document.getElementById('form');
    var pseudo = document.getElementById('pseudo');
    var mdp = document.getElementById('mdp');
    //envoie des données au serveurs
    form.addEventListener('submit', function(e) {
        e.preventDefault();
        if (pseudo.value && mdp.value) {
            ws.send('UserConnexion' + ';'+ pseudo.value +';'+ mdp.value);
            pseudo.value = '';
            mdp.value = '';
        }else{
            alert("veuillez remplir les champs");
        }       
    });
}