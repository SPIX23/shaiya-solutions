USE [PS_GameData]
GO
/****** Object:  StoredProcedure [dbo].[usp_Save_User_BuyPointItems2]    Script Date: 5/4/2020 1:59:29 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE Proc [dbo].[usp_Save_User_BuyPointItems2]

@UserUID int,
@CharID int,
@UsePoint int,
@ProductCode varchar(20),
@UseDate datetime

AS

SET NOCOUNT ON
--SET XACT_ABORT ON

DECLARE @UseType 	int
DECLARE @Ret 		int
DECLARE @RemainPoint  	int
DECLARE @OrderNumber 	int
DECLARE @ReturnValue int

SET @Ret = 0

SET @UseType = 1 -- ??

BEGIN DISTRIBUTED TRANSACTION

EXEC @ReturnValue = PS_UserData.dbo.usp_Update_UserPoint @UserUID, @UsePoint
IF ( @ReturnValue < 0 )
BEGIN
    GOTO ERROR
END

INSERT INTO PointLog(UseType,UserUID,CharID,UsePoint,ProductCode,UseDate,RemainPoint,OrderNumber)
VALUES(@UseType,@UserUID,@CharID,@UsePoint,@ProductCode,@UseDate,@RemainPoint,@OrderNumber)
IF( @@ERROR<>0)
BEGIN
    GOTO ERROR
END

COMMIT TRAN
RETURN 1

ERROR:
ROLLBACK TRAN
RETURN -1

SET XACT_ABORT OFF
SET NOCOUNT OFF
