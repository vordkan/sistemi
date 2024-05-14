int main(){
   int glob = 5; 
   int pid = 0;
   for(int i = 1; i < glob; i++){
      pid = fork();
      if (pid == 0)
         glob = glob -1;
   }
}
