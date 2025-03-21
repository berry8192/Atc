#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

#define MAX_RETURN_X 500
#define MIN_VERIFY_PROB 0.98
#define MAX_CAND 2

using namespace std;
// using namespace atcoder;

std::ofstream outputFile("log.csv");

template <class T> void PV(T pvv) {
    if (!pvv.size())
        return;
    rep(i, pvv.size() - 1) outputFile << pvv[i] << ", ";
    outputFile << pvv[pvv.size() - 1] << endl;
}
// template <class T> void PV(T pvv) {
//     if (!pvv.size())
//         return;
//     rep(i, pvv.size() - 1) cout << pvv[i] << ", ";
//     // rep(i, pvv.size()-1) cout<< pvv[i]/20 SP << pvv[i]%20 <<endl;
//     cout << pvv[pvv.size() - 1] << endl;
// }

// template <class T>void PVV(T pvv) {
// 	rep(i, pvv.size()){
//         // outputFile<< "i: " << i <<endl;
// 		rep(j, pvv[i].size()-1){
// 			outputFile<< pvv[i][j] << ", ";
// 		}
// 		if(pvv[i].size()) outputFile<< pvv[i][pvv[i].size()-1] <<endl;
// 	}
// }
// template <class T> void PM(T pm) {
//     // cout<< "{";
// 	for(auto m : pm){
// 		outputFile<< "(" << m.first << "->" << m.second << "), ";
// 	}
// 	// cout<< "}";
// 	outputFile<<endl;
// }

int imax = 2147483647;
long long llimax = 9223372036854775807;

// 焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT = 2900.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

// 0から0.01刻みで5まで501個の累積正規分布
vector<double> cumulative_normal_distribution = {
    0.500000000000000, 0.503989356314632, 0.507978313716902, 0.511966473414113,
    0.515953436852831, 0.519938805838373, 0.523922182654107, 0.527903170180521,
    0.531881372013987, 0.535856392585172, 0.539827837277029, 0.543795312542317,
    0.547758426020584, 0.551716786654561, 0.555670004805906, 0.559617692370243,
    0.563559462891433, 0.567494931675038, 0.571423715900901, 0.575345434734796,
    0.579259709439103, 0.583166163482442, 0.587064422648215, 0.590954115142006,
    0.594834871697796, 0.598706325682924, 0.602568113201761, 0.606419873198040,
    0.610261247555797, 0.614091881198877, 0.617911422188953, 0.621719521822019,
    0.625515834723320, 0.629300018940654, 0.633071736036028, 0.636830651175619,
    0.640576433217991, 0.644308754800547, 0.648027292424163, 0.651731726535982,
    0.655421741610324, 0.659097026227677, 0.662757273151751, 0.666402179404542,
    0.670031446339406, 0.673644779712080, 0.677241889749652, 0.680822491217444,
    0.684386303483777, 0.687933050582609, 0.691462461274013, 0.694974269102481,
    0.698468212453034, 0.701944034605124, 0.705401483784302, 0.708840313211654,
    0.712260281150973, 0.715661150953676, 0.719042691101436, 0.722404675246535,
    0.725746882249926, 0.729069096216994, 0.732371106531017, 0.735652707884322,
    0.738913700307138, 0.742153889194135, 0.745373085328664, 0.748571104904690,
    0.751747769546430, 0.754902906325691, 0.758036347776927, 0.761147931910013,
    0.764237502220749, 0.767304907699103, 0.770350002835210, 0.773372647623132,
    0.776372707562401, 0.779350053657350, 0.782304562414267, 0.785236115836363,
    0.788144601416603, 0.791029912128398, 0.793891946414187, 0.796730608171932,
    0.799545806739550, 0.802337456877308, 0.805105478748192, 0.807849797896304,
    0.810570345223288, 0.813267056962827, 0.815939874653241, 0.818588745108203,
    0.821213620385628, 0.823814457754742, 0.826391219661375, 0.828943873691518,
    0.831472392533162, 0.833976753936470, 0.836456940672308, 0.838912940489169,
    0.841344746068543, 0.843752354978746, 0.846135769627265, 0.848494997211656,
    0.850830049669019, 0.853140943624104, 0.855427700336090, 0.857690345644061,
    0.859928909911231, 0.862143427967965, 0.864333939053617, 0.866500486757253,
    0.868643118957269, 0.870761887759982, 0.872856849437202, 0.874928064362850,
    0.876975596948657, 0.878999515578982, 0.880999892544799, 0.882976803976891,
    0.884930329778292, 0.886860553556023, 0.888767562552165, 0.890651447574308,
    0.892512302925413, 0.894350226333145, 0.896165318878700, 0.897957684925181,
    0.899727432045558, 0.901474670950252, 0.903199515414390, 0.904902082204761,
    0.906582491006528, 0.908240864349719, 0.909877327535548, 0.911492008562598,
    0.913085038052915, 0.914656549178033, 0.916206677584986, 0.917735561322331,
    0.919243340766229, 0.920730158546608, 0.922196159473454, 0.923641490463261,
    0.925066300465673, 0.926470740390351, 0.927854963034106, 0.929219123008315,
    0.930563376666668, 0.931887882033275, 0.933192798731142, 0.934478287911084,
    0.935744512181064, 0.936991635536022, 0.938219823288188, 0.939429241997941,
    0.940620059405207, 0.941792444361447, 0.942946566762246, 0.944082597480531,
    0.945200708300442, 0.946301071851880, 0.947383861545748, 0.948449251509911,
    0.949497416525896, 0.950528531966352, 0.951542773733277, 0.952540318197053,
    0.953521342136280, 0.954486022678450, 0.955434537241457, 0.956367063475968,
    0.957283779208671, 0.958184862386405, 0.959070491021193, 0.959940843136183,
    0.960796096712518, 0.961636429637129, 0.962462019651483, 0.963273044301273,
    0.964069680887074, 0.964852106415961, 0.965620497554110, 0.966375030580372,
    0.967115881340836, 0.967843225204386, 0.968557237019248, 0.969258091070534,
    0.969945961038800, 0.970621019959591, 0.971283440183998, 0.971933393340228,
    0.972571050296163, 0.973196581122945, 0.973810155059547, 0.974411940478361,
    0.975002104851779, 0.975580814719777, 0.976148235658491, 0.976704532249788,
    0.977249868051821, 0.977784405570569, 0.978308306232353, 0.978821730357328,
    0.979324837133930, 0.979817784594296, 0.980300729590623, 0.980773827772483,
    0.981237233565062, 0.981691100148341, 0.982135579437183, 0.982570822062343,
    0.982996977352367, 0.983414193316395, 0.983822616627834, 0.984222392608909,
    0.984613665216075, 0.984996577026268, 0.985371269224011, 0.985737881589331,
    0.986096552486501, 0.986447418853580, 0.986790616192744, 0.987126278561398,
    0.987454538564054, 0.987775527344955, 0.988089374581453, 0.988396208478097,
    0.988696155761447, 0.988989341675589, 0.989275889978324, 0.989555922938049,
    0.989829561331280, 0.990096924440836, 0.990358130054642, 0.990613294465162,
    0.990862532469427, 0.991105957369663, 0.991343680974483, 0.991575813600654,
    0.991802464075404, 0.992023739739266, 0.992239746449446, 0.992450588583691,
    0.992656369044652, 0.992857189264729, 0.993053149211376, 0.993244347392859,
    0.993430880864453, 0.993612845235057, 0.993790334674224, 0.993963441919587,
    0.994132258284667, 0.994296873667049, 0.994457376556918, 0.994613854045933,
    0.994766391836444, 0.994915074251009, 0.995059984242229, 0.995201203402874,
    0.995338811976281, 0.995472888867033, 0.995603511651879, 0.995730756590911,
    0.995854698638964, 0.995975411457242, 0.996092967425147, 0.996207437652315,
    0.996318891990825, 0.996427399047601, 0.996533026196959, 0.996635839593331,
    0.996735904184109, 0.996833283722642, 0.996928040781350, 0.997020236764946,
    0.997109931923774, 0.997197185367235, 0.997282055077299, 0.997364597922095,
    0.997444869669572, 0.997522925001214, 0.997598817525811, 0.997672599793269,
    0.997744323308457, 0.997814038545087, 0.997881794959595, 0.997947641005061,
    0.998011624145106, 0.998073790867812, 0.998134186699616, 0.998192856219194,
    0.998249843071324, 0.998305189980723, 0.998358938765843, 0.998411130352635,
    0.998461804788262, 0.998511001254763, 0.998558758082660, 0.998605112764508,
    0.998650101968370, 0.998693761551231, 0.998736126572328, 0.998777231306408,
    0.998817109256896, 0.998855793168977, 0.998893315042591, 0.998929706145321,
    0.998964997025197, 0.998999217523386, 0.999032396786782, 0.999064563280486,
    0.999095744800178, 0.999125968484368, 0.999155260826541, 0.999183647687172,
    0.999211154305624, 0.999237805311933, 0.999263624738446, 0.999288636031355,
    0.999312862062084, 0.999336325138560, 0.999359047016340, 0.999381048909613,
    0.999402351502066, 0.999422974957609, 0.999442938930975, 0.999462262578170,
    0.999480964566793, 0.999499063086214, 0.999516575857616, 0.999533520143892,
    0.999549912759408, 0.999565770079618, 0.999581108050550, 0.999595942198136,
    0.999610287637418, 0.999624159081600, 0.999637570850967, 0.999650536881662,
    0.999663070734324, 0.999675185602581, 0.999686894321419, 0.999698209375391,
    0.999709142906709, 0.999719706723184, 0.999729912306037, 0.999739770817573,
    0.999749293108720, 0.999758489726432, 0.999767370920965, 0.999775946653009,
    0.999784226600705, 0.999792220166520, 0.999799936483993, 0.999807384424364,
    0.999814572603067, 0.999821509386095, 0.999828202896254, 0.999834661019280,
    0.999840891409842, 0.999846901497426, 0.999852698492092, 0.999858289390124,
    0.999863680979554, 0.999868879845580, 0.999873892375861, 0.999878724765715,
    0.999883383023184, 0.999887872974018, 0.999892200266523, 0.999896370376326,
    0.999900388611024, 0.999904260114731, 0.999907989872526, 0.999911582714799,
    0.999915043321502, 0.999918376226297, 0.999921585820617, 0.999924676357622,
    0.999927651956075, 0.999930516604120, 0.999933274162970, 0.999935928370511,
    0.999938482844817, 0.999940941087581, 0.999943306487466, 0.999945582323366,
    0.999947771767598, 0.999949877889004, 0.999951903655982, 0.999953851939444,
    0.999955725515688, 0.999957527069211, 0.999959259195441, 0.999960924403402,
    0.999962525118309, 0.999964063684097, 0.999965542365885, 0.999966963352371,
    0.999968328758167, 0.999969640626073, 0.999970900929288, 0.999972111573559,
    0.999973274399281, 0.999974391183526, 0.999975463642034, 0.999976493431131,
    0.999977482149611, 0.999978431340552, 0.999979342493087, 0.999980217044132,
    0.999981056380049, 0.999981861838282, 0.999982634708927, 0.999983376236270,
    0.999984087620281, 0.999984770018052, 0.999985424545209, 0.999986052277273,
    0.999986654250984, 0.999987231465586, 0.999987784884075, 0.999988315434405,
    0.999988824010668, 0.999989311474225, 0.999989778654816, 0.999990226351627,
    0.999990655334330, 0.999991066344087, 0.999991460094529, 0.999991837272697,
    0.999992198539962, 0.999992544532908, 0.999992875864198, 0.999993193123400,
    0.999993496877799, 0.999993787673173, 0.999994066034554, 0.999994332466958,
    0.999994587456092, 0.999994831469043, 0.999995064954938, 0.999995288345588,
    0.999995502056111, 0.999995706485530, 0.999995902017353, 0.999996089020140,
    0.999996267848039, 0.999996438841320, 0.999996602326875, 0.999996758618713,
    0.999996908018431, 0.999997050815677, 0.999997187288589, 0.999997317704221,
    0.999997442318961, 0.999997561378926, 0.999997675120350, 0.999997783769952,
    0.999997887545297, 0.999997986655145, 0.999998081299780, 0.999998171671336,
    0.999998257954109, 0.999998340324856, 0.999998418953081, 0.999998494001322,
    0.999998565625416, 0.999998633974755, 0.999998699192546, 0.999998761416043,
    0.999998820776783, 0.999998877400815, 0.999998931408905, 0.999998982916757,
    0.999999032035204, 0.999999078870404, 0.999999123524027, 0.999999166093434,
    0.999999206671848, 0.999999245348521, 0.999999282208893, 0.999999317334748,
    0.999999350804357, 0.999999382692628, 0.999999413071236, 0.999999442008757,
    0.999999469570797, 0.999999495820111, 0.999999520816723, 0.999999544618035,
    0.999999567278938, 0.999999588851916, 0.999999609387146, 0.999999628932592,
    0.999999647534102, 0.999999665235492, 0.999999682078634, 0.999999698103538,
    0.999999713348428};

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

int N, M;
double eps;
int oil_sum = 0;

int get_max_index(const vector<double> &vec, bool match_first = true) {
    double ma = -imax;
    int mai;
    rep(i, vec.size()) {
        if (match_first && ma < vec[i]) {
            ma = vec[i];
            mai = i;
        }
        if (match_first && ma <= vec[i]) {
            ma = vec[i];
            mai = i;
        }
    }
    return mai;
}

void normalize_vec(vector<double> &vec) {
    double sumv = 0.0;
    rep(i, vec.size()) sumv += vec[i];
    rep(i, vec.size()) vec[i] /= sumv;
}

void pv_bitset(const bitset<400> &bs) {
    rep(i, N) {
        cout << "# ";
        rep(j, N) {
            if (bs.test(i * N + j))
                cout << 1;
            else
                cout << 0;
        }
        cout << endl;
    }
}

// 構造体
struct Timer {
    chrono::_V2::system_clock::time_point start;

    Timer() { start = chrono::system_clock::now(); }
    double progress() {
        chrono::_V2::system_clock::time_point current =
            chrono::system_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(current - start)
                   .count() /
               TIME_LIMIT;
    }
};
Timer timer;

struct Pos {
    int h;
    int w;

    Pos(){};
    Pos(int hh, int ww) {
        h = hh;
        w = ww;
    }

    bool is_oob() {
        // assert(0<=h);
        // assert(h<n);
        // assert(0<=w);
        // assert(w<=h);
        return !(0 <= h && h < N && 0 <= w && w < N);
    }
    int manhattan(Pos pos) { return abs(h - pos.h) + abs(w - pos.w); }
    int index() { return h * N + w; }
    void print() { cout << "(" << h << ", " << w << ")" << endl; }
    // 受け取った近傍でPosを作る
    vector<Pos> around_pos(const vector<Pos> &dir) {
        vector<Pos> rtn;
        Pos new_pos;
        for (int i = 0; i < dir.size(); i++) {
            new_pos = {h + dir[i].h, w + dir[i].w};
            if (!new_pos.is_oob())
                rtn.emplace_back(new_pos);
        }
        return rtn;
    }

    bool operator<(const Pos &in) const {
        return h != in.h ? h < in.h : w < in.w;
    };
    bool operator==(const Pos &cpos) const {
        return (h == cpos.h && w == cpos.w);
    };
    Pos operator+(const Pos pos) {
        Pos rtn;
        rtn.h = h + pos.h;
        rtn.w = w + pos.w;
        return rtn;
    }
    Pos operator-(const Pos pos) {
        Pos rtn;
        rtn.h = h - pos.h;
        rtn.w = w - pos.w;
        return rtn;
    }
};

Pos itop(int idx) { return {idx / N, idx % N}; }

vector<Pos> d4 = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

// 累積正規分布の配列を使って確率を返す。±5σを超える場合は断定する
double get_normdist(double x) {
    if (x < -5.0)
        return 0.0;
    if (x > 5.0)
        return 1.0;

    double flo = floor(x * 100.0);
    double cei = ceil(x * 100.0);
    double left, right;
    if (flo < 0.0) {
        left = 1.0 - cumulative_normal_distribution[abs(flo)];
    } else {
        left = cumulative_normal_distribution[flo];
    }
    if (flo < 0.0) {
        right = 1.0 - cumulative_normal_distribution[abs(cei)];
    } else {
        right = cumulative_normal_distribution[cei];
    }
    // 内分する必要がない場合はここでreturn
    if (left == right)
        return left;

    assert(left < right);

    // 内分する
    double rtn = left * (ceil(x) - x) + right * (x - floor(x));
    assert(left <= rtn);
    assert(rtn <= right);

    return rtn;
}

// 真のv(S)がそれぞれどれくらいの確率かを、参照渡しされたvectorに詰めて返す
void dist_prob(int k, int x, vector<double> &vec) {
    assert(vec.size() == MAX_RETURN_X);
    double mu, sig = sqrt(k * eps * (1 - eps));
    double left_x = x - 0.5, right_x = x + 0.5; // 四捨五入でxになる実数の範囲
    // ask結果が0のときはmax(0, x)前が負の数の可能性もある
    if (x == 0) {
        left_x = -imax;
    }
    double left_sig, right_sig; // μから何σ離れているか
    double left_p, right_p;
    // k=1なら正確なので確率を1にする
    if (k == 1) {
        rep(i, MAX_RETURN_X) vec[i] = 0.0;
        vec[x] = 1.0;
        return;
    }
    rep(i, MAX_RETURN_X) {
        // 真のv(S)がiだとする
        mu = i * (1 - 2 * eps) + eps * k;
        left_sig = (left_x - mu) / sig;
        right_sig = (right_x - mu) / sig;
        left_p = get_normdist(left_sig);
        right_p = get_normdist(right_sig);
        // outputFile << mu SP << sig SP << left_x SP << right_x SP << left_sig
        // SP
        //            << right_sig SP << left_p SP << right_p << endl;
        assert(left_p <= right_p);
        vec[i] *= right_p - left_p;
    }
    // 正規化する
    normalize_vec(vec);
}

struct Probability {
    int val;
    double prob;

    Probability(){};
    Probability(int ival, double iprob) {
        val = ival;
        prob = iprob;
    }
};

struct Polyomino {
    int d;
    int lim_h;
    int lim_w;
    bitset<400> poses_bit;
    vector<Pos> poses;
    int oil_sum;
    double prob;
    bitset<400> oks;

    Polyomino(){};
};

vector<Polyomino> polyominos;

struct Grid {
    set<Pos> estimates;
    vector<vector<Probability>> probability;
    set<Pos> random_search;
    vector<Polyomino> ask_response;
    int ask_remain;
    set<ll> searched_poses;
    set<Pos> searchable_poses;

    void init() {
        probability.resize(N);
        rep(i, N) probability[i].resize(N);
        ask_remain = 2 * N * N;
        rep(i, N) rep(j, N) searchable_poses.insert({i, j});
    }

    int ask(const vector<Pos> &poses) {
        assert(ask_remain > 0);
        ask_remain--;
        cout << "q" SP << poses.size() SP;
        rep(i, poses.size()) { cout << poses[i].h SP << poses[i].w SP; }
        cout << endl;

        int rtn;
        cin >> rtn;
        return rtn;
    }
    int ask(const bitset<400> &poses_bit) {
        assert(ask_remain > 0);
        ask_remain--;
        cout << "q" SP << poses_bit.count() SP;
        rep(i, N * N) {
            if (poses_bit.test(i)) {
                cout << i / N SP << i % N SP;
            }
        }
        cout << endl;

        int rtn;
        cin >> rtn;
        return rtn;
    }

    void itv_serach() {
        for (int i = 1; i < N - 1; i += 2) {
            for (int j = 1; j < N - 1; j += 2) {
                probability[i][j] = {ask({{i, j}}), 1.0};
            }
        }
    }
    int _test_nn_search(int sz, int offset) {
        vector<Pos> tmp;
        rep(i, sz) rep(j, sz) tmp.push_back({i + offset, j + offset});
        return ask(tmp);
    }
    void _test_nn() {
        vector<int> gets(500);
        rep(i, N * N) gets[_test_nn_search(3, 0)]++;
        PV(gets);
        exit(0);
    }
    void _test_crd_search(int sz, int offset) {
        outputFile << fixed << setprecision(2);
        vector<Pos> tmp;
        int cnt = 0;
        rep3(i, offset + sz, offset) tmp.push_back(itop(i));
        int x;
        vector<double> oils(MAX_RETURN_X, 1.0);
        // PV(oils);
        int idx;
        rep(i, N * N) {
            x = ask(tmp);
            dist_prob(tmp.size(), x, oils);
            PV(oils);
            idx = get_max_index(oils);
            if (oils[idx] > 0.95) {
                outputFile << "resolved: " << i << endl;
                break;
            }
        }
        outputFile << idx << ": " << oils[idx] * 100 << "%." << endl;
        exit(0);
    }
    ll get_search_hash(int height, int width, int h, int w) {
        ll ml = 100;
        ll tmp = 0;
        tmp += height;
        tmp += ml * width;
        tmp += ml * ml * h;
        tmp += ml * ml * ml * w;
        return tmp;
    }
    void search_random() {
        Pos pos;
        do {
            pos = {int(mt() % N), int(mt() % N)};
        } while (random_search.find(pos) != random_search.end());
        random_search.insert(pos);

        probability[pos.h][pos.w] = {ask({{pos.h, pos.w}}), 1.0};
    }
    void search_random_connect() {
        Pos pos;
        bool connect_poly;
        int retry_count = N * N / 2;
        do {
            pos = {int(mt() % N), int(mt() % N)};
            if (random_search.find(pos) != random_search.end())
                continue;

            connect_poly = false;
            vector<Pos> poses = pos.around_pos(d4);
            rep(i, poses.size()) {
                if (probability[poses[i].h][poses[i].w].val >= 1 &&
                    probability[poses[i].h][poses[i].w].prob == 1) {
                    connect_poly = true;
                    break;
                }
            }

            retry_count--;
        } while (!connect_poly && retry_count > 0);
        random_search.insert(pos);

        probability[pos.h][pos.w] = {ask({{pos.h, pos.w}}), 1.0};
    }
    void random_ans() {
        while (1) {
            search_random_connect();
            guess_from_probability();
        }
    }
    bool rectangle_random_search(bool use_rectangle) {
        ll search_hash;
        int max_s, height, max_w, width, h, w;
        if (use_rectangle) {
            while (1) {
                int max_s = ceil(sqrt(0.8 / eps));
                // max_s = 1;
                height = mt() % max_s + 1;
                max_w = ceil(1.0 * max_s / height);
                width = mt() % max_w + 1;
                h = mt() % (N - height + 1);
                w = mt() % (N - width + 1);
                search_hash = get_search_hash(height, width, h, w);
                if (searched_poses.find(search_hash) != searched_poses.end())
                    continue;
                vector<Pos> poses;
                for (int i = h; i < h + height; i++) {
                    for (int j = w; j < w + width; j++) {
                        poses.push_back({i, j});
                    }
                }
                if (!imial_search(poses))
                    continue;
                break;
            }
            searched_poses.insert(search_hash);
        } else {
            while (1) {
                if (searchable_poses.empty())
                    return false;
                auto itr = searchable_poses.begin();
                int rnd = mt() % (searchable_poses.size() - 1);
                rep(i, rnd) itr++;
                Pos pos = *itr;
                searchable_poses.erase(itr);
                h = pos.h;
                w = pos.w;
                if (!imial_search({{h, w}}))
                    continue;
                break;
            }
            height = 1;
            width = 1;
        }
        // cout << "# h w hei wid: " << h SP << w SP << height SP << width <<
        // endl;
        Polyomino poly;
        for (int i = h; i < h + height; i++) {
            for (int j = w; j < w + width; j++) {
                poly.poses_bit.set(i * N + j);
                poly.poses.push_back({i, j});
            }
        }
        poly.d = poly.poses_bit.count();
        poly.lim_h = N - height;
        poly.lim_w = N - width;
        // cout << "# d lh lw: " << poly.d SP << poly.lim_h SP << poly.lim_w
        //      << endl;

        vector<double> oils(MAX_RETURN_X, 1.0);
        int x, idx;
        rep(i, 2 * N * N) {
            x = ask(poly.poses_bit);
            dist_prob(poly.d, x, oils);
            idx = get_max_index(oils);
            if (oils[idx] > MIN_VERIFY_PROB) {
                // cout << "#resolved: " << i << endl;
                for (int i = h; i < h + height; i++) {
                    for (int j = w; j < w + width; j++) {
                        cout << "#c " << i SP << j << " #ff8888" << endl;
                    }
                }
                poly.oil_sum = idx;
                poly.prob = oils[idx];
                ask_response.push_back(poly);
                break;
            }
        }
        return true;
    }
    void rectangle_search(int height, int width, int h, int w) {
        // int max_s = ceil(sqrt(1.0 / eps));
        // int height = mt() % max_s + 1;
        // int max_w = ceil(1.0 * max_s / height);
        // int width = mt() % max_w + 1;
        // cout << "# h w hei wid: " << h SP << w SP << height SP << width <<
        // endl;
        Polyomino poly;
        for (int i = h; i < h + height; i++) {
            for (int j = w; j < w + width; j++) {
                poly.poses_bit.set(i * N + j);
            }
        }
        poly.d = poly.poses_bit.count();
        poly.lim_h = N - height;
        poly.lim_w = N - width;
        // cout << "# d lh lw: " << poly.d SP << poly.lim_h SP << poly.lim_w
        //      << endl;

        vector<double> oils(MAX_RETURN_X, 1.0);
        int x, idx;
        rep(i, 2 * N * N) {
            x = ask(poly.poses_bit);
            dist_prob(poly.d, x, oils);
            idx = get_max_index(oils);
            if (oils[idx] > MIN_VERIFY_PROB) {
                cout << "# resolved for: " << i << "times" << endl;
                poly.oil_sum = idx;
                poly.prob = oils[idx];
                ask_response.push_back(poly);
                break;
            }
        }
    }
    // 最後尾のrectangle_random_searchでもらった回答で、各石油ポリオミノのng場所を確定する
    void search_ng_area() {
        int idx = ask_response.size() - 1;
        // pv_bitset(ask_response[idx].poses_bit);
        // cout << "# oil:" << ask_response[idx].oil_sum << endl;
        rep(i, M) {
            rep(j, polyominos[i].lim_h) {
                rep(k, polyominos[i].lim_w) {
                    // cout << "# jk" << j SP << k << endl;
                    int bit_pos = j * N + k;
                    // cout << "# bit_pos: " << bit_pos << endl;
                    // pv_bitset(polyominos[i].poses_bit);
                    bitset<400> bs =
                        (polyominos[i].poses_bit
                         << bit_pos); // 左シフトすると右シフトになる
                    // cout << bs.to_string() << endl;
                    // pv_bitset(bs);
                    int share_cnt = (ask_response[idx].poses_bit & bs).count();

                    if (share_cnt > ask_response[idx].oil_sum) {
                        // cout << "# ijk: " << i SP << j SP << k << endl;
                        // cout << "# cnt oil: " << share_cnt SP
                        //      << ask_response[idx].oil_sum << endl;
                        polyominos[i].oks.reset(bit_pos);
                    }
                }
            }
            // cout << "# i oks: " << i SP << polyominos[i].oks.count() << endl;
            // cout << "# id poses_bit: " << i << endl;
            // pv_bitset(polyominos[i].poses_bit);
            // cout << "# id oks: " << i << endl;
            // pv_bitset(polyominos[i].oks);
        }
    }
    bool imial_search(vector<Pos> poses) {
        rep(i, M) {
            rep(j, polyominos[i].lim_h) {
                rep(k, polyominos[i].lim_w) {
                    int bit_pos = j * N + k;
                    if (!polyominos[i].oks.test(bit_pos))
                        continue; // もう配置が成立する可能性が残っていない場合はなにもしない

                    bitset<400> bs =
                        (polyominos[i].poses_bit
                         << bit_pos); // 左シフトすると右シフトになる
                    rep(l, poses.size()) {
                        int pos_bit = poses[l].index();
                        if (bs.test(pos_bit))
                            return true;
                    }
                }
            }
        }
        return false;
    }
    void check_oks() {
        bool flg = 1;
        rep(i, M) {
            if (polyominos[i].oks.count() != 1) {
                flg = 0;
                return;
            }
        }
        estimates.clear();
        for (int i = 0; i < M; i++) {
            int bit_pos;
            rep(j, N * N) {
                if (polyominos[i].oks.test(j)) {
                    bit_pos = j;
                    break;
                }
            }
            bitset<400> bs = (polyominos[i].poses_bit
                              << bit_pos); // 左シフトすると右シフトになる
            rep(j, N * N) {
                if (bs[j]) {
                    estimates.insert({j / N, j % N});
                }
            }
        }
        submit_ans();
    }
    // 石油を配置した時の各マスの石油量を持ちながら全探索する。高速化はしていない
    void search_all_pos(vector<vector<int>> &oils, int poly_idx, int &cand,
                        bool cancelable) {
        if (poly_idx == M) {
            set<Pos> tmp = estimates;
            estimates.clear();
            rep(i, N) {
                rep(j, N) {
                    assert(oils[i][j] >= 0);
                    if (oils[i][j] > 0) {
                        estimates.insert({i, j});
                    }
                }
            }
            // submit_ans();
            if (tmp != estimates)
                cand++;
            return;
        }
        // cout << "# " << timer.progress() SP
        //      << 1.0 * (2 * N * N - ask_remain) / N * N << endl;
        if (cancelable && timer.progress() > 1.0) {
            cand = 100000;
            return;
        }
        rep(i, polyominos[poly_idx].lim_h) {
            rep(j, polyominos[poly_idx].lim_w) {
                // cout << "# " << i SP << j SP << poly_idx << endl;
                int bit_pos = i * N + j;
                if (!polyominos[poly_idx].oks.test(bit_pos))
                    continue;
                bool over_oil = false;
                // ポリオミノを仮置き
                rep(k, polyominos[poly_idx].poses.size()) {
                    Pos pos = polyominos[poly_idx].poses[k];
                    oils[pos.h + i][pos.w + j]++;
                }
                // 置いてはいけない配置になっていないか、
                rep(k, ask_response.size()) {
                    int ask_oil_sum = 0;
                    rep(l, ask_response[k].poses.size()) {
                        Pos pos = ask_response[k].poses[l];
                        ask_oil_sum += oils[pos.h][pos.w];
                    }
                    if (ask_oil_sum > ask_response[k].oil_sum) {
                        over_oil = true;
                        break;
                    }
                }
                if (!over_oil) {
                    search_all_pos(oils, poly_idx + 1, cand, cancelable);
                    if (cand >= 2)
                        return;
                }
                // oilsを戻す処理
                rep(k, polyominos[poly_idx].poses.size()) {
                    Pos pos = polyominos[poly_idx].poses[k];
                    oils[pos.h + i][pos.w + j]--;
                }
            }
        }
        return;
    }
    void rectangle_ans() {
        for (int i = 0; i < N; i += 2) {
            for (int j = 0; j < N; j += 2) {
                rectangle_search(1, 1, i, j);
                search_ng_area();
                check_oks();
            }
        }
        for (int i = 1; i < N; i += 2) {
            for (int j = 1; j < N; j += 2) {
                rectangle_search(1, 1, i, j);
                search_ng_area();
                check_oks();
            }
        }
    }
    void dfs_ans() {
        rep(i, 2 * N * N) {
            bool searched;
            if (eps < 0.05 && mt() % 2)
                searched = rectangle_random_search(true);
            else
                searched = rectangle_random_search(false);
            search_ng_area();
            vector<vector<int>> oils(N, vector<int>(N));
            int cand = 0;
            if (timer.progress() < 1.0) {
                search_all_pos(oils, 0, cand, true);
                if (cand <= 1) {
                    submit_ans();
                }
            } else {
                if (!searched) {
                    search_all_pos(oils, 0, cand, false);
                    if (cand <= 1) {
                        submit_ans();
                    }
                }
            }
            cout << "#: " << timer.progress() << endl;
        }
    }

    void guess_from_probability() {
        int find_oil = 0;
        rep(i, N) {
            rep(j, N) {
                if (probability[i][j].val >= 1 && probability[i][j].prob == 1) {
                    find_oil += probability[i][j].val;
                    estimates.insert({i, j});
                }
            }
        }
        // outputFile << find_oil << endl;
        if (find_oil == oil_sum) {
            submit_ans();
        }
    }

    void output_probability() {
        outputFile << fixed << setprecision(2);
        rep(i, N) {
            rep(j, N) {
                outputFile << "(" << probability[i][j].val << ":"
                           << probability[i][j].prob << ") ";
            }
            outputFile << endl;
        }
    }
    void submit_ans() {
        assert(ask_remain > 0);
        ask_remain--;
        cout << "a" SP << estimates.size() SP;
        for (auto s : estimates) {
            cout << s.h SP << s.w SP;
        }
        cout << endl;

        int rtn;
        cin >> rtn;
        if (rtn == 1)
            exit(0);
    }
};

void inpt() {
    cin >> N >> M >> eps;
    int d, ii, jj;
    rep(i, M) {
        cin >> d;
        oil_sum += d;
        Polyomino poly;
        poly.d = d;
        int max_h = 0, max_w = 0;
        rep(j, d) {
            cin >> ii >> jj;
            max_h = max(max_h, ii);
            max_w = max(max_w, jj);
            poly.poses_bit.set(ii * N + jj);
            poly.poses.push_back({ii, jj});
        }
        poly.lim_h = N - max_h;
        poly.lim_w = N - max_w;
        rep(i, poly.lim_h) {
            rep(j, poly.lim_w) { poly.oks.set(i * N + j); }
        }
        polyominos.push_back(poly);
    }
}

int main() {
    inpt();

    Grid grid;
    grid.init();
    double parts = 1.0 * M / (oil_sum / M);
    if ((M < 10 && parts < 2.0) || parts < 1.0) {
        grid.dfs_ans();
    } else {
        grid.random_ans();
    }
    return 0;

    int loop = 0;
    while (1) {
        if (timer.progress() > 1.0)
            break;
        loop++;
    }

    return 0;
}
