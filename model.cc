#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;
const double pi = 3.14159;
const int numbernodes = 6;
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
bool network[58647];
int degreedis[10000];
int edgedis[10000];
int travel[9];
int time_home[49];
int time_work[49];
int time_other[49];
int intertime[49][3];
    
//********************
// constants
//********************
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

int main(){
    for(int i = 0;i<9;i++){
        travel[i] = 0;
    }
    int countersolutions = 0;
    char filename[100];
    for(int i = 0;i<10000;i++){
        degreedis[i] = 0;
        edgedis[i] = 0;
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
    int numberrealizations = 0;
    int id;int locationID = 0;
    int counterid = -1;
    int counter = 0;
    int lastid = -1;
    int hnumbernodes = 0;
    int cluster = 0;
    srand(0);
    bool event[48];

    int stayhome[48] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int staywork[48] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int stayother[48] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int traffic[48] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    double pvalue[48] = {0.0058,0.0037,0.0023,0.0015,0.0011,0.0008,0.0006,0.0005,0.0005,0.0005,0.0007,0.0010,0.0016,0.0031,0.0066,0.0119,0.0165,0.0201,0.0240,0.0250,0.0275,0.0284,0.0295,0.0313,0.0353,0.0345,0.0313,0.0292,0.0277,0.0274,0.0290,0.0302,0.0329,0.0355,0.0409,0.0443,0.0458,0.0445,0.0422,0.0384,0.0340,0.0324,0.0281,0.0248,0.0224,0.0205,0.0148,0.0096};
    double pvalue0[48] = {0.0058,0.0037,0.0023,0.0015,0.0011,0.0008,0.0006,0.0005,0.0005,0.0005,0.0007,0.0010,0.0016,0.0031,0.0066,0.0119,0.0165,0.0201,0.0240,0.0250,0.0275,0.0284,0.0295,0.0313,0.0353,0.0345,0.0313,0.0292,0.0277,0.0274,0.0290,0.0302,0.0329,0.0355,0.0409,0.0443,0.0458,0.0445,0.0422,0.0384,0.0340,0.0324,0.0281,0.0248,0.0224,0.0205,0.0148,0.0096};
    for(int i = 0;i < 48;i++){
        pvalue0[i] = pvalue0[i]*1.;
        time_home[i] = 0;
        time_work[i] = 0;
        time_other[i] = 0;
    }
    for(int i = 0;i < 49;i++){
        intertime[i][0] = 0;
        intertime[i][1] = 0;
        intertime[i][2] = 0;
    }
    double multiplicator = 1;
    for(int realizations = 0;realizations < 100000;realizations++){
        hnumbernodes = 1;
        multiplicator = 1;
        for(int i = 0;i < 48;i++){
            locations[i] = 0;
        }
        bool worker = false;
        if(rand()%100 > 49){
            for(int i = 18;i < 35;i++){
                locations[i] = 1;
            }
            worker = true;
            hnumbernodes++;
            for(int i = 0;i < 48;i++){
                pvalue[i] = pvalue0[i];
            }
        }
        else{
            for(int i = 0;i < 48;i++){
                pvalue[i] = pvalue0[i]*1.4;
            }
        }
        int nextevent = 17;
        for(int i = 0;i < 48;i++){
            if(i == nextevent){
                nextevent++;
                if(nextevent == 18 && worker){
                    nextevent = 26;
                }
                if(nextevent == 27 && worker){
                   nextevent = 35;
                }
            }
            if(nextevent < 48){
                double random = double(rand())/double(RAND_MAX);
                if(random < pvalue[i]*multiplicator){
                    locations[nextevent] = hnumbernodes;
                    multiplicator = 10;
                    hnumbernodes++;
                    nextevent++;
                    if(nextevent == 18 && worker){
                        nextevent = 26;
                    }
                    if(nextevent == 27 && worker){
                       nextevent = 35;
                    }                    
                }
                else{
                    multiplicator = 1;
                }
            }
            
        }
        degreedis[hnumbernodes]++;
        int hnumberedges = 0;
        int times = 1;
        int starttime = 0;
        if(worker){
            for(int i = 1;i < 48;i++){
                if(locations[i] == 0){stayhome[i]++;};
                if(locations[i] == 1){staywork[i]++;};
                if(locations[i] > 1){stayother[i]++;};
                if(locations[i] != locations[i - 1]){
                    if(starttime > 0){
                        if(locations[i - 1] == 0){
                            time_home[times]++;
//                            cout << "Home: " << locations[i] << " " << locations[i - 1] << " " << i << " " << i - 1 << " " << times << endl;
                        };
                        if(locations[i - 1] == 1){
                            time_work[times]++;
                        };
                        if(locations[i - 1] > 1){
                            time_other[times]++;
                        };
                    }
                    else{
                        starttime = times;
                    }
                    traffic[i]++;
                    if(locations[i - 1] == 0 && locations[i] == 1){travel[1]++;}
                    else if(locations[i - 1] == 0 && locations[i] > 1){travel[2]++;}
                    else if(locations[i - 1] == 1 && locations[i] == 0){travel[3]++;}
                    else if(locations[i - 1] == 1 && locations[i] > 1){travel[5]++;}
                    else if(locations[i - 1] > 1 && locations[i] == 0){travel[6]++;}
                    else if(locations[i - 1] > 1 && locations[i] == 1){travel[7]++;}
                    else if(locations[i - 1] > 1 && locations[i] > 1){travel[8]++;}
                    times = 0;
                }
                times++;
            }
            if(locations[47] == 0){
                time_home[times + starttime]++;
//                cout << "Home: " << times + starttime << endl;
            };
            if(locations[47] == 1){
                time_work[times]++;time_home[starttime]++;
//                cout << "Work: " << times << " Home:" << starttime << endl;
            };
            if(locations[47] > 1){
                time_other[times]++;
                time_home[starttime]++;
//                cout << "Other: " << times << " Home:" << starttime << endl;
            };
        }
        else{
            for(int i = 1;i < 48;i++){
                if(locations[i] == 0){stayhome[i]++;};
                if(locations[i] > 0){stayother[i]++;};
                if(locations[i] != locations[i - 1]){
                    if(starttime > 0){
                        if(locations[i - 1] == 0){time_home[times]++;};
                        if(locations[i - 1] > 0){time_other[times]++;};
                    }
                    else{
                        starttime = times;
                    }
                    traffic[i]++;
                    if(locations[i - 1] == 0){travel[2]++;}
                    else if(locations[i] == 0){travel[6]++;}
                    else if(locations[i] > 0 && locations[i - 1] > 0){travel[8]++;}
                    times = 0;
                }
                times++;
            }
            if(locations[47] == 0){time_home[times + starttime]++;};
            if(locations[47] > 0){time_other[times]++;time_home[starttime]++;};
        }
        int starthome = -1;
        int startwork = -1;
        int startother = -1;
        for(int i = 1;i < 48;i++){
            if(locations[i] != locations[i - 1]){
                if(locations[i] == 0){
                    if(starthome > 0){
                        intertime[i - starthome][0]++;
                    }
                    starthome = i;
                }
                if(locations[i] == 1){
                    if(startwork > 0){
                        intertime[i - startwork][1]++;
                    }
                    startwork = i;
                }
                if(locations[i] > 1){
                    if(startother > 0){
                        intertime[i - startother][2]++;
                    }
                    startother = i;
                }
                hnumberedges++;
            }
        }
        if(locations[47] != locations[0]){
            travel[6]++;
            hnumberedges++;
        }
        edgedis[hnumberedges]++;
        
            if(hnumbernodes == numbernodes){
                if(hnumbernodes == numbernodes){
                    for(int i = 0;i < numbernodes;i++){
                        for(int j = 0;j < numbernodes;j++){
                            hmatrix[i][j] = false;
                        }
                        outdegree[i] = 0;
                        indegree[i] = 0;
                    }
                    for(int i = 1;i < 48;i++){
                        if(locations[i] != locations[i - 1]){
                            hmatrix[locations[i - 1]][locations[i]] = true;
                        }
                    }
                    if(locations[47] != locations[0]){
                        hmatrix[locations[47]][locations[0]] = true;
                    }
                    for(int i = 0;i < numbernodes;i++){
                        for(int j = 0;j < numbernodes;j++){
                           if(hmatrix[i][j]){
                               outdegree[i]++;
                               indegree[j]++;
                           }
                        }
                    }
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
            hnumbernodes = 0;
    }
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
    char filename1[100];
    sprintf(filename1,"motifs_%d.dat",numbernodes);
    ofstream out(filename1);
    for(int i = 0;i < refnumbernetworks;i++){
        cout << i << " " << countrefnetworks[sortlist[i]][0] << " " << double(countrefnetworks[sortlist[i]][0])/double(numbercountrefnetworks[0]) << ":" << endl;
        if(countrefnetworks[sortlist[i]][0] > 10){
            out << i << " " << double(countrefnetworks[sortlist[i]][0])/double(numbercountrefnetworks[0]);
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
    ofstream out1("degreedistribution.dat");
    for(int i = 0;i < 10000;i++){
        if(degreedis[i] > 0){
            out1 << i << " " << degreedis[i] << endl;
            cout << i << " " << degreedis[i] << endl;
        }
    }
    ofstream out3("edgedistribution.dat");
    for(int i = 0;i < 10000;i++){
        if(edgedis[i] > 0){
            out3 << i << " " << edgedis[i] << endl;
        }
    }
    ofstream out2("travel.dat");
    int sumtravel = 0;
    for(int i = 0;i < 9;i++){
        sumtravel = sumtravel + travel[i];
    }
    ofstream out4("traffic.dat");
    for(int i = 0;i < 48;i++){
        out4 << i << " " << traffic[i] << endl;
    }
    ofstream out5("predictability.dat");
    for(int i = 1;i < 48;i++){
        out5 << i << " " << stayhome[i] << " " << stayhome[i] + staywork[i] << " " << stayhome[i] + staywork[i] + stayother[i] << endl;
    }
    for(int i = 0;i < 9;i++){
        out2 << double(travel[i])/double(sumtravel) << endl;
    }
    ofstream out6("duration_home.dat");
    for(int i = 1;i < 48;i++){
        if(time_home[i] > 0){
            out6 << double(i)/2. << " " << time_home[i] << endl;
        }
    }
    ofstream out7("duration_work.dat");
    for(int i = 1;i < 48;i++){
        if(time_work[i] > 0){
            out7 << double(i)/2. << " " << time_work[i] << endl;
        }
    }
    ofstream out8("duration_other.dat");
    for(int i = 1;i < 48;i++){
        if(time_other[i] > 0){
            out8 << double(i)/2. << " " << time_other[i] << endl;
        }
    }
    ofstream out9("intertime_home.dat");
    for(int i = 1;i < 48;i++){
        if(intertime[i][0] > 0){
            out9 << double(i)/2. << " " << intertime[i][0] << endl;
        }
    }
    ofstream out10("intertime_work.dat");
    for(int i = 1;i < 48;i++){
        if(intertime[i][1] > 0){
            out10 << double(i)/2. << " " << intertime[i][1] << endl;
        }
    }
    ofstream out11("intertime_other.dat");
    for(int i = 1;i < 48;i++){
        if(intertime[i][2] > 0){
            out11 << double(i)/2. << " " << intertime[i][2] << endl;
        }
    }
    system("PAUSE");
    return (0);
}
    
    
    
    
    
