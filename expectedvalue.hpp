float Game::ExpectedValue (float tempScore, int numDiceToRoll) {
    // Super ugly code to return the EV of some roll.
    // Way better version would just call the original code I used to make this table
    // But that is in Java... It's a TODO
    // Also might try to move this to a text file or separate cpp file
    // JSON would also be good
    float evArray[9950][6] = {
        {0,0,0,0,0,531.197},
        {0,0,0,0,362.779,0},
        {0,0,0,273.208,399.046,0},
        {0,0,225.93,306.525,0,0},
        {0,218.434,256.6,342.725,0,0},
        {268.783,250,292.415,0,0,0},
        {300,300,328.245,0,0,784.369},
        {350,350,0,0,595.7,828.331},
        {400,400,400,497.489,637.771,872.321},
        {450,450,450,539.465,679.848,916.326},
        {500,500,500,581.446,721.933,960.376},
        {550,550,550,623.433,764.024,1004.98},
        {600,600,600,665.427,806.209,1050.212},
        {650,650,650,707.427,849.586,1095.593},
        {700,700,700,749.429,893.537,1140.981},
        {750,750,750,791.433,937.49,1186.373},
        {800,800,800,833.44,981.444,1231.766},
        {850,850,850,875.447,1025.398,1277.505},
        {900,900,900,917.454,1069.353,1323.779},
        {950,950,950,959.462,1114.165,1370.27},
        {1000,1000,1000,1001.471,1160.027,1416.789},
        {1050,1050,1050,1050,1206.083,1463.448},
        {1100,1100,1100,1100,1252.14,1510.275},
        {1150,1150,1150,1150,1298.199,1557.104},
        {1200,1200,1200,1200,1344.26,1603.951},
        {1250,1250,1250,1250,1390.323,1650.805},
        {1300,1300,1300,1300,1436.388,1697.66},
        {1350,1350,1350,1350,1482.454,1744.523},
        {1400,1400,1400,1400,1528.522,1791.392},
        {1450,1450,1450,1450,1574.59,1838.262},
        {1500,1500,1500,1500,1620.659,1885.134},
        {1550,1550,1550,1550,1666.728,1932.009},
        {1600,1600,1600,1600,1712.8,1978.886},
        {1650,1650,1650,1650,1758.873,2025.765},
        {1700,1700,1700,1700,1804.947,2073.026},
        {1750,1750,1750,1750,1851.023,2120.424},
        {1800,1800,1800,1800,1897.101,2167.824},
        {1850,1850,1850,1850,1943.18,2215.243},
        {1900,1900,1900,1900,1989.262,2262.673},
        {1950,1950,1950,1950,2035.347,2310.105},
        {2000,2000,2000,2000,2081.434,2357.541},
        {2050,2050,2050,2050,2127.522,2404.984},
        {2100,2100,2100,2100,2173.61,2452.429},
        {2150,2150,2150,2150,2219.699,2499.875},
        {2200,2200,2200,2200,2265.789,2547.322},
        {2250,2250,2250,2250,2311.88,2594.771},
        {2300,2300,2300,2300,2357.972,2642.22},
        {2350,2350,2350,2350,2404.066,2690.104},
        {2400,2400,2400,2400,2450.16,2738.21},
        {2450,2450,2450,2450,2496.256,2786.328},
        {2500,2500,2500,2500,2542.353,2834.459},
        {2550,2550,2550,2550,2588.452,2882.601},
        {2600,2600,2600,2600,2634.553,2930.744},
        {2650,2650,2650,2650,2680.656,2978.888},
        {2700,2700,2700,2700,2726.76,3027.031},
        {2750,2750,2750,2750,2772.863,3075.175},
        {2800,2800,2800,2800,2818.967,3123.318},
        {2850,2850,2850,2850,2865.071,3171.462},
        {2900,2900,2900,2900,2911.175,3219.606},
        {2950,2950,2950,2950,2957.279,3267.789},
        {3000,3000,3000,3000,3003.383,3316.272},
        {3050,3050,3050,3050,3050,3365.017},
        {3100,3100,3100,3100,3100,3413.762},
        {3150,3150,3150,3150,3150,3462.507},
        {3200,3200,3200,3200,3200,3511.252},
        {3250,3250,3250,3250,3250,3559.996},
        {3300,3300,3300,3300,3300,3608.741},
        {3350,3350,3350,3350,3350,3657.486},
        {3400,3400,3400,3400,3400,3706.231},
        {3450,3450,3450,3450,3450,3754.976},
        {3500,3500,3500,3500,3500,3803.72},
        {3550,3550,3550,3550,3550,3852.465},
        {3600,3600,3600,3600,3600,3901.21},
        {3650,3650,3650,3650,3650,3949.955},
        {3700,3700,3700,3700,3700,3998.7},
        {3750,3750,3750,3750,3750,4047.444},
        {3800,3800,3800,3800,3800,4096.189},
        {3850,3850,3850,3850,3850,4144.934},
        {3900,3900,3900,3900,3900,4193.679},
        {3950,3950,3950,3950,3950,4242.424},
        {4000,4000,4000,4000,4000,4291.168},
        {4050,4050,4050,4050,4050,4339.913},
        {4100,4100,4100,4100,4100,4388.658},
        {4150,4150,4150,4150,4150,4437.403},
        {4200,4200,4200,4200,4200,4486.147},
        {4250,4250,4250,4250,4250,4534.892},
        {4300,4300,4300,4300,4300,4583.637},
        {4350,4350,4350,4350,4350,4632.382},
        {4400,4400,4400,4400,4400,4681.127},
        {4450,4450,4450,4450,4450,4729.871},
        {4500,4500,4500,4500,4500,4778.616},
        {4550,4550,4550,4550,4550,4827.361},
        {4600,4600,4600,4600,4600,4876.106},
        {4650,4650,4650,4650,4650,4924.851},
        {4700,4700,4700,4700,4700,4973.595},
        {4750,4750,4750,4750,4750,5022.34},
        {4800,4800,4800,4800,4800,5071.085},
        {4850,4850,4850,4850,4850,5119.829},
        {4900,4900,4900,4900,4900,5168.574},
        {4950,4950,4950,4950,4950,5217.319},
        {5000,5000,5000,5000,5000,5266.064},
        {5050,5050,5050,5050,5050,5314.808},
        {5100,5100,5100,5100,5100,5363.553},
        {5150,5150,5150,5150,5150,5412.298},
        {5200,5200,5200,5200,5200,5461.04},
        {5250,5250,5250,5250,5250,5509.785},
        {5300,5300,5300,5300,5300,5558.53},
        {5350,5350,5350,5350,5350,5607.274},
        {5400,5400,5400,5400,5400,5656.019},
        {5450,5450,5450,5450,5450,5704.764},
        {5500,5500,5500,5500,5500,5753.509},
        {5550,5550,5550,5550,5550,5802.253},
        {5600,5600,5600,5600,5600,5850.998},
        {5650,5650,5650,5650,5650,5899.743},
        {5700,5700,5700,5700,5700,5948.488},
        {5750,5750,5750,5750,5750,5997.232},
        {5800,5800,5800,5800,5800,6045.977},
        {5850,5850,5850,5850,5850,6094.722},
        {5900,5900,5900,5900,5900,6143.467},
        {5950,5950,5950,5950,5950,6192.211},
        {6000,6000,6000,6000,6000,6240.953},
        {6050,6050,6050,6050,6050,6289.697},
        {6100,6100,6100,6100,6100,6338.442},
        {6150,6150,6150,6150,6150,6387.187},
        {6200,6200,6200,6200,6200,6435.932},
        {6250,6250,6250,6250,6250,6484.676},
        {6300,6300,6300,6300,6300,6533.421},
        {6350,6350,6350,6350,6350,6582.166},
        {6400,6400,6400,6400,6400,6630.91},
        {6450,6450,6450,6450,6450,6679.653},
        {6500,6500,6500,6500,6500,6728.398},
        {6550,6550,6550,6550,6550,6777.143},
        {6600,6600,6600,6600,6600,6825.887},
        {6650,6650,6650,6650,6650,6874.632},
        {6700,6700,6700,6700,6700,6923.376},
        {6750,6750,6750,6750,6750,6972.121},
        {6800,6800,6800,6800,6800,7020.862},
        {6850,6850,6850,6850,6850,7069.607},
        {6900,6900,6900,6900,6900,7118.35},
        {6950,6950,6950,6950,6950,7167.077},
        {7000,7000,7000,7000,7000,7215.821},
        {7050,7050,7050,7050,7050,7264.565},
        {7100,7100,7100,7100,7100,7313.308},
        {7150,7150,7150,7150,7150,7362.052},
        {7200,7200,7200,7200,7200,7410.796},
        {7250,7250,7250,7250,7250,7459.54},
        {7300,7300,7300,7300,7300,7508.284},
        {7350,7350,7350,7350,7350,7557.028},
        {7400,7400,7400,7400,7400,7605.766},
        {7450,7450,7450,7450,7450,7654.51},
        {7500,7500,7500,7500,7500,7703.247},
        {7550,7550,7550,7550,7550,7751.991},
        {7600,7600,7600,7600,7600,7800.726},
        {7650,7650,7650,7650,7650,7849.466},
        {7700,7700,7700,7700,7700,7898.204},
        {7750,7750,7750,7750,7750,7946.947},
        {7800,7800,7800,7800,7800,7995.687},
        {7850,7850,7850,7850,7850,8044.43},
        {7900,7900,7900,7900,7900,8093.122},
        {7950,7950,7950,7950,7950,8141.865},
        {8000,8000,8000,8000,8000,8190.559},
        {8050,8050,8050,8050,8050,8239.299},
        {8100,8100,8100,8100,8100,8288.013},
        {8150,8150,8150,8150,8150,8336.728},
        {8200,8200,8200,8200,8200,8385.452},
        {8250,8250,8250,8250,8250,8434.193},
        {8300,8300,8300,8300,8300,8482.924},
        {8350,8350,8350,8350,8350,8531.662},
        {8400,8400,8400,8400,8400,8580.318},
        {8450,8450,8450,8450,8450,8629.055},
        {8500,8500,8500,8500,8500,8677.562},
        {8550,8550,8550,8550,8550,8726.296},
        {8600,8600,8600,8600,8600,8774.927},
        {8650,8650,8650,8650,8650,8823.579},
        {8700,8700,8700,8700,8700,8872.188},
        {8750,8750,8750,8750,8750,8920.916},
        {8800,8800,8800,8800,8800,8969.556},
        {8850,8850,8850,8850,8850,9018.294},
        {8900,8900,8900,8900,8900,9066.971},
        {8950,8950,8950,8950,8950,9115.705},
        {9000,9000,9000,9000,9000,9162.108},
        {9050,9050,9050,9050,9050,9210.77},
        {9100,9100,9100,9100,9100,9259.38},
        {9150,9150,9150,9150,9150,9307.991},
        {9200,9200,9200,9200,9200,9356.449},
        {9250,9250,9250,9250,9250,9405.149},
        {9300,9300,9300,9300,9300,9453.763},
        {9350,9350,9350,9350,9350,9502.364},
        {9400,9400,9400,9400,9400,9550.885},
        {9450,9450,9450,9450,9450,9599.423},
        {9500,9500,9500,9500,9500,9642.895},
        {9550,9550,9550,9550,9550,9691.567},
        {9600,9600,9600,9600,9600,9740.239},
        {9650,9650,9650,9650,9650,9789.082},
        {9700,9700,9700,9700,9700,9837.924},
        {9750,9750,9750,9750,9750,9886.767},
        {9800,9800,9800,9800,9800,9935.61},
        {9850,9850,9850,9850,9850,9984.452},
        {9900,9900,9900,9900,9900,10033.295},
        {9950,9950,9950,9950,9950,10082.137}
    };
    // Rounding to 25 to match the spacing on our precalculated table.
    int refScore = RoundUp(tempScore, 50) / 50;
    return evArray[refScore][numDiceToRoll - 1];
}
