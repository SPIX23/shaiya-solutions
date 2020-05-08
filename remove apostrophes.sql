USE PS_GameDefs
--removes apostrophes from these columns to fix some improper syntax errors--
update dbo.Skills set SkillName=replace(SkillName,'''','');
update dbo.Mobs set MobName=replace(MobName,'''','');
update dbo.Items set ItemName=replace(ItemName,'''','');