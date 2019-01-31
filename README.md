# enumipc

`enumipc.exe` is a small utility to list connections to a Windows share. It is pretty much the sample code from the [`NetConnectionEnum`](https://docs.microsoft.com/en-us/windows/desktop/api/lmshare/nf-lmshare-netconnectionenum) example.

Several Emotet malware write-ups indicate Emotet will query the IPC$ share to get a list of all endpoints that connect to it. 

<img src="enumipc.png" border="0" alt="enumipc">
