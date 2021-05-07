f(double param1) {
	// xmm2 - var1
	// xmm5 - var2,
	// xmm4 - var3
	// xmm3 - var4
	double var1 = 1.0;
	double var2 = .001;
	double var3 = 0.5;
	double var4 = param1;
	
	while(1) {
		double var5 = var1**2 - var4;
		param1 = int2double(abs(int(var5)));
	    if (var2 > param1) break;
		var1 = (var4/var1 + var1) * var3;
	}
	return var1;
}
