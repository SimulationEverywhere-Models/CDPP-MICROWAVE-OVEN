[top]
components : mincook@MinCookReg seccook@SecCookReg
in : c_time_set c_seconds c_minutes
out : c_time_seconds c_time_minutes
Link : c_time_set time_set@seccook
Link : c_time_set time_set@mincook
Link : c_seconds seconds@seccook
Link : c_minutes minutes@mincook
Link : time_seconds@seccook c_time_seconds
Link : time_minutes@mincook c_time_minutes



