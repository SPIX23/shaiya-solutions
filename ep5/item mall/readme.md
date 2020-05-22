**original code** 

https://github.com/zidane168/Shaiya-Projects/tree/master/Fix%20Item%20mall%20SQL%202012

**compatibility**

SQL Server 2019
SQL Server 2017
SQL Server 2016
SQL Server 2014
SQL Server 2012

**additional dependencies**
* legacy_stdio_definitions.lib;

**disable specific warnings**
* 4996;4838;

**instructions**
1. search the dll with a hex editor for the username and password located in the ps_game.sql file as unicode strings
2. replace them with a username and password that has the same amount of characters 
3. be mindful of possible login failure when using certain sql operators in the username

**revisions**
* 16 character strings for the username and password and a new connection string
* made the code smaller, more readable, and used different source code for hooks
* compiled with vc runtime libraries

**contents**
* sql query that creates a login with the minimal database permissions the dll requires
* ps_game reported not to have random disconnects
* ps_dbAgent for ep5 that doesn't dc after 10 item mall purchases
* linked servers query that needs to be edited to match your login credentials
* usp_Save_User_BuyPointItems2 that the ep5 ps_dbAgent requires

**notes**
* the jump to hook the dll is at address 005312FB and overwrites the following code

```asm
pop esi
pop edi
pop ebx
leave
retn
```

* the overwritten code is added to the end of the hook that begins at address 04096181
* the dll name is a binary edit that begins at address 04096195 and is pushed before calling LoadLibraryA

```asm
pushad
push 04096195 //ps_game.dll
call dword ptr ds:[005541C4] //LoadLibraryA
popad
pop esi
pop edi
pop ebx
leave
retn
```

* you may hook as many dlls as you wish by following this example

```asm
pushad
push <dllnameaddress> //ps_game.dll
call dword ptr ds:[005541C4] //LoadLibraryA
push <dllnameaddress> //another.dll
call dword ptr ds:[005541C4] //LoadLibraryA
popad
pop esi
pop edi
pop ebx
leave
retn
```


