ESP 32 LOGGER FOR MAHLER CALORIMETER
-------------------------------------

CONFIGURAZIONE
---------------
I file da modificare prima della compilazione sono:
1) mail_conf.h -> contiene i parametri di configurazione della mail del mittente e del ricevente;
2) parametri_prova.h    -> contiene il numero massimo di misure da fare e il tempo tra le stesse in millisecondi.

USO
-----
1) Attivare l'ESP32;
2.a) Se la rete non è configurata, connettersi a "MahlerAP" con un cellulare o altro;
2.b) Se si vuole cambiare la rete cui si connette ESP, in modalità OZIOSO schiacciare per 10s il pulsante
(led color bianco) e connettersi a "MahlerAP" con un cellulare o altro;
3) Con il browser andare all'indirizzo 192.168.4.1 e immettere i dati della rete cui connettere l'ESP;
4) L'ESP si riavvierà e si collegherà in automatico alla rete configurata;
5) L'ESP entrerà in modalità OZIOSA col led verde lampeggiante;
6) Iniziare la prova schiacciando il pulsante per 0.5s circa. Il led diventerà rosso;
7) Se si vuole interrompere in anticipo il test, schiacciare il pulsante per circa 2s;
8) Al termine della prova il led diventa viola, viene inviata la mail con il file delle letture;
9) Il led torna verde lampaggiante e può essere eseguita una nuova prova.

********************************************************************************************************

CONFIGURATION
--------------
Before compiling, please alter the following two files:
1) mail_conf.h -> contains the emai configuration parameters: imap, port, sender and recipient;
2) parametri_prova.h -> contains the number of measurements and the interval time between them expressed in milliseconds;

USE
----
1) Switch the ESP32 ON;
2.a) If the net is not yet configured, connect with, for instance, a mobile phone, to the "MahlerAP";
2.b) If is necessary tho switch to another net, in OZIOSO mode (green led flashing) push the button for about 10s. Connect (he led will turn white)
to "MahlerAP" with a mobile phone or another mean;
3) Point the mobile browser to 192.168.4.1 and set SSID and Password of the net the ESP should connect to;
4) The ESP will reboot and automatically connect to the configured SSID;
5) The ESP will enter in OZIOSO (IDLE) mode and the green led will start to flash;
6) Start the test by pushing the button for about 0.5s. The led will turn red;
7) Should it be necessary to stop the test beforehand, push the button for about 2s;
8) At the end of the test, the LED will turn purple, and a mail with an attached text file containing the readings will be sent to the recipient;
9) At the end the ESP will go back to the OZIOSO state ready for a new test and the LED will turn green and flashing.
