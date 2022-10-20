# include "iostream"
# include "iomanip"
# include "math.h"
using namespace std;

void insertion();
double divide(int, int), conquer(double, double, int, int);
double find_min_three(int i, int j);
int n;

struct node{
    double x,y;
};

/*
vector<node> guns;
vector<node> c_guns;*/
node guns[10000], c_guns[10000];
int c_guns_size=0;

int main(){
    int T;
    cin>> T ;


    for(int i=0; i<T; i++){
        insertion();

        cout<<fixed;
        cout<<setprecision(6);
        cout<< divide(0,n)<<endl;
    }

    return 0;
}

void insertion(){
    int l=0, r=0, p;
    //guns.clear();
    node gun;
    cin>> n;
    for(int i=0; i<n; i++){
        l=0;
        p=i;
        cin>> gun.x>> gun.y;
        //guns.push_back(gun);
        
        //insertion sort
        /*
        for(int j=0; j<i; j++){
            if(gun.x<guns[j].x){
                for(int k=i; k>j; k--){
                    guns[k]=guns[k-1]; //move data around
                }
                guns[j]=gun;
                break;
            }
        }
        */
        if(guns[0].x>=gun.x){
            p=0;
        }
        else if(guns[r].x<=gun.x){
            p=i;
        }
        else{
            while((r-l)>1){
                if(guns[(r+l)/2].x==gun.x){
                    p=(r+l)/2;
                    break;
                }
                else if(guns[(r+l)/2].x>gun.x)
                    r=(r+l)/2;
                else
                    l=(r+l)/2;

                p=r;
            }
        }
        for(int k=i-1; k>=p; k--){
            guns[k+1]=guns[k]; //move data around
        }
        guns[p]=gun;
        r=i;
    }
    return;
    
}

// divide
double divide(int i, int j){
    double min_L, min_R, min_C;
    double center=(guns[(i+j)/2-1].x+guns[(i+j)/2].x)*0.5;

    if ((j-i)<=3)
        return find_min_three(i, j);
    else{
        min_L=divide(i, (i+j)/2);
        min_R=divide((i+j)/2, j);
        min_C=conquer(center, min(min_L, min_R), i, j);
    }
        return min(min(min_L, min_R), min_C);

}
//conquer
double conquer(double center, double range, int BC_l, int BC_r){
    int l=0, r=0, p;
    int first=BC_l, end=BC_l;
    int left, right;
    double min_distance, L2_norm;
    node gun;
    min_distance=pow(pow(guns[BC_l].x-guns[BC_l+1].x, 2)+pow(guns[BC_l].y-guns[BC_l+1].y, 2),0.5);

    //c_guns.clear();
    c_guns_size=0;

    for(int i=BC_l; i<BC_r; i++){
        if((center-range<=guns[i].x)&&(guns[i].x<=center+range)){
            //c_guns.push_back(guns[i]);
            //c_guns[c_guns_size++]=guns[i];
            //left=0;
            //right=c_guns_size;

            //insertion sort
            /*
            for(int j=0; j<i; j++){
                if(guns[i].y<c_guns[j].y){
                    for(int k=i; k>j; k--){
                        c_guns[k]=c_guns[k-1]; //move data around
                    }
                    c_guns[j]=guns[i];
                    break;
                }
            }*/
            l=0;
            p=c_guns_size;
            c_guns[p]=guns[i];

            if(c_guns[0].y>=guns[i].y){
                p=0;
            }
            else if(c_guns[r].y<=guns[i].y){
                p=c_guns_size;
            }
            else{
                while((r-l)>1){
                    if(c_guns[(r+l)/2].y==guns[i].y){
                        p=(r+l)/2;
                        break;
                    }
                    else if(c_guns[(r+l)/2].y>guns[i].y)
                        r=(r+l)/2;
                    else
                        l=(r+l)/2;

                    p=r;
                }
            }
            for(int k=c_guns_size-1; k>=p; k--){
                c_guns[k+1]=c_guns[k]; //move data around
            }
            c_guns[p]=guns[i];
            r=c_guns_size;
            c_guns_size++;
            
        }

    }   


    //Compute
    if(c_guns_size==0)//(c_guns.size()==0)
        return min_distance;/*
    else if(c_guns_size<=5){
        for(int k=1; k<=c_guns_size-1; k++){
            L2_norm=pow(pow(c_guns[0].x-c_guns[k].x, 2)+pow(c_guns[0].y-c_guns[k].y, 2),0.5);
            if(L2_norm<min_distance)
                min_distance=L2_norm;
        }
    }*/
    else{
        for(int j=0; j<c_guns_size-1; j++){
            for(int k=1; (j+k)<c_guns_size; k++){
                L2_norm=pow(pow(c_guns[j].x-c_guns[j+k].x, 2)+pow(c_guns[j].y-c_guns[j+k].y, 2),0.5);
                if(L2_norm<min_distance)
                    min_distance=L2_norm;
                
                if (k==7)
                    break;
            }
        }

    }

    return min_distance;
}

// BC
double find_min_three(int first, int end){
    double min_distance, L2_norm;
    min_distance=pow(pow(guns[first].x-guns[first+1].x, 2)+pow(guns[first].y-guns[first+1].y, 2),0.5);
    for(int i=first; i<end; i++){
        for(int j=i+1; j<end; j++){
            // Calculate distance between two node via L2 norm
            L2_norm=pow(pow(guns[i].x-guns[j].x, 2)+pow(guns[i].y-guns[j].y, 2),0.5);
            if(L2_norm<min_distance)
                min_distance=L2_norm;
        }
    }
    return min_distance;
}
