#pragma once
#include <curl/curl.h>

#define FROM    "philip.sve@hotmail.com"
#define TO      "philipius96@gmail.com"
#define CC      "<info@example.org>"

static const char *payload_text[] = {
      "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
      "To: " TO "\r\n",
      "From: " FROM " (Example User)\r\n",
      "Cc: " CC " (Another example User)\r\n",
      "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@"
      "rfcpedant.example.org>\r\n",
      "Subject: SMTP TLS example message\r\n",
      "\r\n", /* empty line to divide headers from body, see RFC5322 */
      "The body of the message starts here.\r\n",
      "\r\n",
      "It could be a lot of lines, could be MIME encoded, whatever.\r\n",
      "Check RFC5322.\r\n",
      NULL
};

struct upload_status {
      int lines_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
      struct upload_status *upload_ctx = (struct upload_status *)userp;
      const char *data;
      
      if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
            return 0;
      }
      
      data = payload_text[upload_ctx->lines_read];
      
      if(data) {
            size_t len = strlen(data);
            memcpy(ptr, data, len);
            upload_ctx->lines_read++;
            
            return len;
      }
      
      return 0;
}


void sendEmail();
