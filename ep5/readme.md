**contents**

* revised version of shen's item mall solution for ep5 servers along with the source code

* ps_game that has been reversed to have no custom dll injections for those that don't want an item mall

* ps_dbAgent for ep5 that doesn't dc after 10 item mall purchases

* possible solution for capes being enchanted via client modification (likely accompanied by packet injection)

* ct files that help solve issues with rune skill cutting by delaying the use of runes after using skills

* ct file that will prevent rangers and assassins from adding or removing gear in stealth mode

* ct file that will remove the code that keeps guards from detecting a character in stealth mode

* ct file that will prevent the service from crashing if a gm dismounts while invisible (reported by two admins)

* ct files that disable the /iclear, /eclear, and /warning commands

* ct file that blocks defenders and guardians from using skill reset stones and blocks target res runes in grb


**notes**

* the ps_game has an extra code section that begins at address 04096000 that can be used for code caves ^_^
