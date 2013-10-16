#define UNIX 1
#define LINUX 1

#include "global.h"
#include "ns.h" /* NSGetServerList */
#include "osmisc.h" /* OSLoadString */
#include "osmem.h" /* OSLockObject */

	/* connecting to a remote server: */
	//STATUS error = OSPathNetConstruct(NULL, server_name, db_name, "");

	/* opening a database. */
	// DBHANDLE db_handle = NULLHANDLE;
	/* where @path_name == @db_name above */
	// STATUS error = NSFDbOpen(path_name, &db_handle);

	// char buffer[NSF_INFO_SIZE] = "";
	// STATUS error = NSFDbInfoGet(db_handle, buffer);

	// char title[NSF_INFO_SIZE] = "";
	// NSFDbInfoParse(buffer, INFOPARSE_TITLE, title, sizeof(title) -1);

	// STATUS error = NSFDbClose(db_handle)

#include <stdio.h>

int main(int argc, char **argv)
{
	/* args: [server name] <database filename> */
	STATUS error = NotesInitExtended(argc, argv);
	if (error) {
		if (IS_STRING(error)) {
			puts("is string");
		}
		fprintf(stderr, "NotesInitExtended error: %d, %d\n", PKG(error), ERRNUM(error));
		return 0;
	}

	DHANDLE server_list = NULLHANDLE;
	error = NSGetServerList(NULL, &server_list);
	if (error) {
		fprintf(stderr, "NSGetServerList error: %d, %d\n", PKG(error), ERRNUM(error));
		return 0;
	}

	uint8_t *c = (uint8_t *)OSLockObject(server_list);

	/* little endian, 16 bits. "WORD" is used on windows. */
	uint16_t server_count = (c[0] & 0xff)  | ((c[1] & 0xff) << 8);

	/* an array of uint16_t's in le format. */
	uint8_t *server_lengths = c + sizeof(uint16_t);

	char *name_pos = (char *)server_lengths + server_count * sizeof(uint16_t);

	int i;
	for (i = 0; i < server_count; i++) {
		size_t this_len = (server_lengths[i * sizeof(uint16_t)] & 0xff)
			| ((server_lengths[i * sizeof(uint16_t) + 1] & 0xff) << 8);

		printf("server: %.*s\n", this_len, name_pos);
		name_pos += this_len;
	}

	OSUnlockObject(server_list);
	OSMemFree(server_list);

	NotesTerm();
}
