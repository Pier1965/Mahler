#include <ESP_Mail_Client.h>
#include "mail_conf.h"
/* Declare the global used SMTPSession object for SMTP transport */
SMTPSession smtp;
/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status);
const char rootCACert[] PROGMEM = "-----BEGIN CERTIFICATE-----\n"
                                  "-----END CERTIFICATE-----\n";
void send_mail()
{
  /*  Set the network reconnection option */
  MailClient.networkReconnect(true);
  /** Enable the debug via Serial port
   * 0 for no debugging
   * 1 for basic level debugging
   *
   * Debug port can be changed via ESP_MAIL_DEFAULT_DEBUG_PORT in ESP_Mail_FS.h
   */
  smtp.debug(1);
  /* Set the callback function to get the sending results */
  smtp.callback(smtpCallback);
  /* Declare the ESP_Mail_Session for user defined session credentials */
  ESP_Mail_Session session;
  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = F("mydomain.net");
  /* Set the NTP config time */
  session.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  session.time.gmt_offset = 1; // ora di Roma
  session.time.day_light_offset = 0;
  /* Declare the message class */
  SMTP_Message message;
  /* Set the message headers */
  message.sender.name = F(ESP_NAME); // This witll be used with 'MAIL FROM' command and 'From' header field.
  message.sender.email = AUTHOR_EMAIL; // This witll be used with 'From' header field.
  message.subject = F(OGGETTO);
  message.addRecipient(F(RECIPIENT2), F(RECIPIENT1)); // This will be used with RCPT TO command and 'To' header field.
  String textMsg = MESSAGGIO + Data + " alle " + Ora;
  message.text.content = textMsg;
  message.text.charSet = F("us-ascii");
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  /* Set the custom message header */
  message.addHeader(F("Message-ID: <abcde.fghij@gmail.com>"));
  /* The attachment data item */
  SMTP_Attachment att;
  message.resetAttachItem(att);
  att.descr.filename = "fileDati.txt";
  att.descr.mime = "text/plain"; //txt data
  att.file.path = "/fileDati.txt";
  att.file.storage_type = esp_mail_file_storage_type_flash;
  att.descr.transfer_encoding = Content_Transfer_Encoding::enc_base64;
  /* Add attachment to the message */
  message.addAttachment(att);
  /* Connect to the server */
  if (!smtp.connect(&session /* session credentials */))
    return;
  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    DEBUG_PRINTLN("Error sending Email, " + smtp.errorReason());
  ESP_MAIL_PRINTF("Free Heap: %d\n", MailClient.getFreeHeap());
}
/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status)
{
  /* Print the current status */
  DEBUG_PRINTLN(status.info());
  /* Print the sending result */
  if (status.success())
  {
    DEBUG_PRINTLN("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failed: %d\n", status.failedCount());
    DEBUG_PRINTLN("----------------\n");
    for (size_t i = 0; i < smtp.sendingResult.size(); i++)
    {
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %s\n", asctime(localtime(&ts)));
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients.c_str());
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject.c_str());
    }
    DEBUG_PRINTLN("----------------\n");
    // You need to clear sending result as the memory usage will grow up.
    smtp.sendingResult.clear();
  }
}
