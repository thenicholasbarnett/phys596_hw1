// summations
float sa(int start_i, int stop_i, int* as){
	float sum = 0;
	for(unsigned int i=start_i;i<stop_i+1;i++){sum+=as[i];}
	return sum;
}
float saa(int start_i, int stop_i, int* as){
	float sum = 0;
	for(unsigned int i=start_i;i<stop_i+1;i++){sum+=(as[i]*as[i]);}
	return sum;
}
float sab(int start_i, int stop_i, int* as, int* bs){
	float sum = 0;
	for(unsigned int i=start_i;i<stop_i+1;i++){sum+=(as[i]*bs[i]);}
	return sum;
}

// fit parameters
float finda_0(int n_i, int start_i, int stop_i, int* xs, int* ys){
	float sx = sa(start_i, stop_i, xs);
	float sy = sa(start_i, stop_i, ys);
	float sxx = saa(start_i, stop_i, xs);
	float sxy = sab(start_i, stop_i, xs, ys);
	float a= (sy*sxx - sxy*sx)/(n_i*sxx - sx*sx);
	return a;
}
float findb_0(int n_i, int start_i, int stop_i, int* xs, int* ys){
	float sx = sa(start_i, stop_i, xs);
	float sy = sa(start_i, stop_i, ys);
	float sxx = saa(start_i, stop_i, xs);
	float sxy = sab(start_i, stop_i, xs, ys);
	float b= (n_i*sxy - sx*sy)/(n_i*sxx - sx*sx);
	return b;
}

// slide 14 values //

// goodness of fit
float normalized_chi2(int n_i, int start_i, int stop_i, int* xs, int* ys, int* sigmas, float a, float b){
	// finding chi2
	float chi2=0;
	for(unsigned int i=start_i;i<stop_i+1;i++){chi2+= (ys[i] - a - b*xs[i])*(ys[i] - a - b*xs[i])/(sigmas[i]*sigmas[i]);}
	// normalizing by degrees of freedom
	float n=n_i;
	float nchi2 = chi2/(n-2);
	return nchi2;
}

// summations
float s_sigma(int start_i, int stop_i, int* sigmas){
	float sum=0;
	for(unsigned int i=start_i;i<stop_i+1;i++){sum+= 1/(sigmas[i]*sigmas[i]);}
	return sum;
}
float sa_sigma(int start_i, int stop_i, int* sigmas, int* as){
	float sum=0;
	for(unsigned int i=start_i;i<stop_i+1;i++){sum+= as[i]/(sigmas[i]*sigmas[i]);}
	return sum;
}
float stt(int start_i, int stop_i, int* sigmas, int* xs){
	float s=s_sigma(start_i,stop_i,sigmas);
	float sx=sa_sigma(start_i,stop_i,sigmas,xs);
	float sum=0;
	for(unsigned int i=start_i;i<stop_i+1;i++){
		float ti = (xs[i]-sx/s)/sigmas[i];
		sum+= (ti*ti);
	}
	return sum;
}

// alternate method to get fit parameters
float findb_1(int start_i, int stop_i, int* xs, int* ys, int* sigmas){
	float s=s_sigma(start_i,stop_i,sigmas);
	float sx=sa_sigma(start_i,stop_i,sigmas,xs);
	float stt_d=stt(start_i,stop_i,sigmas,xs);
	float sum=0;
	for(unsigned int i=start_i;i<stop_i+1;i++){
		float ti = (xs[i]-sx/s)/sigmas[i];
		sum+= (ti*ys[i]/sigmas[i]);
	}
	float b= sum/stt_d;
	return b;
}
float finda_1(int start_i, int stop_i, int* xs, int* ys, int* sigmas){
	float s=s_sigma(start_i,stop_i,sigmas);
	float sx=sa_sigma(start_i,stop_i,sigmas,xs);
	float sy=sa_sigma(start_i,stop_i,sigmas,ys);
	float b=findb_1(start_i,stop_i,sigmas,xs,ys);
	float a=(sy - sx*b)/s;
	return a;
}

// uncertainty in fit parameters
float variance_a(int start_i, int stop_i, int* xs, int*ys, int* sigmas){
	float s=s_sigma(start_i,stop_i,sigmas);
	float sx=sa_sigma(start_i,stop_i,sigmas,xs);
	float stt_d=stt(start_i,stop_i,sigmas,xs);
	float var_a = (1+sx*sx/(s*stt_d))/s;
	return var_a;
}
float variance_b(int start_i, int stop_i, int* xs, int* sigmas){
	float stt_d=stt(start_i,stop_i,sigmas,xs);
	float var_b = 1/stt_d;
	return var_b;
}



