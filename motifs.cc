#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;
const double pi = 3.14159;
const int numbernodes = 9;
const int numbernodes2 = numbernodes*numbernodes;
const int numbernodes_2 = pow(2,(numbernodes2-numbernodes));

int countrefnetworks[10000][9];
int numbercountrefnetworks[9];
bool refnetworks[10000][numbernodes2];
int refindegree[10000][numbernodes];
int refoutdegree[10000][numbernodes];
int refnumbernetworks = 0;
bool matrix[numbernodes2];
bool hmatrix[numbernodes][numbernodes];
bool matrixp[numbernodes2];
int indegree[numbernodes];
int outdegree[numbernodes];
int v[numbernodes];
bool comparegoon;
int locations[10000];
int locations1[10000];
double xcor[2][10000];
double ycor[2][10000];
double distances[numbernodes][numbernodes];
bool network[58647];
int degreedis[10000];
double mindistance;
double mindistances[50000];
    
void compare(const int *v, const int size, int ID){
    if (v != 0 && comparegoon){
        for(int i = 0; i < numbernodes; i++){
            int hvalue = numbernodes*v[i];
            for(int j = 0;j < numbernodes;j++){
                matrixp[i*numbernodes + j] = matrix[hvalue + v[j]];
            }
        }
        comparegoon = false;
        for(int i = 0;i < numbernodes2;i++){
            if(matrixp[i] != refnetworks[ID][i]){
                comparegoon = true;
                i = numbernodes2;
            }
        }
    }
}

void permute(int *v, const int start, const int n, int j){  
    if (start == n-1 && comparegoon){
        compare(v, n, j);
    }
    else{
        for(int i = start; i < n; i++){
            if(comparegoon){
                if(outdegree[v[i]] == outdegree[v[start]] && indegree[v[i]] == indegree[v[start]]){
                    int tmp = v[i];
                    v[i] = v[start];
                    v[start] = tmp;
                    permute(v, start+1, n, j);
                    v[start] = v[i];
                    v[i] = tmp;
                }
            }
        }
    }
}

void permute1(int *v, const int start, const int n){  
    if (start == n-1){
        double hdis = distances[v[0]][v[n-1]];
        for(int k = 1;k < n;k++){
            hdis = hdis + distances[v[k - 1]][v[k]];
        }
        if(hdis < mindistance){
            mindistance = hdis;
        }
    }
    else{
        for(int i = start; i < n; i++){
            int tmp = v[i];
            v[i] = v[start];
            v[start] = tmp;
            permute1(v, start+1, n);
            v[start] = v[i];
            v[i] = tmp;
        }
    }
}

int main(){
    int test[numbernodes];
    for(int i = 0;i < numbernodes;i++){
        test[i] = i;
    }
    for(int i = 0;i<50000;i++){
        mindistances[i] = 0;
    }
    int countersolutions = 0;
    char filename[100];
    sprintf(filename,"data.dat");
    ifstream Data(filename);
    if(Data.good()){cout << "Good" << endl;}else{cout << "Bad" << endl;}
    for(int i = 0;i<10000;i++){
        degreedis[i] = 0;
        for(int j = 0;j<9;j++){
            countrefnetworks[i][j] = 0;
        }
    }
    for(int i = 0;i<9;i++){
        numbercountrefnetworks[i] = 0;
    }
    for(int i = 0;i<numbernodes2;i++){
        matrix[i] = false;
    }
    for(int i = 0;i<numbernodes;i++){
        indegree[i] = 0;
        outdegree[i] = 0;
    }
    int id;
    int locationID = 0;
    int counterid = -1;
    int counter = 0;
    int lastid = -1;
    int hnumbernodes = 0; 
    double xcor1;
    double ycor1;
    while(!Data.eof()){
        Data >> id;Data >> locationID;Data >> xcor1;Data >> ycor1;
        if(id != lastid){
/*****  Calculating motif if the number of locations are equal to the input parameter *****/
            if(counterid > -1){
                degreedis[hnumbernodes]++;
                if(hnumbernodes == numbernodes){
/*****  Converting the data into an adjacency matrix  *****/                                
                    for(int i = 0;i < numbernodes;i++){
                        for(int j = 0;j < numbernodes;j++){
                            hmatrix[i][j] = false;
                        }
                        outdegree[i] = 0;
                        indegree[i] = 0;
                    }
                    for(int i = 0;i < counter;i++){
                        locations1[i] = -1; 
                    }
                    int lastlocID = 0;
                    for(int i = 0;i < counter;i++){
                        if(locations1[i] == -1){
                            locations1[i] = lastlocID;
                            xcor[1][lastlocID] = xcor[0][i];
                            ycor[1][lastlocID] = ycor[0][i];
                            for(int j = i + 1;j < counter;j++){
                                if(locations[j] == locations[i]){
                                    locations1[j] = lastlocID;
                                }
                            }
                            lastlocID++;
                        }
                    }
/*****  Calculating the distances the person traveled  *****/                                
                    double hdis = 0;
                    for(int i = 0;i < numbernodes;i++){
                        for(int j = i+1;j < numbernodes;j++){
                            hdis = cos((ycor[1][i]+ycor[1][j])*0.008727)*(xcor[1][i]-xcor[1][j])*cos((ycor[1][i]+ycor[1][j])*0.008727)*(xcor[1][i]-xcor[1][j]) + (ycor[1][i]-ycor[1][j])*(ycor[1][i]-ycor[1][j]);
                            if(hdis > 0){
                                distances[i][j] = 111.3*sqrt(hdis);
                            }
                            else{
                                distances[i][j] = 0;
                            }
                            distances[j][i] = distances[i][j];
                        }
                    }
                    double distance = 0;
                    for(int i = 1;i < counter;i++){
                        if(locations1[i] != locations1[i - 1]){
                            hmatrix[locations1[i - 1]][locations1[i]] = true;
                            distance = distance + distances[locations1[i - 1]][locations1[i]];
                        }
                    }
/*****  Calculating the minimum distances a person has to travel visiting the same locations  *****/
                    mindistance = distance;
                    if(distance > 0){
                        permute1(test,1,numbernodes);
                        mindistances[numbercountrefnetworks[0]] = mindistance/distance;
                    }
                    else{
                        mindistances[numbercountrefnetworks[0]] = 1.;
                    }
                    for(int i = 0;i < numbernodes;i++){
                        for(int j = 0;j < numbernodes;j++){
                           if(hmatrix[i][j]){
                               outdegree[i]++;
                               indegree[j]++;
                           }
                        }
                    }
                    
/*****  Ordering adjacency matrix  *****/
                    int maxin;
                    int maxout;
                    int maxID;
                    for(int i = 0;i < numbernodes - 1;i++){
                        maxin = indegree[i];
                        maxout = outdegree[i];
                        maxID = i;
                        for(int j = i + 1;j < numbernodes;j++){
                           if(maxout < outdegree[j]){
                               maxID = j;
                               maxout = outdegree[j];
                               maxin = indegree[j];
                           }
                           else{
                               if(maxout == outdegree[j]){
                                   if(maxin < indegree[j]){
                                       maxID = j;
                                       maxout = outdegree[j];
                                       maxin = indegree[j];
                                   }
                               }
                           }
                        }
                        bool h;
                        int h1;
                        for(int j = 0;j < numbernodes;j++){
                            h = hmatrix[i][j];
                            hmatrix[i][j] = hmatrix[maxID][j];
                            hmatrix[maxID][j] = h;
                        }
                        for(int j = 0;j < numbernodes;j++){
                            h = hmatrix[j][i];
                            hmatrix[j][i] = hmatrix[j][maxID];
                            hmatrix[j][maxID] = h;
                        }
                        h1 = outdegree[i];
                        outdegree[i] = outdegree[maxID];
                        outdegree[maxID] = h1;
                        h1 = indegree[i];
                        indegree[i] = indegree[maxID];
                        indegree[maxID] = h1;
                    }

                    if(hnumbernodes == numbernodes){
/*****  Calculating if the motif is new  *****/
                        numbercountrefnetworks[0]++;
                        for(int i = 0;i < hnumbernodes;i++){
                            for(int j = 0;j < hnumbernodes;j++){
                                matrix[i*hnumbernodes+j] = hmatrix[i][j];
                            }
                        }
                        bool show = true;
                        if(show){
                            comparegoon = true;
                            for(int i = 0;i < refnumbernetworks;i++){
                                bool compare = true;
                                for(int j = 0;j < numbernodes;j++){
                                    if(outdegree[j] != refoutdegree[i][j] || indegree[j] != refindegree[i][j]){
                                        compare = false;
                                        j = numbernodes;
                                    }
                                }
                                if(compare){
                                    for(int j = 0;j < numbernodes;j++){
                                        v[j] = j;
                                    }
                                    permute(v, 0, numbernodes, i);
                                    if(!comparegoon){
                                        countrefnetworks[i][0]++;
                                        i = refnumbernetworks;
                                        show = false;
                                    }
                                }
                            }
                        }
/*****  Include the motif as a new reference motif  *****/
                        if(show){
                            for(int j = 0;j < numbernodes;j++){
                                refoutdegree[refnumbernetworks][j] = outdegree[j];
                                refindegree[refnumbernetworks][j] = indegree[j];
                            }
                            for(int j = 0;j < numbernodes2;j++){
                                refnetworks[refnumbernetworks][j] = matrix[j];
                            }
                            countrefnetworks[refnumbernetworks][0]++;
                            refnumbernetworks++; 
                /*            cout << countersolutions << endl;
                            for(int i = 0;i < numbernodes2;i++){
                                cout << matrix[i];
                                if(i%numbernodes == numbernodes - 1){
                                    cout << endl;
                                }
                                else{
                                    cout << " ";
                                }
                            }*/
                            countersolutions++;
                        }
                        
                    }
                }
            }
/*****  Reset for new data  *****/
            hnumbernodes = 0;
            counterid++;
            for(int i = 0;i < 58647;i++){
                network[i] = false;
            }
            if(id%1000 == 0){
                cout << id << endl;
            }
            counter = 0;
        }
/*****  Converting input data in locationIDs  *****/
        for(int j = 0; j < counter;j++){
            if(xcor[0][j] == xcor1 && ycor[0][j] == ycor1){
                locationID = locations[j];
                j = counter;
            }
        }
        locations[counter] = locationID;
        xcor[0][counter] = xcor1;
        ycor[0][counter] = ycor1;
        counter++;
        if(!network[locationID]){
            network[locationID] = true;
            hnumbernodes++;
        }
        lastid = id;
    }
    sprintf(filename,"distances_weekday_%d.dat",numbernodes);
    ofstream outdistances(filename);
    int bin[101];
    for(int i = 0;i < 101;i++){
        bin[i] = 0;
    }
    for(int i = 0;i < numbercountrefnetworks[0];i++){
        bin[int(mindistances[i]*100)]++;
    }
    for(int i = 0;i < 101;i++){
        if(bin[i] > 0){
            outdistances << double(i)/100. << " " << double(bin[i])/double(numbercountrefnetworks[0]) << endl;
        }
    }
    sprintf(filename,"distances_weekday_com_%d.dat",numbernodes);
    ofstream outdistances1(filename);
    double sum = 0.;
    for(int i = 0;i < 101;i++){
        if(bin[i] > 0){
            sum = sum + double(bin[i])/double(numbercountrefnetworks[0]);
            outdistances1 << double(i)/100. << " " << sum << endl;
        }
    }
    system("PAUSE");
    int sortlist[refnumbernetworks];
    for(int i = 0;i < refnumbernetworks;i++){
        sortlist[i] = i;
    }
    for(int i = 0;i < refnumbernetworks;i++){
        for(int j = i+1;j < refnumbernetworks;j++){
            if(countrefnetworks[sortlist[i]][0] > countrefnetworks[sortlist[j]][0]){
                int h = sortlist[i];
                sortlist[i] = sortlist[j];
                sortlist[j] = h;
            }
        }
    }
    sprintf(filename,"motifs_weekday_%d.dat",numbernodes);
    ofstream out(filename);
    for(int i = 0;i < refnumbernetworks;i++){
        cout << i << " " << countrefnetworks[sortlist[i]][0] << " " << double(countrefnetworks[sortlist[i]][0])/double(numbercountrefnetworks[0]) << ":" << endl;
        if(countrefnetworks[sortlist[i]][0] > 1){
            out << i << " " << double(countrefnetworks[sortlist[i]][0])/double(numbercountrefnetworks[0]);
            out << endl;
            for(int j = 0;j<numbernodes2;j++){
                cout << refnetworks[sortlist[i]][j];
                if(j%numbernodes == numbernodes - 1){
                    cout << endl;
                }
                else{
                    cout << " ";
                }
            }
        }
    }
    ofstream out1("degreedistribution_weekday.dat");
    for(int i = 0;i < 10000;i++){
        if(degreedis[i] > 0){
            out1 << i << " " << degreedis[i] << endl;
        }
    }
    system("PAUSE");
    return (0);
}
    
    
    
    
    
