#include <vector>
using namespace std;

int divide(vector<int> &vec,int start,int end){
    int pivot=vec[end];

    int startIndex=start;
    int i;

    for(i=start;i<end;i++){

    	if(vec[i]<=pivot){
    		swap(vec[i],vec[startIndex]);
            startIndex++;
        }
     }

    swap(vec[end],vec[startIndex]);

    return startIndex;
}

void quicksort(vector<int>& v, int startIndex, int finalIndex){

    if(startIndex<finalIndex) {
    	int pivotIndex=divide(v,startIndex,finalIndex);
             quicksort(v,startIndex,pivotIndex-1);
             quicksort(v,pivotIndex+1,finalIndex);
    }

}
