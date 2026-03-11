/* zipador.c */

#include "zipador.h"

bool increase(amtlist **list){
    amtlist *p;
    int64 size;
    int32 len;
    if(!*list || ((*list)->capacity >= Maxcap))
        return false;
    len = (*list)->capacity + Blocksize;
    size = (sizeof(struct s_amtlist)+(sizeof(amtentry)*len));
    p = (amtlist *)ralloc(*list,size);
    if(!p)
        return false;
    else{
        p->capacity = len;
        *list = p;
    }
    return true;
}

bool amtadd(amtlist *list, amtentry e){
    int32 idx;
    if(!list)
        return false;
    if(list->lenght == list->capacity){
        if (list-> capacity >= Maxcap)
            return false;
        else if (!increase(&list))
            return false;
    }

    idx = list-> lenght;
    list->data[idx] = e;
    list -> lenght ++;
    return true;
}

void showamtlist(const char *identifier, amtlist *list){
    if(!list)
        return;
    
    printf("(amtlist *)%s = {} \n", identifier);
    printf("(capacity *)%d = {} \n",$i list->capacity);
    printf("(lenght *)%d = {} \n",$i list->lenght);
    return;
}

amtlist *mkamtlist(){
    int32 size;
    amtlist *p;
    size = (sizeof(struct s_amtlist)+(sizeof(amtentry)* Blocksize));
    p = (amtlist *)alloc(size);
    if(!p)
        return (amtlist *)0;
    zero($8 p, size);
    p->lenght = 0;
    p->capacity = Blocksize;
    return p;
}

void zero(int8 *dst, int32 size){
    int8 *p;
    int32 n;
    for(p=dst, n=size;n;p++,n--)
    *p = 0;
    return ;
}

int main(){
    bool ret;
    amtlist *list;
    int32   n;
    amtentry e = {0xaabbccdd, 5};

    list = mkamtlist();
    if(!list)
        return 1;
    show(list);
    for(n=0;n<0x11000;n++)
        amtadd(list,e);
    
    destroy(list);
    return 0;
}
