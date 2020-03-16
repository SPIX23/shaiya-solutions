
/* Add server link, and Shaiya username */ 
IF NOT EXISTS (SELECT [name] FROM master.dbo.syslogins WHERE name = 'Shaiya')
BEGIN
	EXEC sp_addlogin 'Shaiya', 'Shaiya123', 'PS_GameDefs';
END	
EXEC sp_addsrvrolemember 'Shaiya', 'sysadmin';

/* Add linked servers */

IF NOT EXISTS (SELECT srvname FROM master..sysservers WHERE srvname='game')
BEGIN
	EXEC sp_addlinkedserver 'game','','SQLOLEDB','127.0.0.1';
	EXEC sp_addlinkedsrvlogin 'game','false',null,'Shaiya','Shaiya123';
END

exec sp_serveroption @server='game', @optname='rpc', @optvalue='true';
exec sp_serveroption @server='game', @optname='rpc out', @optvalue='true';

IF NOT EXISTS (SELECT srvname FROM master..sysservers WHERE srvname='PS_DEFINEDB')
BEGIN
	EXEC sp_addlinkedserver 'PS_DEFINEDB','','SQLOLEDB','127.0.0.1';
	EXEC sp_addlinkedsrvlogin 'PS_DEFINEDB','false',null,'Shaiya','Shaiya123';
END

exec sp_serveroption @server='PS_DEFINEDB', @optname='rpc', @optvalue='true';
exec sp_serveroption @server='PS_DEFINEDB', @optname='rpc out', @optvalue='true';

IF NOT EXISTS (SELECT srvname FROM master..sysservers WHERE srvname='PS_NCASH')
BEGIN
	EXEC sp_addlinkedserver 'PS_NCASH','','SQLOLEDB','127.0.0.1';
	EXEC sp_addlinkedsrvlogin 'PS_NCASH','false',null,'Shaiya','Shaiya123';
END

exec sp_serveroption @server='PS_NCASH', @optname='rpc', @optvalue='true';
exec sp_serveroption @server='PS_NCASH', @optname='rpc out', @optvalue='true';

IF NOT EXISTS (SELECT srvname FROM master..sysservers WHERE srvname='PS_USERDB')
BEGIN
	EXEC sp_addlinkedserver 'PS_USERDB','','SQLOLEDB','127.0.0.1';
	EXEC sp_addlinkedsrvlogin 'PS_USERDB','false',null,'Shaiya','Shaiya123';
END

exec sp_serveroption @server='PS_USERDB', @optname='rpc', @optvalue='true';
exec sp_serveroption @server='PS_USERDB', @optname='rpc out', @optvalue='true';

IF NOT EXISTS (SELECT srvname FROM master..sysservers WHERE srvname='PS_GAMEDB01')
BEGIN
	EXEC sp_addlinkedserver 'PS_GAMEDB01','','SQLOLEDB','127.0.0.1';
	EXEC sp_addlinkedsrvlogin 'PS_GAMEDB01','false',null,'Shaiya','Shaiya123';
END

exec sp_serveroption @server='PS_GAMEDB01', @optname='rpc', @optvalue='true';
exec sp_serveroption @server='PS_GAMEDB01', @optname='rpc out', @optvalue='true';

IF NOT EXISTS (SELECT srvname FROM master..sysservers WHERE srvname='PS_USERDB01')
BEGIN
	EXEC sp_addlinkedserver 'PS_USERDB01','','SQLOLEDB','127.0.0.1';
	EXEC sp_addlinkedsrvlogin 'PS_USERDB01','false',null,'Shaiya','Shaiya123';
END

exec sp_serveroption @server='PS_USERDB01', @optname='rpc', @optvalue='true';
exec sp_serveroption @server='PS_USERDB01', @optname='rpc out', @optvalue='true';

