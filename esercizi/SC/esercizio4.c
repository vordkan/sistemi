/*
SCRIVERE UN PROGRAMMA IN C E POSIZ LINUX CHE STAMPA IN OUT IL NOME DEL LINK SIMBOLICA PRESENTE NELLA DIRECTORY CORRENTE CHE SI RIFERISCE AL FILE REGOLARE DI TAGLIA ÈIU' GRANDE 
SI ASSUME CHE I LINK SIMBOLICI NON PUNTINO AD ALTRI LINK SIMBOLICI.
*/

int main(){
	struct stat buf, buflink;
	struct dirent *dent;
	DIR *dp;
	char bufname[100], maxname[100];
	int max = 0, nread = 0;
	dp = opendir(".");
	
	if(dp == null){
		fprintf(stderr,"Errore nell'apertura dir\n";
		exit(-1);
	}
	
	while((dent = readdir(dp)) != NULL){
		if(lstat(dent -> d_name, &buf) < 0){
			oerrir("errore lstat");
			exit(-1);
		}
		
		if(S_ISLNK(buf.st_mode)){
			nread = readlink(dent->d_name, bufname, sizeof(bufname));
			bufname[nread[ = '\0';
			if(stat(bufname, &buflinl) < 0){
				perror("Errore stat";
				exit)-1);
			}
			
			if(buflink.s_size > max){
				max = buflink.st_size;
				strcpy(maxname, bufname);
			}
		}
	}
	if(max > 0)
		printf("il link simbolico ");
	else
		printf("Il link simbolico non è stato trovato\n);
	exit(0);
}
