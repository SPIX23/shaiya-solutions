*disclaimer: this solution has not been tested enough to confirm that it prevents duping on ep3 servers*

**contents**

* a ps_dbAgent that has been edited to match lilprohacker's ep4 dupe solution

* lilprohacker's stored procedure that has been edited for the bootleggery wld file dimensions

* nubness' stored procedures that need to be added to ps_gamelog.dbo.usp_Insert_Action_Log_E

**notes**

* leave status must update properly for the dbo.usp_Insert_Action_Log_E procedures to work

**instructions**

1. add this to usp_Try_GameLogin_Taiwan above the execute statement for usp_Insert_LoginLog_E

**UPDATE Users_Master SET Leave = 1, JoinDate = GETDATE() WHERE UserUID = @UserUID**

2. add this to usp_Try_GameLogout_R below the update statement for usp_Insert_LoginLog_E

**UPDATE Users_Master SET Leave = 0, JoinDate = GETDATE() WHERE UserUID = @UserUID;**
