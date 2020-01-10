typedef unsigned int size_t;

void *memset(void *src, int c, size_t n)
{
	unsigned int i;for(i=0;i<n;i++)((char *)src)[i]=c;
	return src;
}

void *memcpy(void *dest, const void *src, size_t n)
{
	unsigned int i;for(i=0;i<n;i++)((char*)dest)[i]=((char *)src)[i];
	return dest;
}

int memcmp (const void *vl, const void *vr, size_t n)
{
	unsigned int i;
	for(i=0;i<n && ((char *)vl)[i]==((char *)vr)[i];i++);
	if(i>=n) return -1;
	else return 0;
}
char * strcpy(char *dest,const char *src)
{
	unsigned int i;
	for(i=0;src[i];i++)dest[i]=src[i];
	dest[i]='\0';
	return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
	memcpy(dest,src,n);
	dest[n]='\0';
	return dest;
}

size_t strlen (const char *s)
{
	unsigned int i;
	for(i=0;s[i];i++);
	return i;
}

int strcmp (const char *s1, const char *s2)
{
	return memcmp(s1,s2,strlen(s2)+1);
}

int strncmp (const char *s1, const char *s2, size_t n)
{
	return memcmp(s1,s2,n);	
}

