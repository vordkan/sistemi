int main(){
    int glob = 4;
    int pid = 1;
    fork();
    glob++;
    if(!fork()){
        pid = fork();
        glob *= 2;
        pid = 0;
    }
    if(!pid) glob -= 2;
    else{
        fork();
        glob++;
    }
    printf("Valore di glob %d\n",glob);
    return 0;
}