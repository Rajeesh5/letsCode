#include<iostream>

using namespace std;


class Sorting {



static void merge(int a[], int start, int mid, int end)  {
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int LeftArray[n1], RightArray[n2]; //temporary arrays  

    /* copy data to temp arrays */
    for (int i = 0; i < n1; i++)
        LeftArray[i] = a[start + i];
    for (int j = 0; j < n2; j++)
        RightArray[j] = a[mid + 1 + j];

    i = 0; /* initial index of first sub-array */
    j = 0; /* initial index of second sub-array */
    k = start;  /* initial index of merged sub-array */

    while (i < n1 && j < n2) {
        if (LeftArray[i] <= RightArray[j]) {            
            a[k] = LeftArray[i++];
        } else {
            a[k] = RightArray[j++];                
        }
        k++;
    }

    while (i < n1) {
        a[k++] = LeftArray[i++];
    }

    while (j < n2) {
        a[k++] = RightArray[j++];
    }
}

static void mergeSort(int a[], int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        mergeSort(a, start, mid);
        mergeSort(a, mid + 1, end);
        merge(a, start, mid, end);
    }
}


};



int main() {


}


boolean checkInclusion(String s1, String s2) {
    if (s1.length() > s2.length())
        return false;
    map<char, int> s1map;
    map<char, int> s2map;
    
    for (int i = 0; i < s1.length(); i++)
        s1map[s1.charAt(i) - 'a']++;



    for (int i = 0; i <= s2.length() - s1.length(); i++) {
        int[] s2map = new int[26];
        for (int j = 0; j < s1.length(); j++) {
            s2map[s2.charAt(i + j) - 'a']++;
        }
        if (matches(s1map, s2map))
            return true;
    }
    return false;
}

boolean matches(int[] s1map, int[] s2map) {
    for (int i = 0; i < 26; i++) {
        if (s1map[i] != s2map[i])
            return false;
    }
    return true;
}
