#include <stdio.h>
#include <string.h>
int main()
{
	char *link="http://www-us.apache.org/dist/hbase/stable/hbase-1.2.4-bin.tar.gz";
	char *url_begin=strstr(link,"http://");
   int i=0;
   int link_length=strlen(link);
     for(i=link_length;i>=7;i--)
	 {
        if('/'!=link[i])
		{
            continue;
        }
        else
		{
            break;
        }
     }
     
    char *SS="djfk";
	printf("%d\n",strlen(SS)); 
	printf("%c %d\n",*(url_begin+7),i);
	return 0;
}
