/*
 * Copyright (c) 2012 Kyle Isom <kyle@tyrfingr.is>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
 * OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 * ---------------------------------------------------------------------
 */


#include <sys/types.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "base64.h"

void test_base64_enclen(void);
void test_base64_declen(void);
void test_base64_encode(void);


/*
 * Stubs required by the test suite, but for which no functionality is
 * required in this code. init_test is called each time a test is run,
 * and cleanup is run after every test.
 */
int init_test(void)
{
        return 0;
}

int cleanup_test(void)
{
        return 0;
}


/*
 * fireball is the code called when adding test fails: cleanup the test
 * registry and exit.
 */
void
fireball(void)
{
        CU_cleanup_registry();
        exit(CU_get_error());
}


/*
 * The main function sets up the test suite, registers the test cases,
 * runs through them, and hopefully doesn't explode.
 */
int
main(void)
{
        CU_pSuite       tsuite = NULL;
        unsigned int    fails;

        if (!(CUE_SUCCESS == CU_initialize_registry())) {
                errx(EX_CONFIG, "failed to initialise test registry");
                return EXIT_FAILURE;
        }

        tsuite = CU_add_suite("base64 test suite", init_test, cleanup_test);
        if (NULL == tsuite)
                fireball();

        if (NULL == CU_add_test(tsuite, "base64 encoding length",
                                test_base64_enclen))
                fireball();

        if (NULL == CU_add_test(tsuite, "base64 decoding length",
                                test_base64_declen))
                fireball();

        if (NULL == CU_add_test(tsuite, "base64 encode",
                                test_base64_encode))
                fireball();

        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
        fails = CU_get_number_of_tests_failed();
        warnx("%u tests failed", fails);

        CU_cleanup_registry();
        return fails;
}


void
test_base64_enclen()
{
        size_t  i = 0;
        size_t  test_vec[] = {
                0, 4, 4, 4, 8, 8, 8, 12, 12, 12, 16, 16, 16, 20, 20, 20, 24, 24, 24,
		28, 28, 28, 32, 32, 32, 36, 36, 36, 40, 40, 40, 44, 44, 44, 48, 48,
		48, 52, 52, 52, 56, 56, 56, 60, 60, 60, 64, 64, 64, 68, 68, 68, 72,
		72, 72, 76, 76, 76, 80, 80, 80, 84, 84, 84, 88, 88, 88, 92, 92, 92,
		96, 96, 96, 100, 100, 100, 104, 104, 104, 108, 108, 108, 112, 112,
		112, 116, 116, 116, 120, 120, 120, 124, 124, 124, 128, 128, 128, 132,
		132, 132, 136, 136, 136, 140, 140, 140, 144, 144, 144, 148, 148, 148,
		152, 152, 152, 156, 156, 156, 160, 160, 160, 164, 164, 164, 168, 168,
		168, 172, 172, 172, 176, 176, 176, 180, 180, 180, 184, 184, 184, 188,
		188, 188, 192, 192, 192, 196, 196, 196, 200, 200, 200, 204, 204, 204,
		208, 208, 208, 212, 212, 212, 216, 216, 216, 220, 220, 220, 224, 224,
		224, 228, 228, 228, 232, 232, 232, 236, 236, 236, 240, 240, 240, 244,
		244, 244, 248, 248, 248, 252, 252, 252, 256, 256, 256, 260, 260, 260,
		264, 264, 264, 268, 268, 268, 272, 272, 272, 276, 276, 276, 280, 280,
		280, 284, 284, 284, 288, 288, 288, 292, 292, 292, 296, 296, 296, 300,
		300, 300, 304, 304, 304, 308, 308, 308, 312, 312, 312, 316, 316, 316,
		320, 320, 320, 324, 324, 324, 328, 328, 328, 332, 332, 332, 336, 336,
		336, 340, 340, 340, 344, 344, 344, 348, 348, 348, 352, 352, 352, 356,
		356, 356, 360, 360, 360, 364, 364, 364, 368, 368, 368, 372, 372, 372,
		376, 376, 376, 380, 380, 380, 384, 384, 384, 388, 388, 388, 392, 392,
		392, 396, 396, 396, 400, 400, 400, 404, 404, 404, 408, 408, 408, 412,
		412, 412, 416, 416, 416, 420, 420, 420, 424, 424, 424, 428, 428, 428,
		432, 432, 432, 436, 436, 436, 440, 440, 440, 444, 444, 444, 448, 448,
		448, 452, 452, 452, 456, 456, 456, 460, 460, 460, 464, 464, 464, 468,
		468, 468, 472, 472, 472, 476, 476, 476, 480, 480, 480, 484, 484, 484,
		488, 488, 488, 492, 492, 492, 496, 496, 496, 500, 500, 500, 504, 504,
		504, 508, 508, 508, 512, 512, 512, 516, 516, 516, 520, 520, 520, 524,
		524, 524, 528, 528, 528, 532, 532, 532, 536, 536, 536, 540, 540, 540,
		544, 544, 544, 548, 548, 548, 552, 552, 552, 556, 556, 556, 560, 560,
		560, 564, 564, 564, 568, 568, 568, 572, 572, 572, 576, 576, 576, 580,
		580, 580, 584, 584, 584, 588, 588, 588, 592, 592, 592, 596, 596, 596,
		600, 600, 600, 604, 604, 604, 608, 608, 608, 612, 612, 612, 616, 616,
		616, 620, 620, 620, 624, 624, 624, 628, 628, 628, 632, 632, 632, 636,
		636, 636, 640, 640, 640, 644, 644, 644, 648, 648, 648, 652, 652, 652,
		656, 656, 656, 660, 660, 660, 664, 664, 664, 668, 668, 668, 672, 672,
		672, 676, 676, 676, 680, 680, 680, 684, 684, 684, 688, 688, 688, 692,
		692, 692, 696, 696, 696, 700, 700, 700, 704, 704, 704, 708, 708, 708,
		712, 712, 712, 716, 716, 716, 720, 720, 720, 724, 724, 724, 728, 728,
		728, 732, 732, 732, 736, 736, 736, 740, 740, 740, 744, 744, 744, 748,
		748, 748, 752, 752, 752, 756, 756, 756, 760, 760, 760, 764, 764, 764,
		768, 768, 768, 772, 772, 772, 776, 776, 776, 780, 780, 780, 784, 784,
		784, 788, 788, 788, 792, 792, 792, 796, 796, 796, 800, 800, 800, 804,
		804, 804, 808, 808, 808, 812, 812, 812, 816, 816, 816, 820, 820, 820,
		824, 824, 824, 828, 828, 828, 832, 832, 832, 836, 836, 836, 840, 840,
		840, 844, 844, 844, 848, 848, 848, 852, 852, 852, 856, 856, 856, 860,
		860, 860, 864, 864, 864, 868, 868, 868, 872, 872, 872, 876, 876, 876,
		880, 880, 880, 884, 884, 884, 888, 888, 888, 892, 892, 892, 896, 896,
		896, 900, 900, 900, 904, 904, 904, 908, 908, 908, 912, 912, 912, 916,
		916, 916, 920, 920, 920, 924, 924, 924, 928, 928, 928, 932, 932, 932,
		936, 936, 936, 940, 940, 940, 944, 944, 944, 948, 948, 948, 952, 952,
		952, 956, 956, 956, 960, 960, 960, 964, 964, 964, 968, 968, 968, 972,
		972, 972, 976, 976, 976, 980, 980, 980, 984, 984, 984, 988, 988, 988,
		992, 992, 992, 996, 996, 996, 1000, 1000, 1000, 1004, 1004, 1004,
		1008, 1008, 1008, 1012, 1012, 1012, 1016, 1016, 1016, 1020, 1020,
		1020, 1024, 1024, 1024, 1028, 1028, 1028, 1032, 1032, 1032, 1036,
		1036, 1036, 1040, 1040, 1040, 1044, 1044, 1044, 1048, 1048, 1048,
		1052, 1052, 1052, 1056, 1056, 1056, 1060, 1060, 1060, 1064, 1064,
		1064, 1068, 1068, 1068, 1072, 1072, 1072, 1076, 1076, 1076, 1080,
		1080, 1080, 1084, 1084, 1084, 1088, 1088, 1088, 1092, 1092, 1092,
		1096, 1096, 1096, 1100, 1100, 1100, 1104, 1104, 1104, 1108, 1108,
		1108, 1112, 1112, 1112, 1116, 1116, 1116, 1120, 1120, 1120, 1124,
		1124, 1124, 1128, 1128, 1128, 1132, 1132, 1132, 1136, 1136, 1136,
		1140, 1140, 1140, 1144, 1144, 1144, 1148, 1148, 1148, 1152, 1152,
		1152, 1156, 1156, 1156, 1160, 1160, 1160, 1164, 1164, 1164, 1168,
		1168, 1168, 1172, 1172, 1172, 1176, 1176, 1176, 1180, 1180, 1180,
		1184, 1184, 1184, 1188, 1188, 1188, 1192, 1192, 1192, 1196, 1196,
		1196, 1200, 1200, 1200, 1204, 1204, 1204, 1208, 1208, 1208, 1212,
		1212, 1212, 1216, 1216, 1216, 1220, 1220, 1220, 1224, 1224, 1224,
		1228, 1228, 1228, 1232, 1232, 1232, 1236, 1236, 1236, 1240, 1240,
		1240, 1244, 1244, 1244, 1248, 1248, 1248, 1252, 1252, 1252, 1256,
		1256, 1256, 1260, 1260, 1260, 1264, 1264, 1264, 1268, 1268, 1268,
		1272, 1272, 1272, 1276, 1276, 1276, 1280, 1280, 1280, 1284, 1284,
		1284, 1288, 1288, 1288, 1292, 1292, 1292, 1296, 1296, 1296, 1300,
		1300, 1300, 1304, 1304, 1304, 1308, 1308, 1308, 1312, 1312, 1312,
		1316, 1316, 1316, 1320, 1320, 1320, 1324, 1324, 1324, 1328, 1328,
		1328, 1332, 1332, 1332, 1336, 1336, 1336, 1340, 1340, 1340, 1344,
		1344, 1344, 1348, 1348, 1348, 1352, 1352, 1352, 1356, 1356, 1356,
		1360, 1360, 1360, 1364, 1364, 1364,
        };
        for (i = 0; i < 1024; i++)
                CU_ASSERT(base64_enclen(i) == test_vec[i]);
}


void
test_base64_declen()
{
        size_t  i = 0;
        size_t  test_vec[] = {
                0, 4, 4, 4, 8, 8, 8, 12, 12, 12, 16, 16, 16, 20, 20, 20, 24, 24, 24,
		28, 28, 28, 32, 32, 32, 36, 36, 36, 40, 40, 40, 44, 44, 44, 48, 48,
		48, 52, 52, 52, 56, 56, 56, 60, 60, 60, 64, 64, 64, 68, 68, 68, 72,
		72, 72, 76, 76, 76, 80, 80, 80, 84, 84, 84, 88, 88, 88, 92, 92, 92,
		96, 96, 96, 100, 100, 100, 104, 104, 104, 108, 108, 108, 112, 112,
		112, 116, 116, 116, 120, 120, 120, 124, 124, 124, 128, 128, 128, 132,
		132, 132, 136, 136, 136, 140, 140, 140, 144, 144, 144, 148, 148, 148,
		152, 152, 152, 156, 156, 156, 160, 160, 160, 164, 164, 164, 168, 168,
		168, 172, 172, 172, 176, 176, 176, 180, 180, 180, 184, 184, 184, 188,
		188, 188, 192, 192, 192, 196, 196, 196, 200, 200, 200, 204, 204, 204,
		208, 208, 208, 212, 212, 212, 216, 216, 216, 220, 220, 220, 224, 224,
		224, 228, 228, 228, 232, 232, 232, 236, 236, 236, 240, 240, 240, 244,
		244, 244, 248, 248, 248, 252, 252, 252, 256, 256, 256, 260, 260, 260,
		264, 264, 264, 268, 268, 268, 272, 272, 272, 276, 276, 276, 280, 280,
		280, 284, 284, 284, 288, 288, 288, 292, 292, 292, 296, 296, 296, 300,
		300, 300, 304, 304, 304, 308, 308, 308, 312, 312, 312, 316, 316, 316,
		320, 320, 320, 324, 324, 324, 328, 328, 328, 332, 332, 332, 336, 336,
		336, 340, 340, 340, 344, 344, 344, 348, 348, 348, 352, 352, 352, 356,
		356, 356, 360, 360, 360, 364, 364, 364, 368, 368, 368, 372, 372, 372,
		376, 376, 376, 380, 380, 380, 384, 384, 384, 388, 388, 388, 392, 392,
		392, 396, 396, 396, 400, 400, 400, 404, 404, 404, 408, 408, 408, 412,
		412, 412, 416, 416, 416, 420, 420, 420, 424, 424, 424, 428, 428, 428,
		432, 432, 432, 436, 436, 436, 440, 440, 440, 444, 444, 444, 448, 448,
		448, 452, 452, 452, 456, 456, 456, 460, 460, 460, 464, 464, 464, 468,
		468, 468, 472, 472, 472, 476, 476, 476, 480, 480, 480, 484, 484, 484,
		488, 488, 488, 492, 492, 492, 496, 496, 496, 500, 500, 500, 504, 504,
		504, 508, 508, 508, 512, 512, 512, 516, 516, 516, 520, 520, 520, 524,
		524, 524, 528, 528, 528, 532, 532, 532, 536, 536, 536, 540, 540, 540,
		544, 544, 544, 548, 548, 548, 552, 552, 552, 556, 556, 556, 560, 560,
		560, 564, 564, 564, 568, 568, 568, 572, 572, 572, 576, 576, 576, 580,
		580, 580, 584, 584, 584, 588, 588, 588, 592, 592, 592, 596, 596, 596,
		600, 600, 600, 604, 604, 604, 608, 608, 608, 612, 612, 612, 616, 616,
		616, 620, 620, 620, 624, 624, 624, 628, 628, 628, 632, 632, 632, 636,
		636, 636, 640, 640, 640, 644, 644, 644, 648, 648, 648, 652, 652, 652,
		656, 656, 656, 660, 660, 660, 664, 664, 664, 668, 668, 668, 672, 672,
		672, 676, 676, 676, 680, 680, 680, 684, 684, 684, 688, 688, 688, 692,
		692, 692, 696, 696, 696, 700, 700, 700, 704, 704, 704, 708, 708, 708,
		712, 712, 712, 716, 716, 716, 720, 720, 720, 724, 724, 724, 728, 728,
		728, 732, 732, 732, 736, 736, 736, 740, 740, 740, 744, 744, 744, 748,
		748, 748, 752, 752, 752, 756, 756, 756, 760, 760, 760, 764, 764, 764,
		768, 768, 768, 772, 772, 772, 776, 776, 776, 780, 780, 780, 784, 784,
		784, 788, 788, 788, 792, 792, 792, 796, 796, 796, 800, 800, 800, 804,
		804, 804, 808, 808, 808, 812, 812, 812, 816, 816, 816, 820, 820, 820,
		824, 824, 824, 828, 828, 828, 832, 832, 832, 836, 836, 836, 840, 840,
		840, 844, 844, 844, 848, 848, 848, 852, 852, 852, 856, 856, 856, 860,
		860, 860, 864, 864, 864, 868, 868, 868, 872, 872, 872, 876, 876, 876,
		880, 880, 880, 884, 884, 884, 888, 888, 888, 892, 892, 892, 896, 896,
		896, 900, 900, 900, 904, 904, 904, 908, 908, 908, 912, 912, 912, 916,
		916, 916, 920, 920, 920, 924, 924, 924, 928, 928, 928, 932, 932, 932,
		936, 936, 936, 940, 940, 940, 944, 944, 944, 948, 948, 948, 952, 952,
		952, 956, 956, 956, 960, 960, 960, 964, 964, 964, 968, 968, 968, 972,
		972, 972, 976, 976, 976, 980, 980, 980, 984, 984, 984, 988, 988, 988,
		992, 992, 992, 996, 996, 996, 1000, 1000, 1000, 1004, 1004, 1004,
		1008, 1008, 1008, 1012, 1012, 1012, 1016, 1016, 1016, 1020, 1020,
		1020, 1024, 1024, 1024, 1028, 1028, 1028, 1032, 1032, 1032, 1036,
		1036, 1036, 1040, 1040, 1040, 1044, 1044, 1044, 1048, 1048, 1048,
		1052, 1052, 1052, 1056, 1056, 1056, 1060, 1060, 1060, 1064, 1064,
		1064, 1068, 1068, 1068, 1072, 1072, 1072, 1076, 1076, 1076, 1080,
		1080, 1080, 1084, 1084, 1084, 1088, 1088, 1088, 1092, 1092, 1092,
		1096, 1096, 1096, 1100, 1100, 1100, 1104, 1104, 1104, 1108, 1108,
		1108, 1112, 1112, 1112, 1116, 1116, 1116, 1120, 1120, 1120, 1124,
		1124, 1124, 1128, 1128, 1128, 1132, 1132, 1132, 1136, 1136, 1136,
		1140, 1140, 1140, 1144, 1144, 1144, 1148, 1148, 1148, 1152, 1152,
		1152, 1156, 1156, 1156, 1160, 1160, 1160, 1164, 1164, 1164, 1168,
		1168, 1168, 1172, 1172, 1172, 1176, 1176, 1176, 1180, 1180, 1180,
		1184, 1184, 1184, 1188, 1188, 1188, 1192, 1192, 1192, 1196, 1196,
		1196, 1200, 1200, 1200, 1204, 1204, 1204, 1208, 1208, 1208, 1212,
		1212, 1212, 1216, 1216, 1216, 1220, 1220, 1220, 1224, 1224, 1224,
		1228, 1228, 1228, 1232, 1232, 1232, 1236, 1236, 1236, 1240, 1240,
		1240, 1244, 1244, 1244, 1248, 1248, 1248, 1252, 1252, 1252, 1256,
		1256, 1256, 1260, 1260, 1260, 1264, 1264, 1264, 1268, 1268, 1268,
		1272, 1272, 1272, 1276, 1276, 1276, 1280, 1280, 1280, 1284, 1284,
		1284, 1288, 1288, 1288, 1292, 1292, 1292, 1296, 1296, 1296, 1300,
		1300, 1300, 1304, 1304, 1304, 1308, 1308, 1308, 1312, 1312, 1312,
		1316, 1316, 1316, 1320, 1320, 1320, 1324, 1324, 1324, 1328, 1328,
		1328, 1332, 1332, 1332, 1336, 1336, 1336, 1340, 1340, 1340, 1344,
		1344, 1344, 1348, 1348, 1348, 1352, 1352, 1352, 1356, 1356, 1356,
		1360, 1360, 1360, 1364, 1364, 1364,
        };

        for (i = 0; i < 1024; i++) {
                CU_ASSERT(base64_declen(test_vec[i]) >= i);
                CU_ASSERT((base64_declen(test_vec[i]) - i) < 3);
        }
}


void
test_base64_encode()
{
        char     testvec[][45] = {
			"",
			"QQ==",
			"QUE=",
			"QUFB",
			"QUFBQQ==",
			"QUFBQUE=",
			"QUFBQUFB",
			"QUFBQUFBQQ==",
			"QUFBQUFBQUE=",
			"QUFBQUFBQUFB",
			"QUFBQUFBQUFBQQ==",
			"QUFBQUFBQUFBQUE=",
			"QUFBQUFBQUFBQUFB",
			"QUFBQUFBQUFBQUFBQQ==",
			"QUFBQUFBQUFBQUFBQUE=",
			"QUFBQUFBQUFBQUFBQUFB",
			"QUFBQUFBQUFBQUFBQUFBQQ==",
			"QUFBQUFBQUFBQUFBQUFBQUE=",
			"QUFBQUFBQUFBQUFBQUFBQUFB",
			"QUFBQUFBQUFBQUFBQUFBQUFBQQ==",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUE=",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUFB",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUFBQQ==",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUE=",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFB",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQQ==",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUE=",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFB",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQQ==",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUE=",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFB",
			"QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQQ==",
        };
        uint8_t  testbuf[33];
        char     base64_buf[45];
        size_t   i;

        for (i = 0; i < 32; i++) {
                memset(base64_buf, 0x0, 45);
                memset(testbuf, 0x0, 33);
                memset(testbuf, 0x41, i);
                CU_ASSERT(-1 != base64_encode(testbuf, i, base64_buf,
                                              base64_enclen(i) + 1));
                CU_ASSERT(strlen(testvec[i]) == strlen(base64_buf));
                CU_ASSERT(0 == strcmp(testvec[i], base64_buf));
        }
}