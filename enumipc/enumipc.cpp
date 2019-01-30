//#ifndef UNICODE
//#define UNICODE
//#endif
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#pragma comment(lib, "Netapi32.lib")
void wmain(int argc, wchar_t *argv[])
{
	DWORD res, i, er = 0, tr = 0, resume = 0;
	PCONNECTION_INFO_1 p, b;
	LPTSTR lpszServer = NULL, lpszShare = NULL;


	if (argc < 2)
		wprintf(L"Syntax: %s [ServerName] ShareName | \\ComputerName\n", argv[0]);
	else
	{
		//
		// The server is not the default local computer.
		//
		if (argc > 2)
			lpszServer = argv[1];
		//
		// ShareName is always the last argument.
		//
		lpszShare = argv[argc - 1];
		//
		// Call the NetConnectionEnum function,
		//  specifying information level 1.
		//
		res = NetConnectionEnum(lpszServer, lpszShare, 1, (LPBYTE *)&p, MAX_PREFERRED_LENGTH, &er, &tr, &resume);
		//
		// If no error occurred,
		//
		if (res == 0)
		{
			//
			// If there were any results,
			//
			if (er > 0)
			{
				b = p;
				//
				// Loop through the entries; print user name and network name.
				//
				for (i = 0; i < er; i++)
				{
					printf("%S\t%S\n", b->coni1_username, b->coni1_netname);
					b++;
				}
				// Free the allocated buffer.
				//
				NetApiBufferFree(p);
			}
			// Otherwise, print a message depending on whether
			//  the qualifier parameter was a computer (\ComputerName)
			//  or a share (ShareName).
			//
			else
			{
				if (lpszShare[0] == '\\')

					printf("No connection to %S from %S\n",
					(lpszServer == NULL) ? TEXT("LocalMachine") : lpszServer, lpszShare);
				else

					printf("No one connected to %S\%S\n",
					(lpszServer == NULL) ? TEXT("\\LocalMachine") : lpszServer, lpszShare);
			}

		}
		//
		// Otherwise, print the error.
		//
		else
			printf("Error: %d\n", res);
	}
	return;
}
