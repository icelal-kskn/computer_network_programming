char * 
ascii( int start, int finish ){
 char *b = new char(finish-start+1);
 for (int i=start; i <= finish; ++i)
   b[i-start]=(char) i;
 return b;
}
