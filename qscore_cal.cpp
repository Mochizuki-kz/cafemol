#include "cstdio"
#include "cstring"
#include "cmath"
#include "cstdlib"
#include "iostream"

using namespace std;
double distance(int,int,double*,double*,double*);

int main(int argc,char *argv[]){
  //argument: molcule_name,filename(ninfo),filename(movie),residues_range(start & end)
  //example: cftr_nbd1 comple_bond+ nbd1_300K_cHP1.00_1 1 108

  if(argc < 5){
    printf("improper arguments!\n");
    exit(1);
  }

  int i,j;//for loop
  FILE *fp,*fp2;
  char *filename_ninfo,*filename_movie,*filename_o;
  char *path_ninfo,*path_movie;
  char str[200];//for file read

  //ninfo data
  const int max_con = 3000;
  char contact[8],p_p[4];
  int icon[max_con],iunit1,iunit2,imp1[max_con],imp2[max_con],imp1un,imp2un,dummy;
  double go_nat[max_con],fac_go,coef_go;

  //movie data
  const int max_resc = 400;
  char atom[5],ca[3],restype[4],unit[2];
  int atmno[max_resc],resno;
  double x[max_resc],y[max_resc],z[max_resc],v1,v2;

  //range where qscores are calculated
  int start = atoi(argv[4]);
  int end = atoi(argv[5]);

  int conc,conc_nat,conc_nat_all;
  const int step_div = 10000;
  const int steps = 5000;
  double qscore;
  int now_step;

  //filename
  filename_ninfo = (char*)malloc(sizeof(char) * (strlen(argv[1]) + strlen(argv[2]) + 17));
  sprintf(filename_ninfo,"../ninfo/%s/%s.ninfo",argv[1],argv[2]);
  
  filename_movie = (char*)malloc(sizeof(char) * (strlen(argv[1]) + strlen(argv[3]) + 19));
  sprintf(filename_movie,"../example/%s/%s.movie",argv[1],argv[3]);

  filename_o = (char*)malloc(sizeof(char) * (strlen(argv[1]) + strlen(argv[3]) + 29));
  sprintf(filename_o,"../example/%s/%s_qs(%d-%d).txt",argv[1],argv[3],start,end);

  //ninfo-file reading
  if((fp = fopen(filename_ninfo,"r")) == NULL){
    printf("file open error!\nfilename:%s\n",filename_ninfo);
    exit(1);
  }
  else{
    printf("\"%s\" opened.\n",filename_ninfo);
  }

  i=0;
  conc_nat = 0;
  while(fgets(str,sizeof(str),fp) != NULL){
    if(strncmp(str,"contact",7) == 0){
      if(sscanf(str,"%s%d%d%d%d%d%d%d%lf%lf%d%lf%s",contact,&icon[i],&iunit1,&iunit2,&imp1[i],&imp2[i],&imp1un,&imp2un,&go_nat[i],&fac_go,&dummy,&coef_go,p_p) == 13){
	if(imp1[i] >= start && imp2[i] <= end){
	  conc_nat++;
	}
	i++;
      }
    }
  }
  conc_nat_all = i;
  printf("native contact count(all): %d\n",conc_nat_all);
  printf("native contact count: %d\n",conc_nat);
  fclose(fp);
  free(filename_ninfo);

  //movie-file reading
  if((fp = fopen(filename_movie,"r")) == NULL){
    printf("file open error!\nfilename:%s\n",filename_movie);
    exit(1);
  }
  else{
    printf("\"%s\" opened.\n",filename_movie);
  }

  if((fp2 = fopen(filename_o,"w")) == NULL){
    printf("file open error!\nfilename:%s\n",filename_o);
    exit(1);
  }
  else{
    printf("\"%s\" opened.\n",filename_o);
    fprintf(fp2,"step qscore\n");
  }

  now_step = 0;
  i=0;
  while(fgets(str,sizeof(str),fp) != NULL){
    if(strncmp(str,"ATOM",4) == 0){
      if(sscanf(str,"%s%d%s%s%s%d%lf%lf%lf%lf%lf",atom,&atmno[i],ca,restype,unit,&resno,&x[i],&y[i],&z[i],&v1,&v2) == 11){
	i++;
      }
    }
    else if(strncmp(str,"END",3) == 0){
      //calculate qscore
      conc = 0;
      for(i=0;i<conc_nat_all;i++){
	if(imp1[i] >= start && imp2[i] <= end){
	  if(distance(imp1[i],imp2[i],x,y,z) < 1.2 * go_nat[i]){
	    conc++;
	  }
	}
      }
      qscore = conc / (conc_nat * 1.0);
      //printf("step %.8d qscore %lf\n",step_div*now_step,qscore);
      fprintf(fp2,"%.8d %.3lf\n",step_div*now_step,qscore);
      now_step++;
      i=0;
    }
  }
  printf("qscores for %d steps calculated.\n",(now_step-1)*step_div);
  fclose(fp);
  fclose(fp2);
  free(filename_movie);
  free(filename_o);
}

double distance(int m1, int m2, double *x,double *y,double *z){
  double d = sqrt(pow(x[m1-1]-x[m2-1], 2) + pow(y[m1-1]-y[m2-1], 2) + pow(z[m1-1]-z[m2-1], 2));
  return d;
}
