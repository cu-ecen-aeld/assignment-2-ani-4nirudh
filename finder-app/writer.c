/* ###### Writer app ###### 
 finder-app/writer.c
 */

#include <syslog.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  /* 
  ## Open a connection to system log ##
  - writer.c is the identity to distinguish between different programs calling syslog
  - LOG_ID -> Add the process ID to the message 
  - LOG_CONS -> Write to system console, if the message cannot be sent to logging socket
  - LOG_USER -> Facility, which area of system the message comes from (User, Daemon, Authentication  etc.)
  */
  openlog("writer.c", LOG_PID | LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "Starting logging ...");

  // Saving string arguments
  char *writefile = argv[1];
  char *writestr = argv[2];

  // Checking the number of arguments
  if (argc != 3) {
    syslog(LOG_ERR, "Wrong number of arguments entered. Please enter 2.");
    return EXIT_FAILURE;
  }

  // Checking file presence
  FILE *fptr;
  fptr = fopen(writefile, "r");
  if (fptr != NULL) {
    syslog(LOG_INFO, "File exists!");

    // Close the pointer to the file if it exists
    fclose(fptr);
  } else {
    syslog(LOG_ERR, "File does not exist!");
  }

  // Creating file and adding text
  fptr = fopen(writefile, "w");
  if (fptr == NULL) {
    syslog(LOG_ERR, "Error opening the file. Exiting!");
    return EXIT_FAILURE;
  }
  syslog(LOG_INFO, "Writing %s to %s", writestr, writefile);
  fputs(writestr, fptr);
  fclose(fptr);

  // Close logging
  closelog();
  return EXIT_SUCCESS;
}
