**contents**
* ps_login ct file that solves the issue of the ps_login allowing client version -1 to pass through the service
* ps_login ct file that will decrease the amount of failed logins allowed before the client gets disconnected
* ps_login with the aforementioned mods applied plus anti-injection (nubness) and handshake fix (anton)
* Insert_Action_Log_E procedure that changes the mapid and coordinates of characters that log off in D2
* apostrophe removal query for mobs, skills, and items that should be executed after updating the tables
* working chinese server bin (read the notes)

**connection overflow workaround**
* 00411ABD - nop jnl (not applied to ps_login)
