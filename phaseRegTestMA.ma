[top]
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



