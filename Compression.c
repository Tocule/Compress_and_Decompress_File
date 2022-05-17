#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

void reduce(FILE *fp)
{
	FILE *fp1;
	fp1=fopen("Compressed.txt","w");
	if(fp1==NULL)
	{
	    printf("Couldn't open the file to write\n");
    	    exit(0);
	}
	char ch,ch1;
	int counter=0;
	int counter1=0;
	int counter2=0;
	int n;
	
	ch=fgetc(fp);
	if(ch=='\n')
	{	
		fputc(ch,fp1);
	}	
	while(ch!=EOF)
	{
	   while(ch!='\n')
	   {
		if(ch=='/')
	     	   counter++;
		if(ch==' ')
		  counter1++;
		if((isalpha(ch)) || (ch=='}'))
		  counter2++;

		ch=fgetc(fp);
	   }
	   if(counter==110 && counter1==0)
	   {
		ch1='*';
     		fputc(ch1,fp1);
		fputc('\n',fp1);
	   }
	   if(counter==8 && counter1==102)
	   {
		ch1='#';
     		fputc(ch1,fp1);
		ch1='\n';
		fputc(ch1,fp1);
	   }
	   if(counter==8 && counter1!=102)
	   {
		ch1='%';
     		fputc(ch1,fp1);
		fseek(fp,-107,SEEK_CUR);
		ch=fgetc(fp);
		while(ch!='/')
		{
		   fputc(ch,fp1);
   		   ch=fgetc(fp);
		}
		while(ch!='\n')
		{
		   ch=fgetc(fp);
   		}
		ch1='\n';
		fputc(ch1,fp1);
	   }
	   if(counter==4 && counter2!=0)
	   {
		ch1='@';
     		fputc(ch1,fp1);
		fseek(fp,-111,SEEK_CUR);
		ch=fgetc(fp);
		while(ch!='/')
                {
                   fputc(ch,fp1);
                   ch=fgetc(fp);
                }
                while(ch!='\n')
                {
                   ch=fgetc(fp);
                }
                ch1='\n';
                fputc(ch1,fp1);
	   }
	   if(counter==6 && counter2!=0)
           {
		int count=0;   
		ch1='@';
                fputc(ch1,fp1);
                fseek(fp,-111,SEEK_CUR);
                ch=fgetc(fp);
                while(ch!='/' || count!=2)
                {
		   if(ch=='/')
		     count++;	   
                   fputc(ch,fp1);
                   ch=fgetc(fp);
                }
                while(ch!='\n')
                {
                   ch=fgetc(fp);
                }
                ch1='\n';
                fputc(ch1,fp1);
	   }		   
   	   if(counter==4 && counter2==0)
	   {
		ch1='!';
     		fputc(ch1,fp1);
		fseek(fp,-111,SEEK_CUR);
		ch=fgetc(fp);
		while(ch!=' ')
		{
		   fputc(ch,fp1);
   		   ch=fgetc(fp);
		}
		while(ch!='\n')
		{
		  ch=fgetc(fp);
  		}
		ch1='\n';
                fputc(ch1,fp1);
	  }
	  if(counter>8 && counter!=110)
       	  {
		ch1='$';
		fputc(ch1,fp1);
		ch1='\n';
                fputc(ch1,fp1);
	  }
	  counter=0;
	  counter1=0;
          counter2=0;

	  ch=fgetc(fp);
      }	  
fclose(fp);
fclose(fp1);
}

void recover(FILE *fp2)
{
     FILE *fp3;
     fp3=fopen("Uncompressed.txt","w");
     if(fp3==NULL)
     {
	 printf("Error opening the file\n");
	 exit(0);
     }
     char ch,ch1;
     int i;
     ch=fgetc(fp2);
     if(ch=='\n')
     {
	  fputc(ch,fp3);
     }  	  
     while(ch!=EOF)
     {
	 if(ch=='*')
    	 {
	     for(i=0;i<110;i++)
    	     {
		ch1='/';
		fputc(ch1,fp3);
	     }
	     ch1='\n';
	     fputc(ch1,fp3);
	     ch=fgetc(fp2);
	}
	if(ch=='#')
        {
	     for(i=0;i<4;i++)
     	     {
		 ch1='/';
		 fputc(ch1,fp3);
	     }
	     for(i=0;i<102;i++)
	     {
		ch1=' ';
   		fputc(ch1,fp3);
	     }
	     for(i=0;i<4;i++)
	     {
		ch1='/';
   		fputc(ch1,fp3);
	     }
	     ch1='\n';
	     fputc(ch1,fp3);
	     ch=fgetc(fp2);
	}
	if(ch=='%')
	{
	    for(i=0;i<4;i++)
            {
                ch1='/';
                fputc(ch1,fp3);
            }
	    ch=fgetc(fp2);
    	    while(ch!='\n')
	    {
		fputc(ch,fp3);
		ch=fgetc(fp2);
    	    }
	    for(i=0;i<4;i++)
	    {
		ch1='/';    
		fputc(ch1,fp3);
    	    }
	    ch1='\n';
	    fputc(ch1,fp3);
	}
	if(ch=='@')
	{
	    ch=fgetc(fp2);
            while(ch!='\n')
            {
                fputc(ch,fp3);
                ch=fgetc(fp2);
            }
	    for(i=0;i<4;i++)
	    {
		ch1='/';
    		fputc(ch1,fp3);
	    }
	    ch1='\n';
	    fputc(ch1,fp3);
	}
	if(ch=='!')
	{
	    ch=fgetc(fp2);
    	    while(ch!='\n')
	    {
		fputc(ch,fp3);
    		ch=fgetc(fp2);
	    }
	    for(i=0;i<102;i++)
	    {
		ch1=' ';
    		fputc(ch1,fp3);
	    }
	    for(i=0;i<4;i++)
	    {
		ch1='/';
    		fputc(ch1,fp3);
	    }
	    ch1='\n';
	    fputc(ch1,fp3);
	}
	if(ch=='$')
	{
	    for(i=0;i<49;i++)
	    {
		ch1='/';
    		fputc(ch1,fp3);
	    }
	    for(i=0;i<2;i++)
	    {
		ch1=' ';
    		fputc(ch1,fp3);
	    }
	    fputc('C',fp3);
	    fputc('O',fp3);
	    fputc('M',fp3);
	    fputc('M',fp3);
	    fputc('E',fp3);
	    fputc('N',fp3);
	    fputc('T',fp3);
	    fputc('S',fp3);	    
	    for(i=0;i<2;i++)
            {
                ch1=' ';
                fputc(ch1,fp3);
            }
	    for(i=0;i<49;i++)
            {
                ch1='/';
                fputc(ch1,fp3);
            }
	    ch1='\n';
	    fputc(ch1,fp3);
	    ch=fgetc(fp2);
	}
	ch=fgetc(fp2);
    }
fclose(fp2);
fclose(fp3);
}     

int main(void)
{
	FILE *fp,*fp2;
	fp=fopen("original.txt","r");
	if(fp==NULL)
	{
	    printf("Couldn't open the file to read\n");
    	    exit(0);
	}
	reduce(fp);

	fp2=fopen("Compressed.txt","r");
	if(fp2==NULL)
	{
	   printf("Couldn't open the compressed file to read\n");
   	   exit(0);
	}
	recover(fp2);	

}	
