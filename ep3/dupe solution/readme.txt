notes:

added a ps_dbAgent that has been edited to match lilprohacker's ep4 dupe solution

added lilprohacker's stored procedure that has been edited for the bootleggery wld dimensions

added nubness' stored procedures that need to be added to ps_gamelog.dbo.usp_Insert_Action_Log_E

side notes:

the leave column in ps_userdata.dbo.users_master must update for the dbo.usp_Insert_Action_Log_E procedures to work

add this to usp_Try_GameLogin_Taiwan above the execute statement for usp_Insert_LoginLog_E

UPDATE Users_Master SET Leave = 1, JoinDate = GETDATE() WHERE UserUID = @UserUID

add this to usp_Try_GameLogout_R below the update statement for usp_Insert_LoginLog_E

UPDATE Users_Master SET Leave = 0, JoinDate = GETDATE() WHERE UserUID = @UserUID;
