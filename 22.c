// Generated with Ghidra
int f2(int *some_arr,int idx1,int idx2)

{
  uint *p_cur_elem;
  uint next_elem;
  uint *p_temp_elem;
  int res;
  longlong i;
  uint *puVar1;
  uint uVar2;
  uint cur_elem;
  
  i = 0;
  p_cur_elem = some_arr + idx2;
  res = idx1 + 1;
  cur_elem = *p_cur_elem;
  do {
    next_elem = *(p_cur_elem + i + 4);
    idx2 += 1;
    if ((cur_elem < next_elem) || (idx1 < idx2)) {
      p_temp_elem = some_arr + res + -1;
      do {
        puVar1 = p_temp_elem;
        uVar2 = *puVar1;
        res += -1;
        p_temp_elem = puVar1 + -1;
      } while (cur_elem < uVar2);
      if (res <= idx2) {
        cur_elem = *p_cur_elem;
        *p_cur_elem = uVar2 ^ cur_elem;
        cur_elem = uVar2 ^ cur_elem ^ *puVar1;
        *puVar1 = cur_elem;
        *p_cur_elem = *p_cur_elem ^ cur_elem;
        return res;
      }
      uVar2 ^= next_elem;
      *(p_cur_elem + i + 4) = uVar2;
      uVar2 ^= *puVar1;
      *puVar1 = uVar2;
      p_temp_elem = p_cur_elem + i + 4;
      *p_temp_elem = *p_temp_elem ^ uVar2;
    }
    i += 4;
  } while( true );
}
