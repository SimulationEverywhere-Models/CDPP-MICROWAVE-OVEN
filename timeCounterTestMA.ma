[top]
components : timecookcounter@TimeCookCounter
in : c_phase_set c_start c_stop c_clear c_seconds c_minutes
out : c_time_remaining c_powerswitch c_beep
Link : c_phase_set phase_set@timecookcounter
Link : c_seconds time_seconds@timecookcounter
Link : c_minutes time_minutes@timecookcounter
Link : c_start start@timecookcounter
Link : c_stop stop@timecookcounter
Link : c_clear clear@timecookcounter
Link : time_of_cook@timecookcounter c_time_remaining
Link : power_switch@timecookcounter c_powerswitch
Link : beep@timecookcounter c_beep