*this is an updated version of the following project* 

https://github.com/zidane168/Shaiya-Projects/tree/master/Fix%20Item%20mall%20SQL%202012

**instructions**

1. search the dll with a hex editor for the username and password located in the ps_game.sql file as unicode strings

2. replace them with a username and password that has the same amount of characters 

3. be mindful of possible login failure when using certain sql operators in the username

**updates**

* updated source code with 16 character strings for the username and password

* connection string that is tested to be compatible with sql versions higher than 2012

**contents**

* sql query that creates a login with the minimal database permissions required

* ps_game reported not to have random disconnects

* ps_dbAgent for ep5 that doesn't dc after 10 item mall purchases

* linked servers query that needs to be edited to match your login credentials

* usp_Save_User_BuyPointItems2 required by the ep5 db_Agent (included with my ps_gamedata)
