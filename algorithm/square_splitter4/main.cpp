#include <iostream>

using namespace std;

int abs(int a) {
    if( a < 0 )
        return -a;
    return a;
}

int main() {
    int N, i, j, t;
    int sum_total = 0;

    cin >> N;

    //int n[N+1][N+1];
    int sum_row[N+1];
    int sum_colum[N+1];
    int sum_part[N+1][N+1];
    sum_part[0][0] = 0;

    for( i = 0; i <= N; i++ ) {
        sum_colum[i] = 0;
        sum_part[0][i+1] = 0;
        sum_part[i+1][0] = 0;
    }

    for( j = 1; j <= N; j++ ) {
        sum_row[j] = 0;
        for( i = 1; i <= N; i++ ) {
            cin >> t;
            //cout << t << " " ;
            //n[j][i] = t;
            sum_total += t;
            sum_row[j] += t;
            sum_colum[i] += t;
            sum_part[j][i] = t
                               + sum_part[j][i-1]
                               + sum_part[j-1][i]
                               - sum_part[j-1][i-1];

            cout << sum_part[j][i] << " ";
        }
        cout << endl;
    }

    //     |
    // -------
    //   |

    int best = 2023123123, best_j, best_s;
    int diff;

    for( j = 1; j <= N; j++ ) {
        diff = sum_total/2 - sum_part[j][N];
        if ( diff < 0 ) 
            diff = -diff;
        if ( diff < best ) {
            best = diff;
            best_j = j;
            best_s = sum_part[j][N];
        }
    }

    int best_s_o2 = best_s/2;
    int best_s2 = sum_total - best_s;
    int best_s2_o2 = best_s2/2;

    int s_lt = 0, s_bl = 0;

    for ( i = 1; i <= N; i++ ) {
        t = sum_part[best_j][i];
        if( abs(best_s_o2 - t) < abs(best_s_o2 - s_lt) ){
            s_lt = t;
        }
        t = sum_part[N][i] - t;
        if( abs(best_s2_o2 - t) < abs(best_s2_o2 - s_bl) ){
            s_bl = t;
        }
    }

    cout << endl << best_j << endl;
    cout << abs(s_lt) << " ";
    cout << abs(best_s - s_lt) << " ";
    cout << abs(s_bl) << " ";
    cout << abs(best_s2 - s_bl) << " ";

    return 0;
}
