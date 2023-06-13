[top]
components : dis@Displayer
in : c_day_time c_counter_time
out : c_cur_time c_rem_time
Link : c_day_time day_time@dis
Link : c_counter_time counter_time@dis 
Link : cur_time@dis c_cur_time
Link : rem_time@dis c_rem_time