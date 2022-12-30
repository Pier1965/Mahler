/* CONFIGURAZIONE POSTA ELETTRONICA */
#define RECIPIENT1 "pierundcarla@gmail.com"   // <------------ mail destinatario
#define RECIPIENT2 "Pierpaolo Garofalo"       // <------------ nome destinatario
/** The smtp port e.g.
 * 25  or esp_mail_smtp_port_25
 * 465 or esp_mail_smtp_port_465
 * 587 or esp_mail_smtp_port_587
 */
#define SMTP_HOST "smtp.libero.it"            // <------------ servizio posta smtp mittente
#define SMTP_PORT esp_mail_smtp_port_465      // <------------ porta smtp server
/* The log in credentials */
#define AUTHOR_EMAIL "pppc65@libero.it"       // <------------ mail mittente
#define AUTHOR_PASSWORD "P@55libero"          // <------------ password mail mittente
#define ESP_NAME "ESP Mahler"
#define OGGETTO "Test calorimetro di Mahler"
#define MESSAGGIO "Rilievo profilo di temperatura prova con calorimetro di Mahler eseguito "
