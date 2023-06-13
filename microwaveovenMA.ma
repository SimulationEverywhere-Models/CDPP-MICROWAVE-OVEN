[top]
components : PHASE timecookcounter@TimeCookCounter powerdriver@PowerDrv bp@BeepDrv curtime@CurTimeRegister dis@Displayer
in : c_phase_set c_powerlevel_in c_seconds c_minutes c_hours c_time_set c_start c_stop c_clear
out : beep_out c_powerlevel_out c_cur_time c_rem_time
Link : c_phase_set c_phase_set@PHASE
Link : c_phase_set phase_set@timecookcounter
Link : c_powerlevel_in c_powerlevel_in@PHASE
Link : c_seconds c_seconds@PHASE
Link : c_minutes c_minutes@PHASE
Link : c_start start@timecookcounter
Link : c_stop stop@timecookcounter
Link : c_clear clear@timecookcounter
Link : c_time_set time_set@curtime
Link : c_hours hours@curtime
Link : c_minutes minutes@curtime
Link : cur_time@curtime day_time@dis
Link : c_time_seconds@PHASE time_seconds@timecookcounter
Link : c_time_minutes@PHASE time_minutes@timecookcounter
Link : c_powerlevel_out@PHASE powerlevel_in@powerdriver
Link : power_switch@timecookcounter power_set@powerdriver
Link : beep@timecookcounter beep_in@bp
Link : time_of_cook@timecookcounter counter_time@dis
Link : rem_time@dis c_rem_time
Link : cur_time@dis c_cur_time
Link : heatlevel_out@powerdriver c_powerlevel_out
Link : sound_out@bp beep_out


[PHASE]
components : COOKTIME powlvl@PowLvlReg
in : c_phase_set c_powerlevel_in c_seconds c_minutes
out : c_time_seconds c_time_minutes c_powerlevel_out
Link : c_phase_set c_time_set@COOKTIME
Link : c_phase_set phase_set@powlvl
Link : c_seconds c_seconds@COOKTIME
Link : c_minutes c_minutes@COOKTIME
Link : c_powerlevel_in powerlevel_in@powlvl
Link : c_time_seconds@COOKTIME c_time_seconds
Link : c_time_minutes@COOKTIME c_time_minutes
Link : powerlevel_out@powlvl c_powerlevel_out

[COOKTIME]
components : mincook@MinCookReg seccook@SecCookReg
in : c_time_set c_seconds c_minutes
out : c_time_seconds c_time_minutes
Link : c_time_set time_set@seccook
Link : c_time_set time_set@mincook
Link : c_seconds seconds@seccook
Link : c_minutes minutes@mincook
Link : time_seconds@seccook c_time_seconds
Link : time_minutes@mincook c_time_minutes



