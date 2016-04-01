#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

void space(FILE*,int);
void spacef(FILE*,float);

int main(int argc,char *argv[]){
  //arguments:filename(including path) of ninfo

  int i,j;
  FILE *rfp,*wfp;
  char str[300];
  char *filename_r,*filename_w;

  //for "native bond length"
  char bond[5],pp[3];
  int ibd,iunit1,iunit2,imp1,imp2,imp1un,imp2un;
  float bd_nat,fac_bd,corr_mgo,coef_bd;

  //for "native bond angles"
  char angl[5],ppp[4];
  int iba,imp3,imp3un;
  float ba_nat,fac_ba,coef_ba;

  //for "1-3 contacts with L_AICG2 or L_AICG2_PLUS"
  char aicg13[7];
  float aicg13_nat,fac_aicg13,coef_aicg13,wid_aicg13;

  //for "native dihedral angles"
  char dihd[5],pppp[5];
  int idih,imp4,imp4un;
  float dih_nat,fac_dih,coef_dih_1,coef_dih_3;

  //for "1-4 contacts with L_AICG2_PLUS"
  char aicgdih[8];
  float fac_aicg14,coef_dih,wid_dih;

  //for "native contact"
  char contact[8],p_p[4];
  int icon,dummy;
  float go_nat,fac_go,coef_go;

  //for "total_contact_unit"
  char aster[3],total[20],eq[2];
  int contact_unit;
  int total_contact_unit = 0;

  //filename setting
  filename_r = (char*)malloc(sizeof(char) * (strlen(argv[1]) + 7));
  filename_w = (char*)malloc(sizeof(char) * (strlen(argv[1]) + 8));
  sprintf(filename_r,"%s.ninfo",argv[1]);
  sprintf(filename_w,"%s_.ninfo",argv[1]);//edit if necessary

 
  //determine total_contact_unit
  if((rfp = fopen(filename_r,"r")) == NULL){
    cout << "file open error!(1)" << endl;
    exit(0);
  }
  else{
    while(fgets(str,sizeof(str),rfp) != 0){
      if(strncmp(str,"** total_contact_unit",21) == 0){
	if(sscanf(str,"%s%s%s%d",aster,total,eq,&contact_unit) == 4){
	  cout << "contact_unit = " << contact_unit << endl;
	  total_contact_unit += contact_unit;
	}
      }
    }
    cout << "total_contact_unit = " << total_contact_unit << endl;
  }
  fclose(rfp);


  //file scan and rewriting
  if((rfp = fopen(filename_r,"r")) == NULL){
    cout << "file open error!(2)" << endl;
    exit(0);
  }
  else if((wfp = fopen(filename_w,"w")) == NULL){
    cout << "file open error!(3)" << endl;
    exit(0);
  }
  else{
    while(fgets(str,sizeof(str),rfp) != 0){
      if(strncmp(str,"bond",4) == 0){
	//native bond length
	if(sscanf(str,"%s%d%d%d%d%d%d%d%f%f%f%f%s",bond,&ibd,&iunit1,&iunit2,&imp1,&imp2,&imp1un,&imp2un,&bd_nat,&fac_bd,&corr_mgo,&coef_bd,pp) ==13){

	  //write some operations

	  //writing to the file
	  fprintf(wfp,"%s   ",bond);
	  space(wfp,ibd);
	  fprintf(wfp,"%d   ",ibd);
	  space(wfp,iunit1);
	  fprintf(wfp,"%d   ",iunit1);
	  space(wfp,iunit2);
	  fprintf(wfp,"%d   ",iunit2);
	  space(wfp,imp1);
	  fprintf(wfp,"%d   ",imp1);
	  space(wfp,imp2);
	  fprintf(wfp,"%d   ",imp2);
	  space(wfp,imp1un);
	  fprintf(wfp,"%d   ",imp1un);
	  space(wfp,imp2un);
	  fprintf(wfp,"%d    ",imp2un);
	  spacef(wfp,bd_nat);
	  fprintf(wfp,"%.4f    ",bd_nat);
	  spacef(wfp,fac_bd);
	  fprintf(wfp,"%.4f    ",fac_bd);
	  spacef(wfp,corr_mgo);
	  fprintf(wfp,"%.4f    ",corr_mgo);
	  spacef(wfp,coef_bd);
	  fprintf(wfp,"%.4f ",coef_bd);
	  fprintf(wfp,"%s",pp);
	  fprintf(wfp,"\n");
	}
      }
      
      else if(strncmp(str,"angl",4) == 0){
	//native bond angles
	if(sscanf(str,"%s%d%d%d%d%d%d%d%d%d%f%f%f%f%s",angl,&iba,&iunit1,&iunit2,&imp1,&imp2,&imp3,&imp1un,&imp2un,&imp3un,&ba_nat,&fac_ba,&corr_mgo,&coef_ba,ppp) ==15){

	  //write some operations

	  //writing to the file
	  fprintf(wfp,"%s   ",angl);
	  space(wfp,iba);
	  fprintf(wfp,"%d   ",iba);
	  space(wfp,iunit1);
	  fprintf(wfp,"%d   ",iunit1);
	  space(wfp,iunit2);
	  fprintf(wfp,"%d   ",iunit2);
	  space(wfp,imp1);
	  fprintf(wfp,"%d   ",imp1);
	  space(wfp,imp2);
	  fprintf(wfp,"%d   ",imp2);
	  space(wfp,imp3);
	  fprintf(wfp,"%d   ",imp3);
	  space(wfp,imp1un);
	  fprintf(wfp,"%d   ",imp1un);
	  space(wfp,imp2un);
	  fprintf(wfp,"%d   ",imp2un);
	  space(wfp,imp3un);
	  fprintf(wfp,"%d    ",imp3un);
	  spacef(wfp,ba_nat);
	  fprintf(wfp,"%.4f    ",ba_nat);
	  spacef(wfp,fac_ba);
	  fprintf(wfp,"%.4f    ",fac_ba);
	  spacef(wfp,corr_mgo);
	  fprintf(wfp,"%.4f    ",corr_mgo);
	  spacef(wfp,coef_ba);
	  fprintf(wfp,"%.4f ",coef_ba);
	  fprintf(wfp,"%s",ppp);
	  fprintf(wfp,"\n");
	}
      }
      else if(strncmp(str,"aicg13",6) == 0){
	//1-3 contacts with L_AICG2 or L_AICG2_PLUS
	if(sscanf(str,"%s%d%d%d%d%d%d%d%d%d%f%f%f%f%f%s",aicg13,&iba,&iunit1,&iunit2,&imp1,&imp2,&imp3,&imp1un,&imp2un,&imp3un,&aicg13_nat,&fac_aicg13,&corr_mgo,&coef_aicg13,&wid_aicg13,ppp) ==16){

	  //write some operations

	  //writing
	  fprintf(wfp,"%s   ",aicg13);
	  space(wfp,iba);
	  fprintf(wfp,"%d   ",iba);
	  space(wfp,iunit1);
	  fprintf(wfp,"%d   ",iunit1);
	  space(wfp,iunit2);
	  fprintf(wfp,"%d   ",iunit2);
	  space(wfp,imp1);
	  fprintf(wfp,"%d   ",imp1);
	  space(wfp,imp2);
	  fprintf(wfp,"%d   ",imp2);
	  space(wfp,imp3);
	  fprintf(wfp,"%d   ",imp3);
	  space(wfp,imp1un);
	  fprintf(wfp,"%d   ",imp1un);
	  space(wfp,imp2un);
	  fprintf(wfp,"%d   ",imp2un);
	  space(wfp,imp3un);
	  fprintf(wfp,"%d    ",imp3un);
	  spacef(wfp,aicg13_nat);
	  fprintf(wfp,"%.4f    ",aicg13_nat);
	  spacef(wfp,fac_aicg13);
	  fprintf(wfp,"%.4f    ",fac_aicg13);
	  spacef(wfp,corr_mgo);
	  fprintf(wfp,"%.4f    ",corr_mgo);
	  spacef(wfp,coef_aicg13);
	  fprintf(wfp,"%.4f    ",coef_aicg13);
	  spacef(wfp,wid_aicg13);
	  fprintf(wfp,"%.4f ",wid_aicg13);
	  fprintf(wfp,"%s",ppp);
	  fprintf(wfp,"\n");
	}
      }
      else if(strncmp(str,"dihd",4) == 0){
	//native dihedral angles
	if(sscanf(str,"%s%d%d%d%d%d%d%d%d%d%d%d%f%f%f%f%f%s",dihd,&idih,&iunit1,&iunit2,&imp1,&imp2,&imp3,&imp4,&imp1un,&imp2un,&imp3un,&imp4un,&dih_nat,&fac_dih,&corr_mgo,&coef_dih_1,&coef_dih_3,pppp) ==18){

	  //write some operations

	  //writing
	  fprintf(wfp,"%s   ",dihd);
	  space(wfp,idih);
	  fprintf(wfp,"%d   ",idih);
	  space(wfp,iunit1);
	  fprintf(wfp,"%d   ",iunit1);
	  space(wfp,iunit2);
	  fprintf(wfp,"%d   ",iunit2);
	  space(wfp,imp1);
	  fprintf(wfp,"%d   ",imp1);
	  space(wfp,imp2);
	  fprintf(wfp,"%d   ",imp2);
	  space(wfp,imp3);
	  fprintf(wfp,"%d   ",imp3);
	  space(wfp,imp4);
	  fprintf(wfp,"%d   ",imp4);
	  space(wfp,imp1un);
	  fprintf(wfp,"%d   ",imp1un);
	  space(wfp,imp2un);
	  fprintf(wfp,"%d   ",imp2un);
	  space(wfp,imp3un);
	  fprintf(wfp,"%d   ",imp3un);
	  space(wfp,imp4un);
	  fprintf(wfp,"%d    ",imp4un);
	  spacef(wfp,dih_nat);
	  fprintf(wfp,"%.4f    ",dih_nat);
	  spacef(wfp,fac_dih);
	  fprintf(wfp,"%.4f    ",fac_dih);
	  spacef(wfp,corr_mgo);
	  fprintf(wfp,"%.4f    ",corr_mgo);
	  spacef(wfp,coef_dih_1);
	  fprintf(wfp,"%.4f    ",coef_dih_1);
	  spacef(wfp,coef_dih_3);
	  fprintf(wfp,"%.4f ",coef_dih_3);
	  fprintf(wfp,"%s",pppp);
	  fprintf(wfp,"\n");
	}
      }
      else if(strncmp(str,"aicgdih",7) == 0){
	//1-4 contacts with L_AICG2_PLUS
	if(sscanf(str,"%s%d%d%d%d%d%d%d%d%d%d%d%f%f%f%f%f%s",aicgdih,&idih,&iunit1,&iunit2,&imp1,&imp2,&imp3,&imp4,&imp1un,&imp2un,&imp3un,&imp4un,&dih_nat,&fac_aicg14,&corr_mgo,&coef_dih,&wid_dih,pppp) ==18){

	  //write some operations

	  //writing
	  fprintf(wfp,"%s   ",aicgdih);
	  space(wfp,idih);
	  fprintf(wfp,"%d   ",idih);
	  space(wfp,iunit1);
	  fprintf(wfp,"%d   ",iunit1);
	  space(wfp,iunit2);
	  fprintf(wfp,"%d   ",iunit2);
	  space(wfp,imp1);
	  fprintf(wfp,"%d   ",imp1);
	  space(wfp,imp2);
	  fprintf(wfp,"%d   ",imp2);
	  space(wfp,imp3);
	  fprintf(wfp,"%d   ",imp3);
	  space(wfp,imp4);
	  fprintf(wfp,"%d   ",imp4);
	  space(wfp,imp1un);
	  fprintf(wfp,"%d   ",imp1un);
	  space(wfp,imp2un);
	  fprintf(wfp,"%d   ",imp2un);
	  space(wfp,imp3un);
	  fprintf(wfp,"%d   ",imp3un);
	  space(wfp,imp4un);
	  fprintf(wfp,"%d    ",imp4un);
	  spacef(wfp,dih_nat);
	  fprintf(wfp,"%.4f    ",dih_nat);
	  spacef(wfp,fac_aicg14);
	  fprintf(wfp,"%.4f    ",fac_aicg14);
	  spacef(wfp,corr_mgo);
	  fprintf(wfp,"%.4f    ",corr_mgo);
	  spacef(wfp,coef_dih);
	  fprintf(wfp,"%.4f    ",coef_dih);
	  spacef(wfp,wid_dih);
	  fprintf(wfp,"%.4f ",wid_dih);
	  fprintf(wfp,"%s",pppp);
	  fprintf(wfp,"\n");
	}
      }
      else if(strncmp(str,"contact",7) == 0){
	//native contact
	if(sscanf(str,"%s%d%d%d%d%d%d%d%f%f%d%f%s",contact,&icon,&iunit1,&iunit2,&imp1,&imp2,&imp1un,&imp2un,&go_nat,&fac_go,&dummy,&coef_go,p_p) == 13){

	  //write some operations

	  //writing
	  fprintf(wfp,"%s   ",contact);
	  space(wfp,icon);
	  fprintf(wfp,"%d   ",icon);
	  space(wfp,iunit1);
	  fprintf(wfp,"%d   ",iunit1);
	  space(wfp,iunit2);
	  fprintf(wfp,"%d   ",iunit2);
	  space(wfp,imp1);
	  fprintf(wfp,"%d   ",imp1);
	  space(wfp,imp2);
	  fprintf(wfp,"%d   ",imp2);
	  space(wfp,imp1un);
	  fprintf(wfp,"%d   ",imp1un);
	  space(wfp,imp2un);
	  fprintf(wfp,"%d   ",imp2un);
	  spacef(wfp,go_nat);
	  fprintf(wfp,"%.4f   ",go_nat);
	  spacef(wfp,fac_go);
	  fprintf(wfp,"%.4f   ",fac_go);
	  space(wfp,dummy);
	  fprintf(wfp,"%d   ",dummy);
	  spacef(wfp,coef_go);
	  fprintf(wfp,"%.4f ",coef_go);
	  fprintf(wfp,"%s",p_p);
	  fprintf(wfp,"\n");
	}
      }
      else
	fprintf(wfp,"%s",str);
    }
  }

  return 0;
}


//print some spaces by the integer next coming 
void space(FILE *wfp, int n){
  if(n >= 0 && n < 10)
    fprintf(wfp,"   ");
  else if(n > -10 && n < 100)
    fprintf(wfp,"  ");
  else if(n > -100 && n < 1000)
    fprintf(wfp," ");
}

void spacef(FILE *wfp, float f){
  if(f >= 0 && f < 10)
    fprintf(wfp,"   ");
  else if(f > -10 && f < 100)
    fprintf(wfp,"  ");
  else if(f > -100 && f < 1000)
    fprintf(wfp," ");
}
