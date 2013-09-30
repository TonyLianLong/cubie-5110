#include <stdio.h>
#include <stdlib.h>
#include <iconv.h> 

#define fontfile "font_opt/HZK16"

int readout(){
 char fontdata[2000] = "";
 FILE *file  = fopen("fontout", "rb+");
 if(file==NULL){
  return 1;
 }else{
 printf("Return:%d\n",file);
 }
 int siz=fread(fontdata, sizeof(char), 1999, file);
 printf("size: %d\n",siz);
 for(int i=0;i<siz;i++){
 //printf("%d %x ",fontdata[i]);
 for(int j=0;j<8;j++){
 //printf("%d %d %d %d ---",i,fontdata[i],j,(fontdata[i] << j) & 0x80);
 if(((fontdata[i] << j) & 0x80) == 0x80){
 printf("1");
 }else{
 printf("0");
 }
 }
 if(i%2 != 0) printf("\n");
 }
 fclose(file);
 printf("\n");
 return 0;
}
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
{
    iconv_t cd;
    int rc;
    char **pin = &inbuf;
    char **pout = &outbuf;
    
    cd = iconv_open(to_charset,from_charset);
    if (cd==0) return -1;
    memset(outbuf,0,outlen);
    //printf("inlen=%d\n",inlen);
    if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
    iconv_close(cd);
    return 0;
}
int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
{
    return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
}
int read16(char txt,char txt2,char txt3,int *sz){
    const int flen = 200000;
    char *fontdata = (char *)malloc(flen);
    char in[3] = {txt,txt2,txt3};
    char out[5];
    u2g(in,3,out,5);
    int index = 94*(out[0]-0xa1)+(out[1]-0xa1);
    printf("get index:%x\n",index);
    FILE *file  = fopen(fontfile, "rb+");
    fseek(file,(index)*32,0);
    printf("ASC:%x AA:%x%x RES:%x\n",txt,out[0],out[1],index);
    int siz=fread(fontdata, sizeof(char), flen-1, file);
    printf("read size:%d\n",siz);
    for(int i=0;i<32;i++){
        printf("data:%d \n",fontdata[i]);
        sz[i] = fontdata[i];
    }
    return 0;
}
int read16_index(int index,int *sz){
    printf("get index:%x\n",index);
    const int flen = 200000;
    char *fontdata = (char *)malloc(flen);
    FILE *file  = fopen(fontfile, "rb+");
    fseek(file,(index)*32,0);
    int siz=fread(fontdata, sizeof(char), flen-1, file);
    printf("read size:%d\n",siz);
    for(int i=0;i<32;i++){
        printf("data:%d \n",fontdata[i]);
        sz[i] = fontdata[i];
    }
    return 0;
}