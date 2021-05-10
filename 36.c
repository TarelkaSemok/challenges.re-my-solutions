f(a, b) {
	if (a == 0) {return b;}
	if (b == 0) {return a;}
	aORb = a | b;
	w2 = 31 - clz((-a) & a);			// number of tailing zeros in a
	aORb = 31 - clz(-aORb & aORb);		// number of tailong zeros in a|b
	w0 = a >> w2;						// first bit must be 1
	
	w1 = b;
	while (1) {
		w2 = clz(-w1 & w1);				// leading zeros
		w3 = 31 - clz(-w1 & w1);		// trailing zeros
		if (w1 != 0) {w2 = w3;}
		else {w2 = w2;}
		w1 = w1 >> w2;
		w2 = w1 ^ w0;
		if (w0 == w1) {break;}
		else if(w0 > w1) {
			w1 = w1 ^ w2;
			w0 = w1 ^ w2;
		}
		w1 = w1 - w0;
		if(w0 == 1) {break;}
	}
	
	w0 = w0 << aORb;
	return w0;
}

