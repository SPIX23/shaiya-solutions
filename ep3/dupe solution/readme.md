*disclaimer: this solution has not been tested enough to confirm that it prevents duping on ep3 servers*

**contents**

* ps_dbAgent for ep3 that has been edited to match lilprohacker's ep4 packet-based dupe solution

* stored procedure that has been slightly edited for the bootleggery Y coordinate (credits: lilprohacker)

* stored procedures that need to be added to ps_gamelog.dbo.usp_Insert_Action_Log_E (credits: nubness)

**notes**

* leave status must update properly for the dbo.usp_Insert_Action_Log_E procedures (included with my ps_userdata)

**instructions**

* add this to ps_userdata.dbo.usp_Try_GameLogin_Taiwan above the execute statement for dbo.usp_Insert_LoginLog_E

**UPDATE Users_Master SET Leave = 1, JoinDate = GETDATE() WHERE UserUID = @UserUID**

* add this to ps_userdata.dbo.usp_Try_GameLogout_R below the update statement for dbo.usp_Insert_LoginLog_E

**UPDATE Users_Master SET Leave = 0, JoinDate = GETDATE() WHERE UserUID = @UserUID;**
