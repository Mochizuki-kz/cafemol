#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){
  //input: filename,trajectory_number(start & end)
  int i;
  FILE *rfp,*wfp;
  char str[120];
  char *filename_r,*filename_w;
  //in this program, filenames include their paths.
  int start,end;
  bool flag1,flag2;//flag for escaping to write the informations of the same steps 2 times
  //flag1: for the first file of the trajectory, false
  //flag2: for the first time-step of each file, false

  filename_r = (char*)malloc(sizeof(char) * (strlen(argv[1]) + 12));
  filename_w = (char*)malloc(sizeof(char) * (strlen(argv[1]) + 12));

  //output file open
  sprintf(filename_w,"%s_full.movie",argv[1]);
  if((wfp = fopen(filename_w,"w")) == NULL){
    cout << "file open error!(w)" << endl;
    exit(1);
  }
  else{
    cout << "\"" << filename_w << "\"" << " opened." << endl;
  }

  start = atoi(argv[2]);
  end = atoi(argv[3]);

  flag1 = false;
  for(i=start;i<=end;i++){
    //input file open
    sprintf(filename_r,"%s_%d.movie",argv[1],i);
    if((rfp = fopen(filename_r,"r")) == NULL){
      cout << "file open error!(" << filename_r << ")" << endl;
      exit(1);
    }
    else{
      cout << "\"" << filename_r << "\"" << " opened." << endl;
    }
    
    flag2 = false;
    //file read and write
    while(fgets(str,sizeof(str),rfp) != NULL){
      if(flag1 == false || flag2 == true){
	fprintf(wfp,"%s",str);
      }
      if(strncmp(str,"END",3) == 0){
	flag2 = true;
      }
    }
    fclose(rfp);
    flag1 = true;
  }
}
