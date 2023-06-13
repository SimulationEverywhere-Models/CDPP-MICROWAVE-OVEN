[top]
components : curtime@CurTimeRegister
in : n_time_set n_hours n_minutes
out : n_cur_time
Link : n_time_set time_set@curtime
Link : n_hours hours@curtime
Link : n_minutes minutes@curtime
Link : cur_time@curtime n_cur_time
