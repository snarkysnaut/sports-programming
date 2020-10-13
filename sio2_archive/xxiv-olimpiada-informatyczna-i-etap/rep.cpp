//Jakub Wasilewski
#include <cstdio>
#include <algorithm>
using namespace std;
int lewa, prawa, srodek, ile, pytanie, odp;
struct roznice
{
    int roznica, jeden, dwa;
};
inline bool operator< (const roznice& mniejszy, const roznice& wiekszy)
{
    return mniejszy.roznica < wiekszy.roznica? 1 : 0;
}
int main()
{
    roznice tablica[] = {531141929, 56, 54, 531141981, 56, 53, 796712893, 56, 52, 796712941, 56, 51, 929498373, 56, 50, 929498419, 56, 49, 995891112, 56, 48, 995891157, 56, 47, 531141876, 55, 54, 531141928, 55, 53, 796712840, 55, 52, 796712888, 55, 51, 929498320, 55, 50, 929498366, 55, 49, 995891059, 55, 48, 995891104, 55, 47, 265570964, 54, 52, 265571012, 54, 51, 398356444, 54, 50, 398356490, 54, 49, 464749183, 54, 48, 464749228, 54, 47, 497945552, 54, 46, 497945596, 54, 45, 514543736, 54, 44, 514543778, 54, 43, 522842827, 54, 42, 522842866, 54, 41, 526992371, 54, 40, 526992408, 54, 39, 529067142, 54, 38, 529067178, 54, 37, 530104527, 54, 36, 530104560, 54, 35, 530623218, 54, 34, 530623250, 54, 33, 530882563, 54, 32, 530882594, 54, 31, 531012235, 54, 30, 531012264, 54, 29, 531077070, 54, 28, 531077098, 54, 27, 531109487, 54, 26, 531109514, 54, 25, 531125695, 54, 24, 531125720, 54, 23, 531133798, 54, 22, 531133822, 54, 21, 531137849, 54, 20, 531137872, 54, 19, 531139874, 54, 18, 531139896, 54, 17, 531140886, 54, 16, 531140904, 54, 15, 531141390, 54, 14, 531141406, 54, 13, 531141641, 54, 12, 531141652, 54, 11, 531141764, 54, 10, 531141774, 54, 9, 531141825, 54, 8, 531141834, 54, 7, 531141855, 54, 6, 531141860, 54, 5, 531141868, 54, 4, 531141872, 54, 3, 531141874, 54, 2, 531141875, 54, 1, 265570912, 53, 52, 265570960, 53, 51, 398356392, 53, 50, 398356438, 53, 49, 464749131, 53, 48, 464749176, 53, 47, 497945500, 53, 46, 497945544, 53, 45, 514543684, 53, 44, 514543726, 53, 43, 522842775, 53, 42, 522842814, 53, 41, 526992319, 53, 40, 526992356, 53, 39, 529067090, 53, 38, 529067126, 53, 37, 530104475, 53, 36, 530104508, 53, 35, 530623166, 53, 34, 530623198, 53, 33, 530882511, 53, 32, 530882542, 53, 31, 531012183, 53, 30, 531012212, 53, 29, 531077018, 53, 28, 531077046, 53, 27, 531109435, 53, 26, 531109462, 53, 25, 531125643, 53, 24, 531125668, 53, 23, 531133746, 53, 22, 531133770, 53, 21, 531137797, 53, 20, 531137820, 53, 19, 531139822, 53, 18, 531139844, 53, 17, 531140834, 53, 16, 531140852, 53, 15, 531141338, 53, 14, 531141354, 53, 13, 531141589, 53, 12, 531141600, 53, 11, 531141712, 53, 10, 531141722, 53, 9, 531141773, 53, 8, 531141782, 53, 7, 531141803, 53, 6, 531141808, 53, 5, 531141816, 53, 4, 531141820, 53, 3, 531141822, 53, 2, 531141823, 53, 1, 132785480, 52, 50, 132785526, 52, 49, 199178219, 52, 48, 199178264, 52, 47, 232374588, 52, 46, 232374632, 52, 45, 248972772, 52, 44, 248972814, 52, 43, 257271863, 52, 42, 257271902, 52, 41, 261421407, 52, 40, 261421444, 52, 39, 263496178, 52, 38, 263496214, 52, 37, 264533563, 52, 36, 264533596, 52, 35, 265052254, 52, 34, 265052286, 52, 33, 265311599, 52, 32, 265311630, 52, 31, 265441271, 52, 30, 265441300, 52, 29, 265506106, 52, 28, 265506134, 52, 27, 265538523, 52, 26, 265538550, 52, 25, 265554731, 52, 24, 265554756, 52, 23, 265562834, 52, 22, 265562858, 52, 21, 265566885, 52, 20, 265566908, 52, 19, 265568910, 52, 18, 265568932, 52, 17, 265569922, 52, 16, 265569940, 52, 15, 265570426, 52, 14, 265570442, 52, 13, 265570677, 52, 12, 265570688, 52, 11, 265570800, 52, 10, 265570810, 52, 9, 265570861, 52, 8, 265570870, 52, 7, 265570891, 52, 6, 265570896, 52, 5, 265570904, 52, 4, 265570908, 52, 3, 265570910, 52, 2, 265570911, 52, 1, 132785432, 51, 50, 132785478, 51, 49, 199178171, 51, 48, 199178216, 51, 47, 232374540, 51, 46, 232374584, 51, 45, 248972724, 51, 44, 248972766, 51, 43, 257271815, 51, 42, 257271854, 51, 41, 261421359, 51, 40, 261421396, 51, 39, 263496130, 51, 38, 263496166, 51, 37, 264533515, 51, 36, 264533548, 51, 35, 265052206, 51, 34, 265052238, 51, 33, 265311551, 51, 32, 265311582, 51, 31, 265441223, 51, 30, 265441252, 51, 29, 265506058, 51, 28, 265506086, 51, 27, 265538475, 51, 26, 265538502, 51, 25, 265554683, 51, 24, 265554708, 51, 23, 265562786, 51, 22, 265562810, 51, 21, 265566837, 51, 20, 265566860, 51, 19, 265568862, 51, 18, 265568884, 51, 17, 265569874, 51, 16, 265569892, 51, 15, 265570378, 51, 14, 265570394, 51, 13, 265570629, 51, 12, 265570640, 51, 11, 265570752, 51, 10, 265570762, 51, 9, 265570813, 51, 8, 265570822, 51, 7, 265570843, 51, 6, 265570848, 51, 5, 265570856, 51, 4, 265570860, 51, 3, 265570862, 51, 2, 265570863, 51, 1, 66392739, 50, 48, 66392784, 50, 47, 99589108, 50, 46, 99589152, 50, 45, 116187292, 50, 44, 116187334, 50, 43, 124486383, 50, 42, 124486422, 50, 41, 128635927, 50, 40, 128635964, 50, 39, 130710698, 50, 38, 130710734, 50, 37, 131748083, 50, 36, 131748116, 50, 35, 132266774, 50, 34, 132266806, 50, 33, 132526119, 50, 32, 132526150, 50, 31, 132655791, 50, 30, 132655820, 50, 29, 132720626, 50, 28, 132720654, 50, 27, 132753043, 50, 26, 132753070, 50, 25, 132769251, 50, 24, 132769276, 50, 23, 132777354, 50, 22, 132777378, 50, 21, 132781405, 50, 20, 132781428, 50, 19, 132783430, 50, 18, 132783452, 50, 17, 132784442, 50, 16, 132784460, 50, 15, 132784946, 50, 14, 132784962, 50, 13, 132785197, 50, 12, 132785208, 50, 11, 132785320, 50, 10, 132785330, 50, 9, 132785381, 50, 8, 132785390, 50, 7, 132785411, 50, 6, 132785416, 50, 5, 132785424, 50, 4, 132785428, 50, 3, 132785430, 50, 2, 132785431, 50, 1, 66392693, 49, 48, 66392738, 49, 47, 99589062, 49, 46, 99589106, 49, 45, 116187246, 49, 44, 116187288, 49, 43, 124486337, 49, 42, 124486376, 49, 41, 128635881, 49, 40, 128635918, 49, 39, 130710652, 49, 38, 130710688, 49, 37, 131748037, 49, 36, 131748070, 49, 35, 132266728, 49, 34, 132266760, 49, 33, 132526073, 49, 32, 132526104, 49, 31, 132655745, 49, 30, 132655774, 49, 29, 132720580, 49, 28, 132720608, 49, 27, 132752997, 49, 26, 132753024, 49, 25, 132769205, 49, 24, 132769230, 49, 23, 132777308, 49, 22, 132777332, 49, 21, 132781359, 49, 20, 132781382, 49, 19, 132783384, 49, 18, 132783406, 49, 17, 132784396, 49, 16, 132784414, 49, 15, 132784900, 49, 14, 132784916, 49, 13, 132785151, 49, 12, 132785162, 49, 11, 132785274, 49, 10, 132785284, 49, 9, 132785335, 49, 8, 132785344, 49, 7, 132785365, 49, 6, 132785370, 49, 5, 132785378, 49, 4, 132785382, 49, 3, 132785384, 49, 2, 132785385, 49, 1, 33196369, 48, 46, 33196413, 48, 45, 49794553, 48, 44, 49794595, 48, 43, 58093644, 48, 42, 58093683, 48, 41, 62243188, 48, 40, 62243225, 48, 39, 64317959, 48, 38, 64317995, 48, 37, 65355344, 48, 36, 65355377, 48, 35, 65874035, 48, 34, 65874067, 48, 33, 66133380, 48, 32, 66133411, 48, 31, 66263052, 48, 30, 66263081, 48, 29, 66327887, 48, 28, 66327915, 48, 27, 66360304, 48, 26, 66360331, 48, 25, 66376512, 48, 24, 66376537, 48, 23, 66384615, 48, 22, 66384639, 48, 21, 66388666, 48, 20, 66388689, 48, 19, 66390691, 48, 18, 66390713, 48, 17, 66391703, 48, 16, 66391721, 48, 15, 66392207, 48, 14, 66392223, 48, 13, 66392458, 48, 12, 66392469, 48, 11, 66392581, 48, 10, 66392591, 48, 9, 66392642, 48, 8, 66392651, 48, 7, 66392672, 48, 6, 66392677, 48, 5, 66392685, 48, 4, 66392689, 48, 3, 66392691, 48, 2, 66392692, 48, 1, 33196324, 47, 46, 33196368, 47, 45, 49794508, 47, 44, 49794550, 47, 43, 58093599, 47, 42, 58093638, 47, 41, 62243143, 47, 40, 62243180, 47, 39, 64317914, 47, 38, 64317950, 47, 37, 65355299, 47, 36, 65355332, 47, 35, 65873990, 47, 34, 65874022, 47, 33, 66133335, 47, 32, 66133366, 47, 31, 66263007, 47, 30, 66263036, 47, 29, 66327842, 47, 28, 66327870, 47, 27, 66360259, 47, 26, 66360286, 47, 25, 66376467, 47, 24, 66376492, 47, 23, 66384570, 47, 22, 66384594, 47, 21, 66388621, 47, 20, 66388644, 47, 19, 66390646, 47, 18, 66390668, 47, 17, 66391658, 47, 16, 66391676, 47, 15, 66392162, 47, 14, 66392178, 47, 13, 66392413, 47, 12, 66392424, 47, 11, 66392536, 47, 10, 66392546, 47, 9, 66392597, 47, 8, 66392606, 47, 7, 66392627, 47, 6, 66392632, 47, 5, 66392640, 47, 4, 66392644, 47, 3, 66392646, 47, 2, 66392647, 47, 1, 16598184, 46, 44, 16598226, 46, 43, 24897275, 46, 42, 24897314, 46, 41, 29046819, 46, 40, 29046856, 46, 39, 31121590, 46, 38, 31121626, 46, 37, 32158975, 46, 36, 32159008, 46, 35, 32677666, 46, 34, 32677698, 46, 33, 32937011, 46, 32, 32937042, 46, 31, 33066683, 46, 30, 33066712, 46, 29, 33131518, 46, 28, 33131546, 46, 27, 33163935, 46, 26, 33163962, 46, 25, 33180143, 46, 24, 33180168, 46, 23, 33188246, 46, 22, 33188270, 46, 21, 33192297, 46, 20, 33192320, 46, 19, 33194322, 46, 18, 33194344, 46, 17, 33195334, 46, 16, 33195352, 46, 15, 33195838, 46, 14, 33195854, 46, 13, 33196089, 46, 12, 33196100, 46, 11, 33196212, 46, 10, 33196222, 46, 9, 33196273, 46, 8, 33196282, 46, 7, 33196303, 46, 6, 33196308, 46, 5, 33196316, 46, 4, 33196320, 46, 3, 33196322, 46, 2, 33196323, 46, 1, 16598140, 45, 44, 16598182, 45, 43, 24897231, 45, 42, 24897270, 45, 41, 29046775, 45, 40, 29046812, 45, 39, 31121546, 45, 38, 31121582, 45, 37, 32158931, 45, 36, 32158964, 45, 35, 32677622, 45, 34, 32677654, 45, 33, 32936967, 45, 32, 32936998, 45, 31, 33066639, 45, 30, 33066668, 45, 29, 33131474, 45, 28, 33131502, 45, 27, 33163891, 45, 26, 33163918, 45, 25, 33180099, 45, 24, 33180124, 45, 23, 33188202, 45, 22, 33188226, 45, 21, 33192253, 45, 20, 33192276, 45, 19, 33194278, 45, 18, 33194300, 45, 17, 33195290, 45, 16, 33195308, 45, 15, 33195794, 45, 14, 33195810, 45, 13, 33196045, 45, 12, 33196056, 45, 11, 33196168, 45, 10, 33196178, 45, 9, 33196229, 45, 8, 33196238, 45, 7, 33196259, 45, 6, 33196264, 45, 5, 33196272, 45, 4, 33196276, 45, 3, 33196278, 45, 2, 33196279, 45, 1, 8299091, 44, 42, 8299130, 44, 41, 12448635, 44, 40, 12448672, 44, 39, 14523406, 44, 38, 14523442, 44, 37, 15560791, 44, 36, 15560824, 44, 35, 16079482, 44, 34, 16079514, 44, 33, 16338827, 44, 32, 16338858, 44, 31, 16468499, 44, 30, 16468528, 44, 29, 16533334, 44, 28, 16533362, 44, 27, 16565751, 44, 26, 16565778, 44, 25, 16581959, 44, 24, 16581984, 44, 23, 16590062, 44, 22, 16590086, 44, 21, 16594113, 44, 20, 16594136, 44, 19, 16596138, 44, 18, 16596160, 44, 17, 16597150, 44, 16, 16597168, 44, 15, 16597654, 44, 14, 16597670, 44, 13, 16597905, 44, 12, 16597916, 44, 11, 16598028, 44, 10, 16598038, 44, 9, 16598089, 44, 8, 16598098, 44, 7, 16598119, 44, 6, 16598124, 44, 5, 16598132, 44, 4, 16598136, 44, 3, 16598138, 44, 2, 16598139, 44, 1, 8299049, 43, 42, 8299088, 43, 41, 12448593, 43, 40, 12448630, 43, 39, 14523364, 43, 38, 14523400, 43, 37, 15560749, 43, 36, 15560782, 43, 35, 16079440, 43, 34, 16079472, 43, 33, 16338785, 43, 32, 16338816, 43, 31, 16468457, 43, 30, 16468486, 43, 29, 16533292, 43, 28, 16533320, 43, 27, 16565709, 43, 26, 16565736, 43, 25, 16581917, 43, 24, 16581942, 43, 23, 16590020, 43, 22, 16590044, 43, 21, 16594071, 43, 20, 16594094, 43, 19, 16596096, 43, 18, 16596118, 43, 17, 16597108, 43, 16, 16597126, 43, 15, 16597612, 43, 14, 16597628, 43, 13, 16597863, 43, 12, 16597874, 43, 11, 16597986, 43, 10, 16597996, 43, 9, 16598047, 43, 8, 16598056, 43, 7, 16598077, 43, 6, 16598082, 43, 5, 16598090, 43, 4, 16598094, 43, 3, 16598096, 43, 2, 16598097, 43, 1, 4149544, 42, 40, 4149581, 42, 39, 6224315, 42, 38, 6224351, 42, 37, 7261700, 42, 36, 7261733, 42, 35, 7780391, 42, 34, 7780423, 42, 33, 8039736, 42, 32, 8039767, 42, 31, 8169408, 42, 30, 8169437, 42, 29, 8234243, 42, 28, 8234271, 42, 27, 8266660, 42, 26, 8266687, 42, 25, 8282868, 42, 24, 8282893, 42, 23, 8290971, 42, 22, 8290995, 42, 21, 8295022, 42, 20, 8295045, 42, 19, 8297047, 42, 18, 8297069, 42, 17, 8298059, 42, 16, 8298077, 42, 15, 8298563, 42, 14, 8298579, 42, 13, 8298814, 42, 12, 8298825, 42, 11, 8298937, 42, 10, 8298947, 42, 9, 8298998, 42, 8, 8299007, 42, 7, 8299028, 42, 6, 8299033, 42, 5, 8299041, 42, 4, 8299045, 42, 3, 8299047, 42, 2, 8299048, 42, 1, 4149505, 41, 40, 4149542, 41, 39, 6224276, 41, 38, 6224312, 41, 37, 7261661, 41, 36, 7261694, 41, 35, 7780352, 41, 34, 7780384, 41, 33, 8039697, 41, 32, 8039728, 41, 31, 8169369, 41, 30, 8169398, 41, 29, 8234204, 41, 28, 8234232, 41, 27, 8266621, 41, 26, 8266648, 41, 25, 8282829, 41, 24, 8282854, 41, 23, 8290932, 41, 22, 8290956, 41, 21, 8294983, 41, 20, 8295006, 41, 19, 8297008, 41, 18, 8297030, 41, 17, 8298020, 41, 16, 8298038, 41, 15, 8298524, 41, 14, 8298540, 41, 13, 8298775, 41, 12, 8298786, 41, 11, 8298898, 41, 10, 8298908, 41, 9, 8298959, 41, 8, 8298968, 41, 7, 8298989, 41, 6, 8298994, 41, 5, 8299002, 41, 4, 8299006, 41, 3, 8299008, 41, 2, 8299009, 41, 1, 2074771, 40, 38, 2074807, 40, 37, 3112156, 40, 36, 3112189, 40, 35, 3630847, 40, 34, 3630879, 40, 33, 3890192, 40, 32, 3890223, 40, 31, 4019864, 40, 30, 4019893, 40, 29, 4084699, 40, 28, 4084727, 40, 27, 4117116, 40, 26, 4117143, 40, 25, 4133324, 40, 24, 4133349, 40, 23, 4141427, 40, 22, 4141451, 40, 21, 4145478, 40, 20, 4145501, 40, 19, 4147503, 40, 18, 4147525, 40, 17, 4148515, 40, 16, 4148533, 40, 15, 4149019, 40, 14, 4149035, 40, 13, 4149270, 40, 12, 4149281, 40, 11, 4149393, 40, 10, 4149403, 40, 9, 4149454, 40, 8, 4149463, 40, 7, 4149484, 40, 6, 4149489, 40, 5, 4149497, 40, 4, 4149501, 40, 3, 4149503, 40, 2, 4149504, 40, 1, 2074734, 39, 38, 2074770, 39, 37, 3112119, 39, 36, 3112152, 39, 35, 3630810, 39, 34, 3630842, 39, 33, 3890155, 39, 32, 3890186, 39, 31, 4019827, 39, 30, 4019856, 39, 29, 4084662, 39, 28, 4084690, 39, 27, 4117079, 39, 26, 4117106, 39, 25, 4133287, 39, 24, 4133312, 39, 23, 4141390, 39, 22, 4141414, 39, 21, 4145441, 39, 20, 4145464, 39, 19, 4147466, 39, 18, 4147488, 39, 17, 4148478, 39, 16, 4148496, 39, 15, 4148982, 39, 14, 4148998, 39, 13, 4149233, 39, 12, 4149244, 39, 11, 4149356, 39, 10, 4149366, 39, 9, 4149417, 39, 8, 4149426, 39, 7, 4149447, 39, 6, 4149452, 39, 5, 4149460, 39, 4, 4149464, 39, 3, 4149466, 39, 2, 4149467, 39, 1, 1037385, 38, 36, 1037418, 38, 35, 1556076, 38, 34, 1556108, 38, 33, 1815421, 38, 32, 1815452, 38, 31, 1945093, 38, 30, 1945122, 38, 29, 2009928, 38, 28, 2009956, 38, 27, 2042345, 38, 26, 2042372, 38, 25, 2058553, 38, 24, 2058578, 38, 23, 2066656, 38, 22, 2066680, 38, 21, 2070707, 38, 20, 2070730, 38, 19, 2072732, 38, 18, 2072754, 38, 17, 2073744, 38, 16, 2073762, 38, 15, 2074248, 38, 14, 2074264, 38, 13, 2074499, 38, 12, 2074510, 38, 11, 2074622, 38, 10, 2074632, 38, 9, 2074683, 38, 8, 2074692, 38, 7, 2074713, 38, 6, 2074718, 38, 5, 2074726, 38, 4, 2074730, 38, 3, 2074732, 38, 2, 2074733, 38, 1, 1037349, 37, 36, 1037382, 37, 35, 1556040, 37, 34, 1556072, 37, 33, 1815385, 37, 32, 1815416, 37, 31, 1945057, 37, 30, 1945086, 37, 29, 2009892, 37, 28, 2009920, 37, 27, 2042309, 37, 26, 2042336, 37, 25, 2058517, 37, 24, 2058542, 37, 23, 2066620, 37, 22, 2066644, 37, 21, 2070671, 37, 20, 2070694, 37, 19, 2072696, 37, 18, 2072718, 37, 17, 2073708, 37, 16, 2073726, 37, 15, 2074212, 37, 14, 2074228, 37, 13, 2074463, 37, 12, 2074474, 37, 11, 2074586, 37, 10, 2074596, 37, 9, 2074647, 37, 8, 2074656, 37, 7, 2074677, 37, 6, 2074682, 37, 5, 2074690, 37, 4, 2074694, 37, 3, 2074696, 37, 2, 2074697, 37, 1, 518691, 36, 34, 518723, 36, 33, 778036, 36, 32, 778067, 36, 31, 907708, 36, 30, 907737, 36, 29, 972543, 36, 28, 972571, 36, 27, 1004960, 36, 26, 1004987, 36, 25, 1021168, 36, 24, 1021193, 36, 23, 1029271, 36, 22, 1029295, 36, 21, 1033322, 36, 20, 1033345, 36, 19, 1035347, 36, 18, 1035369, 36, 17, 1036359, 36, 16, 1036377, 36, 15, 1036863, 36, 14, 1036879, 36, 13, 1037114, 36, 12, 1037125, 36, 11, 1037237, 36, 10, 1037247, 36, 9, 1037298, 36, 8, 1037307, 36, 7, 1037328, 36, 6, 1037333, 36, 5, 1037341, 36, 4, 1037345, 36, 3, 1037347, 36, 2, 1037348, 36, 1, 518658, 35, 34, 518690, 35, 33, 778003, 35, 32, 778034, 35, 31, 907675, 35, 30, 907704, 35, 29, 972510, 35, 28, 972538, 35, 27, 1004927, 35, 26, 1004954, 35, 25, 1021135, 35, 24, 1021160, 35, 23, 1029238, 35, 22, 1029262, 35, 21, 1033289, 35, 20, 1033312, 35, 19, 1035314, 35, 18, 1035336, 35, 17, 1036326, 35, 16, 1036344, 35, 15, 1036830, 35, 14, 1036846, 35, 13, 1037081, 35, 12, 1037092, 35, 11, 1037204, 35, 10, 1037214, 35, 9, 1037265, 35, 8, 1037274, 35, 7, 1037295, 35, 6, 1037300, 35, 5, 1037308, 35, 4, 1037312, 35, 3, 1037314, 35, 2, 1037315, 35, 1, 259345, 34, 32, 259376, 34, 31, 389017, 34, 30, 389046, 34, 29, 453852, 34, 28, 453880, 34, 27, 486269, 34, 26, 486296, 34, 25, 502477, 34, 24, 502502, 34, 23, 510580, 34, 22, 510604, 34, 21, 514631, 34, 20, 514654, 34, 19, 516656, 34, 18, 516678, 34, 17, 517668, 34, 16, 517686, 34, 15, 518172, 34, 14, 518188, 34, 13, 518423, 34, 12, 518434, 34, 11, 518546, 34, 10, 518556, 34, 9, 518607, 34, 8, 518616, 34, 7, 518637, 34, 6, 518642, 34, 5, 518650, 34, 4, 518654, 34, 3, 518656, 34, 2, 518657, 34, 1, 259313, 33, 32, 259344, 33, 31, 388985, 33, 30, 389014, 33, 29, 453820, 33, 28, 453848, 33, 27, 486237, 33, 26, 486264, 33, 25, 502445, 33, 24, 502470, 33, 23, 510548, 33, 22, 510572, 33, 21, 514599, 33, 20, 514622, 33, 19, 516624, 33, 18, 516646, 33, 17, 517636, 33, 16, 517654, 33, 15, 518140, 33, 14, 518156, 33, 13, 518391, 33, 12, 518402, 33, 11, 518514, 33, 10, 518524, 33, 9, 518575, 33, 8, 518584, 33, 7, 518605, 33, 6, 518610, 33, 5, 518618, 33, 4, 518622, 33, 3, 518624, 33, 2, 518625, 33, 1, 129672, 32, 30, 129701, 32, 29, 194507, 32, 28, 194535, 32, 27, 226924, 32, 26, 226951, 32, 25, 243132, 32, 24, 243157, 32, 23, 251235, 32, 22, 251259, 32, 21, 255286, 32, 20, 255309, 32, 19, 257311, 32, 18, 257333, 32, 17, 258323, 32, 16, 258341, 32, 15, 258827, 32, 14, 258843, 32, 13, 259078, 32, 12, 259089, 32, 11, 259201, 32, 10, 259211, 32, 9, 259262, 32, 8, 259271, 32, 7, 259292, 32, 6, 259297, 32, 5, 259305, 32, 4, 259309, 32, 3, 259311, 32, 2, 259312, 32, 1, 129641, 31, 30, 129670, 31, 29, 194476, 31, 28, 194504, 31, 27, 226893, 31, 26, 226920, 31, 25, 243101, 31, 24, 243126, 31, 23, 251204, 31, 22, 251228, 31, 21, 255255, 31, 20, 255278, 31, 19, 257280, 31, 18, 257302, 31, 17, 258292, 31, 16, 258310, 31, 15, 258796, 31, 14, 258812, 31, 13, 259047, 31, 12, 259058, 31, 11, 259170, 31, 10, 259180, 31, 9, 259231, 31, 8, 259240, 31, 7, 259261, 31, 6, 259266, 31, 5, 259274, 31, 4, 259278, 31, 3, 259280, 31, 2, 259281, 31, 1, 64835, 30, 28, 64863, 30, 27, 97252, 30, 26, 97279, 30, 25, 113460, 30, 24, 113485, 30, 23, 121563, 30, 22, 121587, 30, 21, 125614, 30, 20, 125637, 30, 19, 127639, 30, 18, 127661, 30, 17, 128651, 30, 16, 128669, 30, 15, 129155, 30, 14, 129171, 30, 13, 129406, 30, 12, 129417, 30, 11, 129529, 30, 10, 129539, 30, 9, 129590, 30, 8, 129599, 30, 7, 129620, 30, 6, 129625, 30, 5, 129633, 30, 4, 129637, 30, 3, 129639, 30, 2, 129640, 30, 1, 64806, 29, 28, 64834, 29, 27, 97223, 29, 26, 97250, 29, 25, 113431, 29, 24, 113456, 29, 23, 121534, 29, 22, 121558, 29, 21, 125585, 29, 20, 125608, 29, 19, 127610, 29, 18, 127632, 29, 17, 128622, 29, 16, 128640, 29, 15, 129126, 29, 14, 129142, 29, 13, 129377, 29, 12, 129388, 29, 11, 129500, 29, 10, 129510, 29, 9, 129561, 29, 8, 129570, 29, 7, 129591, 29, 6, 129596, 29, 5, 129604, 29, 4, 129608, 29, 3, 129610, 29, 2, 129611, 29, 1, 32417, 28, 26, 32444, 28, 25, 48625, 28, 24, 48650, 28, 23, 56728, 28, 22, 56752, 28, 21, 60779, 28, 20, 60802, 28, 19, 62804, 28, 18, 62826, 28, 17, 63816, 28, 16, 63834, 28, 15, 64320, 28, 14, 64336, 28, 13, 64571, 28, 12, 64582, 28, 11, 64694, 28, 10, 64704, 28, 9, 64755, 28, 8, 64764, 28, 7, 64785, 28, 6, 64790, 28, 5, 64798, 28, 4, 64802, 28, 3, 64804, 28, 2, 64805, 28, 1, 32389, 27, 26, 32416, 27, 25, 48597, 27, 24, 48622, 27, 23, 56700, 27, 22, 56724, 27, 21, 60751, 27, 20, 60774, 27, 19, 62776, 27, 18, 62798, 27, 17, 63788, 27, 16, 63806, 27, 15, 64292, 27, 14, 64308, 27, 13, 64543, 27, 12, 64554, 27, 11, 64666, 27, 10, 64676, 27, 9, 64727, 27, 8, 64736, 27, 7, 64757, 27, 6, 64762, 27, 5, 64770, 27, 4, 64774, 27, 3, 64776, 27, 2, 64777, 27, 1, 16208, 26, 24, 16233, 26, 23, 24311, 26, 22, 24335, 26, 21, 28362, 26, 20, 28385, 26, 19, 30387, 26, 18, 30409, 26, 17, 31399, 26, 16, 31417, 26, 15, 31903, 26, 14, 31919, 26, 13, 32154, 26, 12, 32165, 26, 11, 32277, 26, 10, 32287, 26, 9, 32338, 26, 8, 32347, 26, 7, 32368, 26, 6, 32373, 26, 5, 32381, 26, 4, 32385, 26, 3, 32387, 26, 2, 32388, 26, 1, 16181, 25, 24, 16206, 25, 23, 24284, 25, 22, 24308, 25, 21, 28335, 25, 20, 28358, 25, 19, 30360, 25, 18, 30382, 25, 17, 31372, 25, 16, 31390, 25, 15, 31876, 25, 14, 31892, 25, 13, 32127, 25, 12, 32138, 25, 11, 32250, 25, 10, 32260, 25, 9, 32311, 25, 8, 32320, 25, 7, 32341, 25, 6, 32346, 25, 5, 32354, 25, 4, 32358, 25, 3, 32360, 25, 2, 32361, 25, 1, 8103, 24, 22, 8127, 24, 21, 12154, 24, 20, 12177, 24, 19, 14179, 24, 18, 14201, 24, 17, 15191, 24, 16, 15209, 24, 15, 15695, 24, 14, 15711, 24, 13, 15946, 24, 12, 15957, 24, 11, 16069, 24, 10, 16079, 24, 9, 16130, 24, 8, 16139, 24, 7, 16160, 24, 6, 16165, 24, 5, 16173, 24, 4, 16177, 24, 3, 16179, 24, 2, 16180, 24, 1, 8078, 23, 22, 8102, 23, 21, 12129, 23, 20, 12152, 23, 19, 14154, 23, 18, 14176, 23, 17, 15166, 23, 16, 15184, 23, 15, 15670, 23, 14, 15686, 23, 13, 15921, 23, 12, 15932, 23, 11, 16044, 23, 10, 16054, 23, 9, 16105, 23, 8, 16114, 23, 7, 16135, 23, 6, 16140, 23, 5, 16148, 23, 4, 16152, 23, 3, 16154, 23, 2, 16155, 23, 1, 4051, 22, 20, 4074, 22, 19, 6076, 22, 18, 6098, 22, 17, 7088, 22, 16, 7106, 22, 15, 7592, 22, 14, 7608, 22, 13, 7843, 22, 12, 7854, 22, 11, 7966, 22, 10, 7976, 22, 9, 8027, 22, 8, 8036, 22, 7, 8057, 22, 6, 8062, 22, 5, 8070, 22, 4, 8074, 22, 3, 8076, 22, 2, 8077, 22, 1, 4027, 21, 20, 4050, 21, 19, 6052, 21, 18, 6074, 21, 17, 7064, 21, 16, 7082, 21, 15, 7568, 21, 14, 7584, 21, 13, 7819, 21, 12, 7830, 21, 11, 7942, 21, 10, 7952, 21, 9, 8003, 21, 8, 8012, 21, 7, 8033, 21, 6, 8038, 21, 5, 8046, 21, 4, 8050, 21, 3, 8052, 21, 2, 8053, 21, 1, 2025, 20, 18, 2047, 20, 17, 3037, 20, 16, 3055, 20, 15, 3541, 20, 14, 3557, 20, 13, 3792, 20, 12, 3803, 20, 11, 3915, 20, 10, 3925, 20, 9, 3976, 20, 8, 3985, 20, 7, 4006, 20, 6, 4011, 20, 5, 4019, 20, 4, 4023, 20, 3, 4025, 20, 2, 4026, 20, 1, 2002, 19, 18, 2024, 19, 17, 3014, 19, 16, 3032, 19, 15, 3518, 19, 14, 3534, 19, 13, 3769, 19, 12, 3780, 19, 11, 3892, 19, 10, 3902, 19, 9, 3953, 19, 8, 3962, 19, 7, 3983, 19, 6, 3988, 19, 5, 3996, 19, 4, 4000, 19, 3, 4002, 19, 2, 4003, 19, 1, 1012, 18, 16, 1030, 18, 15, 1516, 18, 14, 1532, 18, 13, 1767, 18, 12, 1778, 18, 11, 1890, 18, 10, 1900, 18, 9, 1951, 18, 8, 1960, 18, 7, 1981, 18, 6, 1986, 18, 5, 1994, 18, 4, 1998, 18, 3, 2000, 18, 2, 2001, 18, 1, 990, 17, 16, 1008, 17, 15, 1494, 17, 14, 1510, 17, 13, 1745, 17, 12, 1756, 17, 11, 1868, 17, 10, 1878, 17, 9, 1929, 17, 8, 1938, 17, 7, 1959, 17, 6, 1964, 17, 5, 1972, 17, 4, 1976, 17, 3, 1978, 17, 2, 1979, 17, 1, 504, 16, 14, 520, 16, 13, 755, 16, 12, 766, 16, 11, 878, 16, 10, 888, 16, 9, 939, 16, 8, 948, 16, 7, 969, 16, 6, 974, 16, 5, 982, 16, 4, 986, 16, 3, 988, 16, 2, 989, 16, 1, 486, 15, 14, 502, 15, 13, 737, 15, 12, 748, 15, 11, 860, 15, 10, 870, 15, 9, 921, 15, 8, 930, 15, 7, 951, 15, 6, 956, 15, 5, 964, 15, 4, 968, 15, 3, 970, 15, 2, 971, 15, 1, 251, 14, 12, 262, 14, 11, 374, 14, 10, 384, 14, 9, 435, 14, 8, 444, 14, 7, 465, 14, 6, 470, 14, 5, 478, 14, 4, 482, 14, 3, 484, 14, 2, 485, 14, 1, 235, 13, 12, 246, 13, 11, 358, 13, 10, 368, 13, 9, 419, 13, 8, 428, 13, 7, 449, 13, 6, 454, 13, 5, 462, 13, 4, 466, 13, 3, 468, 13, 2, 469, 13, 1, 123, 12, 10, 133, 12, 9, 184, 12, 8, 193, 12, 7, 214, 12, 6, 219, 12, 5, 227, 12, 4, 231, 12, 3, 233, 12, 2, 234, 12, 1, 112, 11, 10, 122, 11, 9, 173, 11, 8, 182, 11, 7, 203, 11, 6, 208, 11, 5, 216, 11, 4, 220, 11, 3, 222, 11, 2, 223, 11, 1, 61, 10, 8, 70, 10, 7, 91, 10, 6, 96, 10, 5, 104, 10, 4, 108, 10, 3, 110, 10, 2, 111, 10, 1, 51, 9, 8, 60, 9, 7, 81, 9, 6, 86, 9, 5, 94, 9, 4, 98, 9, 3, 100, 9, 2, 101, 9, 1, 30, 8, 6, 35, 8, 5, 43, 8, 4, 47, 8, 3, 49, 8, 2, 50, 8, 1, 21, 7, 6, 26, 7, 5, 34, 7, 4, 38, 7, 3, 40, 7, 2, 41, 7, 1, 13, 6, 4, 17, 6, 3, 19, 6, 2, 20, 6, 1, 8, 5, 4, 12, 5, 3, 14, 5, 2, 15, 5, 1, 6, 4, 2, 7, 4, 1, 2, 3, 2, 3, 3, 1, 1, 2, 1};
    sort (tablica, &tablica[sizeof(tablica) / sizeof(roznice)]);
    int rozmiar = sizeof(tablica) / sizeof(roznice);
    scanf("%d", &ile);
    do
    {
        scanf ("%d", &pytanie);
        prawa = rozmiar;
        lewa = 0;
        if (pytanie <= tablica[prawa - 1].roznica)
        {
            while (lewa < prawa)
            {
                srodek = (prawa + lewa) / 2;
                if (pytanie > tablica[srodek].roznica)
                    lewa = srodek  + 1;
                else
                    prawa = srodek;
            }
            srodek = (lewa + prawa) / 2;
            if (tablica[srodek].roznica == pytanie)
                printf("%d %d\n", tablica[srodek].jeden, tablica[srodek].dwa);
            else
            {
                odp = (pytanie - srodek) * 2 + 2;
                printf ("%d %d\n", odp, odp - 1);
            }
        }
        else
        {
            odp = (pytanie - prawa) * 2 + 2;
            printf("%d %d\n", odp, odp - 1);
        }
    }
    while (--ile);
}
