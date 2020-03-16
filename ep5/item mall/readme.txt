this is an updated version of this project - https://github.com/zidane168/Shaiya-Projects/tree/master/Fix%20Item%20mall%20SQL%202012

search the dll with a hex editor for the username and password located in the ps_game.sql file as a unicode string and replace them with a username and password that has the same amount of characters. i suggest avoiding the use of sql operators in the username.

notes:

updated the source code to have 16 character strings for the username and password

the new connection string is tested to be compatible with sql versions higher than 2012

added an sql script that creates a login with the minimal database permissions required for use

replaced the ps_game with one reported not to have random disconnects by two server administrators

removed the prior dll assembly hooks in the ps_game and added a new hook for the ps_game.dll

renamed itemmallfix.dll to ps_game.dll

added the linked server sql query

side notes:

the linked servers query has the default username and password and needs to be edited with your credentials
