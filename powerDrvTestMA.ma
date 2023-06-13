[top]
components : powerdriver@PowerDrv
in : c_power_set c_powerlevel_in
out : c_powerlevel_out
Link : c_power_set power_set@powerdriver
Link : c_powerlevel_in powerlevel_in@powerdriver
Link : heatlevel_out@powerdriver c_powerlevel_out
