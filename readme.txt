notes:

added sql database files that can be used with ep4 and ep5 servers that are 99% bug free

added a connection overflow solution for the most commonly used ps_login (312kb)

added a solution for the ps_login allowing client version -1 to pass through the service

side notes:

ps_gamedefs needs to be edited to match your client and the psmagent.dll needs to be installed in the ps_gamelog database

psmagent can be removed by deleting the dbo.command procedure and the psmagnet assembly in the ps_gamelog database

comment out or remove the grb leader resurrection procedure in dbo.usp_Insert_Action_Log_E if you don't use the psmagent
