// casting the data from the text file to arrays
void castdata(string filename, int* xs, int* ys, int* sigmas, int* lasts){
    ifstream txtfile(filename);
    string line;
    string value;
	int q=0;

    while(getline(txtfile, line)){
		// cout<<"q="<<q<<endl<<line<<endl;

		stringstream ss(line);
		string value;

		getline(ss, value, ',');
		xs[q]=stoi(value);

		getline(ss, value, ',');
		ys[q] = stoi(value);

		getline(ss, value, ',');
		sigmas[q] = stoi(value);

		getline(ss, value, ',');
		lasts[q] = stoi(value);

		// cout<<"xs[q]="<<xs[q]<<", ys[q]="<<ys[q]<<", sigmas[q]="<<sigmas[q]<<", lasts[q]="<<lasts[q]<<endl;
		q+=1;
	}
}

// processing the data
void eventloop(int* xs, int* ys, int* sigmas, int* lasts){

	// holding the starting and stopping indices as well as the number of entries for each of the 6 events
	int start_i[6]={0};
	int stop_i[6]={0};
	int n_i[6]={0};

	// event loop
	for(unsigned int e=0;e<6;e++){
		std::cout<<"event "<<e+1<<" is being processed"<<std::endl;

		// finding the number of entries in each event as well as index each event starts and stops at
		// looping over the lasts array, with a counter, for each event until a 1 appears then going to next event
		int flag=0;
		while(flag!=1){
			// m is number of entries in event so far + starting index of the event
			int m=n_i[e]+start_i[e];
			flag=lasts[m];
			n_i[e]+=1;
		}
		// setting stop index of the event
		stop_i[e]=start_i[e]+n_i[e]-1;
		if(e!=5){start_i[e+1]=stop_i[e]+1;}

		// determining values for event //
		// slide 12 fit parameter values
		float a0=finda_0(n_i[e], start_i[e], stop_i[e], xs, ys);
		float b0=findb_0(n_i[e], start_i[e], stop_i[e], xs, ys);
		// chi^2 value
		float chi0=normalized_chi2(n_i[e], start_i[e], stop_i[e], xs, ys, sigmas, a0, b0);
		// variances in fit parameter values
		float avar=variance_a(start_i[e], stop_i[e], xs, ys, sigmas);
		float bvar=variance_b(start_i[e], stop_i[e], xs, sigmas);

		// print statements //
		
		// while loop counting
		// std::cout<<"number of entries in event "<<e+1<<" is "<<n_i[e]<<std::endl;
		// std::cout<<"start index for event "<<e+1<<" is "<<start_i[e]<<" and lasts["<<start_i[e]<<"] is "<< lasts[start_i[e]]<<std::endl;
		// std::cout<<"stop index for event "<<e+1<<" is "<<stop_i[e]<<" and lasts["<<stop_i[e]<<"] is "<< lasts[stop_i[e]]<<std::endl;
		// slide 12 values
		// std::cout<<"fist method gives an a value of "<<a0<<" and b value of "<<b0<<" giving a normalized chi^2 of "<<chi0<<std::endl;
		std::cout<<"a="<<a0<<", b="<<b0<<", chi^2/ndf="<<chi0<<std::endl;
		// uncertainties in parameter fit values
		// std::cout<<"the variance of a is "<<avar<<" and of b is "<<bvar<<std::endl;
	}
}
