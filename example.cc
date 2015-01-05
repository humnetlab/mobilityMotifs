#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

// Compilation: g++ example.cc -O3 -o example_motifs

using namespace std;
const double pi = 3.14159;
const int numbernodes = 6;
const int numbernodes2 = numbernodes*numbernodes;
const int numbernodes_2 = pow(2,(numbernodes2-numbernodes));

//stringIDs[87012255];
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
int degreedis[10000];
int degreedisweekend[10000];
int degreedisweekday[10000];
int unknowndis[10000];
int visits[156][48][3506];
int visits1[3506];
int jumps[3506][3506];
int times[200000];
int locationsID[200000];
long int transition0[29][29];
long int transition1[29][29];
long int transition2[29][29];
int lastnumbernodes;
int motifs_weekday[29];
int motifs_weekend[29];
int motifs[29];
int motifsweekday[29];
int motifsweekend[29];
bool visits2[3506];
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
    bool h1[36] = {false,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[0][i] = h1[i];};
    bool h2[36] = {false,true,false,false,false,false, true,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[1][i] = h2[i];};
    bool h3[36] = {false,true,true,false,false,false, true,false,false,false,false,false, true,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[2][i] = h3[i];};
    bool h4[36] = {false,true,false,false,false,false, false,false,true,false,false,false, true,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[3][i] = h4[i];};
    bool h5[36] = {false,true,true,false,false,false, true,false,false,false,false,false, false,true,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[4][i] = h5[i];};
    bool h6[36] = {false,true,false,true,false,false, false,false,true,false,false,false, true,false,false,false,false,false, true,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[5][i] = h6[i];};
    bool h7[36] = {false,true,false,false,false,false, false,false,true,false,false,false, false,false,false,true,false,false, true,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[6][i] = h7[i];};
    bool h8[36] = {false,true,true,true,false,false, true,false,false,false,false,false, true,false,false,false,false,false, true,false,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[7][i] = h8[i];};
    bool h9[36] = {false,true,true,false,false,false, true,false,false,true,false,false, true,false,false,false,false,false, false,true,false,false,false,false, false,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[8][i] = h9[i];};
    bool h10[36] = {false,true,false,false,true,false, false,false,true,false,false,false, false,false,false,true,false,false, true,false,false,false,false,false, true,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[9][i] = h10[i];};
    bool h11[36] = {false,true,false,false,false,false, false,false,true,false,false,false, false,false,false,true,false,false, false,false,false,false,true,false, true,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[10][i] = h11[i];};
    bool h12[36] = {false,true,false,true,true,false, false,false,true,false,false,false, true,false,false,false,false,false, true,false,false,false,false,false, true,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[11][i] = h12[i];};
    bool h13[36] = {false,true,false,true,false,false, false,false,true,false,false,false, true,false,false,false,false,false, false,false,false,false,true,false, true,false,false,false,false,false, false,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[12][i] = h13[i];};
    bool h14[36] = {false,true,false,false,false,true, false,false,true,false,false,false, false,false,false,true,false,false, false,false,false,false,true,false, true,false,false,false,false,false, true,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[13][i] = h14[i];};
    bool h15[36] = {false,true,false,false,false,false, false,false,true,false,false,false, false,false,false,true,false,false, false,false,false,false,true,false, false,false,false,false,false,true, true,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[14][i] = h15[i];};
    bool h16[36] = {false,true,false,true,false,false, false,false,true,false,false,false, true,false,false,false,false,false, false,false,false,false,true,false, false,false,false,false,false,true, true,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[15][i] = h16[i];};
    bool h17[36] = {false,true,true,true,false,false, true,false,false,false,false,false, true,false,false,false,false,false, false,false,false,false,true,false, false,false,false,false,false,true, true,false,false,false,false,false};
    for(int i = 0;i<36;i++){refnetworks[16][i] = h17[i];};
    refnumbernetworks = 17;
    for(int i = 0;i < refnumbernetworks;i++){
        for(int j = 0;j<numbernodes;j++){
            refoutdegree[i][j] = 0;
            refindegree[i][j] = 0;  
        }
    }
    for(int i = 0;i < refnumbernetworks;i++){
        for(int j = 0;j<numbernodes2;j++){
            if(refnetworks[i][j]){
                refoutdegree[i][int(j/numbernodes)]++;
                refindegree[i][j%numbernodes]++;
            }
            cout << refnetworks[i][j];
            if(j%numbernodes == numbernodes - 1){
                cout << endl;
            }
            else{
                cout << " ";
            }
        }
        for(int j = 0;j<numbernodes;j++){
            cout << j << " " <<refoutdegree[i][j] << " " << refindegree[i][j] << endl;
        }
        cout << endl;
    }
    
    for(int i = 0;i < 29;i++){
        for(int j = 0;j < 29;j++){
            transition0[i][j] = 0;
            transition1[i][j] = 0;
            transition2[i][j] = 0;
        }
    }
    int countersolutions = 0;
    char filename[100];
    sprintf(filename,"data_example.dat");
    ifstream Data(filename);
    if(Data.good()){cout << "Good" << endl;}else{cout << "Bad" << endl;cin >> filename;}
    for(int i = 0;i<10000;i++){
        degreedis[i] = 0;
        degreedisweekend[i] = 0;
        degreedisweekday[i] = 0;
        unknowndis[i] = 0;
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
    int id = 0;int locationID = 0;
    int counterid = -1;
    int lastid = -1;
    int hnumbernodes = 0;
    int cluster;
    int max[156][48];
    int sum = 0;
    for(int j = 0;j < 3506;j++){
        for(int i = 0;i < 3506;i++){
            jumps[i][j] = 0;
        }
    }
    int lasttime = -1;
    int lastlocation = -1;
    int counter = 0;
    int addlocvisits[1000];
    int addlocid[1000][10];
    int counteraddlocs = 0;
    bool locs[3506];
    for(int k = 0;k < 29;k++){
	    motifs_weekday[k] = 0;
	    motifs_weekend[k] = 0;
	    motifsweekday[k] = 0;
	    motifsweekend[k] = 0;
	    motifs[k] = 0;
    }
    int countuser = 0;
    bool goon = true;
    int maxunknown = 40;
//    while(!Data.eof() && goon){
    while(!Data.eof()){
        Data >> id;Data >> locationID;
        if(locationID == -1){
            lasttime = -1;
            if(counterid > -1){
                countuser++;
                counteraddlocs = 0;
                for(int i = 0;i < 3506;i++){
                    locs[i] = false;
                }
                for(int i = 0;i < counter;i++){
                    locs[locationsID[i]] = true;
                }
                for(int i = 0;i < counter;){
		    int hday = times[i]/1440;
		    int hend = i + 1;
		    for(int j = i + 1;j < counter;j++){
			if(int(times[j]/1440) != hday){
			    hend = j;
			    j = counter;
			    
			}
		    }
//		    cout << i << " " << hend << endl;
		    if(hend > i + 1){
			for(int j = 0; j < 3506;j++){
			    visits2[j] = false;
			}
			visits2[locationsID[i]] = true;
		        for(int j = i + 1;j < hend;j++){
//			    cout << locationsID[j] << " " << locationsID[j - 1] << endl;
			    jumps[locationsID[j - 1]][locationsID[j]]++;
			    visits2[locationsID[j]] = true;
		        }
		        int hvalue = -1;
		    	for(int j = 0;j < 3506;j++){
			    hvalue = -1;
			    if(visits2[j]){
			    for(int k = j + 1;k < 3506;k++){
			     	if(jumps[j][k] > 3 && jumps[k][j] > 3){
//				    cout << "Here " << hday << " " << j << " " << k << endl;
				    if(hvalue == -1){
				    	hvalue = k;
				    }
				    for(int l = i + 1;l < hend;l++){
				    	if(locationsID[l] == j){
					    locationsID[l] = hvalue;
				    	}
				    }
			    	}
			    	jumps[j][k] = 0;
			    	jumps[k][j] = 0;
			    }
			    visits2[j] = false;
			    }
			}
		    }
//		    cin >> i;
		    i = hend;
		}
                for(int i = 0;i < counter - 1;i++){
		    if(locationsID[i] == locationsID[i+1]){
                        visits[times[i]/(1440)][(times[i]%1440)/30][locationsID[i]]++;
                        visits1[locationsID[i]]++;
                        sum++;
		    }
                }
                int hmaxid = 0;
                int hmax = 0;
                for(int i = 0;i < 3506;i++){
                    if(visits1[i] > 0){
                        int hmaxlocations = 0;
                        for(int k = 0;k < 156;k++){
                            for(int h = 0;h < 7;h++){
                                hmaxlocations = hmaxlocations + visits[k][h][i];
                            }
                        }
                        if(hmaxlocations > hmax){
                            hmax = hmaxlocations;
                            hmaxid = i;
                        }
                    }
                }
		        for(int k = 0;k < 29;k++){
		            motifs_weekday[k] = 0;
		            motifs_weekend[k] = 0;
		        }
                for(int k = 0;k < 156;k++){
//                    while(k%7 == 1 || k%7 == 2 || k%7 == 3 || k%7 == 4 || k%7 == 5){
//                        k++;
//                        transition[lastnumbernodes][0];
//                        lastnumbernodes = 0;
//                    }
                    if(k%7 == 0 || k%7 == 6){
                        numbercountrefnetworks[1]++;
                    }
                    else{
                        numbercountrefnetworks[0]++;
                    }
                    int unknown = 0;
                    max[k][0] = 0;
                    for(int i = 0;i < 48;i++){
                        for(int j = 0;j < 3506;j++){
                            if(visits[k][i][j] > visits[k][i][max[k][0]] && visits1[j]*500 > sum){
//                            if(visits[k][i][j] > visits[k][i][max[k][0]]){
                                max[k][0] = j;
                            }
                        }
                        if(visits[k][i][max[k][0]] < 1){
                            unknown++;
                            if(i == 0 || i == 47){
                                max[k][0] = hmaxid;
                            }
                        }
                        locations[i] = max[k][0];
                        locations1[i] = -1;
                    }
                    hnumbernodes = 0;
                    for(int i = 0;i < 48;i++){
                        if(locations1[i] == -1){
                            for(int j = i;j < 48;j++){
                                if(locations[j] == locations[i]){
                                    locations1[j] = hnumbernodes;
                                }
                            }
                            hnumbernodes++;
                        }
                    }
                    unknowndis[unknown]++;
		    degreedis[hnumbernodes]++;
                    if(unknown > maxunknown || hnumbernodes > 6){
//                        transition[lastnumbernodes][0]++;
                        if(unknown > maxunknown){
                            if(k%7 == 0 || k%7 == 6){
                                motifs_weekend[28]++;
                                countrefnetworks[28][1]++;
                            }
                            else{
                                motifs_weekday[28]++;
                                countrefnetworks[28][0]++;
                            }
                        }
                        else if(hnumbernodes > 11){
                            if(k%7 == 0 || k%7 == 6){
                                motifs_weekend[27]++;
                                countrefnetworks[27][1]++;
                            }
                            else{
                                motifs_weekday[27]++;
                                countrefnetworks[27][0]++;
                            }
                        }
			else{
                            if(k%7 == 0 || k%7 == 6){
                                motifs_weekend[hnumbernodes + 15]++;
                                countrefnetworks[hnumbernodes + 15][1]++;
                            }
                            else{
                                motifs_weekday[hnumbernodes + 15]++;
                                countrefnetworks[hnumbernodes + 15][0]++;
                            }
			}
                    }
		    if(unknown < maxunknown + 1){
                        if(k%7 == 0 || k%7 == 6){
                            degreedisweekend[hnumbernodes]++;
                        }
                        else{
                            degreedisweekday[hnumbernodes]++;
			}
                    }
                    if(unknown < maxunknown + 1 && hnumbernodes < 7){
                            for(int i = 0;i < numbernodes;i++){
                                for(int j = 0;j < numbernodes;j++){
                                    hmatrix[i][j] = false;
                                }
                                outdegree[i] = 0;
                                indegree[i] = 0;
                            }
                            for(int i = 1;i < 48;i++){
                                if(locations1[i] != locations1[i - 1]){
                                    hmatrix[locations1[i - 1]][locations1[i]] = true;
                                }
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
        
                                for(int i = 0;i < numbernodes;i++){
                                    for(int j = 0;j < numbernodes;j++){
                                        matrix[i*numbernodes+j] = hmatrix[i][j];
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
                                                if(k%7 == 0 || k%7 == 6){
                                                    motifs_weekend[i]++;
                                                    countrefnetworks[i][1]++;
                                                }
                                                else{
                                                    motifs_weekday[i]++;
                                                    countrefnetworks[i][0]++;
                                                }
                                                i = refnumbernetworks;
                                                show = false;
                                            }
                                        }
                                    }
                                }
                                if(show){
                                    if(k%7 == 0 || k%7 == 6){
                                        motifs_weekend[15+hnumbernodes]++;
                                        countrefnetworks[15+hnumbernodes][1]++;
                                    }
                                    else{
                                        motifs_weekday[15+hnumbernodes]++;
                                        countrefnetworks[15+hnumbernodes][0]++;
                                    }
                                }
                    }//*/
                }
            }

//	        for(int i = 0;i < 23;i++){
//		    cout << i << " " << motifs_weekend[i] << " " << motifs_weekday[i] << endl;
//		}
	    for(int i = 0;i < 29;i++){
                for(int j = 0;j < 29;j++){
	            transition0[i][j] = transition0[i][j] + motifs_weekend[i]*motifs_weekday[j];
	            transition1[i][j] = transition1[i][j] + motifs_weekend[i]*motifs_weekend[j];
	            transition2[i][j] = transition2[i][j] + motifs_weekday[i]*motifs_weekday[j];
                }
		motifs[i] = motifs[i] + motifs_weekend[i] + motifs_weekday[i];
		motifsweekend[i] = motifsweekend[i] + motifs_weekend[i];
		motifsweekday[i] = motifsweekday[i] + motifs_weekday[i];
            }
//	    cin >> hnumbernodes;
            hnumbernodes = 0;
            counterid++;
            
            for(int j = 0;j < 3506;j++){
                if(visits1[j] > 0){
                    for(int k = 0;k < 156;k++){
                        for(int i = 0;i < 48;i++){
                            visits[k][i][j] = 0;
                        }
                    }
                    visits1[j] = 0;
                }
            }
            if(id%100 == 99){
//		goon = false;
                cout << id << endl;
            }
            sum = 0;
            counter = 0;
        }
	else{
            if(id > 180){
                times[counter] = id - 180;
                locationsID[counter] = locationID;
                counter++;
	    }
        }
    }
    ofstream out("unknowndis.dat");
    for(int i = 0;i < 48;i++){
	out << i << " " << unknowndis[i] << endl;
    }
    int outputarray[29] = {0,1,17,2,3,4,18,5,6,7,8,19,9,10,11,12,20,13,14,15,16,21,22,23,24,25,26,27,28};
    ofstream out2("transition_weekendday_absolut_min8e.dat");
    ofstream out21("transition_weekendend_absolut_min8e.dat");
    ofstream out22("transition_weekdayday_absolut_min8e.dat");
    for(int i = 0;i < 29;i++){
        for(int j = 0;j < 29;j++){
            out2 << double(transition0[outputarray[i]][outputarray[j]])/111./double(countrefnetworks[outputarray[i]][1]) << " ";
            out21 << double(transition1[outputarray[i]][outputarray[j]])/45./double(countrefnetworks[outputarray[i]][1]) << " ";
            out22 << double(transition2[outputarray[i]][outputarray[j]])/111./double(countrefnetworks[outputarray[i]][0]) << " ";
        }
        out2 << endl;
        out21 << endl;
        out22 << endl;
    }
    cout << countuser << endl; 
    for(int i = 0;i < 29;i++){
	cout << i << " " << countrefnetworks[i][0] << " " << countrefnetworks[i][1] << endl;
    }
    
    ofstream out3("transition_weekendday_relative_min8e.dat");
    ofstream out31("transition_weekendend_relative_min8e.dat");
    ofstream out32("transition_weekdayday_relative_min8e.dat");
    for(int i = 0;i < 29;i++){
        for(int j = 0;j < 29;j++){
	    double hdouble = transition0[outputarray[i]][outputarray[j]];
	    hdouble = hdouble/double(countrefnetworks[outputarray[j]][0]);
	    hdouble = hdouble/double(countrefnetworks[outputarray[i]][1]);
	    hdouble = hdouble*countuser;
	    if(hdouble > 0){
                out3 << log(hdouble) << " ";
	    }
	    else{
                out3 << 0 << " ";
	    }
	    hdouble = transition1[outputarray[i]][outputarray[j]];
	    hdouble = hdouble/double(countrefnetworks[outputarray[j]][1]);
	    hdouble = hdouble/double(countrefnetworks[outputarray[i]][1]);
	    hdouble = hdouble*countuser;
	    if(hdouble > 0){
                out31 << log(hdouble) << " ";
	    }
	    else{
                out31 << 0 << " ";
	    }
	    hdouble = transition2[outputarray[i]][outputarray[j]];
	    hdouble = hdouble/double(countrefnetworks[outputarray[j]][0]);
	    hdouble = hdouble/double(countrefnetworks[outputarray[i]][0]);
	    hdouble = hdouble*countuser;
	    if(hdouble > 0){
                out32 << log(hdouble) << " ";
	    }
	    else{
                out32 << 0 << " ";
	    }
        }
	out31 << endl;
	out32 << endl;
        out3 << endl;
    }
    ofstream outmotifsall("motifs_min8e.dat");
    ofstream outmotifsweekend("motifs_weekend_min8e.dat");
    ofstream outmotifsweekday("motifs_weekday_min8e.dat");
    for(int i = 0;i < 29;i++){
	if(motifs[i] > 0){outmotifsall << i << " " << motifs[i] << endl;}
	if(motifsweekend[i] > 0){outmotifsweekend << i << " " << motifsweekend[i] << endl;}
	if(motifsweekday[i] > 0){outmotifsweekday << i << " " << motifsweekday[i] << endl;}
    }//*/
    ofstream outdegreedisweekend("degreedis_weekend_min8e.dat");
    ofstream outdegreedisweekday("degreedis_weekday_min8e.dat");
    for(int i = 0;i < 29;i++){
	if(degreedisweekend[i] > 0){
	    outdegreedisweekend << i << " " << degreedisweekend[i] << endl;
	}
	if(degreedisweekday[i] > 0){
	    outdegreedisweekday << i << " " << degreedisweekday[i] << endl;
	}
    }
    return (0);
}
