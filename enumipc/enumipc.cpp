// Slightly moidified NetConnectionEnum() example from 
// https://docs.microsoft.com/en-us/windows/desktop/api/lmshare/nf-lmshare-netconnectionenum

//#ifndef UNICODE
//#define UNICODE
//#endif
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#pragma comment(lib, "Netapi32.lib")

int wmain(int argc, wchar_t *argv[])
{
	DWORD res, i, er = 0, tr = 0, resume = 0;
	PCONNECTION_INFO_1 p, b;
	LPTSTR lpszServer = NULL, lpszShare = NULL;


	if (argc < 3)
	{
		wprintf(L"Syntax: %s <ServerName> <ShareName>\n", argv[0]);
	}
	else
	{
		lpszServer = argv[1];

		// ShareName is the last argument.
		lpszShare = argv[2];
		
		// Call the NetConnectionEnum function,
		// specifying information level 1.
		res = NetConnectionEnum(lpszServer, lpszShare, 1, (LPBYTE *)&p, MAX_PREFERRED_LENGTH, &er, &tr, &resume);
		
		// If no error occurred,
		if (res == 0)
		{
			// If there were any results,
			if (er > 0)
			{
				printf("\nConnections to \\\\%S\\%S\n\n", lpszServer, lpszShare);
				printf("User - Source\n");
				printf("-------------------------------------\n");
				
				b = p;
		
				// Loop through the entries; print user name and network name.
				for (i = 0; i < er; i++)
				{
					printf("%S - %S\n", b->coni1_username, b->coni1_netname);
					b++;
				}

				// Free the allocated buffer.
				NetApiBufferFree(p);
			}
			else
			{
				printf("No one connected to \\\\%S\\%S\n", lpszServer, lpszShare);
			}

		}
		else
		{
			// Otherwise, print the error.
			
			LPVOID lpMsgBuf;
			DWORD dw = GetLastError();

			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dw,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&lpMsgBuf,
				0, NULL);

			// Display the error message and exit the process
			printf("%S", (LPTSTR)lpMsgBuf);

			LocalFree(lpMsgBuf);
			printf("Error: %d\n", res);
		}
	}
	return 0;
}
