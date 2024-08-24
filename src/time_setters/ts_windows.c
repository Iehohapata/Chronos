#include "../includes.h"
FILETIME filetime;

int set_timestamp(char* filename, time_t time) {
	SetLastError(0);
	HANDLE file = CreateFile(
		filename,
		FILE_WRITE_ATTRIBUTES,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD err_msg_id;
	if ((err_msg_id = GetLastError())) {
		print_err(err_msg_id);
		exit(EXIT_FAILURE);
	}
	if (!SetFileTime(file, &filetime, &filetime, &filetime)) {
		perror("Error occured during time change.");
	}
}
void print_err(DWORD err_msg_id) {
	LPSTR msg_buff = NULL;
	DWORD stored = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, err_msg_id, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&msg_buff, 0, NULL);
	if (stored) {
		wprintf(msg_buff);
	}
	LocalFree(msg_buff);
}