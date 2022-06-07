#include <stdio.h>
#include <math.h>
double Acceleration(double m,double T){ //akceleracia motora
    double result_As;
    result_As = T/m;
    return result_As;
}

double df_height(double g,double H,double m,double T){
    double result_df;
    double tmp;
    tmp = Acceleration(m,T);
    result_df = (tmp-g)*H/tmp;
    //printf("df = %lf\n",result_df);
    return result_df;

}
double de_height(double g,double H,double m,double T){
    double result_de;
    double tmp = df_height(g,H,m,T);
    result_de = H - tmp; 
    return result_de;
}


double t_calc(double dt,double t){
    double t_result;
    t_result = t+dt;
    return t_result;
}

double v_calc(double dt,double a,double v){
    double v_result;
    v_result = v + a*dt;
    return v_result;
}

double h_calc(double dt,double a,double h,double v){
    double h_result;
    //printf("V = %f\n",v);
    h_result = h + (v*dt)+((a*pow(dt,2))/2);
    return h_result;
}
void simulation(double g,double H,double m,double T,double vsoft,double dt,int count,int countrow_max){
    int s; // stav motora
   // double h = H,t,v; //aktual vyska,cas,rychlost
    double tmp = de_height(g,H,m,T);
    double a;
    double acceler = Acceleration(m,T);
    int countrow_tmp = 0;
    int count_row = 0;
    double h = H,t = 0,v = 0;
    while(h>=0){
        if (h<=tmp && v<vsoft){
            s = 1;
            count +=1;
        }
        else
            s = 0;
        if (s==1 && countrow_tmp ==1){
            count_row+=1;
            if (countrow_max<count_row)
            countrow_max = count_row;
        }
        else 
            count_row = 0;
        if (s == 0)  
            a = - g;
        else
            a = acceler - g;
        printf("s=%d h=%08.3lf t=%.3lf v=%.3lf\n",s,h,t,v);
        t = t_calc(dt,t); 
        h = h_calc(dt,a,h,v);
        v = v_calc(dt,a,v); 
        countrow_tmp = s;   // predchadzajuci
    }
    printf("---Landed---\n");
    printf("h    =%08.3lf\nt    =%8.3lf\nv    =%8.3lf\ntotal=%4d\nmax  =%4d",h,t,v,count,countrow_max+1);
}
int main()
{
    int count = 0,countrow_max = 0;
    double m,T,H,g,vsoft,dt;
    scanf("%lf %lf %lf %lf %lf %lf",&m,&T,&H,&g,&vsoft,&dt);
    printf("m=%.3lf\nT=%.3lf\nH=%.3lf\ng=%.3lf\nvsoft=%.3lf\ndt=%.3lf\n",m,T,H,g,vsoft,dt);
    printf("de=%.3f\n",de_height(g,H,m,T));
    simulation(g,H,m,T,vsoft,dt,count,countrow_max);
    return 0;
}