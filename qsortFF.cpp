void split3parts(student* tab, int n, student edge1, student edge2, int &i, int &k){
    i = -1;
    int j = 0;
    k = n;
    while (j<k){
        if (tab[j].punkty<=edge1.punkty){
            i++;
            swap(tab[i], tab[j]);
            j++;
        }
        else if (tab[j].punkty>edge2.punkty){
            k--;
            swap(tab[k], tab[j]);
        }
        else {
            j++;
        }
    }
}


void sortowanieQuickSortFlFr(student* tab, int n){
    int lewy = 0;
    int prawy = n-1;
    student pivotLewy = tab[lewy];
    student pivotPrawy = tab[prawy];
    if (pivotLewy.punkty > pivotPrawy.punkty) {
        swap(tab[lewy], tab[prawy]);
        pivotLewy = tab[lewy];
        pivotPrawy = tab[prawy];
    }
    
    split3parts(tab+1, n-2, pivotLewy, pivotPrawy, lewy, prawy);
    lewy++;
    prawy++;
    prawy++;
    
    tab[n-1] = tab[prawy-1];
    tab[prawy-1] = pivotPrawy;
    tab[0] = tab[lewy];
    tab[lewy] = pivotLewy;

    if (lewy > 1){
        sortowanieQuickSortFlFr(tab, lewy);
    }
    if ((prawy - lewy - 2) > 1){
        sortowanieQuickSortFlFr(tab+lewy+1, prawy-lewy-2);
    }
    if ((n-prawy)>1){
        sortowanieQuickSortFlFr(tab+prawy, n-prawy);
    }
}
