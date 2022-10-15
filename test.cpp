# include <iostream>
# include <vector>
using namespace std;

struct node
{
    double x=0, y=0;
};

int main()
{   /*
    double test, node, x, y;
    cout<< "Please: "<<endl;
    cin>> test >> node >> x >> y;
    cout<<test<< "  "<< node<< "    "<< x<<"    "<<y<<endl;*/

    vector<node> guns;
    node gun;
    for(int i=0; i<5; i++){
        gun.x=-i;
        gun.y=-i;
        guns.push_back(gun);

        cout<< "inserted gun: "<<gun.x <<"  "<<gun.y<<endl;

        //insertion
        for(int j=0; j<i; j++){
            if(gun.x<guns[j].x){
                for(int k=i; k>j; k--){
                    guns[k]=guns[k-1]; //move data around
                }
                guns[j]=gun;
                break;
            }
        }
    }

    for(int i=0; i<5; i++){
        cout<<guns[i].x<<"   "<<guns[i].y<<endl;
    }

    cout<<guns.size()<<endl;
    cout<<guns.capacity()<<endl;



    return 0;
}
