use ps_gamedefs
--removes apostrophes from these columns to prevent errors
update dbo.skills set skillname=replace(skillname,'''','');
update dbo.mobs set mobname=replace(mobname,'''','');
update dbo.items set itemname=replace(itemname,'''','');
