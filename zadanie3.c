#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define max 1000

void printpole(int lenght,char line[]){
    int i = 0;
    for (i = 0;i<lenght;i++)
        printf("%c",line[i]);
}

void default_case(int *lenght,char line[]){
    int i,j = 0;
    for (i = 0; i < *lenght ;i++){
        if (isdigit(line[i]) != 0){ //nie je cislo,uloz znak do pola
            continue;}
        else if (ispunct(line[i]) != 0){
            continue;}
        else{
            line[j] = line[i];
            j++;
        }
    }
    *lenght = j; //nova dlzka 
}

void d_case(int *lenght,char line[]){
    int i = 0,j = 0;
    for (i = 0; i < *lenght ;i++){
        if (ispunct(line[i]) != 0)
            continue;
        else{
            line[j] = line[i];
            j++;}
    }     *lenght = j; //nova dlzka 6
}

void p_case(int *lenght,char line[]){
    int i = 0,j = 0;
    for (i = 0; i < *lenght ;i++){
        if (isdigit(line[i]) != 0)
            continue;
        else{
            line[j] = line[i];
            j++;}
    }
    *lenght = j; //nova dlzka 
}

void lowercase(int lenght,char line[]){
    int i = 0;
    for(i = 0; i < lenght ;i++){
        line[i] = tolower(line[i]);
    }
}

void uppercase(int lenght,char line[]){
    int i = 0;
    for(i = 0; i < lenght ;i++){
        line[i] = toupper(line[i]);
    }
}

void case_r(int lenght,char line[],char slovo[]){
    int i = 0;
    int k = 0;
    int lenght_slovo = strlen(slovo);
    for(i = 0;i < lenght;i++){
        if(isalnum(line[i]) != 0){
            if(k == lenght_slovo){
                line[i] = line[i];
            }
            else{
            line[i] = slovo[k];
            k++;
            }
        }
        else{
            k = 0;
        }
    }
}

void case_r_nword(char line[],char slovo[],char *nword[]){
    int start = 0,end = 0,strlenght = 0;
    char *ptr;
        while(1){
            ptr = strstr(line+end,*nword);
            if(ptr == NULL){
            break;
            }
            start = ptr - line;
            end = start;  
            while(isalnum(line[end]) != 0){
                end++;
            }
            if(isalnum(line[start-1]) != 0 && start != 0){
                continue; 
            }
            strlenght = end-start;
            if (strlen(slovo)<strlenght)
                strlenght = strlen(slovo);
            strncpy(ptr,slovo,strlenght);  
    }
}

void case_R1(int lenght,char line[],char slovo[]){
    int i = 0;
    int k = 0;
   // printf("\nsom tu 1;");
    int lenght_slovo = strlen(slovo);
    for(i = 0;i<lenght;i++){
        if(isalnum(line[i]) !=0 ){
            if (k == lenght_slovo){
                line[i] = line[i];
            }
            else{
                if(isupper(line[i]) != 0 && isdigit(line[i]) == 0){
                    line[i] = toupper(slovo[k]);
                    //printf("\nsom tu 13;");
                    k++;}
                else if(isupper(line[i]) == 0 && isdigit(line[i]) == 0){
                    line[i] = tolower(slovo[k]);
                   // printf("\nsom tu 14;");
                    k++;}
                else{
                    line[i] = slovo[k];
                  //  printf("\nsom tu 15;");
                    k++;}
                }   
        }
        else{
            k = 0;
        }
    }
}

void case_R_nword(int lenght,char line[],char slovo[],char *nword[]){
   int i = 0,start = 0,end = 0,strlenght = 0;
 //  printf("som tu 16;");
   int lenght_nword = strlen(*nword);
   int lenght_slovo = strlen(slovo);
   char copy_line[lenght+1];
   char copy_nword[lenght_nword+1];
   char *ptr;
   strcpy (copy_line,line);
   strcpy(copy_nword,*nword);
   for(i = 0;i<lenght;i++){
    copy_line[i] = tolower(copy_line[i]);
   }
   for(i = 0;i<lenght_nword;i++){
    copy_nword[i] = tolower(copy_nword[i]);
   }
   while(1){ 
      ptr = strstr(copy_line+end,copy_nword);
      if(ptr == NULL)
         break;
      start = ptr - copy_line;
      end = start;
      while(isalnum(copy_line[end]) != 0){
         end++;
      }

      if(isalnum(copy_line[start-1]) != 0 && start != 0){  //&& doplnene
         continue; 
      }

      strlenght = end - start;
      for(i = 0;i<strlenght;i++){ //start = 0 end = 10
         if(i >= lenght_slovo)
            line[start+i] = line[start+i];
         else{
         if(isupper(line[start+i]) != 0 && isdigit(line[start+i]) == 0) //1
            line[start+i] = toupper(slovo[i]);
         else if(isupper(line[start+i]) == 0 && isdigit(line[start+i]) == 0)
            line[start+i] = tolower(slovo[i]);
         else
            line[start+i] = slovo[i];
         }
      }
   }
}

int main(int argc, char *argv[]){
    char used_opt[5] = {' '};
    char line[max];
    char *parameter;
    char *ptr;
    char **ptr1;
    char *Nwords[100];
    char tmp;
	int opt,i = 0,k = 0 ,lenght = 0,count = 0;
	char* optstring = "-:dpulr:R:";

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        ptr = &used_opt[i];
        switch (opt)
        {
        case 'd':
            *ptr = 'd';
            i+=1;
            break;
        case 'p':
            *ptr = 'p';
            i+=1;
            break;    
        case 'u':
            *ptr = 'u';
            i+=1;
            break;
        case 'l':
            *ptr = 'l';
            i+=1;
            break;
        case 'r':
            *ptr = 'r';
            parameter = optarg;       
            i+=1;
            break;
        case 'R':
            *ptr = 'R';
            parameter = optarg;
            i+=1;
            break;
        case 1:
            Nwords[count] = optarg;
            count ++;
            break;
        case ':':
            return 2;
        default: 
            return 1;
        } 
    }

    while(1)
    {   
        fgets(line,max,stdin);
        if(line[0] == '\n'){
            break;
            }
        

        lenght = strlen(line);
        k = 0;
        for(i = 0;i<5;i++){
            ptr = &used_opt[i]; //{" "} {d} {p} {d,p}
            if(*ptr == 'p'){
            tmp = 'p';
            k +=1;
            continue;}
            if(*ptr == 'd'){
            tmp = 'd';
            k+=1;
            continue;}
        }
/***************************************UPRAVA PRVY TEST************************/
        if(k == 0)
            default_case(&lenght,line); //konverzia iba pismena
        else if(tmp == 'd' && k!=2)
            d_case(&lenght,line);    //konverzia 
        else if(tmp == 'p' && k!=2)
            p_case(&lenght,line);

        for(i = 0;i<5;i++){
            ptr = &used_opt[i];
            if(*ptr == 'l')
            lowercase(lenght,line);
            else if(*ptr == 'u')
            uppercase(lenght,line);
        }
        for(i = 0;i < 5;i++){
            ptr = &used_opt[i];
            if(*ptr == 'r' && count == 0){
                case_r(lenght,line,parameter);
                break;
               }
            if(*ptr == 'r' && count != 0){
                for(k = 0;k<count;k++){
                    ptr1 = &Nwords[k];
                    case_r_nword(line,parameter,ptr1);
                }  
                break;
            }
            if(*ptr == 'R' && count == 0){
                case_R1(lenght,line,parameter);
                break;
            }
            if(*ptr == 'R' && count != 0){
                for(k = 0;k<count;k++){
                    ptr1 = &Nwords[k];
                    case_R_nword(lenght,line,parameter,ptr1);
                } 
            }
        }   
    printpole(lenght,line);    
    }
	return 0;
}