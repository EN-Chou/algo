// bug in insertion
# include "iostream"
# include "iomanip"
# include "math.h"
using namespace std;

void insertion();
double divide(int, int), conquer(double, double, int, int);
double brutal_search(int i, int j);
int n;

struct node{
    double x,y;
};

/*
vector<node> guns;
vector<node> c_guns;*/
node guns[10], c_guns[10];
int c_guns_size=0;

int main(){
    int T;
    cin>> T ;

    for(int i=0; i<T; i++){
        insertion();

        cout<<fixed<<setprecision(6);
        cout<< divide(0,n)<<endl;
    }

    return 0;
}

void insertion(){
    int l=0, r=0, pivot; //pivot is where to insert
    //guns.clear();
    node gun;
    cin>> n;
    for(int i=0; i<n; i++){
        l=0;
        pivot=i;
        cin>> gun.x>> gun.y;
        //guns.push_back(gun);
        
       //Binary search 
        if(guns[0].x>=gun.x)    pivot=0;
        else if(guns[r].x<=gun.x)    pivot=i;
        else{
            while((r-l)>1){ //r-l>1 == not adjacent == not yet found pivot
                if(guns[(r+l)/2].x==gun.x){
                    pivot=(r+l)/2;
                    break;
                }
                else if(guns[(r+l)/2].x>gun.x)    r=(r+l)/2;
                else if(guns[(r+l)/2].x<gun.x)    l=(r+l)/2;

                pivot=r;
            }
        }

        //move data around
        for(int k=i; k>pivot; k--){
            guns[k]=guns[k-1]; 
        }
        guns[pivot]=gun;
        r=i;
    }
    return;
}

double divide(int i, int j){
    double min_L, min_R, min_C;
    double center=(guns[(i+j)/2-1].x+guns[(i+j)/2].x)*0.5;

    if ((j-i)<=3)
        return brutal_search(i, j);
    else{
        min_L=divide(i, (i+j)/2);
        min_R=divide((i+j)/2, j);
        min_C=conquer(center, min(min_L, min_R), i, j);
    }
    
    return min(min(min_L, min_R), min_C);
}

double conquer(double center, double range, int BC_l, int BC_r){
    int l=0, r=0, pivot;
    double min_distance, L2_norm;
    node gun;
    min_distance=pow(pow(guns[BC_l].x-guns[BC_l+1].x, 2)+pow(guns[BC_l].y-guns[BC_l+1].y, 2),0.5);

    //c_guns.clear();
    c_guns_size=0;

    for(int i=BC_l; i<BC_r; i++){
        if((center-range<=guns[i].x)&&(guns[i].x<=center+range)){
            //c_guns.push_back(guns[i]);

            //Binary search
            l=0;
            pivot=c_guns_size;
            c_guns[pivot]=guns[i];

            if(c_guns[0].y>=guns[i].y)    pivot=0;
            else if(c_guns[r].y<=guns[i].y)    pivot=c_guns_size;
            else{
                while((r-l)>1){
                    if(c_guns[(r+l)/2].y==guns[i].y){
                        pivot=(r+l)/2;
                        break;
                    }
                    else if(c_guns[(r+l)/2].y>guns[i].y)    r=(r+l)/2;
                    else if(c_guns[(r+l)/2].y<guns[i].y)    l=(r+l)/2;

                    pivot=r;
                }
            }

            //move data around
            for(int k=c_guns_size; k>pivot; k--){
                c_guns[k]=c_guns[k-1]; 
            }
            c_guns[pivot]=guns[i];
            r=c_guns_size;
            c_guns_size++;  
        }
    }   

    //Find minimum distance in the center zone
    if(c_guns_size==0)//(c_guns.size()==0)
        return min_distance;
    else{
        for(int j=0; j<c_guns_size-1; j++){
            for(int k=1; (j+k)<c_guns_size; k++){
                L2_norm=pow(pow(c_guns[j].x-c_guns[j+k].x, 2)+pow(c_guns[j].y-c_guns[j+k].y, 2),0.5);
                if(L2_norm<min_distance)
                    min_distance=L2_norm;
                // Compute at most 7 points ahead
                if (k==7)
                    break;
            }
        }

    }
    return min_distance;
}

// Boundary Condition: when there are less then 3 nodes in a divide, this is when is function is called.
double brutal_search(int first, int end){
    double min_distance, L2_norm;
    min_distance=pow(pow(guns[first].x-guns[first+1].x, 2)+pow(guns[first].y-guns[first+1].y, 2),0.5);
    for(int i=first; i<end; i++){
        for(int j=i+1; j<end; j++){
            L2_norm=pow(pow(guns[i].x-guns[j].x, 2)+pow(guns[i].y-guns[j].y, 2),0.5);
            if(L2_norm<min_distance)
                min_distance=L2_norm;
        }
    }
    return min_distance;
}
