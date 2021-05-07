// MS call-convention: rcx, rdx, r8, r9...

f(char* s1, char* s2){
	if (*s2 == 0) {return s1;}
	p_s2 = s2;
	p_s1 = s1;
	char var3 = *s1;
	if(var3 == 0) {return 0;}
	delta = p_s1 - p_s2;

	do{
		p_cur = p_s2;
		if (var3 != 0) {
			do {
				var3 = *p_cur;
				if (var3 == 0) {return p_s1;}
				var5 = *(p_cur+delta);
				if(var5 != var3) {break;}
				p_cur++;
			} while (*(p_cur+delta)!=0)
		}
		
		if(*p_cur == 0) {return p_s1;}
		var3 = *(p_s1+1);
		p_s1++;
		delta++;
	} while (var3 != 0)
	return 0;
}
