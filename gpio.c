#include <stdlib.h>
#include <stdio.h>
#include "gpio_lib.c"
#include <string.h>

int dy(int port,int tf)
{
    //printf("SUNXI GPIO tool\n");
    if(SETUP_OK!=sunxi_gpio_init()){
        printf("Failed to initialize GPIO\n");
        return 1;
    }
    
    if(SETUP_OK!=sunxi_gpio_set_cfgpin(SUNXI_GPD(port),OUTPUT)){
        printf("Failed to config GPIO pin\n");
        return 1;
    }
    
    int i;
    if(tf == 0){
    if(sunxi_gpio_output(SUNXI_GPD(port),LOW)){
        printf("Failed to set GPIO pin value\n");
        return 1;
    }
    }else{
        if(sunxi_gpio_output(SUNXI_GPD(port),HIGH)){
            printf("Failed to set GPIO pin value\n");
            return 1;
        }
    }
    sunxi_gpio_cleanup();
    
    return 0;
    
}

int main(int argc,char* argv[]){
    if(argc != 3){
    printf("gpio [port] [1 or 0]\n");
    return 1;
    }else{
    int a = 0;
    int i = 0;
    for(i=0;i<strlen(argv[1]);i++){
        a*=10;
        a+=argv[1][i]-'0';
    }
    //dy(a,argv[2][0]-'0');
    //printf("%d \\ %d \n",argv[1][0]-'0',argv[2][0]-'0');
    //printf("%c\n",argv[1][0]);
    return dy(a,argv[2][0]-'0');
    }
}
