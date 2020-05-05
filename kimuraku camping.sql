IF @ActionType = 108 -- character leaving game
BEGIN
    IF EXISTS (SELECT CharID, Map, Family FROM PS_GameData.dbo.Chars -- check AoL Kimu camping
	  WHERE CharID = @CharID AND Map BETWEEN 9 AND 11 AND Family BETWEEN 0 AND 1) -- AoL logout in D2
	  BEGIN -- gets here if the light character logged out on any floor in D2
	  UPDATE PS_GameData.dbo.Chars SET Map = 0, PosX = 763.0, PosY = 29.0, PosZ = 1258.0 -- D-Water
	  WHERE CharID = @CharID -- they will spawn outside the D2 portal for their faction
	  END
	  
	  ELSE IF EXISTS (SELECT CharID, Map, Family FROM PS_GameData.dbo.Chars -- check UoF Kimu camping
	  WHERE CharID = @CharID AND Map BETWEEN 9 AND 11 AND Family BETWEEN 2 AND 3) -- UoF logout in D2
	  BEGIN -- gets here if the fury character logged out on any floor in D2
	  UPDATE PS_GameData.dbo.Chars SET Map = 0, PosX = 1319.0, PosY = 49.0, PosZ = 1472.0 -- D-Water
	  WHERE CharID = @CharID -- they will spawn outside the D2 portal for their faction
	  END
END	 
