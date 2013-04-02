mobilityMotifs


Datasets:

Preprocessed survey data from Chicago to run the survey motif detection algorithm: Chicago


Simulated phone usage to run the phone motif detection algorithm: Example


Source files:

The c++ file for the introduced perturbation model for the Chicago survey: Chicago
Input: Models the motifs for a given size (parameter: numbernodes in the source-file)
Output: 
a) motifs_N.dat: fraction of the most common daily networks and the total number of networks with size N if they appear more than 10 times
b) degreedistribution.dat: size distribution of the motifs
c) edgedistribution.dat: edge distribution of the motifs
d) travel.dat: number of trips between different activities
e) traffic.dat: trips per 30min-interval
f) predictability.dat: fraction of time spend at work and home
g) duration_home.dat: distribution of consecutive time spend at home
h) duration_work.dat: distribution of consecutive time spend at work
i) duration_other.dat: distribution of consecutive time spend at other locations
j) intertime_home.dat: distribution of time between two home locations  
k) intertime_work.dat: distribution of time between two work locations  
l) intertime_other.dat: distribution of time between two other locations  
Daily networks are shown at the end of the program (not in a file), if they appear more than 10 times. The structure of the networks is the following:
Motif_ID total_count fraction
Motif_Matrix (N x N)


The c++ file for motif detection in the survey data: Chicago
Input: Calculates the motifs for a given size from data.dat (parameter: numbernodes in the source-file)
Output: 
a) degreedistribution_weekday.dat: size distribution of the motifs
b) distances_weekday_N.dat: distribution of the reported distance of the daily path vs the optimal distance of the daily path visiting the same locations for motifs with the given size N
c) distances_weekday_com_N.dat: cumulative distribution of distances_weekday_N.dat
d) motifs_weekday_N.dat: motif ID and the fraction of these motifs and the total number of motifs with size N

Daily networks are shown at the end of the program (not in a file), if they appear more than once. The structure of the networks is the following:
Motif_ID total_count fraction
Motif_Matrix (N x N)


The c++ file for motif detection in the simulated phone usage: Example
Input: Calculates the motifs for a given size from data_example.dat
Output:
a) unknowndis.dat: distribution of unknown 30-minutes intervals for daily networks
b) degreedis_weekend_min8e.dat: size distribution of the motifs for weekends
c) degreedis_weekday_min8e.dat: size distribution of the motifs for weekdays
d) motifs_min8e.dat: motif distribution for any day
e) motifs_weekend_min8e.dat: motif distribution for weekends
f) motifs_weekday_min8e.dat: motif distribution for weekdays
g) transition_weekendday_relative_min8e.dat: normalized transition probability between motifs for any days
h) transition_weekendend_relative_min8e.dat: normalized transition probability between motifs for weekends
i) transition_weekdayday_relative_min8e.dat: normalized transition probability between motifs for weekdays
j) transition_weekendday_absolut_min8e.dat: total number of transitions between motifs for any days
k) transition_weekendend_absolut_min8e.dat: total number of transitions between motifs for weekends
l) transition_weekdayday_absolut_min8e.dat: total number of transitions between motifs for weekdays

Motifs_IDs are from the paper
